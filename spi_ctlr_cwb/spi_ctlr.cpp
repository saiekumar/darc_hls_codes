#include "spi_ctlr.h"


void spi_ctlr::spi_clock_gen() {
	bool clk_polarity;

	spi_clk.write(0x0);
	clk_polarity = 0x0;

	wait();

	while(true) {
		if(spi_cs.read() == 0) {
			clk_polarity = ~clk_polarity;
			spi_clk.write(clk_polarity);
			wait();
		}
		else {
			spi_clk.write(0x0);
			wait();
		}
	}
}


void spi_ctlr::spi_trans() {

	sc_uint<8> 	spi_cmd;
	sc_uint<16> spi_addr;
	sc_uint<32> spi_data;
	sc_uint<16> i;

    /* checks the AHB slave transacions & reads/writes to config registers */
    CBM_Req_Stat<> stat;

    
/*	<reset condition>	*/
	spi_cmd  = SPI_READ_COMMAND;
	spi_addr = 0x0;
	spi_data = 0x0;

	spi_cs.write(0x1);
	spi_mosi0.write(0x0);
	spi_mosi1.write(0x0);
	spi_mosi2.write(0x0);
	spi_mosi3.write(0x0);


    wait();

    SPI_SA.poll_req(&stat);    /* get status */


    while(true){

        if (stat.req == CBM_READ_REQ) {
			SPI_SA.set_response(CBM_BUSY);
			spi_addr = stat.addr.range(15,0);
			
			spi_cs.write(0x0);
			wait();

			/* transmitting SPI command */
			for( i = 8; i > 0; i = i - 1) {
				spi_mosi0.write(spi_cmd[i-1]);
				spi_mosi1.write(0x0);
				spi_mosi2.write(0x0);
				spi_mosi3.write(0x0);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
			}

			/* transmitting SPI addr */
			for( i = 16; i > 0; i = i - 4) {
				spi_mosi3.write(spi_addr[i-1]);
				spi_mosi2.write(spi_addr[i-2]);
				spi_mosi1.write(spi_addr[i-3]);
				spi_mosi0.write(spi_addr[i-4]);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
			}

			/* one Dummy Cycle */
			SPI_SA.set_response(CBM_BUSY);
			wait(1);
			SPI_SA.set_response(CBM_BUSY);
			wait(1);

			/* receiving the SPI data */
			for( i = 32; i > 0; i = i - 4) {
				spi_data[i-1] = spi_miso3.read();
				spi_data[i-2] = spi_miso2.read();
				spi_data[i-3] = spi_miso1.read();
				spi_data[i-4] = spi_miso0.read();
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);			
			}

			spi_cs.write(0x1);
       		SPI_SA.put_data(spi_data);
			SPI_SA.set_response(CBM_OKAY);
			wait();
   		}

        else if (stat.req == CBM_WRITE_REQ) {
			SPI_SA.set_response(CBM_BUSY);
			spi_addr = stat.addr.range(15,0);
			spi_data = SPI_SA.get_data();
			
			spi_cs.write(0x0);
			wait();

			/* transmitting SPI command */
			for( i = 8; i > 0; i = i - 1) {
				spi_mosi0.write(spi_cmd[i-1]);
				spi_mosi1.write(0x0);
				spi_mosi2.write(0x0);
				spi_mosi3.write(0x0);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
			}

			/* transmitting SPI addr */
			for( i = 16; i > 0; i = i - 4) {
				spi_mosi3.write(spi_addr[i-1]);
				spi_mosi2.write(spi_addr[i-2]);
				spi_mosi1.write(spi_addr[i-3]);
				spi_mosi0.write(spi_addr[i-4]);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
			}

			/* one Dummy Cycle */
			SPI_SA.set_response(CBM_BUSY);
			wait(1);
			SPI_SA.set_response(CBM_BUSY);
			wait(1);

			/* transmitting the SPI data */
			for( i = 32; i > 0; i = i - 4) {
				spi_mosi3.write(spi_data[i-1]);
				spi_mosi2.write(spi_data[i-2]);
				spi_mosi1.write(spi_data[i-3]);
				spi_mosi0.write(spi_data[i-4]);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
				SPI_SA.set_response(CBM_BUSY);
				wait(1);
			}

			spi_cs.write(0x1);
			SPI_SA.set_response(CBM_OKAY);
			wait();
       	}
		else {
			wait();
			SPI_SA.poll_req(&stat); /* get status */
		}
	}
}
