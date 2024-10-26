/**
 ******************************************************************************
 * @file    stedgeai_app_main.c
 * @author  MCD/AIS Team
 * @brief   Minimal main template to use the ST AI generated c-model using
            the "legacy" API
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software is licensed under terms that can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "network_data.h"

// #define USE_AI_REPORT

/* Global handle to reference the instantiated C-model */
static ai_handle network = AI_HANDLE_NULL;

/* Global c-array to handle the activations buffer(s) */
AI_ALIGNED(32)
static ai_u8 activations_1[AI_NETWORK_DATA_ACTIVATION_1_SIZE];

/* Array to store the data of the input tensors */
/* -> data_in_1 is allocated in activations buffer */

/* Array to store the data of the output tensors */
/* -> data_out_1 is allocated in activations buffer */

/* Array of pointer to manage the model's input/output tensors */
static ai_buffer *ai_input;
static ai_buffer *ai_output;

#ifdef USE_AI_REPORT
static ai_network_report report;
#endif

int aiRun(void);
void main_loop(void);
int main(void);

/* 
 * Bootstrap
 */
int aiInit(void) {
  
  /* Create and initialize the c-model */
  const ai_handle acts[] = {
    activations_1
  };

  ai_network_create_and_init(&network, acts, NULL);

  /* Reteive pointers to the model's input/output tensors */
  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);

  /* Set the @ of the input/output buffers when not allocated in the activations buffer */
  /* -> ai_input[0].data = ai_input[0].data */
  /* -> ai_output[0].data = ai_output[0].data */

#ifdef USE_AI_REPORT
  ai_network_get_report(network, &report);
#endif

  return 0;
}

/* 
 * Run inference
 */
int aiRun() {
  int res;

  res = ai_network_run(network, &ai_input[0], &ai_output[0]);
  
  return res;
}

/* 
 * Example of main loop function
 */
void main_loop() {

  aiInit();

  
  while (1) {
    /* 1 - Acquire, pre-process and fill the input buffers */
    // acquire_and_process_data(...);

    /* 2 - Call inference engine */
    aiRun();

    /* 3 - Post-process the predictions */
    // post_process(...);
  }
}

/* 
 * Example of system initialization function
 */
void SystemInit(void)
{

}

/* 
 * Example of main application function
 */
int main()
{
  SystemInit();
  main_loop();
  return 0;
}
