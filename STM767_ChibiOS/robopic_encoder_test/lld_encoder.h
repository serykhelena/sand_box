#ifndef LLD_ENCODER_H_
#define LLD_ENCODER_H_

#include <ch.h>
#include <hal.h>

#include <stdint.h>
#include <stdlib.h>
//#include <math.h>
#include <stdbool.h>

typedef int32_t    rawEncoderValue_t;
typedef float      rawRevEncoderValue_t;

/**
 * @brief   Initialize periphery connected to encoder
 * @note    Stable for repeated calls
 */
void lldEncoderInit( void );

/**
 * @brief   Get number of encoder ticks
 * @note    Max number of ticks is defined by MAX_TICK_NUM
 * @return  Encoder ticks number depends on direction of rotation
 *          [0; ENC_MAX_TICK_NUM]
 *          after ENC_MAX_TICK_NUM it resets
 */
rawEncoderValue_t lldGetEncoderRawTicks( void );

/**
 * @brief   Get direction of encoder rotation
 * @return  clockwise           -> 0
 *          counterclockwise    -> 1
 */
bool lldGetEncoderDirection( void );

/**
 * @brief   Get number of encoder revolutions [double]
 * @note    1 revolution = MAX_TICK_NUM ticks
 * @return  Encoder revolutions number depends on direction of rotation
 */
rawRevEncoderValue_t   lldGetEncoderRawRevs( void );

/*
 * @brief   Reset all variable for lld-encoder unit
 */
void lldResetEncoder( void );

#endif /* LLD_ENCODER_H_ */
