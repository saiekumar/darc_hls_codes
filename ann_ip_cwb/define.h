#ifndef DEFINE_ANN_IP_H
#define DEFINE_ANN_IP_H

	#define SC_INCLUDE_FX
	#define SC_FX_EXCLUDE_OTHER
	
    #include "/home/sai/Downloads/systemc-2.3.3/include/systemc.h"
    #include "stdio.h"
	#include "math.h"

	
	#define ANN_LAYERS			2		/* input layer & output layer are not accounted */

	#define INP_NEURONS			784
	#define OUP_NEURONS			10		
    #define L1_NEURONS_DEF		16
	#define L2_NEURONS_DEF		16
	#define L3_NEURONS_DEF		16
	#define L4_NEURONS_DEF		16
	#define L5_NEURONS_DEF		16
	#define MAX_NEURONS			16

	#define NUM_MACS			8

	#if ANN_LAYERS == 1
		#define ANN_TOTAL_LAYERS	2
		#define L1_NEURONS			L1_NEURONS_DEF
		#define L2_NEURONS			OUP_NEURONS
    	#define ANN_WEIGHTS			(INP_NEURONS * L1_NEURONS) + (L1_NEURONS * OUP_NEURONS)
		#define ANN_BIASES			L1_NEURONS + OUP_NEURONS
		#define L3_NEURONS			0
		#define L4_NEURONS			0
		#define L5_NEURONS			0
	#elif ANN_LAYERS == 2
		#define ANN_TOTAL_LAYERS	3
		#define L1_NEURONS			L1_NEURONS_DEF
		#define L2_NEURONS			L2_NEURONS_DEF
		#define L3_NEURONS			OUP_NEURONS
		#define ANN_WEIGHTS			(INP_NEURONS * L1_NEURONS) + (L1_NEURONS * L2_NEURONS) + (L2_NEURONS * OUP_NEURONS)
		#define ANN_BIASES			L1_NEURONS + L2_NEURONS + OUP_NEURONS
		#define L4_NEURONS			0
		#define L5_NEURONS			0
	#elif ANN_LAYERS == 3
		#define ANN_TOTAL_LAYERS	4
		#define L1_NEURONS			L1_NEURONS_DEF
		#define L2_NEURONS			L2_NEURONS_DEF
		#define L3_NEURONS			L3_NEURONS_DEF
		#define L4_NEURONS			OUP_NEURONS
		#define ANN_WEIGHTS			(INP_NEURONS * L1_NEURONS) + (L1_NEURONS * L2_NEURONS) + (L2_NEURONS * L3_NEURONS) + (L3_NEURONS * OUP_NEURONS)
		#define ANN_BIASES			L1_NEURONS + L2_NEURONS + L3_NEURONS + OUP_NEURONS
		#define L5_NEURONS			0
	#elif ANN_LAYERS == 4
		#define ANN_TOTAL_LAYERS	5
		#define L1_NEURONS			L1_NEURONS_DEF
		#define L2_NEURONS			L2_NEURONS_DEF
		#define L3_NEURONS			L3_NEURONS_DEF
		#define L4_NEURONS			L4_NEURONS_DEF
		#define L5_NEURONS			OUP_NEURONS
		#define ANN_WEIGHTS			(INP_NEURONS * L1_NEURONS) + (L1_NEURONS * L2_NEURONS) + (L2_NEURONS * L3_NEURONS) + (L3_NEURONS * L4_NEURONS) + (L4_NEURONS * OUP_NEURONS)
		#define ANN_BIASES			L1_NEURONS + L2_NEURONS + L3_NEURONS + L4_NEURONS + OUP_NEURONS
	#endif

	
	#define NEURON_CNT(X)	(((X) == 0) ? INP_NEURONS : ((X) == 1) ? L1_NEURONS : ((X) == 2) ? L2_NEURONS : ((X) == 3) ? L3_NEURONS : ((X) == 4) ? L4_NEURONS : L5_NEURONS)

	
#endif
