#ifdef sim_cycle
	#include "spi_ctlr_C.h"
#else
	#include "spi_ctlr.h"
#endif

#include "tb_spi.h"

int sc_main(int argc, char** argv)
{
 	sc_clock               		clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
 	sc_signal<bool>        		rst;

 	sc_signal<sc_uint<1> >   	SPI_SA_CBM_busy;
 	sc_signal<sc_uint<1> >   	SPI_SA_CBM_error;
 	sc_signal<sc_uint<1> >   	SPI_SA_CBM_retry;
 	sc_signal<sc_uint<1> >   	SPI_SA_CBM_split;
 	sc_signal<sc_uint<16> >  	SPI_SA_CBM_read_data;
 	sc_signal<sc_uint<1> >  	SPI_SA_CBM_read_req;
 	sc_signal<sc_uint<1> >  	SPI_SA_CBM_write_req;
 	sc_signal<sc_uint<16> >  	SPI_SA_CBM_addr;
 	sc_signal<sc_uint<3> >  	SPI_SA_CBM_size;
 	sc_signal<sc_uint<16> >  	SPI_SA_CBM_write_data;
 	sc_signal<sc_uint<4> >  	SPI_SA_CBM_hmaster;

	sc_signal<bool>				spi_clk;
	sc_signal<bool>				spi_cs;
	sc_signal<bool>				spi_mosi0;
	sc_signal<bool>				spi_mosi1;
	sc_signal<bool>				spi_mosi2;
	sc_signal<bool>				spi_mosi3;
	sc_signal<bool>				spi_miso0;
	sc_signal<bool>				spi_miso1;
	sc_signal<bool>				spi_miso2;
	sc_signal<bool>				spi_miso3;


    spi_ctlr u_spi("SPI*");
    tb_SPI u_tb("TB*");

   	u_spi.clk(clk);
   	u_spi.rst(rst);
   	u_spi.SPI_SA.CBM_addr(SPI_SA_CBM_addr);
   	u_spi.SPI_SA.CBM_read_req(SPI_SA_CBM_read_req);
   	u_spi.SPI_SA.CBM_write_req(SPI_SA_CBM_write_req);
   	u_spi.SPI_SA.CBM_size(SPI_SA_CBM_size);
   	u_spi.SPI_SA.CBM_write_data(SPI_SA_CBM_write_data);
   	u_spi.SPI_SA.CBM_error(SPI_SA_CBM_error);
	u_spi.SPI_SA.CBM_read_data(SPI_SA_CBM_read_data);
   	u_spi.SPI_SA.CBM_hmaster(SPI_SA_CBM_hmaster);
   	u_spi.SPI_SA.CBM_busy(SPI_SA_CBM_busy);
   	u_spi.SPI_SA.CBM_retry(SPI_SA_CBM_retry);
   	u_spi.SPI_SA.CBM_split(SPI_SA_CBM_split);

	u_spi.spi_clk(spi_clk);
	u_spi.spi_cs(spi_cs);
	u_spi.spi_mosi0(spi_mosi0);
	u_spi.spi_mosi1(spi_mosi1);
	u_spi.spi_mosi2(spi_mosi2);
	u_spi.spi_mosi3(spi_mosi3);
	u_spi.spi_miso0(spi_miso0);
	u_spi.spi_miso1(spi_miso1);
	u_spi.spi_miso2(spi_miso2);
	u_spi.spi_miso3(spi_miso3);

   	u_tb.clk(clk);
   	u_tb.rst(rst);
   	u_tb.SPI_SA_CBM_addr(SPI_SA_CBM_addr);
   	u_tb.SPI_SA_CBM_read_req(SPI_SA_CBM_read_req);
   	u_tb.SPI_SA_CBM_write_req(SPI_SA_CBM_write_req);
   	u_tb.SPI_SA_CBM_size(SPI_SA_CBM_size);
   	u_tb.SPI_SA_CBM_write_data(SPI_SA_CBM_write_data);
   	u_tb.SPI_SA_CBM_error(SPI_SA_CBM_error);
	u_tb.SPI_SA_CBM_read_data(SPI_SA_CBM_read_data);
   	u_tb.SPI_SA_CBM_hmaster(SPI_SA_CBM_hmaster);
   	u_tb.SPI_SA_CBM_busy(SPI_SA_CBM_busy);
   	u_tb.SPI_SA_CBM_retry(SPI_SA_CBM_retry);
   	u_tb.SPI_SA_CBM_split(SPI_SA_CBM_split);

	u_tb.spi_clk(spi_clk);
	u_tb.spi_cs(spi_cs);
	u_tb.spi_mosi0(spi_mosi0);
	u_tb.spi_mosi1(spi_mosi1);
	u_tb.spi_mosi2(spi_mosi2);
	u_tb.spi_mosi3(spi_mosi3);
	u_tb.spi_miso0(spi_miso0);
	u_tb.spi_miso1(spi_miso1);
	u_tb.spi_miso2(spi_miso2);
	u_tb.spi_miso3(spi_miso3);


#ifdef WAVE_DUMP
  	// Trace files
  	sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  	// Top level signals
  	sc_trace(trace_file, clk             		, "clk");
  	sc_trace(trace_file, rst             		, "rst"); 
   	sc_trace(trace_file, SPI_SA_CBM_addr		, "SPI_SA_CBM_addr");
    sc_trace(trace_file, SPI_SA_CBM_read_req	, "SPI_SA_CBM_read_req");
    sc_trace(trace_file, SPI_SA_CBM_write_req	, "SPI_SA_CBM_write_req");
    sc_trace(trace_file, SPI_SA_CBM_size		, "SPI_SA_CBM_size");
    sc_trace(trace_file, SPI_SA_CBM_write_data	, "SPI_SA_CBM_write_data");
    sc_trace(trace_file, SPI_SA_CBM_error		, "SPI_SA_CBM_error");
    sc_trace(trace_file, SPI_SA_CBM_read_data	, "SPI_SA_CBM_read_data");
    sc_trace(trace_file, SPI_SA_CBM_hmaster		, "SPI_SA_CBM_hmaster");
    sc_trace(trace_file, SPI_SA_CBM_busy		, "SPI_SA_CBM_busy");
    sc_trace(trace_file, SPI_SA_CBM_retry		, "SPI_SA_CBM_retry");
    sc_trace(trace_file, SPI_SA_CBM_split		, "SPI_SA_CBM_split");
	sc_trace(trace_file, spi_clk				, "spi_clk");
	sc_trace(trace_file, spi_cs					, "spi_cs");
	sc_trace(trace_file, spi_mosi0				, "spi_mosi0");
	sc_trace(trace_file, spi_mosi1				, "spi_mosi1");
	sc_trace(trace_file, spi_mosi2				, "spi_mosi2");
	sc_trace(trace_file, spi_mosi3				, "spi_mosi3");
	sc_trace(trace_file, spi_miso0				, "spi_miso0");
	sc_trace(trace_file, spi_miso1				, "spi_miso1");
	sc_trace(trace_file, spi_miso2				, "spi_miso2");
	sc_trace(trace_file, spi_miso3				, "spi_miso3");
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
