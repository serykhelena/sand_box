#include "tests.h"
#include "remote_control.h"
#include "drive_cs.h"


static void autoMove( float ref_speed )
{
	float speed_deadzone = 0.05

	driveSteerCSSetPosition( 0 ); // keep steering wheels in the center 
	// while( )
	driveSpeedCSSetSpeed( ref_speed );
}

void testFrictionRoutine( void )
{
    remoteControlInit( NORMALPRIO + 1 );
	driverCSInit( NORMALPRIO );
    driverIsEnableCS(true);

    float                test_speed_ref     = 0.3;


    systime_t time = chVTGetSystemTimeX();
    while(1)
    {
    	mode = rcModeIsEnabled();
    	if( mode == true )
        {
            rc_speed        = rcGetSpeedDutyCycleValue( );
            rc_steer        = rcGetSteerDutyCycleValue( );
            rc_steer_prt    = rcGetSteerControlValue( );
            rc_speed_prt    = rcGetSpeedControlValue( );
            // TODO: check if lld_control is included 
            // in drive_cs.h or remote_control.h
            lldControlSetDrMotorPower( rc_speed_prt );
            lldControlSetSteerMotorPower( rc_steer_prt );
        }
        else
        {

        }

    	time = chThdSleepUntilWindowed( time, time + MS2ST( 10 ) );
    }
}