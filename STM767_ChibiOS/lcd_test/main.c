#include <ch.h>
#include <hal.h>

#include <chprintf.h>
#include <stdint.h>

#define SCL_LINE    PAL_LINE( GPIOB, 8 )
#define DATA_LINE   PAL_LINE( GPIOB, 9 )

static I2CDriver    *i2cDriver  = &I2CD1;

static const I2CConfig i2c1conf = {
         STM32_TIMINGR_PRESC(15U)  |
         STM32_TIMINGR_SCLDEL(9U) | STM32_TIMINGR_SDADEL(9U) |
         STM32_TIMINGR_SCLH(21U)   | STM32_TIMINGR_SCLL(24U),
         0,              // CR1
         0              // CR2
};

//extern I2C_HandleTypeDef hi2c1; // ????????????????????
uint8_t buf[1] = {0};
uint8_t port_lcd = 0;
char srtl[100];

void lcdWriteByte( uint8_t byte)
{

    buf[0] = byte;

    msg_t msg = i2cMasterTransmitTimeout( i2cDriver, (uint16_t)0x27, buf, 1, NULL, 0, 1000 );
    if( msg == MSG_OK )
    {
        palSetLine( LINE_LED3 );
    }

}

#define e_set()     lcdWriteByte( port_lcd |= 0x04 )  // set E in 1
#define e_reset()   lcdWriteByte( port_lcd &= ~0x04 ) // set E in 0
#define rs_set()    lcdWriteByte( port_lcd |= 0x01 )  // set RS in 1
#define rs_reset()  lcdWriteByte( port_lcd &= ~0x01 ) // set RS in 0
#define set_led()   lcdWriteByte( port_lcd |= 0x08 )  // turn on backlight
#define set_write() lcdWriteByte( port_lcd &= ~0x02 ) // writing into lcd-memory

void lcdSendHalfByte( uint8_t byte )
{
    byte <<= 4;
//    lcdWriteByte( port_lcd |= byte );
    e_set();
    chThdSleepMicroseconds( 50 );
    lcdWriteByte( port_lcd|byte );
    e_reset();
    chThdSleepMicroseconds( 50 );
//    lcdWriteByte( port_lcd &= 15 );
}


void lcdSendByte( uint8_t byte, uint8_t mode )
{
    if( mode == 0 ) rs_reset();
    else rs_set();

    uint8_t hc = 0;
    hc = byte >> 4;
    lcdSendHalfByte( hc );
    lcdSendHalfByte( byte );
}


void lcdClear(void)
{
    lcdSendByte( 0x01, 0 );
    chThdSleepMicroseconds( 1500 );
}


void lcdSendChar(char ch)
{
//    char ch = 'a';
    lcdSendByte( ch, 1 );
}


void lcdString( char* str )
{
    uint8_t i = 0;
    while( str[i] != 0 )
    {
        lcdSendByte( str[i], 1 );
        i++;
    }
}


void lcdSetPos( uint8_t x, uint8_t y )
{
//    switch(y)
//    {
//        case 0:
//            lcdSendByte( x | 0x80, 0 );
//            chThdSleepMilliseconds( 1 );
//            break;
//        case 1:
//            lcdSendByte( (0x40 + x) | 0x80, 0 );
//            chThdSleepMilliseconds( 1 );
//            break;
//        case 2:
//            lcdSendByte( (0x14 + x) | 0x80, 0 );
//            chThdSleepMilliseconds( 1 );
//            break;
//        case 3:
//            lcdSendByte( (0x54 + x) | 0x80, 0 );
//            chThdSleepMilliseconds( 1 );
//            break;
//    }
//  if (file_i2c < 0 || x < 0 || x > 15 || y < 0 || y > 1)
//        return 1;
//    uint8_t cCmd;
    uint8_t cCmd = (y==0) ? 0x80 : 0xc0;
    cCmd |= x;
    lcdSendByte( cCmd, 0);

}


void lcdInit( void )
{
    chThdSleepMilliseconds( 20 );
    lcdSendHalfByte( 0x03 );
    chThdSleepMilliseconds( 4 );
    lcdSendHalfByte( 0x03 );
    chThdSleepMicroseconds( 100 );
    lcdSendHalfByte( 0x03 );
    chThdSleepMilliseconds( 1 );
    lcdSendHalfByte( 0x02 );
    chThdSleepMilliseconds( 1 );

    lcdSendByte( 0x28, 0 ); // 4 bit mode (DL = 0), 2 lines (N = 1)
    chThdSleepMilliseconds( 1 );
    lcdSendByte( 0x0C, 0 ); // show image on lcd (D = 1)
    chThdSleepMilliseconds( 1 );
    lcdSendByte( 0x01, 0 ); //  clean the screen
    chThdSleepMilliseconds(2);
    lcdSendByte(0x06, 0); // cursor will move to the right
    chThdSleepMilliseconds(1);
    lcdSendByte(0x80, 0);   // !!!!!!!!!!!
    chThdSleepMilliseconds(1);
//    lcdSendByte(0x0E, 0);   // !!!!!!!!!!!
//    chThdSleepMilliseconds(1);
    set_led();  // turn on highlight
    set_write();
//    lcdSetPos( 3, 0 );

}

//void lcd_command( uint8_t byte )
//{
//
//}


int main(void)
{
    chSysInit();
    halInit();

    palSetLineMode( SCL_LINE,  PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN ); //PAL_MODE_OUTPUT_OPENDRAIN );
    palSetLineMode( DATA_LINE, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN ); //PAL_MODE_OUTPUT_OPENDRAIN );

    i2cStart(i2cDriver, &i2c1conf);

    lcdInit( );

    while (true)
    {



        lcdSetPos( 0 , 0 );
//        lcdSendChar( 'a' );
//
        lcdString("Let me die");
//        chThdSleepMilliseconds( 1000 );
//        e_reset();
        chThdSleepMilliseconds( 1000 );
    }
}
