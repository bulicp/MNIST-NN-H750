/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2024-10-25T17:35:36+0000
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0xa5ac311aabe22d0f41c0f21b096c0ece"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2024-10-25T17:35:36+0000"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[6] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_1_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  output_QuantizeLinear_Input_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 100352, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 128, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_1_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8192, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_1_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  output_QuantizeLinear_Input_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 640, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  output_QuantizeLinear_Input_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 10, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 1424, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _Relu_1_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 448, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  output_QuantizeLinear_Input_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 114, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Relu_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02078697457909584f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Relu_1_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.013014258816838264f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(output_QuantizeLinear_Input_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.027057994157075882f),
    AI_PACK_INTQ_ZP(52)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Relu_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 128,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0007079303031787276f, 0.004798804875463247f, 0.0006557782180607319f, 0.0006772403721697628f, 0.0006666581030003726f, 0.006614090874791145f, 0.0006518425652757287f, 0.005044047720730305f, 0.0006716084899380803f, 0.0057374294847249985f, 0.0032937335781753063f, 0.0035804472863674164f, 0.0006321714608930051f, 0.0006854009116068482f, 0.0006794706569053233f, 0.006392627954483032f, 0.0006399615667760372f, 0.005387026350945234f, 0.0055902618914842606f, 0.00482142111286521f, 0.0007145257550291717f, 0.00408439664170146f, 0.0006720233359374106f, 0.004974322393536568f, 0.00436790706589818f, 0.0006655697361566126f, 0.0006671634619124234f, 0.004876002669334412f, 0.000651294132694602f, 0.0006839141715317965f, 0.0006926680216565728f, 0.004385636653751135f, 0.005424050614237785f, 0.0006507214275188744f, 0.00665832357481122f, 0.004899454768747091f, 0.0060631027445197105f, 0.0007145549170672894f, 0.006111845839768648f, 0.000651771726552397f, 0.003723611356690526f, 0.003942638169974089f, 0.0006514053093269467f, 0.004722905810922384f, 0.006069133058190346f, 0.005942018702626228f, 0.006881318520754576f, 0.00470268540084362f, 0.0006849363562650979f, 0.0006323257111944258f, 0.007021876517683268f, 0.0006779689574614167f, 0.005106836091727018f, 0.006364201195538044f, 0.0006827316829003394f, 0.005739910993725061f, 0.000705077254679054f, 0.0009670770959928632f, 0.0007469153497368097f, 0.006096397992223501f, 0.0006512370309792459f, 0.005328229628503323f, 0.0034368669148534536f, 0.0006838019471615553f, 0.00578533997759223f, 0.0006555812433362007f, 0.0006886208429932594f, 0.0040330481715500355f, 0.004025324247777462f, 0.005612461362034082f, 0.00063967244932428f, 0.006361733190715313f, 0.004511095117777586f, 0.005411465186625719f, 0.006272089201956987f, 0.0006518274312838912f, 0.004252892453223467f, 0.007723911665380001f, 0.008155285380780697f, 0.00065000937320292f, 0.005018426571041346f, 0.0006805950542911887f, 0.0007662266725674272f, 0.0007019646582193673f, 0.0007399418973363936f, 0.0005571809597313404f, 0.003980040084570646f, 0.00065085687674582f, 0.00794442929327488f, 0.004844946321099997f, 0.006902300287038088f, 0.00605217507109046f, 0.006040289532393217f, 0.0006887312047183514f, 0.004506099037826061f, 0.0006515003624372184f, 0.0006676748162135482f, 0.000710821186657995f, 0.005779065657407045f, 0.00932462140917778f, 0.004895070102065802f, 0.004898945800960064f, 0.0038957016076892614f, 0.007720173802226782f, 0.0006388192414306104f, 0.0006835124222561717f, 0.000651845708489418f, 0.004661445040255785f, 0.0006516302819363773f, 0.004030119627714157f, 0.005400246009230614f, 0.000651131384074688f, 0.004434374626725912f, 0.0047165281139314175f, 0.0006509926752187312f, 0.004840277135372162f, 0.0006825158488936722f, 0.0008338158950209618f, 0.005801742430776358f, 0.0006515680579468608f, 0.0006516785360872746f, 0.0045315660536289215f, 0.0006509677041321993f, 0.0006892987294122577f, 0.005895208101719618f, 0.004730329383164644f, 0.0006514348788186908f, 0.006713477429002523f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Relu_1_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0020708483643829823f, 0.004371901508420706f, 0.004955550655722618f, 0.005913735833019018f, 0.00295217614620924f, 0.003168373368680477f, 0.0026747803203761578f, 0.004568376578390598f, 0.004937137942761183f, 0.00321712507866323f, 0.004700086545199156f, 0.001768662710674107f, 0.004476066678762436f, 0.0061930203810334206f, 0.004511879291385412f, 0.006653035990893841f, 0.005077613051980734f, 0.005941698793321848f, 0.004278345033526421f, 0.005262451246380806f, 0.005647633690387011f, 0.00413140095770359f, 0.004109985660761595f, 0.005918528418987989f, 0.005260901525616646f, 0.004640751052647829f, 0.005877786781638861f, 0.005704729352146387f, 0.0033618060406297445f, 0.004034784156829119f, 0.004187416285276413f, 0.003938888665288687f, 0.004383360967040062f, 0.005414336454123259f, 0.004388932138681412f, 0.0035513623151928186f, 0.0037720734253525734f, 0.005536900367587805f, 0.004465639125555754f, 0.004400654695928097f, 0.004222390241920948f, 0.00576400151476264f, 0.002058459213003516f, 0.0020173052325844765f, 0.0045510148629546165f, 0.004415665753185749f, 0.003635640488937497f, 0.0032049512956291437f, 0.004771118517965078f, 0.003899256233125925f, 0.005302914883941412f, 0.00548310624435544f, 0.0036878446117043495f, 0.003544251201674342f, 0.0021047107875347137f, 0.003593332599848509f, 0.002593556186184287f, 0.0046307966113090515f, 0.0036126605700701475f, 0.00460649561136961f, 0.003082391805946827f, 0.002643000101670623f, 0.00612301891669631f, 0.00613008625805378f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(output_QuantizeLinear_Input_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 10,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0058645689859986305f, 0.008751314133405685f, 0.005145509727299213f, 0.005495833698660135f, 0.006232853513211012f, 0.004730059765279293f, 0.006336245685815811f, 0.006422881968319416f, 0.005525283049792051f, 0.0064177378080785275f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(input_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921163268387318f),
    AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_output_0_output, AI_STATIC,
  0, 0x1,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 1, 1, 128, 128),
  1, &_Relu_output_0_output_array, &_Relu_output_0_output_array_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_1_output_0_scratch0, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 448, 1, 1), AI_STRIDE_INIT(4, 2, 2, 896, 896),
  1, &_Relu_1_output_0_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_1_output_0_output, AI_STATIC,
  2, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &_Relu_1_output_0_output_array, &_Relu_1_output_0_output_array_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  output_QuantizeLinear_Input_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 1, 1, 10, 10),
  1, &output_QuantizeLinear_Input_output_array, &output_QuantizeLinear_Input_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_output_0_weights, AI_STATIC,
  4, 0x1,
  AI_SHAPE_INIT(4, 784, 128, 1, 1), AI_STRIDE_INIT(4, 1, 784, 100352, 100352),
  1, &_Relu_output_0_weights_array, &_Relu_output_0_weights_array_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  output_QuantizeLinear_Input_scratch0, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 114, 1, 1), AI_STRIDE_INIT(4, 2, 2, 228, 228),
  1, &output_QuantizeLinear_Input_scratch0_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_output_0_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_Relu_output_0_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_1_output_0_weights, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 128, 64, 1, 1), AI_STRIDE_INIT(4, 1, 128, 8192, 8192),
  1, &_Relu_1_output_0_weights_array, &_Relu_1_output_0_weights_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_1_output_0_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_Relu_1_output_0_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  output_QuantizeLinear_Input_weights, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 64, 10, 1, 1), AI_STRIDE_INIT(4, 1, 64, 640, 640),
  1, &output_QuantizeLinear_Input_weights_array, &output_QuantizeLinear_Input_weights_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  output_QuantizeLinear_Input_bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &output_QuantizeLinear_Input_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _Relu_output_0_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1424, 1, 1), AI_STRIDE_INIT(4, 2, 2, 2848, 2848),
  1, &_Relu_output_0_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 28, 28, 1), AI_STRIDE_INIT(4, 1, 1, 28, 784),
  1, &input_output_array, &input_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  input_output0, AI_STATIC,
  13, 0x1,
  AI_SHAPE_INIT(4, 1, 784, 1, 1), AI_STRIDE_INIT(4, 1, 1, 784, 784),
  1, &input_output_array, &input_output_array_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_QuantizeLinear_Input_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_QuantizeLinear_Input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &output_QuantizeLinear_Input_weights, &output_QuantizeLinear_Input_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_QuantizeLinear_Input_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  output_QuantizeLinear_Input_layer, 16,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &output_QuantizeLinear_Input_chain,
  NULL, &output_QuantizeLinear_Input_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Relu_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Relu_1_output_0_weights, &_Relu_1_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_1_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _Relu_1_output_0_layer, 13,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_Relu_1_output_0_chain,
  NULL, &output_QuantizeLinear_Input_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Relu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Relu_output_0_weights, &_Relu_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Relu_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _Relu_output_0_layer, 10,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_Relu_output_0_chain,
  NULL, &_Relu_1_output_0_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 109992, 1, 1),
    109992, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3760, 1, 1),
    3760, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output_QuantizeLinear_Input_output),
  &_Relu_output_0_layer, 0xdd8c5ad8, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 6,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 109992, 1, 1),
      109992, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3760, 1, 1),
      3760, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output_QuantizeLinear_Input_output),
  &_Relu_output_0_layer, 0xdd8c5ad8, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    _Relu_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Relu_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _Relu_1_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Relu_1_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    output_QuantizeLinear_Input_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    output_QuantizeLinear_Input_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    input_output_array.data = AI_PTR(g_network_activations_map[0] + 2848);
    input_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2848);
    _Relu_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3632);
    _Relu_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3632);
    _Relu_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2848);
    _Relu_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2848);
    output_QuantizeLinear_Input_output_array.data = AI_PTR(g_network_activations_map[0] + 2912);
    output_QuantizeLinear_Input_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2912);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 6, params)) {
    /* Updating weights (byte) offsets */
    
    _Relu_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _Relu_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    _Relu_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    _Relu_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _Relu_output_0_bias_array.data = AI_PTR(g_network_weights_map[1] + 0);
    _Relu_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[1] + 0);
    _Relu_1_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _Relu_1_output_0_weights_array.data = AI_PTR(g_network_weights_map[2] + 0);
    _Relu_1_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[2] + 0);
    _Relu_1_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _Relu_1_output_0_bias_array.data = AI_PTR(g_network_weights_map[3] + 0);
    _Relu_1_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[3] + 0);
    output_QuantizeLinear_Input_weights_array.format |= AI_FMT_FLAG_CONST;
    output_QuantizeLinear_Input_weights_array.data = AI_PTR(g_network_weights_map[4] + 0);
    output_QuantizeLinear_Input_weights_array.data_start = AI_PTR(g_network_weights_map[4] + 0);
    output_QuantizeLinear_Input_bias_array.format |= AI_FMT_FLAG_CONST;
    output_QuantizeLinear_Input_bias_array.data = AI_PTR(g_network_weights_map[5] + 0);
    output_QuantizeLinear_Input_bias_array.data_start = AI_PTR(g_network_weights_map[5] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 109386,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xdd8c5ad8,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 109386,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xdd8c5ad8,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

