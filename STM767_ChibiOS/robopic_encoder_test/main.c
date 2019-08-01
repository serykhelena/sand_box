#include <ch.h>
#include <hal.h>

#include <chprintf.h>
#include <lld_encoder.h>


/*** Serial configuration ***/

static const SerialConfig sdcfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};


int main(void)
{
    chSysInit();
    halInit();

    sdStart( &SD7, &sdcfg );
    palSetPadMode( GPIOE, 8, PAL_MODE_ALTERNATE(8) );   // TX
    palSetPadMode( GPIOE, 7, PAL_MODE_ALTERNATE(8) );   // RX

    lldEncoderInit( );

    rawEncoderValue_t       enc_test_ticks       = 0;
    rawRevEncoderValue_t    enc_test_revs        = 0;
    uint8_t                 enc_test_dir         = 0;

    systime_t time = chVTGetSystemTimeX();
    chprintf( (BaseSequentialStream *)&SD7, "TEST\n\r");
    while ( true )
    {
        palToggleLine( LINE_LED1 );
        enc_test_ticks      = lldGetEncoderRawTicks( );
        enc_test_revs       = lldGetEncoderRawRevs( );
        enc_test_dir        = lldGetEncoderDirection( );

        chprintf( (BaseSequentialStream *)&SD7, "Ticks:(%d)\tRevs:(%d)\tDir:(%d)\n\r",
                                               enc_test_ticks, (int)enc_test_revs,
                                               (int)enc_test_dir);

        time = chThdSleepUntilWindowed( time, time + MS2ST( 400 ) );
    }
}
