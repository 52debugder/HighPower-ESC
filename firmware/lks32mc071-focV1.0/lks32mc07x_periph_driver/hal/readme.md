# LKS32MC03x HAL 库使用说明

## 概述

本仓库提供了针对 LKS32MC03x 系列微控制器的硬件抽象层(HAL)库,包含各种外设驱动和底层硬件支持。

## 文件结构

```
├── hal_lks32mc03x.c        # 主HAL实现文件(需添加到工程)
├── hal_lks32mc03x.h        # 主HAL头文件(需包含)
├── hal_lksmcu_lib.lib      # Keil使用的静态库 内部实现校准参数读取,非法操作会导致芯片损坏,只提供静态库
├── libhal_lksmcu_lib.a     # GCC使用的静态库 内部实现校准参数读取,非法操作会导致芯片损坏,只提供静态库
├── readme.md               # 本说明文件
├── include/                # 头文件目录 不建议直接使用这个目录下的文件
│   ├── hal_lksmcu_adc.h    # ADC外设驱动
│   ├── hal_lksmcu_can.h    # CAN外设驱动
│   ├── ...                 # 其他外设驱动头文件
└── source/                 # 源文件目录 不建议直接使用这个目录下的文件
    ├── hal_lks32mc03x_adc.c # ADC实现
    ├── hal_lks32mc03x_clk.c # 时钟实现
    ├── ...                 # 其他外设实现
```

## 使用说明

### 1. 添加到工程

#### 对于Keil MDK工程:
1. 将 `hal_lks32mc03x.c` 和 `hal_lksmcu_lib.lib` 添加到工程源文件组
2. 将 `hal_lks32mc03x.h` 添加到工程头文件包含路径

#### 对于GCC工程:
1. 将 `hal_lks32mc03x.c` 添加到编译源文件列表
2. 确保 `hal_lks32mc03x.h` 在编译器包含路径中
3. 链接时添加静态库:
   ```
   -l:libhal_lksmcu_lib.a
   ```

### 2. 包含头文件

在需要使用HAL功能的源文件中包含主头文件:
```c
#include "hal_lks32mc03x.h"
```

## 版本信息

参考：version.txt

## 问题反馈

库函数问题反馈可以通过gitee或github提交issue
gitee仓库地址：https://gitee.com/LinkoSemiconductor/lks32mc03x_periph_driver
github仓库地址：https://github.com/Linko-Semiconductor/lks32mc03x_periph_driver
