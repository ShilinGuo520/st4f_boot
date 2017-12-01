/**
  ******************************************************************************
  * @file    TIM/TIM_PWMOutput/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "timer.h"
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* TIM Configuration */
  tim_config();

  /* UART1 Configuration */
  com1_config(); 

  /* TIM PWM Out */
  tim_pwm_output();
  
  while (1) {
    com1_puts("hello word \r\n");
  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
