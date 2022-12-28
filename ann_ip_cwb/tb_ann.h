
#include "define.h"


#ifndef TB_ANN_H_
#define TB_ANN_H_

SC_MODULE (tb_ANN){

  // Inputs
  sc_in<bool>          	clk;
  sc_in<bool>          	rst;

  //  Data in
  sc_out< sc_fixed<32,8> >		data_in;
  sc_out< bool >				pix_en;
  sc_out< bool >				cfg_en;

  // Inputs
  sc_in< sc_uint<OUP_NEURONS> >  ann_out;
  sc_in< bool >					 ann_op_en;


//void send_configs();
  void send_images();


  SC_CTOR ( tb_ANN ) {
 
//  SC_CTHREAD(send_configs,clk.pos());
//  reset_signal_is(rst,false);

    SC_CTHREAD(send_images,clk.pos());
    reset_signal_is(rst,false);
  }

  ~tb_ANN(){}

};


#endif  // TB_ANN_H
