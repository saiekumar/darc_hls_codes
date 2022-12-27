g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c ann_ip.cpp -o ann_ip.o
g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c main.cpp -o main.o
g++ -pthread -O1 -I"/home/sai/Downloads/systemc-2.3.3/include/" -I"." -c tb_ann.cpp -o tb_ann.o
g++ -pthread -o "ann_ip.exe"  ann_ip.o main.o tb_ann.o -lm "/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc.a"  -Wl,-rpath="/home/sai/Downloads/systemc-2.3.3/lib-linux64/libsystemc-2.3.3.so"
