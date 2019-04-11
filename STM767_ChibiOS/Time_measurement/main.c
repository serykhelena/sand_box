#include <ch.h>
#include <hal.h>

#include <chprintf.h>


/*** Serial configuration ***/

static const SerialConfig sdcfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};


/***        Defines Zone      ***/
/*
 * Each define will unlock code for different tools:
 * Time Measurement Unit or Measurement with GPT, correspondingly
 * TM Unit works slower, because it's able to get statistics
 *  - TM Unit is recommended for diagnostic and debugging
 *  - Using GPT for time measurement is recommended in real control system
 */

//#define TM_USE

#define GPT_USE

/*********************************/

#ifdef TM_USE

#define SYSTEM_FREQUENCY   216000000UL
static time_measurement_t  processing_time;

#else


static void gpt_cb ( GPTDriver *Tim5 );
static GPTDriver            *GPT_Timer5 = &GPTD5;

int32_t startPoint                  = 0;
int32_t stopPoint             = 0;
int32_t gpt_ticks                       = 0;
int32_t total_time                        = 0;

static const GPTConfig gpt5cfg = {
  .frequency =  200000,
  .callback  =  gpt_cb,
  .cr2       =  0,
  .dier      =  0U
};

static void gpt_cb (GPTDriver *gptd)
{
    gptd = gptd;
    gpt_ticks += gpt5cfg.frequency/20;
}

#define SYSTEM_FREQUENCY   gpt5cfg.frequency

#define period_50ms        gpt5cfg.frequency/20

#endif


int main(void)
{
    chSysInit();
    halInit();

    sdStart( &SD7, &sdcfg );
    palSetPadMode( GPIOE, 8, PAL_MODE_ALTERNATE(8) );   // TX
    palSetPadMode( GPIOE, 7, PAL_MODE_ALTERNATE(8) );   // RX

#ifdef TM_USE
    _tm_init( );

    chTMObjectInit( &processing_time );
#endif

#ifdef GPT_USE
    gptStart(GPT_Timer5, &gpt5cfg);



#endif

    while ( true )
    {
#ifdef TM_USE

        chTMStartMeasurementX( &processing_time );
        double var;
        for( uint32_t g = 0; g < 4000000; g++)
        {
            var = chVTGetSystemTimeX();
            var = var * var;
            var = var - 5.2;
        }
        chTMStopMeasurementX( &processing_time );

        chprintf( (BaseSequentialStream *)&SD7, "%d / Best time:(%d)\tWorst time:(%d)\n\r",
                          (int)var,
                          RTC2US( SYSTEM_FREQUENCY, processing_time.best ),
                          RTC2US( SYSTEM_FREQUENCY, processing_time.worst ) );
#else
        gpt_ticks = 0;
        gptStartContinuous(GPT_Timer5, period_50ms);

        float var;
        for( uint32_t g = 0; g < 40000000; g++)
        {
          var = chVTGetSystemTimeX();
          var = var * var / var;
          var = var - 5.2;
        }

        stopPoint = gptGetCounterX(GPT_Timer5);

        total_time = gpt_ticks + stopPoint;


        chprintf( (BaseSequentialStream *)&SD7, "Time:(%d / %d) - %d\n\r",
                  (int)RTC2US( SYSTEM_FREQUENCY * 1.0, total_time ), total_time, (int)var );
#endif


        chThdSleepMilliseconds(100);
    }
}
