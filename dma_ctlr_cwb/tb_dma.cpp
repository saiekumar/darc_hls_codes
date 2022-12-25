#include "tb_dma.h"

void tb_DMA::rcv_dma_trans(){
  	MA_CBM_read_data.write(0xAA55);
  	MA_CBM_command_busy.write(0x0);
  	MA_CBM_data_ready.write(0x1);
  	MA_CBM_error.write(0x0);
  	MA_CBM_count.write(0x0);
}

//--------------------------
// Send data thread
//--------------------------
void tb_DMA::send_cfg_trans(){

	SA_CBM_read_req.write(0x0);
	SA_CBM_write_req.write(0x0);
 	SA_CBM_addr.write(0x0);
	SA_CBM_size.write(0x0);
 	SA_CBM_write_data.write(0x0);
	SA_CBM_hmaster.write(0x1);

 	wait();

 	while(true){
		
		SA_CBM_read_req.write(0x0);
		SA_CBM_write_req.write(0x1);
		SA_CBM_size.write(0x01);
		SA_CBM_addr.write(0x10);
		SA_CBM_write_data.write(0xAA55);
        wait();

		SA_CBM_read_req.write(0x1);
		SA_CBM_write_req.write(0x0);
		SA_CBM_size.write(0x01);
		SA_CBM_addr.write(0x10);
		SA_CBM_write_data.write(0xBB66);
		wait();

		SA_CBM_read_req.write(0x1);
		SA_CBM_write_req.write(0x0);
		SA_CBM_size.write(0x01);
		SA_CBM_addr.write(0xC);
		SA_CBM_write_data.write(0xCC77);
        wait();

		SA_CBM_read_req.write(0x0);
		SA_CBM_write_req.write(0x0);
 		SA_CBM_addr.write(0x0);
		SA_CBM_size.write(0x0);
 		SA_CBM_write_data.write(0x0);
		SA_CBM_hmaster.write(0x0);

 		wait(80);

		SA_CBM_read_req.write(0x1);
		SA_CBM_write_req.write(0x0);
		SA_CBM_size.write(0x01);
		SA_CBM_addr.write(0xF0);
		SA_CBM_write_data.write(0x0);

        wait(5);
 		sc_stop();
		
 	}//while_loop
}

