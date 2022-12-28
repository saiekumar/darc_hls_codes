#include "tb_ann.h"

//void tb_ANN::send_configs(){
//}

//--------------------------
// Send data thread
//--------------------------
void tb_ANN::send_images(){


	data_in.write(0x0);
	pix_en.write(0x0);
 	cfg_en.write(0x0);

	std::ifstream ifs("images.txt");
	std::ifstream ifsout("outputs.txt");
	cout << "Start of simulation" << endl;

 	wait();

 	while(true){

		float 					buffer;	
		bool 					op_en = 0;
		sc_uint<OUP_NEURONS>    out;
		
		sc_fixed<32,8>  		pixel;
		int 					out_exp;


		for (int j = 0; j < 784; j++) {

			if(ifs.is_open()) {
				//cout << endl << "File opened for reading" << j << endl;
				ifs >> pixel;			//we have to read the decimals into a float/fixed point
				buffer = pixel;
				//cout << "Buffer Loaded " << buffer << endl; //is the buffer being loaded 32 bits?
			}
			else {
				//why sometimes this error?
				cout << "Unable to open the file" << endl;
			}
			
			data_in.write(buffer);
			pix_en.write(0x1);
			cfg_en.write(0x0); 	//what does cfg mean?
    		wait();
		}

		data_in.write(0x0);
		pix_en.write(0x0);
		cfg_en.write(0x0);

		while(op_en == 0) {
			op_en = ann_op_en.read();
			out = ann_out.read();
			wait(1);
			//cout << "TB :: op_en = " << op_en << endl;	
		}


		if(ifsout.is_open()) {
			ifsout >> out_exp;
			if( out == out_exp) {
				cout << "Comparison pass" << endl;
			}
			else {
				cout << "Comparison fail" << endl;
			}

			cout << "DUT :: ann_oup = " << out << endl;	
			cout << "OUT_EXP :: ann_oup = " << out_exp << endl;	
		}

		ifs.close();
		sc_stop();
    	wait(100);

 	}//while_loop
}

