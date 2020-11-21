#include "tests.h"
#include "remote_control.h"
#include "drive_cs.h"

#include <lld_odometry.h>
#include <lld_steer_angle_fb.h>


void testFrictionRoutine( void )
{
    remoteControlInit( NORMALPRIO );
	driverCSInit( NORMALPRIO );
	lldOdometryInit( );

    debug_stream_init();

    bool                    mode            = false;
    icuControlValue_t       rc_steer_prt    = 0;
    icuControlValue_t       rc_speed_prt    = 0;

    steerAngleDegValue_t    steer_pos       = 0;
    float                   speed_mps       = 2.0;
    float                   real_speed_lpf  = 0;

    uint8_t                 matlab_flag = 0;

    uint16_t                auto_move_mode = 0;

    uint16_t                init_iter = 100 * 2;

    uint8_t                 iter_number = 0;

    odometryValue_t         test_x_pos      = 0;
    odometryValue_t         test_y_pos      = 0;

//    dbgprintf("Start friction test!\n\r");

    uint16_t dbg_counter = 0;
    systime_t time = chVTGetSystemTimeX();
    while(1)
    {
        dbg_counter     += 1;

        char rc_data = sdGetTimeout( &SD3, TIME_IMMEDIATE );

        real_speed_lpf = lldOdometryGetLPFObjSpeedMPS( );

        test_x_pos      = lldGetOdometryObjX( OBJ_DIST_CM );
        test_y_pos      = lldGetOdometryObjY( OBJ_DIST_CM );

        if( rc_data == 'p' )
        {
            matlab_flag = 1;
        }

        if( matlab_flag )
        {
//              sdWrite(&SD3, (uint8_t*) &real_speed_lpf, 4);
            sdWrite(&SD3, (uint8_t*) &test_x_pos, 4);
            sdWrite(&SD3, (uint8_t*) &test_y_pos, 4);
        }



    	mode = rcModeIsEnabled();
    	if( mode == true )
        {
    	    driverIsEnableCS(false);
    	    auto_move_mode = 0;

    	    rc_steer_prt    = rcGetSteerControlValue( );
            rc_speed_prt    = rcGetSpeedControlValue( );

            lldControlSetDrMotorPower( rc_speed_prt );
            lldControlSetSteerMotorPower( rc_steer_prt );
        }
        else
        {
            driverIsEnableCS(true);



            if( matlab_flag == 1 && iter_number < 3 )
            {

                auto_move_mode  += 1;

                // keep steering wheels in the center
                driveSteerCSSetPosition( steer_pos );

                if( auto_move_mode < init_iter )
                {
                    driveSpeedCSSetSpeed( speed_mps );
                }
                if( auto_move_mode >= init_iter && auto_move_mode < init_iter + 20 )
                {
                    driveSpeedCSSetSpeed( -speed_mps  );

                }
                if( auto_move_mode >= init_iter + 20 && auto_move_mode <= init_iter + 70 )
                {
                    driveSpeedCSSetSpeed( 0.3 );
                    auto_move_mode = 0;
                    iter_number += 1;
                }
            }
            else
            {
                driveSpeedCSSetSpeed( 0 );
            }
        }

    	time = chThdSleepUntilWindowed( time, time + MS2ST( 5 ) );
    }
}
