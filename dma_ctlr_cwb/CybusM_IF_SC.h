// Configured by CybusM

#ifndef	CYBUSM_IF_SC_H
#define	CYBUSM_IF_SC_H

#include	<systemc.h>

// configurable system parameters
#define CBM_ADDRESS_RANGE 16
#define CBM_DATA_RANGE 16

#define CBM_LEN_RANGE 11
#define CBM_BURST_RET_RANGE 11
#define CBM_CLEN_RANGE 4
#define CBM_CBURST_RET_RANGE 5

// HBURST type
#define SINGLE      0
#define INCR        1
#define WRAP4       2
#define INCR4       3
#define WRAP8       4
#define INCR8       5
#define WRAP16      6
#define INCR16      7

//
// MASTER
//
// Constant definition
#define CBM_CHUNK_SIZE_AHB 1024
#define CBM_RD             0
#define CBM_WR             1
#define CBM_SINGLE         0
#define CBM_BURST          1


template <unsigned int ADDRESS_WIDTH=CBM_ADDRESS_RANGE, unsigned int DATA_WIDTH=CBM_DATA_RANGE>
class ahb_master_if {
  public:
    // Clock, Reset
//    sc_in_clock				HCLK;
//    sc_in<bool>				HRESETn /* Cyber reset_active=low */;

    // Declaration of the BUS Side I/F
    sc_out<sc_uint<1> >			CBM_read_req /* Cyber port_type=TER*/;
    sc_out<sc_uint<1> >			CBM_write_req /* Cyber port_type=TER*/;

    sc_out<sc_uint<3> >			CBM_burst /* Cyber port_type=TER*/; // 0->SINGLE, 1->INCR ... 7->INCR16
    sc_out<sc_uint<ADDRESS_WIDTH> >	CBM_addr /* Cyber port_type=TER*/; // read/write address
    sc_out<sc_uint<CBM_LEN_RANGE> >	CBM_length /* Cyber port_type=TER*/; // read/write transfer length
    sc_out<sc_uint<3> >			CBM_size /* Cyber port_type=TER*/; // read/write size (width)
    sc_out<sc_uint<1> >			CBM_lock /* Cyber port_type=TER*/; // read/write LOCK
    sc_out<sc_uint<DATA_WIDTH> >	CBM_write_data /* Cyber port_type=TER*/; // write data from UDL

    sc_in<sc_uint<DATA_WIDTH> >		CBM_read_data;	// read data from UDL
    sc_in<sc_uint<1> >			CBM_command_busy;
    sc_in<sc_uint<1> >			CBM_data_ready;
    sc_in<sc_uint<1> >			CBM_error;
    sc_in<sc_uint<CBM_LEN_RANGE> >	CBM_count;

    // constructor
    ahb_master_if() {}

    // destructor
    ~ahb_master_if() {}

