
#ifndef __TIM1_H__
#define __TIM1_H__

#define ENC_RANGE 10000
#define ENC_ABS_RANGE 5000 //AO!: This must be half of ENC_RANGE.
//#define ENC_RANGE 3200
//#define ENC_ABS_RANGE 1600

//AO!: Prescaler in the encoder mode is not documented correctly. The actual prescaler value will be the value below +1. If the final value is even, the encoder will not work correctly and drift.
//TODO: Change to 0:
#define ENC_Prescaler 0 //Used in TIM1 prescaler.
//#define ENC_Prescaler 1 //Used in TIM1 prescaler.
//#define ENC_Prescaler 10 //This value was implemented wrong!

#define ENC_FILTER 0x50  //fs=fm/2, N=8 samples.


void TIM1_setup(void);


#endif
