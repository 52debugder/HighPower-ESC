/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dsp.c\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2015年11月5日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:DSP调用函数内增加中断打断重新复位DSP功能
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */

#include "lks32mc07x_dsp.h"

/**
 *@brief @b 函数名称:   void DSP_Init(void)
 *@brief @b 功能描述:   DSP使能和关闭
 *@see被引用内容：       SYS_ModuleClockCmd()
 *@param输入参数：       无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP0, ENABLE); /* DSP时钟使能*/
}

/**
 *@brief @b 函数名称:   s16 DSP_sin(u16 angle)
 *@brief @b 功能描述:   DSP sin计算函数
 *@see被引用内容：
 *@param输入参数：      angle： 输入角度
 *@param输出参数：      无
 *@return返 回 值：     sin角度值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP_sin(s16 angle)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SIN_COS_MODE();
    DSP_REG->THETA = angle;
    answer         = DSP_REG->SIN;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称:  s16 DSP_cos(u16 angle)
 *@brief @b 功能描述:   DSP cos计算函数
 *@see被引用内容：
 *@param输入参数：      angle： 输入角度
 *@param输出参数：      无
 *@return返 回 值：     cos角度值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP_cos(s16 angle)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_SIN_COS_MODE();
    DSP_REG->THETA = angle;
    answer         = DSP_REG->COS;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称:  s16 u16 DSP_rms(s16 a,s16 b)
 *@brief @b 功能描述:   DSP 除法求余数计算函数
 *@see被引用内容：
 *@param输入参数：      a： 被除数
 *                     b:除数
 *@param输出参数：      无
 *@return返 回 值：     两数的余数
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s32 DSP_rms(s32 a, s32 b)
{
    s32 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_REG->DID = a;
    DSP_REG->DIS = b;
    answer       = DSP_REG->REM;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称:  DSP_arctan(s16 x,s16 y)
 *@brief @b 功能描述:   DSP 反正切计算函数
 *@see被引用内容：
 *@param输入参数：      x：分母
 *                     y:分子
 *@param输出参数：      无
 *@return返 回 值：     反正切值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s16 DSP_arctan(s16 x, s16 y)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_ARCTAN_MODE();
    DSP_REG->X = x;
    DSP_REG->Y = y;
    answer     = DSP_REG->ARCTAN;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称: s32 DSP_div(s32 a,s32 b)
 *@brief @b 功能描述:   DSP 除法计算
 *@see被引用内容：
 *@param输入参数：      x：被除数
 *                     y:除数
 *@param输出参数：      无
 *@return返 回 值：     两数的商
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
s32 DSP_div(s32 a, s32 b)
{
    s32 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_REG->DID = a;
    DSP_REG->DIS = b;
    answer       = DSP_REG->QUO;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称: s16 DSP_mod(s32 x,s16 y)
 *@brief @b 功能描述:   DSP 计算向量的模
 *@see被引用内容：
 *@param输入参数：      x：x轴
 *                     y: y轴
 *@param输出参数：      无
 *@return返 回 值：     向量的模
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
u16 DSP_mod(s16 x, s16 y)
{
    s16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_REG->X = x;
    DSP_REG->Y = y;
    answer     = DSP_REG->MOD;
    __set_PRIMASK(flg);
    return answer;
}

/**
 *@brief @b 函数名称: u16 DSP_sqrt(u32 val)
 *@brief @b 功能描述:   开平方函数
 *@see被引用内容：
 *@param输入参数：      val ：被开方数
 *@param输出参数：      无
 *@return返 回 值：     向量的莫
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>2.0     <td>ywx   <td>修改
 * </table>
 */
u16 DSP_sqrt(u32 val)
{
    u16 answer;
    int32_t flg = __get_PRIMASK();
    __disable_irq();
    DSP_REG->RAD = val;
    answer       = DSP_REG->SQRT;
    __set_PRIMASK(flg);
    return answer;
}
/**
 * @brief sincos模式
 */
void DSP_SinCosMode(void)
{
    DSP_SIN_COS_MODE();
}
/**
 * @brief Arctan模式
 */
void DSP_ArctanMode(void)
{
    DSP_ARCTAN_MODE();
}
