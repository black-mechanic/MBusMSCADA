
#include "fb/fb.h"
#include "drivers/drv_user.h"
extern pFB_proc FB_proc_list[INSAT_MAX_FB_TYPE];

// example description user FB
extern int FB_example( FB_MODE fbMode, FB_CB PTR fbCB );

// FB user type
#define  FB_USER_TYPE 150 // max type = 199
//Drivers
extern int Driver_MBus(DRIVER_MODE mode, SERIAL_TASK_CB PTR taskCB);
#define  DRIVER_USER_TYPE 51
// --------------------------------------------------------
// InitFB_user
// --------------------------------------------------------
void InitFB_user(void)
{
	// example register user FB
	FB_proc_list[FB_USER_TYPE] = FB_example;
	// example register user driver
	Drivers_proc_list[DRIVER_USER_TYPE] = Driver_MBus;
}	

