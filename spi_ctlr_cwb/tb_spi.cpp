#include "tb_spi.h"


//--------------------------
// Send SPI data thread
//--------------------------
void tb_SPI::send_spi_data(){
	bool sa_busy;

	SPI_SA_CBM_read_req.write(0x0);
	SPI_SA_CBM_write_req.write(0x0);
	SPI_SA_CBM_addr.write(0x0);
	SPI_SA_CBM_size.write(0x0);
	SPI_SA_CBM_write_data.write(0x0);
	SPI_SA_CBM_hmaster.write(0x1);
	spi_miso0.write(0x1);
	spi_miso1.write(0x0);
	spi_miso2.write(0x1);
	spi_miso3.write(0x0);

 	wait();

 	while(true){

		SPI_SA_CBM_read_req.write(0x1);
		SPI_SA_CBM_write_req.write(0x0);
		SPI_SA_CBM_size.write(0x01);
		SPI_SA_CBM_addr.write(0xF0F0);
		SPI_SA_CBM_write_data.write(0x0);
		wait(2);		

		sa_busy = SPI_SA_CBM_busy.read();
		while(sa_busy) {
 			wait();
			sa_busy = SPI_SA_CBM_busy.read();
		}

		SPI_SA_CBM_read_req.write(0x0);
		SPI_SA_CBM_size.write(0x00);
		SPI_SA_CBM_addr.write(0x0);
		
		wait(5);

		SPI_SA_CBM_read_req.write(0x1);
		SPI_SA_CBM_write_req.write(0x0);
		SPI_SA_CBM_size.write(0x01);
		SPI_SA_CBM_addr.write(0xAA55);
		SPI_SA_CBM_write_data.write(0x0);
		
		wait(2);
		sa_busy = SPI_SA_CBM_busy.read();
		while(sa_busy) {
 			wait();
			sa_busy = SPI_SA_CBM_busy.read();
		}

		SPI_SA_CBM_read_req.write(0x0);
		SPI_SA_CBM_size.write(0x00);
		SPI_SA_CBM_addr.write(0x0);
        		
		wait(10);
 		sc_stop();

 	}//while_loop
}

