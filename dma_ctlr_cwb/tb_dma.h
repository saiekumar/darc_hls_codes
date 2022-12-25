
#include "define.h"


#ifndef TB_DMA_H_
#define TB_DMA_H_

SC_MODULE (tb_DMA){

  // Inputs
  sc_in<bool>          	clk;
  sc_in<bool>          	rst;

  // AHB bus master interfaces
  sc_in<sc_uint<1> >    SA_CBM_busy;
  sc_in<sc_uint<1> >    SA_CBM_error;
  sc_in<sc_uint<1> >    SA_CBM_retry;
  sc_in<sc_uint<1> >    SA_CBM_split;
  sc_in<sc_uint<16> >   SA_CBM_read_data;
  sc_out<sc_uint<1> >  	SA_CBM_read_req;
  sc_out<sc_uint<1> >  	SA_CBM_write_req;
  sc_out<sc_uint<16> >  SA_CBM_addr;
  sc_out<sc_uint<3> >  	SA_CBM_size;
  sc_out<sc_uint<16> >  SA_CBM_write_data;
  sc_out<sc_uint<4> >  	SA_CBM_hmaster;

  sc_in<sc_uint<1> >   	MA_CBM_read_req;
  sc_in<sc_uint<1> >   	MA_CBM_write_req;
  sc_in<sc_uint<3> >   	MA_CBM_burst;
  sc_in<sc_uint<16> >   MA_CBM_addr;
  sc_in<sc_uint<11> >   MA_CBM_length;
  sc_in<sc_uint<3> >   	MA_CBM_size;
  sc_in<sc_uint<1> >   	MA_CBM_lock;
  sc_in<sc_uint<16> >   MA_CBM_write_data;
  sc_out<sc_uint<16> >  MA_CBM_read_data;
  sc_out<sc_uint<1> >   MA_CBM_command_busy;
  sc_out<sc_uint<1> >   MA_CBM_data_ready;
  sc_out<sc_uint<1> >   MA_CBM_error;
  sc_out<sc_uint<11> >  MA_CBM_count;

  sc_in<bool> dma_intr;


  void send_cfg_trans();
  void rcv_dma_trans();


  SC_CTOR ( tb_DMA ) {
 
    SC_CTHREAD(send_cfg_trans,clk.pos());
    reset_signal_is(rst,false);

    SC_CTHREAD(rcv_dma_trans,clk.pos());
    reset_signal_is(rst,false);
  }

  ~tb_DMA(){}

};


#endif  // TB_DMA_H
