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
	scpars -EE   -info_base_name scpars  "dma_ctlr.cpp"

gen_scripts :
	bdltran -EE -c1000 -sN -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_cfg_regs.IFF -Zflib_fcnt_out option -EE -c1000 -sN -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_cfg_regs.IFF -Zflib_fcnt_out -tcio -Zlower_module
	bdltran -EE -c1000 -sN -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_trans.IFF -Zflib_fcnt_out option -EE -c1000 -sN -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_trans.IFF -Zflib_fcnt_out -tcio -Zlower_module

synth :
	bdltran   -EE  -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_cfg_regs.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_cfg_regs.IFF -tcio -Zlower_module
	cwbxmlgen -EE  dma_ctlr_dma_cfg_regs_C.IFF
	veriloggen -EE    dma_ctlr_dma_cfg_regs_E.IFF
	bdltran   -EE  -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_trans.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zshared_reg_lutram_re_gen -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr_dma_trans.IFF -tcio -Zlower_module
	cwbxmlgen -EE  dma_ctlr_dma_trans_C.IFF
	veriloggen -EE    dma_ctlr_dma_trans_E.IFF
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr.IFF -Zflib_fcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr.IFF -Zflib_fcnt_out -sN -tcio -Zreset_state=NO
	bdltran  -EE   -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB  dma_ctlr.IFF -sN -tcio -Zreset_state=NO
	cwbxmlgen -EE  dma_ctlr_C.IFF
	veriloggen -EE    dma_ctlr_dma_cfg_regs_E.IFF
	veriloggen -EE    dma_ctlr_E.IFF

cwb :
	make pars 
	make gen_scripts 
	make synth


exec :
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c dma_ctlr.cpp -o dma_ctlr.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c main.cpp -o main.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c tb_dma.cpp -o tb_dma.o
	g++ -pthread -o "dma_ctlr.exe"  dma_ctlr.o main.o tb_dma.o -lm "/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc.a"  -Wl,-rpath="/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc-2.3.3.so"


sim :
	./dma_ctlr.exe



clean_sim : 
	rm -rf image*.txt
	rm -rf output*.txt
	rm -rf log

clean_exec : 
	rm -rf dma_ctlr.exe
	rm -rf dma_ctlr.o
	rm -rf main.o
	rm -rf tb_dma.o
	rm -rf weights.h
	rm -rf biases.h

clean_cwb :
	rm -rf  dma_ctlr-auto*
	rm -rf  dma_ctlr.err
	rm -rf  dma_ctlr.LMSPEC
	rm -rf  dma_ctlr.LOG.gz
	rm -rf  dma_ctlr_pwr.xpe
	rm -rf  dma_ctlr.QOR.HTML
	rm -rf  dma_ctlr.SR
	rm -rf  dma_ctlr.SUMM
	rm -rf  dma_ctlr.tips
	rm -rf  dma_ctlr.VSG
	rm -rf  scpars.sperr
	rm -rf  scpars.SPINFO
	rm -rf  dma_ctlr_E*
	rm -rf  *.BDL
	rm -rf  *.IFF
	rm -rf  *.FCNT
	rm -rf  *.FLIB
	rm -rf  *.CSV
	rm -rf  *.xml
	rm -rf  dma_ctlr_dma_*
	rm -rf weights.h
	rm -rf biases.h

clean:
	make clean_cwb
	make clean_exec
	make clean_sim