    //
    // wait for transfer completion
    //
    // Cyber func = inline
    void
    CBM_wait()
    {
      do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);
    }

    //
    // wait for read transfer completion
    //
    // Cyber func = inline, scheduling_block
    sc_uint<DATA_WIDTH>
    wait_read()
    {
      sc_uint<DATA_WIDTH>	rv;

      do {
	wait();
	rv = CBM_read_data.read();
      } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);
      return rv;
    }

    //
    // wait for read transfer completion with error status check
    //
    // Cyber func = inline, scheduling_block
    sc_uint<1>	// succeed -> 0 error -> 1
    wait_read_stat(sc_uint<DATA_WIDTH> *r)
    {
      sc_uint<1>	f, err;

      do {
	wait();
	*r = CBM_read_data.read();
	err = CBM_error.read();
	f = CBM_data_ready.read() | err;
      } while (CBM_command_busy.read()==1 || f==0);
      return err;
    }

    //
    // wait for write transfer completion with error status check
    //
    // Cyber func = inline, scheduling_block
    sc_uint<1>	// succeed -> 0 error -> 1
    wait_write_stat()
    {
      sc_uint<1>	f, err;

      do {
	wait();
	err = CBM_error.read();
	f = CBM_data_ready.read() | err;
      } while (CBM_command_busy.read()==1 || f==0);
      return err;
    }

    //
    // single read with lock control
    //
    // Cyber func = inline, scheduling_block
    void
    single_read_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

      // read 1 word
      CBM_read_req.write(1);
      CBM_write_req.write(0);
      CBM_burst.write(SINGLE);
      CBM_addr.write(a);
      CBM_length.write(1);
      CBM_size.write(2);	// 32bit access
      CBM_lock.write(lk);
    }

    //
    // burst read with lock control
    // direct -> blocking
    //
    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_read_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<CBM_LEN_RANGE>	l	/* read length (1-1024) */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      sc_uint<CBM_LEN_RANGE>	i;
      sc_uint<1>		err;
      sc_uint<CBM_LEN_RANGE>	c;
      sc_uint<CBM_LEN_RANGE>	err_ix;		// error data index
      sc_uint<1>		dr;		// data ready flag

      do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

      // burst read
      CBM_read_req.write(1);
      CBM_write_req.write(0);
      CBM_burst.write(INCR);
      CBM_addr.write(a);
      CBM_length.write(l);
      CBM_size.write(2);	// 32bit access
      CBM_lock.write(lk);

      i = 0;
      do {
	wait();
	if ((dr = CBM_data_ready.read()) == 1) {
	  d[i++] = CBM_read_data.read();
	}
	c = CBM_count.read();
	err = CBM_error.read();
      } while (c != (sc_uint<CBM_LEN_RANGE>)(l - 1) && err != 1);

      if (err == 1) {
	if (c == 0 && dr == 0) {
	  err_ix = 0;
	}
	else {
	  err_ix = c + 1;
	}
      }

      return (err_ix, err);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_read(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<CBM_LEN_RANGE>	l	/* read length (1-1024) */)
    {
      return burst_read_lk(a, d, l, 0);
    }

    //
    // burst read with lock control
    // direct -> blocking
    //
    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_read_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<CBM_LEN_RANGE>	l	/* read length (1-1024) */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      return burst_read_lk(a, d, l, lk);
    }

    //
    // constant length burst read with lock control
    // direct -> blocking
    //
    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_read_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<3>		b	/* burst mode */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      sc_uint<CBM_CLEN_RANGE>		i;
      sc_uint<CBM_CLEN_RANGE>		l;
      sc_uint<1>			f;
      sc_uint<1>			err;
      sc_uint<CBM_CLEN_RANGE>		c;
      sc_uint<CBM_CBURST_RET_RANGE>	rv;
      sc_uint<CBM_CLEN_RANGE>		err_ix;	// error data index
      sc_uint<1>			dr;	// data ready flag

      switch (b) {
      case INCR4:  
	f = 0;
	l = 3;
	break;
      case INCR8:  
	f = 0;
	l = 7;
	break;
      case INCR16:  
	f = 0;
	l = 15;
	break;
      default:	// other transfer mode is not supported
	f = 1;
	break;
      }

      if (f == 0) {
	do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

	// burst read
	CBM_read_req.write(1);
	CBM_write_req.write(0);
	CBM_burst.write(b);
	CBM_addr.write(a);
	CBM_length.write(0);	// dummy
	CBM_size.write(2);	// 32bit access
	CBM_lock.write(lk);

	i = 0;
	do {
	  wait();
	  if ((dr = CBM_data_ready.read()) == 1) {
	    d[i++] = CBM_read_data.read();
	  }
	  c = CBM_count.read();
	  err = CBM_error.read();
	} while (c != l && err != 1);

	if (err == 1) {
	  if (c == 0 && dr == 0) {
	    err_ix = 0;
	  }
	  else {
	    err_ix = c + 1;
	  }
	}
        rv = (err_ix, err);
      }
      else {
	rv = 0;
      }
      return rv;
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_read(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<3>		b	/* burst mode */)
    {
      return cburst_read_lk(a, d, b, 0);
    }

    //
    // constant length burst read with lock control
    // direct -> blocking
    //
    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_read_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data buffer */,
	sc_uint<3>		b	/* burst mode */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      return cburst_read_lk(a, d, b, lk);
    }

    //
    // single read (blocking)
    //
    // Cyber func = inline, scheduling_block
    sc_uint<DATA_WIDTH>
    single_read(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */)
    {
      single_read_lk(a, 0);
      return wait_read();
    }

    // Cyber func = inline, scheduling_block
    sc_uint<DATA_WIDTH>
    single_read_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      single_read_lk(a, lk);
      return wait_read();
    }

    // Cyber func = inline, scheduling_block
    sc_uint<1>
    single_read_stat(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data pointer */)
    {
      single_read_lk(a, 0);
      return wait_read_stat(d);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<1>
    single_read_lock_stat(
	sc_uint<ADDRESS_WIDTH>	a	/* read address */,
	sc_uint<DATA_WIDTH>	*d	/* read data pointer */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      single_read_lk(a, lk);
      return wait_read_stat(d);
    }

    //
    // single write with lock control
    //
    // Cyber func = inline, scheduling_block
    void
    single_write_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	d	/* write data */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

      // write 1 word
      CBM_read_req.write(0);
      CBM_write_req.write(1);
      CBM_burst.write(SINGLE);
      CBM_addr.write(a);
      CBM_length.write(1);
      CBM_size.write(2);	// 32bit access
      CBM_lock.write(lk);
      CBM_write_data.write(d);
    }

    // Cyber func = inline, scheduling_block
    void
    single_write(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	d	/* write data */)
    {
      single_write_lk(a, d, 0);
    }

    // Cyber func = inline, scheduling_block
    void
    single_write_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	d	/* write data */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      single_write_lock(a, d, lk);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<1>
    single_write_stat(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	d	/* write data */)
    {
      single_write_lk(a, d, 0);
      return wait_write_stat();
    }

    // Cyber func = inline, scheduling_block
    sc_uint<1>
    single_write_lock_stat(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	d	/* write data */,
	sc_uint<1>			lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      single_write_lk(a, d, lk);
      return wait_write_stat();
    }

    //
    // burst write with lock control
    // direct -> blocking
    //
    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_write_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<CBM_LEN_RANGE>	l	/* write length */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      sc_uint<CBM_LEN_RANGE>	i;
      sc_uint<1>		err;
      sc_uint<CBM_LEN_RANGE>	c;

      do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

      // burst write
      CBM_read_req.write(0);
      CBM_write_req.write(1);
      CBM_burst.write(INCR);
      CBM_addr.write(a);
      CBM_length.write(l);
      CBM_size.write(2);	// 32bit access
      CBM_lock.write(lk);
      CBM_write_data.write(d[0]);

      i = 1;
      do {
	wait();
	if (CBM_data_ready.read() == 1) {
	  CBM_write_req.write(1);
	  CBM_write_data.write(d[i++]);
	}
	c = CBM_count.read();
	err = CBM_error.read();
      } while (c != (sc_uint<CBM_LEN_RANGE>)(l - 1) && err != 1);
      return (c, err);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_write(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<CBM_LEN_RANGE>	l	/* write length */)
    {
      return burst_write_lk(a, d, l, 0);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_BURST_RET_RANGE>
    burst_write_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<CBM_LEN_RANGE>	l	/* write length */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      return burst_write_lk(a, d, l, lk);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_write_lk(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<3>		b	/* burst mode */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      sc_uint<CBM_CLEN_RANGE>		i;
      sc_uint<CBM_CLEN_RANGE>		l;
      sc_uint<1>			f;
      sc_uint<1>			err;
      sc_uint<CBM_CLEN_RANGE>		c;
      sc_uint<CBM_CBURST_RET_RANGE>	rv;

      switch (b) {
      case INCR4:  
        f = 0;
        l = 3;
        break;
      case INCR8:  
        f = 0;
        l = 7;
        break;
      case INCR16:  
        f = 0;
        l = 15;
        break;
      default:	// other transfer mode is not supported
        f = 1;
        break;
      }

      if (f == 0) {
        do { wait(); } while (CBM_command_busy.read()==1 || CBM_data_ready.read()==0);

        // burst write
	CBM_read_req.write(0);
	CBM_write_req.write(1);
	CBM_burst.write(b);
	CBM_addr.write(a);
	CBM_length.write(0);	// dummy
	CBM_size.write(2);	// 32bit access
	CBM_lock.write(lk);
	CBM_write_data.write(d[0]);

	i = 1;
	do {
	  wait();
	  if (CBM_data_ready.read() == 1) {
	    CBM_write_req.write(1);
	    CBM_write_data.write(d[i++]);
	  }
	  c = CBM_count.read();
	  err = CBM_error.read();
	} while (c != l && err != 1);
	rv = (c, err);
      }
      else {
	rv = 0;
      }
      return rv;
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_write(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<3>		b	/* burst mode */)
    {
      return cburst_write_lk(a, d, b, 0);
    }

    // Cyber func = inline, scheduling_block
    sc_uint<CBM_CBURST_RET_RANGE>
    cburst_write_lock(
	sc_uint<ADDRESS_WIDTH>	a	/* write address */,
	sc_uint<DATA_WIDTH>	*d	/* write data */,
	sc_uint<3>		b	/* burst mode */,
	sc_uint<1>		lk	/* lock flag, CBM_lock->1 else 0 */)
    {
      return cburst_write_lk(a, d, b, lk);
    }
};


//
// SLAVE
//
// Constant definition
#define CBM_IDLE      0
#define CBM_READ_REQ  1
#define CBM_WRITE_REQ 2

#define CBM_OKAY      0
#define CBM_BUSY      1
#define CBM_RETRY     2
#define CBM_SPLIT     3
#define CBM_ERROR     4


// SLAVE API argument
template <unsigned int ADDRESS_WIDTH=CBM_ADDRESS_RANGE>
class CBM_Req_Stat {
  public:
    sc_uint<2>			req;	// CBM_IDLE or CBM_READ_REQ or CBM_WRITE_REQ
    sc_uint<ADDRESS_WIDTH>	addr;	// read/write address
    sc_uint<4>			hmaster;	// Master ID
};


template <unsigned int ADDRESS_WIDTH=CBM_ADDRESS_RANGE, unsigned int DATA_WIDTH=CBM_DATA_RANGE>
class ahb_slave_if {
  public:
    // Clock, Reset
//    sc_in_clock				HCLK;
//    sc_in<bool>				HRESETn /* Cyber reset_active=low */;

    // Declaration of the BUS Side I/F
    sc_out<sc_uint<1> >			CBM_busy /* Cyber port_type=TER*/; // status signal for UDL -> BUS I/F
    sc_out<sc_uint<1> >			CBM_error /* Cyber port_type=TER*/; // error signal for UDL -> BUS I/F
    sc_out<sc_uint<1> >			CBM_retry /* Cyber port_type=TER*/; // retry signal for UDL -> BUS I/F
    sc_out<sc_uint<1> >			CBM_split /* Cyber port_type=TER*/; // split signal for UDL -> BUS I/F
    sc_out<sc_uint<DATA_WIDTH> >	CBM_read_data /* Cyber port_type=TER*/;
    sc_in<sc_uint<1> >			CBM_read_req;
    sc_in<sc_uint<1> >			CBM_write_req;
    sc_in<sc_uint<ADDRESS_WIDTH> >	CBM_addr; // read/write address
    sc_in<sc_uint<3> >			CBM_size; // read/write size
    sc_in<sc_uint<DATA_WIDTH> >		CBM_write_data;
    sc_in<sc_uint<4> >			CBM_hmaster; // HMASTER

    // constructor
    ahb_slave_if() {}

    // destructor
    ~ahb_slave_if() {}

    //
    // request with global decoder
    //
    // Cyber func = inline, scheduling_block
    void
    poll_req(
	CBM_Req_Stat<ADDRESS_WIDTH> *p)
    {
      p->req =	(CBM_write_req.read(), CBM_read_req.read());
      p->addr =	CBM_addr.read();
      p->hmaster =	CBM_hmaster.read();
    }

    //
    // read/write data
    //
    // Cyber func = inline, scheduling_block
    void
    set_data(
	sc_uint<2>		req	/* CBM_IDLE or CBM_READ_REQ or CBM_WRITE_REQ */,
	sc_uint<DATA_WIDTH>	*p)
    {
      switch (req) {
      case CBM_READ_REQ:  
	CBM_read_data.write(*p);
	break;
      case CBM_WRITE_REQ:  
	*p = CBM_write_data.read();
	break;
      default:  
	break;
      }
    }

    //
    // read data
    //
    // Cyber func = inline, scheduling_block
    void
    put_data(
	sc_uint<DATA_WIDTH>	d)
    {
      CBM_read_data.write(d);
    }

    //
    // write data
    //
    // Cyber func = inline, scheduling_block
    sc_uint<DATA_WIDTH>
    get_data()
    {
      return CBM_write_data.read();
    }

    //
    // access response
    //
    // Cyber func = inline, scheduling_block
    void
    set_response(
	sc_uint<3>	r	/* CBM_OKAY,CBM_BUSY,CBM_RETRY,CBM_SPLIT,CBM_ERROR */)
    {
      switch (r) {
      case CBM_OKAY:  
	CBM_busy.write(0);
	CBM_error.write(0);
	CBM_retry.write(0);
	CBM_split.write(0);
	break;
      case CBM_BUSY:  
	CBM_busy.write(1);
	CBM_error.write(0);
	CBM_retry.write(0);
	CBM_split.write(0);
	break;
      case CBM_RETRY:  
	CBM_busy.write(1);
	CBM_error.write(0);
	CBM_retry.write(1);
	CBM_split.write(0);
	break;
      case CBM_SPLIT:  
	CBM_busy.write(1);
	CBM_error.write(0);
	CBM_retry.write(0);
	CBM_split.write(1);
	break;
      case CBM_ERROR:  
	CBM_busy.write(1);
	CBM_error.write(1);
	CBM_retry.write(0);
	CBM_split.write(0);
	break;
      default :  
	CBM_busy.write(0);
	CBM_error.write(0);
	CBM_retry.write(0);
	CBM_split.write(0);
	break;
      }
    }
};
#endif
