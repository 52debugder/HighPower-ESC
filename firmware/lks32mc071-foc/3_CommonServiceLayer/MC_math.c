/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MC_math.c
 * 文件标识：
 * 内容摘要： 电机控制相关数学计算函数
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
#include "mc_math.h"
#include "project_mcu.h"

#define SIN_COS_TABLE { \
0x0000,0x00C9,0x0192,0x025B,0x0324,0x03ED,0x04B6,0x057F,\
0x0648,0x0711,0x07D9,0x08A2,0x096B,0x0A33,0x0AFB,0x0BC4,\
0x0C8C,0x0D54,0x0E1C,0x0EE4,0x0FAB,0x1073,0x113A,0x1201,\
0x12C8,0x138F,0x1455,0x151C,0x15E2,0x16A8,0x176E,0x1833,\
0x18F9,0x19BE,0x1A83,0x1B47,0x1C0C,0x1CD0,0x1D93,0x1E57,\
0x1F1A,0x1FDD,0x209F,0x2162,0x2224,0x22E5,0x23A7,0x2467,\
0x2528,0x25E8,0x26A8,0x2768,0x2827,0x28E5,0x29A4,0x2A62,\
0x2B1F,0x2BDC,0x2C99,0x2D55,0x2E11,0x2ECC,0x2F87,0x3042,\
0x30FC,0x31B5,0x326E,0x3327,0x33DF,0x3497,0x354E,0x3604,\
0x36BA,0x3770,0x3825,0x38D9,0x398D,0x3A40,0x3AF3,0x3BA5,\
0x3C57,0x3D08,0x3DB8,0x3E68,0x3F17,0x3FC6,0x4074,0x4121,\
0x41CE,0x427A,0x4326,0x43D1,0x447B,0x4524,0x45CD,0x4675,\
0x471D,0x47C4,0x486A,0x490F,0x49B4,0x4A58,0x4AFB,0x4B9E,\
0x4C40,0x4CE1,0x4D81,0x4E21,0x4EC0,0x4F5E,0x4FFB,0x5098,\
0x5134,0x51CF,0x5269,0x5303,0x539B,0x5433,0x54CA,0x5560,\
0x55F6,0x568A,0x571E,0x57B1,0x5843,0x58D4,0x5964,0x59F4,\
0x5A82,0x5B10,0x5B9D,0x5C29,0x5CB4,0x5D3E,0x5DC8,0x5E50,\
0x5ED7,0x5F5E,0x5FE4,0x6068,0x60EC,0x616F,0x61F1,0x6272,\
0x62F2,0x6371,0x63EF,0x646C,0x64E9,0x6564,0x65DE,0x6657,\
0x66D0,0x6747,0x67BD,0x6832,0x68A7,0x691A,0x698C,0x69FD,\
0x6A6E,0x6ADD,0x6B4B,0x6BB8,0x6C24,0x6C8F,0x6CF9,0x6D62,\
0x6DCA,0x6E31,0x6E97,0x6EFB,0x6F5F,0x6FC2,0x7023,0x7083,\
0x70E3,0x7141,0x719E,0x71FA,0x7255,0x72AF,0x7308,0x735F,\
0x73B6,0x740B,0x7460,0x74B3,0x7505,0x7556,0x75A6,0x75F4,\
0x7642,0x768E,0x76D9,0x7723,0x776C,0x77B4,0x77FB,0x7840,\
0x7885,0x78C8,0x790A,0x794A,0x798A,0x79C9,0x7A06,0x7A42,\
0x7A7D,0x7AB7,0x7AEF,0x7B27,0x7B5D,0x7B92,0x7BC6,0x7BF9,\
0x7C2A,0x7C5A,0x7C89,0x7CB7,0x7CE4,0x7D0F,0x7D3A,0x7D63,\
0x7D8A,0x7DB1,0x7DD6,0x7DFB,0x7E1E,0x7E3F,0x7E60,0x7E7F,\
0x7E9D,0x7EBA,0x7ED6,0x7EF0,0x7F0A,0x7F22,0x7F38,0x7F4E,\
0x7F62,0x7F75,0x7F87,0x7F98,0x7FA7,0x7FB5,0x7FC2,0x7FCE,\
0x7FD9,0x7FE2,0x7FEA,0x7FF1,0x7FF6,0x7FFA,0x7FFE,0x7FFF}

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
STR_TrigComponents Vector_Components;
const s16 hSin_Cos_Table[256] = SIN_COS_TABLE;


/*******************************************************************************
 * Function Name  : Trig_Functions 
 * Description    : This function returns Cosine and Sine functions of the input 
 *                  angle
 * Input          : angle in s16 format
 * Output         : Cosine and Sine in s16 format
 * Return         : none.
 *******************************************************************************/ 
