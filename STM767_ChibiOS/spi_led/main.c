#include <ch.h>
#include <hal.h>

#include <chprintf.h>

#define SPI_PORT    GPIOC
#define SCK_LINE    PAL_LINE( GPIOC, 10 )
#define MISO_LINE   PAL_LINE( GPIOC, 11 )
#define MOSI_LINE   PAL_LINE( GPIOC, 12 )
#define CS_LINE
#define CS1_LINE

static SPIDriver    *spiDriver  = &SPID3;


/*
 * Maximum speed SPI configuration (27MHz, CPHA=0, CPOL=0, MSb first).
 */
static const SPIConfig hs_spicfg = {
  .end_cb   = NULL,
  .ssport   = SPI_PORT,
  .sspad    = GPIOB_ARD_D15, // ????????????????
  .cr1      = SPI_CR1_BR_0,
  .cr2      = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
};

bool isInizialized = false;

void ledMatrixInit( )
{
  if( isInizialized )
    return;

  palSetLineMode( SCK_LINE,  PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MISO_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MOSI_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);


  spiStart( spiDriver, &hs_spicfg );

  isInizialized = true;
}


int main ( void )
{
  halInit( );
  chSysInit( );


  systime_t time = chVTGetSystemTimeX();

  while( 1 )
  {


    time = chThdSleepUntilWindowed( time, time + MS2ST( 400 ) );
  }




  return 0;
}
