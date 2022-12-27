import sys
import h5py
import pathlib
import numpy as np
import pandas as pd
import tensorflow as tf
from numpy import exp
from keras.layers import Dense, Flatten
from keras.models import Sequential
from tensorflow.keras.utils import to_categorical
from keras.datasets import mnist
from keras import backend as K
from keras.models import Model



def sigmoid(X):
   return 1.0 / (1.0 + np.exp(-X))

# calculate the softmax of a vector
def softmax(X):
	e = np.exp(X - max(X))	#to avoid getting 'nan' as exponential of large values blows up
	return e / e.sum()
	






##### Creating Neural Network Model
hidden_layers = int(sys.argv[1]) 
layer_neurons = sys.argv[2].split(',')
output_neurons = int(sys.argv[3])
af_layers = sys.argv[4].split(',')
af_output = sys.argv[5]

##### Compiling and Training the Model
loss_function = sys.argv[6]
optimizer_function = sys.argv[7]
metric_function = sys.argv[8]
epoch_count = int(sys.argv[9])

##### Extracting weights and biases
deci_acc_weights = int(sys.argv[10])
deci_acc_biases = int(sys.argv[11])							# decimal accuracy

np.set_printoptions(threshold=10000000000)				# for printing all the values 

# Load MNIST handwritten digit data
(X_train, Y_train), (X_test, Y_test) = mnist.load_data()


image_no = 1


# Normalize the input image so that each pixel value is between 0 to 1.
# Training is done with normalised image
X_train = X_train.astype(np.float32) / 255.0
X_test = X_test.astype(np.float32) / 255.0


# Convert y_train into one-hot format
temp = []
for i in range(len(Y_train)):
    temp.append(to_categorical(Y_train[i], num_classes=10))
y_train = np.array(temp)

temp = []
for i in range(len(Y_test)):    
    temp.append(to_categorical(Y_test[i], num_classes=10))
y_test = np.array(temp)



# Dump the test images and test outputs into the files
for i in range(len(X_test)):
	img = X_test[i].flatten()
	imgname = "image" + str(i) + ".txt"
	with open(imgname, 'w') as f1:
		for x in range(len(img)):			
			print(img[x], file=f1)

	with open("images.txt", 'a') as f3:
		for x in range(len(img)):			
			print(img[x], file=f3)
	
	oup = Y_test[i]
	opname = "output" + str(i) + ".txt"
	with open(opname, 'w') as f4:
		print(oup, file=f4)

	with open("outputs.txt", 'a') as f2:
		print(oup , file=f2)


	if (i == 100):
		break



# Create simple Neural Network model
model = Sequential()
model.add(Flatten(input_shape=(28,28))) #input layer

for i in range(hidden_layers):
	model.add(Dense(layer_neurons[i], activation = af_layers[i]))	# n hidden layers #here we decide the activation function of each hidden layer

model.add(Dense(output_neurons, activation = af_output))			# output layer #here we decide the activation function of output layer

model.summary()

model.compile(loss = loss_function, 
              optimizer = optimizer_function,
              metrics = metric_function)

model.fit(X_train, y_train, epochs = epoch_count, 				#trains the model for a fixed number of epochs
          validation_data=(X_test,y_test))
          

#model done training
#Tensor Flow model generated
#print(model.get_layer("dense"))

'''
#predicting the digit after training the model
pred = model.predict(X_train[2].reshape(1, 28, 28, 1))
print(pred.argmax())
quit()
'''

weights = []
biases = []

index_wgts = 0
index_bias = 0


##### extracting weights and biases for the first hidden layer
for i in range(1, hidden_layers+2):

    weights.append(model.layers[i].get_weights()[0]) 				
    biases.append(model.layers[i].get_weights()[1])

    weights[i-1] = np.round(weights[i-1], decimals = deci_acc_weights)
    biases[i-1] = np.round(biases[i-1], decimals = deci_acc_biases)

    DF = pd.DataFrame(weights[i-1])
    DF.to_csv("weights_" +str(i) + ".csv", header=False, index=False)

    DF = pd.DataFrame(biases[i-1])
    DF.to_csv("biases_" +str(i) + ".csv", header=False, index=False)

    lib = open("weights_" +str(i) + ".csv","r")
    text=lib.read().strip().split("\n")
    lib.close()

    with open("weights.h", 'a') as f:				
        for line in text:
            number_list = line.split(",")
            for x in range(len(number_list)):
                print("ann_weights[" + str(index_wgts) +"]	=	" + number_list[x] + ";", file = f)
                index_wgts = index_wgts + 1;

    lib = open("biases_" +str(i) + ".csv","r")
    text=lib.read().strip().split("\n")	#whole lib is stored in text
    lib.close()
	
    with open("biases.h", 'a') as f:				
        for line in text:
            print("ann_biases[" + str(index_bias) +"]	=	" + line + ";" , file = f)
            index_bias = index_bias + 1;
			
			

exit()