// Cpu frequency for util/delay.h
#define F_CPU 1000000

// Half of delay in main execution loop, given in milliseconds.
#define LOOP_DELAY 50

// Half length of indicator led on-off sequence. In other words, the time
// the indicator is lit of darkened. Given in units of LOOP_DELAY
#define INDICATOR_HALF_PERIOD 10

// Eye periods
#define EYE_LEFT_OFF_PERIOD 150
#define EYE_LEFT_ON_PERIOD 50
#define EYE_RIGHT_OFF_PERIOD 74
#define EYE_RIGHT_ON_PERIOD 68
