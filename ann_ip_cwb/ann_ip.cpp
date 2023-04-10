#include "ann_ip.h"


void ann_ip::ann_load() {

	int weight_cnt 	= 0x0;
	int bias_cnt	= 0x0;
    CBM_Req_Stat<> 	ann_stat;
	
	ann_configure_done = 0x0;
	pix_loading_done = 0x0;
	pix_cnt	= 0x0;
	#include "weights.h"
	#include "biases.h"

	wait();
    
	
	while(true) {

		ANN_SA.poll_req(&ann_stat);

		// Loading the weights
		if((weight_cnt == ANN_WEIGHTS) & (bias_cnt == ANN_BIASES)) {
			ann_configure_done = 0x1;
			bias_cnt = 0x0;
			weight_cnt = 0x0;
		}
		
		if(pix_cnt == INP_NEURONS) {
			pix_loading_done = 0x1;
			pix_cnt = 0x0;
		}

		if(ann_processing_done == 0x1) {
			pix_loading_done = 0x0;
		}
		
		
        //if (cfg_en) {
        if ((ann_stat.req == CBM_WRITE_REQ) & (ann_stat.addr.range(15,0) == 0x4200)) {
         	ANN_SA.set_response(CBM_OKAY);
   
			if (weight_cnt == ANN_WEIGHTS) {
				//ann_biases[bias_cnt] = cwb::data2float(data_in.read());
				//ann_biases[bias_cnt] = data_in.read();
				ann_biases[bias_cnt]   = ANN_SA.get_data();
				bias_cnt = bias_cnt + 0x1;
			}
			else {
				//ann_weights[weight_cnt] = cwb::data2float(data_in.read());
				//ann_weights[weight_cnt] = data_in.read();
				ann_weights[weight_cnt]   = ANN_SA.get_data();
				weight_cnt = weight_cnt + 0x1;
			}
		}

		// Load the pixels
        else if (pix_en) {
        //else if ((ann_stat.req == CBM_WRITE_REQ) & (ann_stat.addr.range(15,0) == 0x4400)) {
        	//ANN_SA.set_response(CBM_OKAY);
			
			//pix_in[pix_cnt] = ANN_SA.get_data();
			pix_in[pix_cnt] = (double)data_in.read();
			pix_cnt = pix_cnt + 1;
			pix_loading_done = 0x0;
		}

		wait();
		
	}
}



void ann_ip::ann_activate() {

	int 	weight_index  	= 0x0;
	int 	bias_offset   	= 0x0;
	int 	weight_offset 	= 0x0;
	int 	ann_oup			= 0x0;

	double 	softmax_sum 	= 0;
	double 	max_p 			= 0;
    double  ann_act[ANN_TOTAL_LAYERS][MAX_NEURONS];

	for (int i = 0; i < OUP_NEURONS; i = i + 1) {
		ann_out.write(0);
	}
	ann_op_en.write(0);
	ann_processing_done = 0x0;
 
	wait();


	while(true) {

		if(pix_loading_done == 0x0) {

			ann_op_en.write(0);
			ann_processing_done = 0x0;
			ann_oup = 0x0;
			wait();
			continue;
		}


		// ---------- Layer-1 computation -------------
		
		weight_offset = 0x0;
		bias_offset   = 0x0;

		for (int k = 0; k < L1_NEURONS; k = k + 1) {
			ann_act[0][k] = ann_biases[bias_offset + k];
		}
		
		/* Cyber unroll_times = 1 */
		for (int j = 0; j < INP_NEURONS; j = j + 1) {				// Layer-0 (input layer)
		
			/* Cyber unroll_times = all */	
			for (int k = 0; k < L1_NEURONS; k = k + 1) {			// Layer-1 loop
				weight_index = weight_offset + (j * L1_NEURONS) + k;
				ann_act[0][k] = ann_act[0][k] + (ann_weights[weight_index] * pix_in[j]);
			}
		}
		
		/* Cyber unroll_times = all */
		for (int k = 0; k < L1_NEURONS; k = k + 1) {
			ann_act[0][k] =  (ann_act[0][k] < 0) ? 0 : 1; 
		}
		wait();
		

		// ---------- Layer-2 computation -------------

		weight_offset = weight_offset + INP_NEURONS * L1_NEURONS;
		bias_offset   = bias_offset + L1_NEURONS;

		for (int k = 0; k < L2_NEURONS; k = k + 1) {
			ann_act[1][k] = ann_biases[bias_offset + k];
		}

		/* Cyber unroll_times = 1 */
		for (int j = 0; j < L1_NEURONS; j = j + 1) {				// Layer-1 (input layer)
		
			/* Cyber unroll_times = all */	
			for (int k = 0; k < L2_NEURONS; k = k + 1) {			// Layer-2 loop
				weight_index = weight_offset + (j * L2_NEURONS) + k;
				ann_act[1][k] = ann_act[1][k] + (ann_weights[weight_index] * ann_act[0][j]);
			}
		}

		/* Cyber unroll_times = all */
		for (int k = 0; k < L2_NEURONS; k = k + 1) {
			ann_act[1][k] =  (ann_act[1][k] < 0) ? 0 : 1; 
		}
		wait();



		// ---------- Layer-3 (output) computation -------------
		weight_offset = weight_offset + L1_NEURONS * L2_NEURONS;
		bias_offset   = bias_offset + L2_NEURONS;

		for (int k = 0; k < OUP_NEURONS; k = k + 1) {
			ann_act[2][k] = ann_biases[bias_offset + k];
		}

		/* Cyber unroll_times = 1 */
		for (int j = 0; j < L2_NEURONS; j = j + 1) {				// Layer-2 (input layer)
		
			/* Cyber unroll_times = all */	
			for (int k = 0; k < OUP_NEURONS; k = k + 1) {			// Layer-3 loop
				weight_index = weight_offset + (j * OUP_NEURONS) + k;
				ann_act[2][k] = ann_act[2][k] + (ann_weights[weight_index] * ann_act[1][j]);
			}
		}

		/* Cyber unroll_times = all */
		for (int k = 0; k < OUP_NEURONS; k = k + 1) {
			softmax_sum = softmax_sum + exp(ann_act[2][k]);
		}
		wait();


			
		// SOFTMAX LAYER
		max_p = 0;

		/* Cyber unroll_times = all */
		for (int i = 0; i < OUP_NEURONS ; i = i+1) {
			ann_act[2][i] = exp(ann_act[2][i])/softmax_sum;

		    if(ann_act[2][i] > max_p)
		    {
		    	max_p = ann_act[2][i];
		    	ann_oup = i; //output the index with highest probability
		    }
		}
		ann_out.write(ann_oup);
		ann_op_en.write(1);
		ann_processing_done = 0x1;

		wait();
	}		
}
