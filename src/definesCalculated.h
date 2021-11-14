#include "defines.h"

#define T_PWM (F_CPU/(F_PWM*PWM_STEPS))
#if (T_PWM<(93+5))
    #error T_PWM zu klein, F_CPU muss vergrössert werden oder F_PWM oder PWM_STEPS verkleinert werden
#endif