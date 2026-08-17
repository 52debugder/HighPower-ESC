


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_CLARKE_PARK_H
#define __MC_CLARKE_PARK_H

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
//#include "LKS32MC05x.h"
#include "LKS32MC03x.h"
#include "MC_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MAX_MODULE      32767   // root(Vd^2+Vq^2) <= MAX_MODULE = 32767*100%

/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

//Curr_Components Clarke(Curr_Components);
//Curr_Components Park(Curr_Components,s16);
//void RevPark_Circle_Limitation(void);
//Volt_Components Rev_Park(Volt_Components Volt_Input); 
void Trig_Functions(s16 hAngle,STR_TrigComponents *t_pTrigComponents);

#endif //__MC_CLARKE_PARK_H

