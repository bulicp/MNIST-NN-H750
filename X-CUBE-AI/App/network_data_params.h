/**
  ******************************************************************************
  * @file    network_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2024-10-25T17:35:36+0000
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef NETWORK_DATA_PARAMS_H
#define NETWORK_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_NETWORK_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_network_data_weights_params[1]))
*/

#define AI_NETWORK_DATA_CONFIG               (NULL)


#define AI_NETWORK_DATA_ACTIVATIONS_SIZES \
  { 3760, }
#define AI_NETWORK_DATA_ACTIVATIONS_SIZE     (3760)
#define AI_NETWORK_DATA_ACTIVATIONS_COUNT    (1)
#define AI_NETWORK_DATA_ACTIVATION_1_SIZE    (3760)



#define AI_NETWORK_DATA_WEIGHTS_SIZES \
  { 100352, 512, 8192, 256, 640, 40, }
#define AI_NETWORK_DATA_WEIGHTS_SIZE         (109992)
#define AI_NETWORK_DATA_WEIGHTS_COUNT        (6)
#define AI_NETWORK_DATA_WEIGHT_1_SIZE        (100352)
#define AI_NETWORK_DATA_WEIGHT_2_SIZE        (512)
#define AI_NETWORK_DATA_WEIGHT_3_SIZE        (8192)
#define AI_NETWORK_DATA_WEIGHT_4_SIZE        (256)
#define AI_NETWORK_DATA_WEIGHT_5_SIZE        (640)
#define AI_NETWORK_DATA_WEIGHT_6_SIZE        (40)



#define AI_NETWORK_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_network_activations_table[1])

extern ai_handle g_network_activations_table[1 + 2];



#define AI_NETWORK_DATA_WEIGHTS_TABLE_GET() \
  (&g_network_weights_table[1])

extern ai_handle g_network_weights_table[6 + 2];


#endif    /* NETWORK_DATA_PARAMS_H */
