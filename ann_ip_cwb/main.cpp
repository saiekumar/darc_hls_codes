#ifdef sim_cycle
	#include "ann_ip_C.h"
#else
	#include "ann_ip.h"
#endif

#include "tb_ann.h"

int sc_main(int argc, char** argv)
{
 	sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
 	sc_signal<bool>         rst;

 	sc_signal<bool>  				pix_en;
 	sc_signal<bool>  				cfg_en;
 	sc_signal< sc_fixed<32,8> > 	data_in;

    sc_signal< sc_uint<OUP_NEURONS> >  ann_out;
    sc_signal< bool >				   ann_op_en;

    ann_ip u_ann("ANN*");
    tb_ANN u_tb("TB*");

   	u_ann.clk(clk);
   	u_ann.rst(rst);
   	u_ann.ann_out(ann_out);
   	u_ann.ann_op_en(ann_op_en);
   	u_ann.cfg_en(cfg_en);
   	u_ann.pix_en(pix_en);
   	u_ann.data_in(data_in);

   	u_tb.clk(clk);
   	u_tb.rst(rst);
   	u_tb.ann_out(ann_out);
   	u_tb.ann_op_en(ann_op_en);
   	u_tb.cfg_en(cfg_en);
   	u_tb.pix_en(pix_en);
   	u_tb.data_in(data_in);


#ifdef WAVE_DUMP
  	// Trace files
  	sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  	// Top level signals
  	sc_trace(trace_file, u_ann.clk             		, "clk");
  	sc_trace(trace_file, u_ann.rst             		, "rst"); 
   	sc_trace(trace_file, u_ann.cfg_en	 			, "cfg_en");
   	sc_trace(trace_file, u_ann.pix_en	  			, "pix_en");
   	sc_trace(trace_file, u_ann.data_in		  		, "data_in");
   	sc_trace(trace_file, u_ann.ann_out		  		, "ann_out");
   	sc_trace(trace_file, u_ann.ann_op_en			, "ann_op_en");
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
