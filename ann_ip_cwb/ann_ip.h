#ifndef ANN_IP_H_
#define ANN_IP_H_


#include "define.h"


SC_MODULE (ann_ip) {

    // Inputs
    sc_in_clk 		clk;
    sc_in<bool> 	rst;


	//  Data in
	sc_in< sc_uint<32> >  			data_in;
	sc_in< bool >					pix_en;
	sc_in< bool >					cfg_en;

    // Output
	sc_out< sc_uint<OUP_NEURONS> >  ann_out;
	sc_out< bool >					ann_op_en;

	float 							ann_weights[ANN_WEIGHTS] 		            /* Cyber array = RAM, immediate_access = RW, packed */;
	float 							ann_biases[ANN_BIASES] 			            /* Cyber array = RAM, immediate_access = RW, packed */;

    sc_uint< 8 > 					pix_in[INP_NEURONS] 						/* Cyber array = RAM, immediate_access = RW, packed */;

	sc_uint < 1 >					ann_configure_done;
    sc_uint < 1 >                   pix_loading_done;
    sc_uint < 1 >                   ann_processing_done;
	sc_uint < 16 >					pix_cnt;

    /* methods */
    void ann_load ( void ) ;
	void ann_activate ( void );


    // Constructor
    SC_CTOR (ann_ip) {
        SC_CTHREAD (ann_load, clk.pos() );
        reset_signal_is(rst, false) ;

        SC_CTHREAD (ann_activate, clk.pos() );
        reset_signal_is(rst, false) ;
    }
};

#endif   //  ANN_IP_H_

