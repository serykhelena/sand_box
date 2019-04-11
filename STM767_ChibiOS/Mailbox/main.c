#include <ch.h>
#include <hal.h>

#include <chprintf.h>

#include <string.h>     // memcpy


/*===========================================================================*/
/* PWM (Timer 3) for ADC trigger                                             */
/*===========================================================================*/

PWMConfig pwm3conf = {
    .frequency = 1000000,   // frequency of timer ticks
    .period    = 1000,      /* 1 ms => 1 kHz
                             * PWM period = period/frequency [s] */
    .callback  = NULL,      // in the end of each PWM period (callback)
    .channels  = {
                  {.mode = PWM_OUTPUT_DISABLED,     .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,     .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,     .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH,  .callback = NULL}    // PB_1
                  },
    .cr2        = 0,
    .dier       = 0
};

/*===========================================================================*/
/* ADC driver related.                                                       */
/*===========================================================================*/
#ifdef NOT_USED
#define MAILBOX_SIZE 50
//static mailbox_t adc_send;          // name of mailbox for getting steering pulses
static msg_t buffer_adc_send[MAILBOX_SIZE]; // size for steer_mb
MAILBOX_DECL(adc_send, buffer_adc_send, MAILBOX_SIZE);

#endif

static thread_reference_t trp_adc_com = NULL;

#define ADC1_NUM_CHANNELS   2       // because only 2 sensors for now
#define ADC1_BUF_DEPTH      20

static adcsample_t samples1[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];
static adcsample_t sample_work[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];

/*
 * ADC streaming callback.
 */

// when ADC conversion ends, this func will be called
/* if the depth is equal to 1, another way it will be called twice per conversion!
   conversion is sampling of all your channel N times (N is buffer depth) */

static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
  adcp = adcp; n = n;

  // Full buffer
  if ( buffer != samples1 )
  {
    chSysLockFromISR();                   // ISR Critical Area
    chThdResumeI( &trp_adc_com, MSG_OK );
    chSysUnlockFromISR();                 // Close ISR Critical Area
  }
}

/*
 * ADC errors callback, should never happen.
 */

//static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) { adcp = adcp; err = err; }

static const ADCConversionGroup adc1conf = {
  // Half filled buffer callback not called in linear mode
  .circular     = true,                     // working mode = looped
  /* Buffer will continue writing to the beginning when it come to the end */
  .num_channels = ADC1_NUM_CHANNELS,        // number of channels
  .end_cb       = adccallback,              // after ADC conversion ends - call this func
  /* Don`t forget about depth of buffer */
  .error_cb     = NULL,                     // in case of errors, this func will be called
/*
 * Bits 25:24 RES[1:0]: Resolution
 * These bits are written by software to select the resolution of the conversion.
 * 00: 12-bit (minimum 15 ADCCLK cycles)
 * 01: 10-bit (minimum 13 ADCCLK cycles)
 * 10: 8-bit (minimum 11 ADCCLK cycles)
 * 11: 6-bit (minimum 9 ADCCLK cycles)
 * ChibiOS/HAL: ADC_CR1_RES_*
 */
#define ADC_CR1_12B_RESOLUTION      0
#define ADC_CR1_10B_RESOLUTION      ADC_CR1_RES_0
#define ADC_CR1_8B_RESOLUTION       ADC_CR1_RES_1
#define ADC_CR1_6B_RESOLUTION       ADC_CR1_RES_0 | ADC_CR1_RES_1

  .cr1          = ADC_CR1_12B_RESOLUTION,                       // just because it has to be 0
  /* Cause we don`t need to write something to the register */
  .cr2          = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(6), // Commutated from PWM Timer 3
  /* 6 means 0b0110, and from RM (p.449) it is GPT3 => PWM */
  /* ADC_CR2_EXTEN_RISING - means to react on the rising signal (front) */
#ifdef ADC_REPLACE_2ND_CHANNEL_VREFINT
  .smpr1        = ADC_SMPR1_SMP_VREF(ADC_SAMPLE_480),
#else
  .smpr1        = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_480),
#endif
  .smpr2        = ADC_SMPR2_SMP_AN3(ADC_SAMPLE_480),
  .sqr1         = 0,   //
  /* Usually this field is set to 0 as config already know the number of channels (.num_channels) */
  .sqr2         = 0,
  .sqr3         = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN3) |             // sequence of channels
#ifdef ADC_REPLACE_2ND_CHANNEL_VREFINT
                  ADC_SQR3_SQ2_N(ADC_CHANNEL_VREFINT)
#else
                  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN10)
#endif
  /* If we can macro ADC_SQR2_SQ... we need to write to .sqr2 */
};


