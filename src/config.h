// Cpu frequency for util/delay.h
#define F_CPU 1000000

// Half of delay in main execution loop, given in milliseconds.
#define LOOP_DELAY 50

// Half length of indicator led on-off sequence. In other words, the time
// the indicator is lit of darkened. Given in units of LOOP_DELAY
#define INDICATOR_HALF_PERIOD 10

// Eye and outline periods. Given in units of LOOP_DELAY
#define EYE_LEFT_OFF_PERIOD 150
#define EYE_LEFT_ON_PERIOD 50
#define EYE_RIGHT_OFF_PERIOD 74
#define EYE_RIGHT_ON_PERIOD 68
#define OUTLINE_OFF_PERIOD 170
#define OUTLINE_ON_PERIOD 38

// Mouth periods
#define MOUTH_BIG_PERIOD 40
#define MOUTH_SMALL_PERIOD 80
#define MOUTH_TINY_PERIOD 5
