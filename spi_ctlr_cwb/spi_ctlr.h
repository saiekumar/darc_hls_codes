#ifndef SPI_CTLR_H_
#define SPI_CTLR_H_


#include "define_spi.h"


SC_MODULE (spi_ctlr) {

    // Inputs
    sc_in_clk 			clk;
    sc_in<bool> 		rst;

    // AHB bus slave interfaces
    ahb_slave_if<>  	SPI_SA;

	// SPI interface signals
	sc_out<bool>	spi_clk;
	sc_out<bool>	spi_cs;
	sc_out<bool>	spi_mosi0;
	sc_out<bool>	spi_mosi1;
	sc_out<bool>	spi_mosi2;
	sc_out<bool>	spi_mosi3;
	sc_in<bool>		spi_miso0;
	sc_in<bool>		spi_miso1;
	sc_in<bool>		spi_miso2;
	sc_in<bool>		spi_miso3;

    
    /* Global variables */
    

    /* methods */
	void spi_trans ( void );
	void spi_clock_gen ( void );

    // Constructor
    SC_CTOR (spi_ctlr) {
        SC_CTHREAD (spi_trans, clk.pos() );
        reset_signal_is(rst, false) ;

        SC_CTHREAD (spi_clock_gen, clk.pos() );
        reset_signal_is(rst, false) ;
    }

    // Destructor
    ~spi_ctlr() {}
};

#endif   //  SPI_CTLR_H_

