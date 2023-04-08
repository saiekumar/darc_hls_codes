#ifdef sim_cycle
	#include "dma_ctlr_C.h"
#else
	#include "dma_ctlr.h"
#endif

#include "tb_dma.h"

int sc_main(int argc, char** argv)
{
 	sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
 	sc_signal<bool>         rst;

 	sc_signal<sc_uint<1> >   	SA_CBM_busy;
 	sc_signal<sc_uint<1> >   	SA_CBM_error;
 	sc_signal<sc_uint<1> >   	SA_CBM_retry;
 	sc_signal<sc_uint<1> >   	SA_CBM_split;
 	sc_signal<sc_uint<16> >  	SA_CBM_read_data;
 	sc_signal<sc_uint<1> >  	SA_CBM_read_req;
 	sc_signal<sc_uint<1> >  	SA_CBM_write_req;
 	sc_signal<sc_uint<16> >  	SA_CBM_addr;
 	sc_signal<sc_uint<3> >  	SA_CBM_size;
 	sc_signal<sc_uint<16> >  	SA_CBM_write_data;
 	sc_signal<sc_uint<4> >  	SA_CBM_hmaster;

    sc_signal<sc_uint<1> >   	MA_CBM_read_req;
    sc_signal<sc_uint<1> >   	MA_CBM_write_req;
    sc_signal<sc_uint<3> >   	MA_CBM_burst;
    sc_signal<sc_uint<16> >   	MA_CBM_addr;
    sc_signal<sc_uint<11> >   	MA_CBM_length;
    sc_signal<sc_uint<3> >   	MA_CBM_size;
    sc_signal<sc_uint<1> >   	MA_CBM_lock;
    sc_signal<sc_uint<16> >   	MA_CBM_write_data;
    sc_signal<sc_uint<16> > 	MA_CBM_read_data;
    sc_signal<sc_uint<1> >  	MA_CBM_command_busy;
    sc_signal<sc_uint<1> >  	MA_CBM_data_ready;
    sc_signal<sc_uint<1> >  	MA_CBM_error;
    sc_signal<sc_uint<11> > 	MA_CBM_count;

    sc_signal<bool>   dma_intr;

    dma_ctlr u_dma("DMA*");
    tb_DMA u_tb("TB*");

   	u_dma.clk(clk);
   	u_dma.rst(rst);
   	u_dma.dma_intr(dma_intr);
   	u_dma.DMA_SA.CBM_addr(SA_CBM_addr);
   	u_dma.DMA_SA.CBM_read_req(SA_CBM_read_req);
   	u_dma.DMA_SA.CBM_write_req(SA_CBM_write_req);
   	u_dma.DMA_SA.CBM_size(SA_CBM_size);
   	u_dma.DMA_SA.CBM_write_data(SA_CBM_write_data);
   	u_dma.DMA_SA.CBM_error(SA_CBM_error);
	u_dma.DMA_SA.CBM_read_data(SA_CBM_read_data);
   	u_dma.DMA_SA.CBM_hmaster(SA_CBM_hmaster);
   	u_dma.DMA_SA.CBM_busy(SA_CBM_busy);
   	u_dma.DMA_SA.CBM_retry(SA_CBM_retry);
   	u_dma.DMA_SA.CBM_split(SA_CBM_split);

    u_dma.DMA_MA.CBM_read_req(MA_CBM_read_req);    	
    u_dma.DMA_MA.CBM_write_req(MA_CBM_write_req);
    u_dma.DMA_MA.CBM_burst(MA_CBM_burst);
    u_dma.DMA_MA.CBM_addr(MA_CBM_addr);
    u_dma.DMA_MA.CBM_length(MA_CBM_length);
    u_dma.DMA_MA.CBM_size(MA_CBM_size);
    u_dma.DMA_MA.CBM_lock(MA_CBM_lock);
    u_dma.DMA_MA.CBM_write_data(MA_CBM_write_data);
    u_dma.DMA_MA.CBM_read_data(MA_CBM_read_data);
    u_dma.DMA_MA.CBM_command_busy(MA_CBM_command_busy);
    u_dma.DMA_MA.CBM_data_ready(MA_CBM_data_ready);
    u_dma.DMA_MA.CBM_error(MA_CBM_error);
    u_dma.DMA_MA.CBM_count(MA_CBM_count);

   	u_tb.clk(clk);
   	u_tb.rst(rst);
   	u_tb.dma_intr(dma_intr);
   	u_tb.SA_CBM_addr(SA_CBM_addr);
   	u_tb.SA_CBM_read_req(SA_CBM_read_req);
   	u_tb.SA_CBM_write_req(SA_CBM_write_req);
   	u_tb.SA_CBM_size(SA_CBM_size);
   	u_tb.SA_CBM_write_data(SA_CBM_write_data);
   	u_tb.SA_CBM_error(SA_CBM_error);
	u_tb.SA_CBM_read_data(SA_CBM_read_data);
   	u_tb.SA_CBM_hmaster(SA_CBM_hmaster);
   	u_tb.SA_CBM_busy(SA_CBM_busy);
   	u_tb.SA_CBM_retry(SA_CBM_retry);
   	u_tb.SA_CBM_split(SA_CBM_split);

    u_tb.MA_CBM_read_req(MA_CBM_read_req);    	
    u_tb.MA_CBM_write_req(MA_CBM_write_req);
    u_tb.MA_CBM_burst(MA_CBM_burst);
    u_tb.MA_CBM_addr(MA_CBM_addr);
    u_tb.MA_CBM_length(MA_CBM_length);
    u_tb.MA_CBM_size(MA_CBM_size);
    u_tb.MA_CBM_lock(MA_CBM_lock);
    u_tb.MA_CBM_write_data(MA_CBM_write_data);
    u_tb.MA_CBM_read_data(MA_CBM_read_data);
    u_tb.MA_CBM_command_busy(MA_CBM_command_busy);
    u_tb.MA_CBM_data_ready(MA_CBM_data_ready);
    u_tb.MA_CBM_error(MA_CBM_error);
    u_tb.MA_CBM_count(MA_CBM_count);


#ifdef WAVE_DUMP
  	// Trace files
  	sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  	// Top level signals
  	sc_trace(trace_file, clk             		, "clk");
  	sc_trace(trace_file, rst             		, "rst"); 
   	sc_trace(trace_file, SA_CBM_addr		 	, "SA_CBM_addr");
    sc_trace(trace_file, SA_CBM_read_req		, "SA_CBM_read_req");
    sc_trace(trace_file, SA_CBM_write_req		, "SA_CBM_write_req");
    sc_trace(trace_file, SA_CBM_size		  	, "SA_CBM_size");
    sc_trace(trace_file, SA_CBM_write_data		, "SA_CBM_write_data");
    sc_trace(trace_file, SA_CBM_error		  	, "SA_CBM_error");
    sc_trace(trace_file, SA_CBM_read_data		, "SA_CBM_read_data");
    sc_trace(trace_file, SA_CBM_hmaster			, "SA_CBM_hmaster");
    sc_trace(trace_file, SA_CBM_busy		  	, "SA_CBM_busy");
    sc_trace(trace_file, SA_CBM_retry		  	, "SA_CBM_retry");
    sc_trace(trace_file, SA_CBM_split		  	, "SA_CBM_split");
    sc_trace(trace_file, MA_CBM_read_req		, "MA_CBM_read_req");
    sc_trace(trace_file, MA_CBM_write_req		, "MA_CBM_write_req");
    sc_trace(trace_file, MA_CBM_burst			, "MA_CBM_burst");
    sc_trace(trace_file, MA_CBM_addr			, "MA_CBM_addr");
    sc_trace(trace_file, MA_CBM_length			, "MA_CBM_length");
    sc_trace(trace_file, MA_CBM_size			, "MA_CBM_size");
    sc_trace(trace_file, MA_CBM_lock			, "MA_CBM_lock");
    sc_trace(trace_file, MA_CBM_write_data		, "MA_CBM_write_data");
    sc_trace(trace_file, MA_CBM_read_data		, "MA_CBM_read_data");
    sc_trace(trace_file, MA_CBM_command_busy	, "MA_CBM_command_busy");
    sc_trace(trace_file, MA_CBM_data_ready		, "MA_CBM_data_ready");
    sc_trace(trace_file, MA_CBM_error			, "MA_CBM_error");
    sc_trace(trace_file, MA_CBM_count			, "MA_CBM_count");
   	sc_trace(trace_file, dma_intr		  		, "dma_intr");
#endif  // End WAVE_DUMP

  	sc_start( 25, SC_NS );
  	rst.write(0);

  	sc_start( 25, SC_NS );
  	rst.write(1);

  	sc_start();

#ifdef WAVE_DUMP
   	sc_close_vcd_trace_file(trace_file);
#endif

 	return 0;
};
