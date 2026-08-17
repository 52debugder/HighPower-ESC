/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Time_Process.c
 * 文件标识：
 * 内容摘要： 定时相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "project_config.h"
#include "MA_Static_Variable.h"
#include "math.h"
#include "Time_Process.h"
#include "state_machine.h"

extern void MACtrlObjTask(void);
extern void UACtrlObjTask(void);

extern STR_TaskScheduler gS_TaskScheduler; 
extern void MDtaskHandleIn1msLoop(void);

#ifdef _TIME_TEST_DEFINED
extern s16 Debug1MsTimes;
extern s16 Debug1MsTimesRecord;
#endif
/*******************************************************************************
 函数名称：    void Task_Scheduler(void)
 功能描述：    按时间片任务调度函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Task_Scheduler(void)
{
    volatile u32 t_data;

    if (gS_TaskScheduler.bTimeCnt1ms >= TASK_SCHEDU_1MS)
    {   /* 1毫秒事件，任务调度 */
        gS_TaskScheduler.bTimeCnt1ms = 0;

		MDtaskHandleIn1msLoop();			// MD 慢速任务，时间严格时需在中断处理
		UACtrlObjTask();					/* UA状态机调度及任务处理 */
		MACtrlObjTask();					/* MA状态机调度及任务处理 */

		#ifdef _TIME_TEST_DEFINED				// 时间测量
		Debug1MsTimesRecord = Debug1MsTimes;
		Debug1MsTimes		= 0;
		#endif
    }

    if (gS_TaskScheduler.nTimeCnt10ms >= TASK_SCHEDU_10MS)
    {   /* 10毫秒事件，任务调度 */
        gS_TaskScheduler.nTimeCnt10ms = 0;

    }

    if (gS_TaskScheduler.nTimeCnt500ms >= TASK_SCHEDU_500MS)
    {   /* 500毫秒事件，任务调度 */
        gS_TaskScheduler.nTimeCnt500ms = 0;
    }

    if(gS_TaskScheduler.bPWM_UpdateFlg)
    {   /* 每个PWM周期更新一次 */
        gS_TaskScheduler.bPWM_UpdateFlg = 0;
    }

}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



