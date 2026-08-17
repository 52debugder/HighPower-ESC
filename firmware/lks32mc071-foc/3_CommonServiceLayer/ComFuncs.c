/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： ComFuncs.c
 * 文件标识：
 * 内容摘要： Define the commom function for motor control
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LKS/MC TEAM
 * 完成日期： 2022年8月11日
 *******************************************************************************/
#include "basic.h"
#include "PubData_DriverInstance.h"
/*******************************************************************************
 函数名称：    void delay(u16 cnt)
 功能描述：    软件延时程序
 操作的表：    无
 输入参数：    cnt 需要延时的时间
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------

 *******************************************************************************/
 
void delay(u16 cnt)
{
    u16 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}


unsigned char CountLeadZero(unsigned int val)	
{
	return (__clz(val));
}

// user 2 App trans

/*****************************************************************************
 * 函数名   : User2AppFreqTrans(PSTR_TransCoefElement pUser2App,float val)
 * 说明     : User2App 频率转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 User2AppFreqTrans(PSTR_TransCoefElement pUser2App,float val)
{
    s32 ax;
    ax = ((s32)(pUser2App->nuFreq * val)) >> (pUser2App->nFreqShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : User2AppCurTrans(s32 val)
 * 说明     : struUser2App 频率转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 User2AppCurTrans(PSTR_TransCoefElement pUser2AppCur,float val)
{
    s32 ax;
    ax = ((s32)(pUser2AppCur->nuCur * val)) >> (pUser2AppCur->nCurShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : User2AppVolTrans(PSTR_TransCoefElement pUser2AppVolt,float val)
 * 说明     : User2App 电压转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 User2AppVolTrans(PSTR_TransCoefElement pUser2AppVolt,float val)
{
    s32 ax;
    ax = ((s32)(pUser2AppVolt->nuVol* val)) >> (pUser2AppVolt->nVolShftNum);
    return (ax);
}

// App 2 core trans

/*****************************************************************************
 * 函数名   : App2CoreFreqTrans(s32 val)
 * 说明     : App2Core 频率转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 App2CoreFreqTrans(PSTR_TransCoefElement pApp2CoreFreq,s32 val)
{
    s32 ax;
    ax = (s32)pApp2CoreFreq->nuFreq * val >> (pApp2CoreFreq->nFreqShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : App2CoreCurTrans(s32 val)
 * 说明     : App2Core 电流转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 App2CoreCurTrans(PSTR_TransCoefElement pApp2CoreCur,s32 val)
{
    s32 ax;
    ax = (s32)pApp2CoreCur->nuCur * val >> (pApp2CoreCur->nCurShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : App2CoreVoltTrans(PSTR_TransCoefElement pApp2CoreVolt,s32 val)
 * 说明     : App2Core 电压转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 App2CoreVoltTrans(PSTR_TransCoefElement pApp2CoreVolt,s32 val)
{
    s32 ax;
    ax = (s32)pApp2CoreVolt->nuVol * val >> (pApp2CoreVolt->nVolShftNum);
    return (ax);
}

// Core 2 App trans
/*****************************************************************************
 * 函数名   : Core2AppFreqTrans(s32 val)
 * 说明     : Core2App 频率转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 Core2AppFreqTrans(PSTR_TransCoefElement pCore2AppFreq,s32 val)
{
    s32 ax;
    ax = (s32)pCore2AppFreq->nuFreq * val >> (pCore2AppFreq->nFreqShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : Core2AppCurTrans(PSTR_TransCoefElement pCore2AppCur,s32 val)
 * 说明     : Core2App 电流转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 Core2AppCurTrans(PSTR_TransCoefElement pCore2AppCur,s32 val)
{
    s32 ax;
    ax = (s32)pCore2AppCur->nuCur * val >> (pCore2AppCur->nCurShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : Core2AppVolTrans(PSTR_TransCoefElement pCore2AppVolt,s32 val)
 * 说明     : Core2App 电压转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 Core2AppVolTrans(PSTR_TransCoefElement pCore2AppVolt,s32 val)
{
	s32 ax;
    ax = (s32)pCore2AppVolt->nuVol * val >> (pCore2AppVolt->nVolShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : Core2AppPowerTrans(PSTR_TransCoefElement pCore2AppPower,s16 val)
 * 说明     : Core2App 电压转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s32 Core2AppPowerTrans(PSTR_TransCoefElement pCore2AppPower,s16 val)
{
    s32 ax;
    ax = (s32)pCore2AppPower->nuPower * val >> (pCore2AppPower->nPowerShftNum);
    return (ax);
}

/*****************************************************************************
 * 函数名   : s16 App2UsrFreqTrans(PSTR_TransCoefElement pUsr2AppFreq,s32 val) 
 * 说明     : User2Core 电压转换 
 * 设计思路 ：1.标幺系统转换
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 *****************************************************************************/
s16 App2UsrFreqTrans(PSTR_TransCoefElement pUsr2AppFreq,s32 val)
{
    s16 ax;
    ax = (s16)(val/pUsr2AppFreq->nuFreq);
    return (ax);
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */






////////////////////