#if (MCU_DSP_SINCOS == FUNCTION_OFF)
void Trig_Functions(s16 hAngle,STR_TrigComponents *t_pTrigComponents)
{
	u8  sector;	

	// 10 bit index computation //
	sector = ((u16)hAngle) >> 14;  
	hAngle = hAngle >> 6;  

	switch (sector)
	{
		case 0:		//U0_90:
			t_pTrigComponents->hSin = hSin_Cos_Table[(u8)(hAngle)];
			t_pTrigComponents->hCos = hSin_Cos_Table[(u8)(~hAngle)];
		break;

		case 1:		//U90_180:
			t_pTrigComponents->hSin = hSin_Cos_Table[(u8)(~hAngle)];
			t_pTrigComponents->hCos = -hSin_Cos_Table[(u8)(hAngle)];
		break;	

		case 2:		//U180_270:
			t_pTrigComponents->hSin = -hSin_Cos_Table[(u8)(hAngle)];
			t_pTrigComponents->hCos = -hSin_Cos_Table[(u8)(~hAngle)];
		break;

		case 3:		//U270_360:
			t_pTrigComponents->hSin = -hSin_Cos_Table[(u8)(~hAngle)];
			t_pTrigComponents->hCos = hSin_Cos_Table[(u8)(hAngle)];
		break;

		default:
		break;
	}
}
#else
void Trig_Functions(s16 hAngle,STR_TrigComponents *t_pTrigComponents)
{

    DSP0_SC |= BIT2;
    DSP0_THETA = hAngle;

    t_pTrigComponents->hSin = DSP0_SIN;
    t_pTrigComponents->hCos = DSP0_COS;
}
#endif

/*******************************************************************************
 * Function Name  : Sqrt_Functions 
 * Description    : This function returns SqrtT of the input variable
 *                  
 * Input          : in s16 format
 * Output         : Sqrt
 * Return         : none.
 *******************************************************************************/
s16 Sqrt_Functions(s16 x,s16 y)
{
	s16 result;
	DSP0_RAD = (s32)x * x  + (s32)y * y;
    result = DSP0_SQRT;
	return result;
}

/*******************************************************************************
 * Function Name  : DIV_Functions 
 * Description    : This function returns SqrtT of the input variable
 *                  
 * Input          : in s16 format
 * Output         : Sqrt
 * Return         : none.
 *******************************************************************************/
#if (MCU_DSP_DIV == FUNCTION_ON)
s16 Div_Functions(s32 y, s16 x)
{
	s16 result;	
	DSP0_DID = y;
    DSP0_DIS = x;
    result = DSP0_QUO;
	return result;
}
#else
s16 Div_Functions(s32 y, s16 x)
{	
	return (y/x);
}
#endif



/*******************************************************************************
 函数名称：    void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
 功能描述：    以8Bit为一次复制数据到另外一个地址
 输入参数：    u8* nDestAddr, u8* pSrcBuff, u16 nSize
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void CopyFromBuffer(u8* nDestAddr, u8* pSrcBuff, u16 nSize)
{
    u8* ps = (u8*) pSrcBuff;
    u8* pd = (u8*) nDestAddr;

    while(nSize--)
        *pd++ = *ps++;


}

void ramp32GenInit(PSTR_RampGen32 this)
{
    this->wRampIn		= 0;
    this->wRampOut		= 0;
    this->wRampTmp		= 0;
}


void ramp32GenCalc(PSTR_RampGen32 this)
{
    s32 t_wTmp = 0;
	bool isIncrease = FALSE;

    if (this->wRampOut != this->wRampIn)
    {
        if ( this->wRampIncrease == 0 )
        {
            this->wRampOut		= this->wRampIn;
            this->wRampTmp		= 0;
            return;
        }

        if (this->wRampIn >= this->wRampOut)
        {
            this->wRampTmp		+= this->wRampIncrease;
			isIncrease			= TRUE;
        }
        else
        {
            this->wRampTmp		-= this->wRampDecrease;          
        }

		t_wTmp					= ABS(this->wRampTmp);
		if(this->wRampTmp >=0)
		{
			this->wRampOut		+= (t_wTmp >> 16);
		}
		else
		{
			this->wRampOut		-= (t_wTmp >> 16);
		}
		
        t_wTmp					= t_wTmp & 0x0000FFFF;
        this->wRampTmp			= this->wRampTmp >= 0 ? t_wTmp : -t_wTmp;

		if(isIncrease)
		{
	        if (this->wRampOut > this->wRampIn)
	        {
	            this->wRampOut	= this->wRampIn;
	            this->wRampTmp	= 0;
	        }
		}
		else
		{
			if (this->wRampOut < this->wRampIn)
	        {
	            this->wRampOut	= this->wRampIn;
	            this->wRampTmp	= 0;
	        }
		}
    }
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
