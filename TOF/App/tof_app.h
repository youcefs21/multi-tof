/**
 ******************************************************************************
 * @file          : app_tof.h
 * @author        : IMG SW Application Team
 * @brief         : This file provides code for the configuration
 *                  of the STMicroelectronics.X-CUBE-TOF1.3.4.2 instances.
 ******************************************************************************
 *
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TOF_APP_H
#define __TOF_APP_H

#include <custom_ranging_sensor.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /* Includes ------------------------------------------------------------------*/

  /* Exported defines ----------------------------------------------------------*/

  /* Exported functions --------------------------------------------------------*/
  void MX_TOF_Init(uint32_t Instance);
  RANGING_SENSOR_Result_t MX_TOF_Process(uint32_t Instance, uint32_t gap);

#ifdef __cplusplus
}
#endif

#endif /* __TOF_APP_H */
