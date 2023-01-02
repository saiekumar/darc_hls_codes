#=============================================================================
#
# File Name    : Makefile
# Revision History
#---------------------------------------------------------------------------
# Date           Author      	Version     		Description
#---------------------------------------------------------------------------
# 12/25/2022    Sai Marri         1.0         	Initial makefile
#============================================================================

pars : 
	scpars -EE   -info_base_name scpars  "spi_ctlr.cpp"

gen_scripts :
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out -sN -tcio -Zreset_state=NO
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml spi_ctlr-auto.MLIB -lmc spi_ctlr-auto.MCNT spi_ctlr.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml spi_ctlr-auto.MLIB -lmc spi_ctlr-auto.MCNT spi_ctlr.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out -sN -tcio -Zreset_state=NO

synth :
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr_spi_load.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr_spi_load.IFF -tcio -Zlower_module
	cwbxmlgen -EE  spi_ctlr_spi_load_C.IFF
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr_spi_activate.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB spi_ctlr_spi_activate.IFF -tcio -Zlower_module
	cwbxmlgen -EE  spi_ctlr_spi_activate_C.IFF
	bdltran  -EE   -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl spi_ctlr-auto.FLIB -lfc spi_ctlr-auto.FCNT -lml spi_ctlr-auto.MLIB -lmc spi_ctlr-auto.MCNT -Zmem_reg_locate=outside spi_ctlr.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl spi_ctlr-auto.FLIB -lfc spi_ctlr-auto.FCNT -lml spi_ctlr-auto.MLIB -lmc spi_ctlr-auto.MCNT -Zmem_reg_locate=outside spi_ctlr.IFF -sN -tcio -Zreset_state=NO
	cwbxmlgen  -EE  spi_ctlr_C.IFF
	veriloggen -EE  spi_ctlr_spi_load_E.IFF
	veriloggen -EE  spi_ctlr_spi_activate_E.IFF	
	veriloggen -EE  spi_ctlr_E.IFF

cwb :
	make pars 
	make gen_scripts 
	make synth


exec :
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c spi_ctlr.cpp -o spi_ctlr.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c main.cpp -o main.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c tb_spi.cpp -o tb_spi.o
	g++ -pthread -o "spi_ctlr.exe"  spi_ctlr.o main.o tb_spi.o -lm "/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc.a"  -Wl,-rpath="/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc-2.3.3.so"


sim :
	./spi_ctlr.exe



clean_sim : 
	rm -rf image*.txt
	rm -rf output*.txt
	rm -rf log

clean_exec : 
	rm -rf spi_ctlr.exe
	rm -rf spi_ctlr.o
	rm -rf main.o
	rm -rf tb_spi.o
	rm -rf weights.h
	rm -rf biases.h

clean_cwb :
	rm -rf  spi_ctlr-auto*
	rm -rf  spi_ctlr.err
	rm -rf  spi_ctlr.LMSPEC
	rm -rf  spi_ctlr.LOG.gz
	rm -rf  spi_ctlr_pwr.xpe
	rm -rf  spi_ctlr.QOR.HTML
	rm -rf  spi_ctlr.SR
	rm -rf  spi_ctlr.SUMM
	rm -rf  spi_ctlr.tips
	rm -rf  spi_ctlr.VSG
	rm -rf  scpars.sperr
	rm -rf  scpars.SPINFO
	rm -rf  spi_ctlr_E*
	rm -rf  *.BDL
	rm -rf  *.IFF
	rm -rf  *.FCNT
	rm -rf  *.FLIB
	rm -rf  *.CSV
	rm -rf  *.xml
	rm -rf  spi_ctlr_spi_*
	rm -rf weights.h
	rm -rf biases.h

clean:
	make clean_cwb
	make clean_exec
	make clean_sim
