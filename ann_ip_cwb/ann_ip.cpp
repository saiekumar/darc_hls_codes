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

		/* Cyber unroll_times = 1 */
		for (int i = 0; i <= ANN_LAYERS ; i = i+1) {				// i defines NN layers
			if(i == 0) {
				weight_offset = 0x0;
				bias_offset   = 0x0;
			}
			else {
			    weight_offset = weight_offset + NEURON_CNT(i-1) * NEURON_CNT(i);
			    bias_offset   = bias_offset + NEURON_CNT(i);
			}
			
			/* Cyber unroll_times = 1 */
			for (int j = 0; j < NEURON_CNT(i); j = j + 1) {		// j defines the input layer/previous layer inputs

				/* Cyber unroll_times = NUM_MACS */	
				for (int k = 0; k < NEURON_CNT(i+1); k = k + 1) {			// k defines the existing layer neurons or output neurons

					if (j == 0) {
						ann_act[i][k] = ann_biases[bias_offset + k];
					}

					weight_index = weight_offset + (j * NEURON_CNT(i+1)) + k;
					if(i == 0) {
						ann_act[0][k] = ann_act[0][k] + (ann_weights[weight_index] * pix_in[j]);
					} else {
						ann_act[i][k] = ann_act[i][k] + (ann_weights[weight_index] * ann_act[i-1][j]);
					}
					
					// activation applied on the last iteration
					if( j == (NEURON_CNT(i) - 1)) {

						if(i != ANN_LAYERS) { 
							//RELU ACTIVATION 
							ann_act[i][k] =  (ann_act[i][k] < 0) ? 0 : 1; 
						}
						else {
							softmax_sum = softmax_sum + exp(ann_act[ANN_LAYERS][k]);
						}
					}
					wait();
				}
				wait();
			}
			wait();
		}
		wait();

		max_p = 0;

		// SOFTMAX LAYER
		/* Cyber unroll_times = all */
		for (int i = 0; i < OUP_NEURONS ; i = i+1) {
			ann_act[ANN_LAYERS][i] = exp(ann_act[ANN_LAYERS][i])/softmax_sum;

		    if(ann_act[ANN_LAYERS][i] > max_p)
		    {
		    	max_p = ann_act[ANN_LAYERS][i];
		    	ann_oup = i; //output the index with highest probability
		    }
		}
		ann_out.write(ann_oup);
		ann_op_en.write(1);
		ann_processing_done = 0x1;

		wait();
	}		
}
