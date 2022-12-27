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
	scpars -EE   -info_base_name scpars  "ann_ip.cpp"

gen_scripts :
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip.IFF -Zmem_reg_locate=outside -Zmlib_mcnt_out -sN -tcio -Zreset_state=NO
	bdltran -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml ann_ip-auto.MLIB -lmc ann_ip-auto.MCNT ann_ip.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out option -EE -c1000 -sN -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB -lml ann_ip-auto.MLIB -lmc ann_ip-auto.MCNT ann_ip.IFF -Zmem_reg_locate=outside -Zflib_fcnt_out -sN -tcio -Zreset_state=NO

synth :
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip_ann_load.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip_ann_load.IFF -tcio -Zlower_module
	cwbxmlgen -EE  ann_ip_ann_load_C.IFF
	bdltran  -EE   -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip_ann_activate.IFF option -EE -c1000 -s -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Zdup_reset=YES -Zfolding_sharing=inter_stage -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1-float.FLIB ann_ip_ann_activate.IFF -tcio -Zlower_module
	cwbxmlgen -EE  ann_ip_ann_activate_C.IFF
	bdltran  -EE   -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl ann_ip-auto.FLIB -lfc ann_ip-auto.FCNT -lml ann_ip-auto.MLIB -lmc ann_ip-auto.MCNT -Zmem_reg_locate=outside ann_ip.IFF option -EE -c1000 -sN -Zresource_fcnt=GENERATE -Zresource_mcnt=GENERATE -Ztop_module -Zdup_reset=YES -tcio -EE -lb /eda/cwb/cyber_611/LINUX/packages/zynq-1.BLIB -lfl /eda/cwb/cyber_611/LINUX/packages/zynq-1.FLIB +lfl ann_ip-auto.FLIB -lfc ann_ip-auto.FCNT -lml ann_ip-auto.MLIB -lmc ann_ip-auto.MCNT -Zmem_reg_locate=outside ann_ip.IFF -sN -tcio -Zreset_state=NO
	cwbxmlgen  -EE  ann_ip_C.IFF
	veriloggen -EE  ann_ip_ann_load_E.IFF
	veriloggen -EE  ann_ip_ann_activate_E.IFF	
	veriloggen -EE  ann_ip_E.IFF

cwb :
	make pars 
	make gen_scripts 
	make synth


exec :
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c ann_ip.cpp -o ann_ip.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c main.cpp -o main.o
	g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c tb_ann.cpp -o tb_ann.o
	g++ -pthread -o "ann_ip.exe"  ann_ip.o main.o tb_ann.o -lm "/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc.a"  -Wl,-rpath="/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc-2.3.3.so"

clean_exec : 
	rm -rf ann_ip.exe
	rm -rf ann_ip.o
	rm -rf main.o
	rm -rf tb_ann.o

clean_synth :
	rm -rf  ann_ip-auto*
	rm -rf  ann_ip.err
	rm -rf  ann_ip.LMSPEC
	rm -rf  ann_ip.LOG.gz
	rm -rf  ann_ip_pwr.xpe
	rm -rf  ann_ip.QOR.HTML
	rm -rf  ann_ip.SR
	rm -rf  ann_ip.SUMM
	rm -rf  ann_ip.tips
	rm -rf  ann_ip.VSG
	rm -rf  scpars.sperr
	rm -rf  scpars.SPINFO
	rm -rf  ann_ip_E*
	rm -rf  *.BDL
	rm -rf  *.IFF
	rm -rf  *.FCNT
	rm -rf  *.FLIB
	rm -rf  *.CSV
	rm -rf  *.xml
	rm -rf  ann_ip_ann_*
