#include <ch.h>
#include <hal.h>

#include <chprintf.h>

#include "max7219.h"


#define SCK_LINE    PAL_LINE( GPIOC, 10 )
#define MISO_LINE   PAL_LINE( GPIOC, 11 )

#define MOSI_LINE   PAL_LINE( GPIOC, 12 )
#define CS_PORT     GPIOC
#define CS_PIN      9
#define CS_LINE     PAL_LINE( CS_PORT, CS_PIN )

static SPIDriver    *spiDriver  = &SPID3;


#define MAX_DIGITS  8

static uint8_t signs[1][MAX_DIGITS] = {
   {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00}
};



/*
 * Maximum speed SPI configuration (27MHz, CPHA=0, CPOL=0, MSb first).
 */
static const SPIConfig spicfg = {
  .end_cb   = NULL,
  .ssport   = CS_PORT,
  .sspad    = CS_PIN,
  .cr1      = SPI_CR1_BR | SPI_CR1_BR_0,    // /64
  .cr2      = SPI_CR2_DS                    // 16-bit size mode
};

bool isInizialized = false;

void ledMatrixInit( )
{
  if( isInizialized )
    return;

  palSetLineMode( SCK_LINE,  PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MISO_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MOSI_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);

  palSetLineMode( CS_LINE, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
  palSetLine( CS_LINE );

  spiStart( spiDriver, &spicfg );

  isInizialized = true;
}

int main ( void )
{
  halInit( );
  chSysInit( );

  ledMatrixInit( );


  max7219WriteRegister(spiDriver, MAX7219_AD_DISPLAY_TEST, FALSE);
  static uint16_t txbuf[3] = {0x01, 0x00, 0x00};
  systime_t time = chVTGetSystemTimeX();
  int i = 0;
  while( 1 )
  {
    palToggleLine( LINE_LED1 );
//    max7219WriteRegister(spiDriver, MAX7219_AD_DISPLAY_TEST, TRUE);
    max7219WriteRegister(spiDriver, 0x1100, 0xFF);

//    max7219WriteRegister(spiDriver, MAX7219_AD_SHUTDOWN, 0);

//    max7219WriteRegister(spiDriver, MAX7219_AD_SCAN_LIMIT, MAX7219_SL_7);

//    max7219WriteRegister(spiDriver, MAX7219_AD_DECODE_MODE, MAX7219_DM_No_decode);

//    max7219WriteRegister(spiDriver, MAX7219_AD_INTENSITY, MAX7219_IM_31_32);

//    max7219WriteRegister(spiDriver, MAX7219_DI_0, 0x00);
//    max7219WriteRegister(spiDriver, MAX7219_DI_1, 1);
//      max7219WriteRegister(spiDriver, MAX7219_DI, 0x0F);



    time = chThdSleepUntilWindowed( time, time + MS2ST( 500 ) );
  }




  return 0;
}
