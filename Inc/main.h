/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define HEX1_Pin GPIO_PIN_2
#define HEX1_GPIO_Port GPIOE
#define HEX3_Pin GPIO_PIN_3
#define HEX3_GPIO_Port GPIOE
#define HEX0_Pin GPIO_PIN_4
#define HEX0_GPIO_Port GPIOE
#define HEX2_Pin GPIO_PIN_5
#define HEX2_GPIO_Port GPIOE
#define NRFOK_Pin GPIO_PIN_3
#define NRFOK_GPIO_Port GPIOC
#define Button_Pin GPIO_PIN_4
#define Button_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_6
#define Buzzer_GPIO_Port GPIOE
#define Voltage_Pin GPIO_PIN_5
#define Voltage_GPIO_Port GPIOA
#define CE_Pin GPIO_PIN_11
#define CE_GPIO_Port GPIOB
#define CSN_Pin GPIO_PIN_12
#define CSN_GPIO_Port GPIOB
#define IRQ_Pin GPIO_PIN_8
#define IRQ_GPIO_Port GPIOD
#define MD3_Pin GPIO_PIN_11
#define MD3_GPIO_Port GPIOD
#define USBEnable_Pin GPIO_PIN_12
#define USBEnable_GPIO_Port GPIOD
#define MD4_Pin GPIO_PIN_13
#define MD4_GPIO_Port GPIOD
#define IMUOk_Pin GPIO_PIN_14
#define IMUOk_GPIO_Port GPIOD
#define USBReceive_Pin GPIO_PIN_15
#define USBReceive_GPIO_Port GPIOD
#define USBTransmit_Pin GPIO_PIN_8
#define USBTransmit_GPIO_Port GPIOC
#define DRDY_Pin GPIO_PIN_9
#define DRDY_GPIO_Port GPIOA
#define INTA_Pin GPIO_PIN_10
#define INTA_GPIO_Port GPIOA
#define FSYNC_Pin GPIO_PIN_15
#define FSYNC_GPIO_Port GPIOA
#define MDSpinn_Pin GPIO_PIN_0
#define MDSpinn_GPIO_Port GPIOD
#define DebugTransmit_Pin GPIO_PIN_1
#define DebugTransmit_GPIO_Port GPIOD
#define DebugReceive_Pin GPIO_PIN_3
#define DebugReceive_GPIO_Port GPIOD
#define DataCorrect_Pin GPIO_PIN_4
#define DataCorrect_GPIO_Port GPIOD
#define DataArrived_Pin GPIO_PIN_7
#define DataArrived_GPIO_Port GPIOD
#define ShootOK_Pin GPIO_PIN_4
#define ShootOK_GPIO_Port GPIOB
#define ShootIsCharged_Pin GPIO_PIN_5
#define ShootIsCharged_GPIO_Port GPIOB
#define MD1_Pin GPIO_PIN_0
#define MD1_GPIO_Port GPIOE
#define MD2_Pin GPIO_PIN_1
#define MD2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
