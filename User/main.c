#include "stm32f10x.h"
#include "Delay.h"
#include "PWM.h"

int main(void)
{
    u16 pwm_val = 0;  // 占空比
    u8 dir = 1;       // 方向：1=变亮 0=变暗

    PWM_Init();       // 初始化PWM

    while (1)
    {
        if (dir)
        {
            pwm_val++;  // 占空比增加 → 变亮
            if (pwm_val >= 999) dir = 0;
        }
        else
        {
            pwm_val--;  // 占空比减少 → 变暗
            if (pwm_val <= 0) dir = 1;
        }

        TIM_SetCompare1(TIM2, pwm_val);  // 设置占空比
        Delay_ms(1);                     // 控制呼吸速度
    }
}