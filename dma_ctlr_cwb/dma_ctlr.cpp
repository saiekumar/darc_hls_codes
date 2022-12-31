#include "dma_ctlr.h"

void dma_ctlr::dma_trans() {

	sc_uint<16> pend_trans_len;
	sc_uint<16> rd_addr;
	sc_uint<16> wr_addr;
	sc_uint<16> dma_buff[8];
	sc_uint<16> i;

	dma_buff[0] = 0x0;
	pend_trans_len = 0x0;
    dma_intr_status = 0x0;

	wait();

	while(true) {
		if((dma_chan_prog[0] == 1) & (dma_intr.read() == 0x0)) {
			for( i = 0; i < dma_chan_transfer_len[0]; i = i + 2) {
				rd_addr = dma_chan_src_addr[0] + i;
				dma_buff[0] = MA.single_read(rd_addr);
				//MA.cburst_read(rd_addr, dma_buff, INCR4);
				//MA.burst_read(rd_addr, dma_buff, 4);
				wait();

				wr_addr = dma_chan_dest_addr[0] + i;
				MA.single_write(wr_addr, dma_buff[0]);
				//MA.cburst_write(wr_addr, dma_buff, INCR4);
				//MA.burst_write(wr_addr, dma_buff, 4);
				wait();
			}
			dma_intr_status = 0x1;
			dma_intr.write(0x1);
		}
		wait();
	}
}






void dma_ctlr::dma_cfg_regs() {

    /* checks the AHB slave transacions & reads/writes to config registers */

    CBM_Req_Stat<> stat;

    dma_intr_mask 				= 	0x0;
	dma_chan_src_addr[0]		=	0x1000;
	dma_chan_dest_addr[0]		=	0x2000;
	dma_chan_transfer_len[0]	=	0x20;
	dma_chan_burst[0]			=	0x1;
	dma_chan_qos[0]				=	0x0;
	dma_chan_prog[0]			=	0x1;
    
    for (int i = 1; i < DMA_CHAN; i++) {
        dma_chan_src_addr[i]        = 0x0;
        dma_chan_dest_addr[i]       = 0x0;
        dma_chan_transfer_len[i]    = 0x0;
        dma_chan_burst[i]           = 0x0;
        dma_chan_qos[i]             = 0x0;
		dma_chan_prog[i]			= 0x0;
    }
    
    
    wait();

    SA.poll_req(&stat);    /* get status */

    while(true){
        wait();

        if (stat.req == CBM_READ_REQ) {
         	SA.set_response(CBM_OKAY);

        	if(stat.addr.range(7,0) == 0xF4) {                              				/* intr_mask */
        	    SA.put_data(dma_intr_mask);
        	} else if(stat.addr.range(7,0) == 0xF8) { 										/* intr_clear */
        	    SA.put_data(dma_intr_status);
        	} else if(stat.addr.range(7,0) == 0xF0) {   									/* intr_status */
        	    SA.put_data(dma_intr_status);
        	} else if(stat.addr.range(3,0) == 0x0)  {										/* channel-0 src addr */
        	    SA.put_data(dma_chan_src_addr[stat.addr.range(7,4)]);
        	} else if(stat.addr.range(3,0) == 0x4) {                                       	/* channel-0 dest addr */
        	    SA.put_data(dma_chan_dest_addr[stat.addr.range(7,4)]);
        	} else if(stat.addr.range(3,0) == 0x8) {                                       	/* channel-0 transfer length */
        	    SA.put_data(dma_chan_transfer_len[stat.addr.range(7,4)]);
        	} else if(stat.addr.range(3,0) == 0xC) {                                       	/* channel-0 burst */
        	    SA.put_data((0x0,dma_chan_burst[stat.addr.range(7,4)],dma_chan_qos[stat.addr.range(7,4)],dma_chan_prog[stat.addr.range(7,4)]));
        	}
   		}
        else if (stat.req == CBM_WRITE_REQ) {
            SA.set_response(CBM_OKAY);

            if(stat.addr.range(7,0) == 0xF4) {                                              /* intr_mask */
                dma_intr_mask = SA.get_data();
            } else if(stat.addr.range(7,0) == 0xF8) {                                       /* intr_clear */
                dma_intr_clear = SA.get_data();
            } else if((stat.addr.range(3,0) == 0x0) && (stat.addr.range(7,4) != 0x0)) {      /* channel-0 src addr */
                dma_chan_src_addr[stat.addr.range(7,4)] = SA.get_data();
            } else if((stat.addr.range(3,0) == 0x4) && (stat.addr.range(7,4) != 0x0)) {      /* channel-0 dest addr */
                dma_chan_dest_addr[stat.addr.range(7,4)] = SA.get_data();
            } else if((stat.addr.range(3,0) == 0x8) && (stat.addr.range(7,4) != 0x0)) {      /* channel-0 transfer length */
                dma_chan_transfer_len[stat.addr.range(7,4)] = SA.get_data();
            } else if((stat.addr.range(3,0) == 0xC) && (stat.addr.range(7,4) != 0x0)) {       /* channel-0 burst */
				dma_chan_prog[stat.addr.range(7,4)] 	= SA.get_data()[0];
				dma_chan_qos[stat.addr.range(7,4)] 		= SA.get_data()(2,1);
				dma_chan_burst[stat.addr.range(7,4)] 	= SA.get_data()(4,2);
            }

        }
            
		SA.poll_req(&stat); /* get status */
	}
}
