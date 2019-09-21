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

#define MAX_DIGITS          8
#define MAX_PRESET_NUMB     10

static uint8_t signs[MAX_PRESET_NUMB][MAX_DIGITS] = {
   {0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00}, /** Brick sign             */
   {0x00, 0x18, 0x3C, 0x5A, 0x18, 0x18, 0x18, 0x00}, /** Only Forward sign      */
   {0x00, 0x08, 0x04, 0x7E, 0x7E, 0x64, 0x68, 0x00}, /** Only Right sign        */
   {0x00, 0x10, 0x20, 0x7E, 0x7E, 0x26, 0x16, 0x00}, /** Only Left sign         */
   {0x20, 0x70, 0xA8, 0x20, 0x22, 0x3F, 0x22, 0x24}, /** Forward OR Right sign  */
   {0x04, 0x0E, 0x15, 0x04, 0x44, 0xFC, 0x44, 0x24}, /** Forward OR Left sign   */
   {0x00, 0x24, 0x24, 0x24, 0x81, 0x42, 0x3C, 0x00}, /** Happy Face             */
   {0x00, 0x24, 0x24, 0x24, 0x00, 0x3C, 0x42, 0x81}, /** Sad Face               */
   {0x24, 0x24, 0x24, 0x00, 0xFF, 0x05, 0x02, 0x00}, /** Tongue Face            */
   {0x7C, 0x62, 0x62, 0x62, 0x7C, 0x60, 0x60, 0x60}, /** Parking                */

};

typedef enum{
  brick_sign        = 0,
  only_forward      = 1,
  only_right        = 2,
  only_left         = 3,
  forward_or_right  = 4,
  forward_or_left   = 5,
  happy_face        = 6,
  sad_face          = 7,
  tongue_face       = 8,
  parking           = 9

}sign;

void led_show(sign figure)
{
  for(int i = 0; i < MAX_DIGITS; i++)
  {
    max7219WriteRegister(spiDriver, MAX7219_AD_DIGIT_0 + (i << 8), signs[figure][i]);
  }
}


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

void ledMatrixInit( void )
{
  if( isInizialized )
    return;

  palSetLineMode( SCK_LINE,  PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MISO_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);
  palSetLineMode( MOSI_LINE, PAL_MODE_ALTERNATE( 6 ) | PAL_STM32_OSPEED_HIGHEST);

  palSetLineMode( CS_LINE, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
  palSetLine( CS_LINE );

  spiStart( spiDriver, &spicfg );

  // LED-matrix Configuration for MAX7219
  max7219WriteRegister(spiDriver, MAX7219_AD_DISPLAY_TEST, FALSE);
  max7219WriteRegister(spiDriver, MAX7219_AD_SHUTDOWN, MAX7219_OM_Normal);
  max7219WriteRegister(spiDriver, MAX7219_AD_SCAN_LIMIT, MAX7219_SL_7);
  max7219WriteRegister(spiDriver, MAX7219_AD_DECODE_MODE, MAX7219_DM_No_decode);
  max7219WriteRegister(spiDriver, MAX7219_AD_INTENSITY, MAX7219_IM_31_32);

  isInizialized = true;
}

int main ( void )
{
  halInit( );
  chSysInit( );

  ledMatrixInit( );

  systime_t time = chVTGetSystemTimeX();

  while( 1 )
  {
    palToggleLine( LINE_LED1 );
    led_show(parking);

    time = chThdSleepUntilWindowed( time, time + MS2ST( 500 ) );
  }

  return 0;
}
