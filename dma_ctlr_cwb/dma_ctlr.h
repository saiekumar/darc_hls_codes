#ifndef DMA_CTLR_H_
#define DMA_CTLR_H_


#include "define_dma.h"


SC_MODULE (dma_ctlr) {

    // Inputs
    sc_in_clk clk;
    sc_in<bool> rst;

    // AHB bus slave interfaces
    ahb_slave_if<>  SA;

    // AHB bus slave interfaces
    ahb_master_if<> MA;

    // Output
    sc_out<bool> dma_intr;

    
    /* Global variables */
    sc_uint<16>   dma_chan_src_addr[DMA_CHAN];
    sc_uint<16>   dma_chan_dest_addr[DMA_CHAN];
    sc_uint<16>   dma_chan_transfer_len[DMA_CHAN];        /* transfer length : maximum 16KB */
    sc_uint<2>    dma_chan_burst[DMA_CHAN];               /* 2'b00 - single transfer;  2'b01 - Incr4;  2'b10 - Incr8;  2'b11 - Incr16 */
    sc_uint<2>    dma_chan_qos[DMA_CHAN];                 /* 2'b00 - Disabled;  2'b01 - Highest priority;  2'b11 - Lowest Priority */
    sc_uint<1>    dma_chan_prog[DMA_CHAN];                /* 1'b0 - channel not programmed */

    sc_uint<16>   dma_intr_mask;
    sc_uint<16>   dma_intr_clear;
    sc_uint<16>   dma_intr_status;                        /* each bit specifies a channel */
    

    /* methods */
    void dma_cfg_regs ( void ) ;
	void dma_trans ( void );


    // Constructor
    SC_CTOR (dma_ctlr) {
        SC_CTHREAD (dma_cfg_regs, clk.pos() );
        reset_signal_is(rst, false) ;

        SC_CTHREAD (dma_trans, clk.pos() );
        reset_signal_is(rst, false) ;
    }

    // Destructor
    ~dma_ctlr() {}
};

#endif   //  DMA_CTLR_H_

