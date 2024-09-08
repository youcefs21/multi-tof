/**
 ******************************************************************************
 * @file          : app_tof.c
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

#ifdef __cplusplus
extern "C"
{
#endif

#include "tof_app.h"
#include <stdio.h>
#include <custom_ranging_sensor.h>

#define TIMING_BUDGET (30U)		/* 5 ms < TimingBudget < 100 ms */
#define RANGING_FREQUENCY (10U) /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
#define POLLING_PERIOD (1000)	// measure once per 10 minute
#define EOF_MARKER "<EOF>"
#define CHUNK_SIZE 100

	static RANGING_SENSOR_Capabilities_t Cap[CUSTOM_RANGING_INSTANCES_NBR];
	static RANGING_SENSOR_ProfileConfig_t Profile[CUSTOM_RANGING_INSTANCES_NBR];
	static int32_t status = 0;

	void MX_TOF_Init(uint32_t Instance)
	{

		status = CUSTOM_RANGING_SENSOR_Init(Instance);
		if (status != BSP_ERROR_NONE)
		{
			printf("CUSTOM_RANGING_SENSOR_Init failed\n");
			while (1)
				;
		}

		uint32_t Id;
		CUSTOM_RANGING_SENSOR_ReadID(Instance, &Id);
		CUSTOM_RANGING_SENSOR_GetCapabilities(Instance, &Cap[Instance]);

		Profile[Instance].RangingProfile = RS_PROFILE_8x8_AUTONOMOUS;
		Profile[Instance].TimingBudget = TIMING_BUDGET;
		Profile[Instance].Frequency = RANGING_FREQUENCY; /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
		Profile[Instance].EnableAmbient = 0;			 /* Enable: 1, Disable: 0 */
		Profile[Instance].EnableSignal = 0;				 /* Enable: 1, Disable: 0 */

		/* set the profile if different from default one */
		CUSTOM_RANGING_SENSOR_ConfigProfile(Instance, &Profile[Instance]);

		//	status = CUSTOM_RANGING_SENSOR_Stop(Instance);

		//	status = CUSTOM_RANGING_SENSOR_SetPowerMode(Instance, CUSTOM_RANGING_POWERMODE_OFF);
	}

	RANGING_SENSOR_Result_t MX_TOF_Process(uint32_t Instance, uint32_t gap)
	{
		static RANGING_SENSOR_Result_t Result[CUSTOM_RANGING_INSTANCES_NBR];

		/* polling mode */
		// status = CUSTOM_RANGING_SENSOR_SetPowerMode(Instance, CUSTOM_RANGING_POWERMODE_OFF);

		status = CUSTOM_RANGING_SENSOR_Start(Instance, RS_MODE_BLOCKING_CONTINUOUS);

		do
		{
			status = CUSTOM_RANGING_SENSOR_GetDistance(Instance, &Result[Instance]);
		} while (status == BSP_ERROR_BUSY);

		HAL_Delay(gap);

		// status = CUSTOM_RANGING_SENSOR_Stop(Instance);

		//  status = CUSTOM_RANGING_SENSOR_SetPowerMode(Instance, CUSTOM_RANGING_POWERMODE_ON);

		return Result[Instance];
	}

#ifdef __cplusplus
}
#endif
