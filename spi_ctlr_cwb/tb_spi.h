
#include "define.h"


#ifndef TB_SPI_H_
#define TB_SPI_H_

SC_MODULE (tb_SPI){

 	// Inputs
 	sc_in<bool>          	clk;
 	sc_in<bool>          	rst;

 	// AHB bus master interfaces
 	sc_in<sc_uint<1> >   	SPI_SA_CBM_busy;
 	sc_in<sc_uint<1> >   	SPI_SA_CBM_error;
 	sc_in<sc_uint<1> >   	SPI_SA_CBM_retry;
 	sc_in<sc_uint<1> >   	SPI_SA_CBM_split;
 	sc_in<sc_uint<16> >  	SPI_SA_CBM_read_data;
 	sc_out<sc_uint<1> >  	SPI_SA_CBM_read_req;
 	sc_out<sc_uint<1> >  	SPI_SA_CBM_write_req;
 	sc_out<sc_uint<16> >  	SPI_SA_CBM_addr;
 	sc_out<sc_uint<3> >  	SPI_SA_CBM_size;
 	sc_out<sc_uint<16> >  	SPI_SA_CBM_write_data;
 	sc_out<sc_uint<4> >  	SPI_SA_CBM_hmaster;

	// SPI interface signals
	sc_in<bool>				spi_clk;
	sc_in<bool>				spi_cs;
	sc_in<bool>				spi_mosi0;
	sc_in<bool>				spi_mosi1;
	sc_in<bool>				spi_mosi2;
	sc_in<bool>				spi_mosi3;
	sc_out<bool>			spi_miso0;
	sc_out<bool>			spi_miso1;
	sc_out<bool>			spi_miso2;
	sc_out<bool>			spi_miso3;


  	void send_spi_data();


  	SC_CTOR ( tb_SPI ) {
    	SC_CTHREAD(send_spi_data,clk.pos());
    	reset_signal_is(rst,false);
  	}

  	~tb_SPI(){}

};


#endif  // TB_SPI_H
