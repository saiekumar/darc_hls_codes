
#include "define_ann_ip.h"


#ifndef TB_ANN_H_
#define TB_ANN_H_

SC_MODULE (tb_ANN){

  // Inputs
  sc_in<bool>          	clk;
  sc_in<bool>          	rst;

  //  Data in
  sc_out< sc_fixed<32,8> >		data_in;
  sc_out< bool >				pix_en;
  //sc_out< bool >				cfg_en;

  // AHB bus master interfaces
  sc_in<sc_uint<1> >    SA_CBM_busy;
  sc_in<sc_uint<1> >    SA_CBM_error;
  sc_in<sc_uint<1> >    SA_CBM_retry;
  sc_in<sc_uint<1> >    SA_CBM_split;
  sc_in<sc_uint<32> >   SA_CBM_read_data;
  sc_out<sc_uint<1> >  	SA_CBM_read_req;
  sc_out<sc_uint<1> >  	SA_CBM_write_req;
  sc_out<sc_uint<16> >  SA_CBM_addr;
  sc_out<sc_uint<3> >  	SA_CBM_size;
  sc_out<sc_uint<32> >  SA_CBM_write_data;
  sc_out<sc_uint<4> >  	SA_CBM_hmaster;

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
