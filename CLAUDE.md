# CLAUDE.md — STM32F103C8T6 LED呼吸灯 (PWM)

## 技术栈

- **MCU**: STM32F103C8T6（Cortex-M3, 64KB Flash, 20KB SRAM, 72MHz）
- **库**: ST 标准外设库 v3.5.0
- **构建工具**: Keil MDK uVision5 + EIDE (VSCode 插件 `cl.eide`)
- **调试器**: ST-Link (SWD)

## 目录结构

```
├── Start/           CMSIS 启动 + system_stm32f10x
├── Library/         ST 标准外设库 v3.5.0
├── System/          Delay.c/h — SysTick 延时
├── Hardwera/        自定义硬件驱动
│   └── PWM.c/h      ← TIM2 CH1 PWM 驱动 (PA0)
├── User/            main.c, stm32f10x_conf.h, stm32f10x_it.c/h
├── build/           EIDE 构建输出
└── Objects/Listings/
```

## 硬件引脚映射

| 引脚 | 功能 | 连接目标 |
|------|------|----------|
| PA0 | TIM2_CH1 AF PP | LED (PWM 低电平点亮) |

## PWM 驱动 (Hardwera/PWM.c/h)

### TIM2 配置
- 时钟: 72MHz / (71+1) = 1MHz
- ARR: 999 → PWM 频率 = 1MHz / 1000 = 1kHz
- 模式: PWM1, 极性低 (OCPolarity_Low)
- 预装载使能

### API
- `PWM_Init()` — 初始化 GPIO PA0 + TIM2 CH1 PWM
- `PWM_SetCompare1(Compare)` — 设置 CCR1 (0~999)

## 功能说明

PA0 输出 PWM 控制 LED 亮度。主循环中占空比 0→999→0 循环变化，实现 LED 呼吸效果（渐亮渐暗），速度由 1ms 延时控制。

## 编码规范
- GPIO/定时器配置用标准库
- 编码: UTF-8，注释用中文

## Git 规范
```
main              ← 稳定分支
提交: feat:/fix:/docs: 格式
```

## 构建命令
```
Keil:  打开 Project.uvprojx → F7 编译 → F8 烧录
EIDE:  Ctrl+Shift+P → "EIDE: Build"
```

## 注意事项
- `USE_STDPERIPH_DRIVER` + `STM32F10X_MD` 编译选项必须定义
- 启动文件 `startup_stm32f10x_md.s`
- TIM2 挂载 APB1, GPIOA 挂载 APB2