static THD_WORKING_AREA(waRangefindersProcessor, 128);
static THD_FUNCTION(RangefindersProcessor, arg)
{
  arg = arg;

  msg_t     msg         = 0;

#ifdef ADC_MATLAB_DEBUG
  bool      start_com   = false;
  int16_t   input       = 0;
#endif

  while (true)
  {
    chSysLock();
    // Renamed as we don`t need to have thread work if no ADC processed
    msg = chThdSuspendS(&trp_adc_com);
    chSysUnlock();

#ifdef ADC_MATLAB_DEBUG                 // Defined in <protos.h>
    // After ADC data converted, check input SD buffer
    input = sdGetTimeout(&SD7, TIME_IMMEDIATE);
    if ( input == 1 )
    {
      palSetLine( ADC_MATLAB_DEBUG_LED );
      start_com = true;
    }
    else if ( input == 2 )
    {
      palClearLine( ADC_MATLAB_DEBUG_LED );
      start_com = false;
    }
#endif /* ADC_MATLAB_DEBUG */

    // MSG_OK in msg means that conversion ended
    // Now no timeout possible - it sleeps until ADC ends
    if ( msg == MSG_OK )
    {
      /* Calc ADC data */
      // Copy data for not being rewrited by future data
      memcpy( sample_work, samples1, sizeof( sample_work ) );

      static uint16_t adc_filtred_val[ADC1_NUM_CHANNELS];
      static uint32_t adc_sum_vals[ADC1_NUM_CHANNELS];
      memset( adc_sum_vals, 0, sizeof( adc_sum_vals ) );

      static const float window = 1.0 / ADC1_BUF_DEPTH;                  // how many values we want to average

      for ( int i = 0; i < ADC1_BUF_DEPTH; i++ )
      {
        for ( int ch = 0; ch < ADC1_NUM_CHANNELS; ch++ )
        {
          adc_sum_vals[ch] += sample_work[i * ADC1_NUM_CHANNELS + ch];
        }
      }

      for ( int ch = 0; ch < ADC1_NUM_CHANNELS; ch++ )
      {
        adc_filtred_val[ch] = adc_sum_vals[ch] * window;
      }

      /* Send ADC data */
#ifdef ROS_ENABLED                      // Defined in <protos.h>
      ros_driver_send_rangefinders( adc_filtred_val, sizeof( adc_filtred_val ) / sizeof( adc_filtred_val[0] ) );
#endif /* ROS_ENABLED */

#ifdef ADC_MATLAB_DEBUG                 // Defined in <protos.h>
      if ( start_com )
      {
#if ADC_DEBUG_SEND_DATA == ADC_DEBUG_SEND_DATA_FILTERED
#ifdef FILTER_FOR_2_SENSORS
        sdWrite(&SD7, (uint8_t *)adc_filtred_val, sizeof(adc_filtred_val));
#endif /* FILTER_FOR_2_SENSORS */

#elif ADC_DEBUG_SEND_DATA == ADC_DEBUG_SEND_DATA_FULL
#ifndef ADC_MATLAB_DEBUG_LINE_SEND
        // Second arg type cast just for Warning =)
        sdWrite(&SD7, (uint8_t *)sample_work, sizeof(samples1[0]) * ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH);
#else /* ADC_MATLAB_DEBUG_LINE_SEND */
        // Example for processing line-by-line of buffer
        for ( int i = 0; i < ADC1_BUF_DEPTH; i++ )
        {
          sdWrite(&SD7, (uint8_t *)&sample_work[i*ADC1_NUM_CHANNELS], sizeof(samples1[0]) * ADC1_NUM_CHANNELS);
        }
#endif /* ADC_MATLAB_DEBUG_LINE_SEND */

#endif /* ADC_DEBUG_SEND_DATA */
      }
#endif /* ADC_MATLAB_DEBUG */
    }
  }
}

void main ( void )
{
    /*
    * Fixed an errata on the STM32F7xx, the DAC clock is required for ADC
    * triggering.
    */
    rccEnableDAC1(false);
    /* This enables DAC clock that is required for ADC triggering,
    * it`s errata feature (not bug but not so pleased thing) =)
    */

    // PWM init for ADC trigger
    PWMDriver *pwmTriggerADC        = &PWMD3;            // Use Timer 3 for ADC
    palSetPadMode( GPIOB, 1, PAL_MODE_ALTERNATE(2) );    // PB_1
    pwmStart( pwmTriggerADC, &pwm3conf );                // Start PWM

    // ADC driver
    adcStart(&ADCD1, NULL);
#ifdef ADC_REPLACE_2ND_CHANNEL_VREFINT
    adcSTM32EnableTSVREFE();
#endif
    palSetLineMode( LINE_ADC123_IN10, PAL_MODE_INPUT_ANALOG );  // PC0
    palSetLineMode( LINE_ADC123_IN3, PAL_MODE_INPUT_ANALOG );   // PA3
    adcStartConversion(&ADCD1, &adc1conf, samples1, ADC1_BUF_DEPTH);
    pwmEnableChannel( pwmTriggerADC, 3, pwm3conf.period/2 ); // ADC get values when PWM is triggering

    // Thread for ADC data send
    chThdCreateStatic( waRangefindersProcessor, sizeof(waRangefindersProcessor), NORMALPRIO, RangefindersProcessor, NULL );
}
