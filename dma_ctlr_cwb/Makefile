#=============================================================================
#
# File Name    : Makefile
# Revision History
#---------------------------------------------------------------------------
# Date           Author      	Version     		Description
#---------------------------------------------------------------------------
# 12/25/2022    Sai Marri         1.0         	Initial makefile
#============================================================================

gen_bus :
	CybusM -GUI -c1000 -lb "${CYBER_PATH}/packages/zynq-1.BLIB" -lfl "${CYBER_PATH}/packages/zynq-1.FLIB" +lfl "${CYBER_PATH}/packages/zynq-1-float.FLIB" "/home/sai/GIT_reps/darc_hls_codes/dma_ctlr_cwb/soc_bus.bdef"

pars : 
	scpars -EE   -info_base_name scpars  "dma_ctlr.cpp"

gen_scripts :
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out -sN -tcio -Zreset_state=NO
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml dma_ctlr-auto.MLIB -lmc dma_ctlr-auto.MCNT dma_ctlr.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml dma_ctlr-auto.MLIB -lmc dma_ctlr-auto.MCNT dma_ctlr.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out -sN -tcio -Zreset_state=NO

synth :
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_load.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_load.IFF -tcio -Zlower_module
	cwbxmlgen -EE  dma_ctlr_dma_load_C.IFF
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_activate.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB dma_ctlr_dma_activate.IFF -tcio -Zlower_module
	cwbxmlgen -EE  dma_ctlr_dma_activate_C.IFF
	bdltran  -EE   -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl dma_ctlr-auto.FLIB -lfc dma_ctlr-auto.FCNT -lml dma_ctlr-auto.MLIB -lmc dma_ctlr-auto.MCNT -Zmem_reg_locate=outside dma_ctlr.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl dma_ctlr-auto.FLIB -lfc dma_ctlr-auto.FCNT -lml dma_ctlr-auto.MLIB -lmc dma_ctlr-auto.MCNT -Zmem_reg_locate=outside dma_ctlr.IFF -sN -tcio -Zreset_state=NO
	cwbxmlgen  -EE  dma_ctlr_C.IFF
	veriloggen -EE  dma_ctlr_dma_load_E.IFF
	veriloggen -EE  dma_ctlr_dma_activate_E.IFF	
	veriloggen -EE  dma_ctlr_E.IFF

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
