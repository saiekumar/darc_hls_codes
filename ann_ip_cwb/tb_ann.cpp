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
	cout << "Start of simulation" << endl;

 	wait();

 	while(true){
		sc_uint<8> 	pixel[4];
		sc_uint<32>	buffer = 0;

		for (int j = 0; j < 784; j++) {

			if(ifs.is_open()) {
				cout << endl << "File opened for reading" << j;
				for (int i = 0; i < 4; i++) {
					ifs >> pixel[i];
				}
				buffer = (pixel[3], pixel[2], pixel[1], pixel[0]); 
			}
			else {
				cout << "Unable to open the file" << endl;
			}
			
			data_in.write(buffer);
			pix_en.write(0x1);
			cfg_en.write(0x0);
    		wait();
		}

		data_in.write(0x0);
		pix_en.write(0x0);
		cfg_en.write(0x0);

        wait(2000);
 		sc_stop();
		
 	}//while_loop

	ifs.close();
}

