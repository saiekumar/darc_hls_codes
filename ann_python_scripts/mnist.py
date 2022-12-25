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
   #return 1/(1+np.exp(-X))
   return 1.0 / (1.0 + np.exp(-X))


'''
def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))
'''
   
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
(X_train, y_train), (X_test, y_test) = mnist.load_data()


image_no = 1

'''
#shapes
X_train (60000, 28, 28)
y_train (60000,)
X_test (10000, 28, 28)
y_test (10000,)
'''

#img1 = X_train[0].flatten()
img1 = X_train[image_no].flatten()

#784 pixels, and each pixel value is between 0 to 255
with open("input_image.txt", 'w') as f:					
	for x in range(len(img1)):			
		print(img1[x], file=f)


# Normalize the input image so that each pixel value is between 0 to 1.
# Training is done with normalised image
X_train = X_train.astype(np.float32) / 255.0
X_test = X_test.astype(np.float32) / 255.0


# Convert y_train into one-hot format
# what is this one-hot format?
temp = []
for i in range(len(y_train)):
    temp.append(to_categorical(y_train[i], num_classes=10))
y_train = np.array(temp)
# Convert y_test into one-hot format
temp = []
for i in range(len(y_test)):    
    temp.append(to_categorical(y_test[i], num_classes=10))
y_test = np.array(temp)


#print(X_train[0]) #one 28x28 image
#print (type(X_train[0])) #numpy array

#img = X_train[0].flatten()
img = X_train[image_no].flatten()
print(img)
#print(len(img))
#quit()

#784 pixels, and each pixel value is between 0 to 1
#considering the first image in dataset, so this pixel values not going to change
with open("input_image_normalised.txt", 'w') as f:					
	for x in range(len(img)):			
		#print(img[x], ',', end = ' ', file=f)
		print(img[x], file=f)

'''
print(X_train)
print(y_train) 
print(X_test)
print(y_test)
'''

# Create simple Neural Network model
model = Sequential()
model.add(Flatten(input_shape=(28,28))) #input layer

for i in range(hidden_layers):
	model.add(Dense(layer_neurons[i], activation = af_layers[i]))	# n hidden layers #here we decide the activation function of each hidden layer

model.add(Dense(output_neurons, activation = af_output))			# output layer #here we decide the activation function of output layer

model.summary()
#quit()


model.compile(loss = loss_function, 
              optimizer = optimizer_function,
              metrics = metric_function)

model.fit(X_train, y_train, epochs = epoch_count, 				#trains the model for a fixed number of epochs
          validation_data=(X_test,y_test))
          

'''          
#predicting the digit after training the model
pred = model.predict(X_train[2].reshape(1, 28, 28, 1))
print(pred.argmax())
quit()
'''


#model done training
#Tensor Flow model generated

#print(model.get_layer("dense"))


#clearing files, before appending
with open("layer_outputs.txt", 'w') as f:								
	pass
	
with open("layer_outputs_AF.txt", 'w') as f:
	pass


test_image = X_train[image_no].flatten()

#to get weights and biases of model before quantization
for i in range(1, hidden_layers+2):		#hidden layer = 2
						#model.layers[1] -> first hidden layer,   model.layers[2] -> second hidden layer, model.layers[3] -> output layer
##### extracting weights and biases for the first hidden layer
	weights = model.layers[i].get_weights()[0] #first layer has shape 784 x 16
	biases = model.layers[i].get_weights()[1] #shape 16 X 1 
	#print("layer number" + str(i))
	print("input image")
	print(test_image)	
	print(np.shape(test_image))
	print("weights")
	print(weights)	
	print(np.shape(weights))
	print("biases")			
	print(biases)
	print(np.shape(biases))
	#print(len(weights), len(biases))
	
	#for first layer output
	if(i == 1):
		print(type(test_image))
		print(type(weights))
		print(type(biases))
		
		print(test_image.shape)
		print(weights.shape)
		print(biases.shape)
		
		x = np.dot(test_image, weights) + biases #output of the first layer, before activation
		print(x)
		print(np.shape(x))
		#quit()
	else:
		#x = np.dot(x, weights) + biases #output of the other layers
		x = np.dot(xs, weights) + biases #output of the other layers, use the input after applying AF
		
	#some issue with the AF, have to look into it
	#for now just write output layer values to a file

	with open("layer_outputs.txt", 'a') as f:			#writing layer outputs before AF					
    		print(x, file=f)
    		
	print("before activation")
	print (x) #16 outputs from layer1
	
	if(i < hidden_layers+1):
		xs = sigmoid(x) #output of the first layer, after activation
	else:
		xs = softmax(x) #applying softmax activation for the output layer
		
	with open("layer_outputs_AF.txt", 'a') as f:			#writing layer outputs after AF
    		print(xs, file=f)
    		
    		if(len(xs) == 10):
    			print("Max Probability: ", max(xs), file = f)
    			print("Predicted Number: ",np.argmax(xs), file = f)
	#print("after activation")
	#print (xs)
	#quit()

'''
#to get output of each layer before quantization
for i in range(1, hidden_layers+2):
	outputs = model.layers[i].output
	print(outputs)
	model.layers[i].output.get_shape()
	
quit()
'''

'''
#predict the neuron values for one of the images?
layer_outputs = []
for i in range(1, len(model.layers)):
    tmp_model = Model(model.layers[0].input, model.layers[i].output)
    tmp_output = tmp_model.predict(X_train)[0]
    layer_outputs.append(tmp_output)
print (layer_outputs)
quit()
'''

#print(type(model.layers[1].output)) # keras tensor type
#quit()

#writing weights and biases to file before quantization

weights = []					#3 elements
biases = []

allw = []
allb = []

for i in range(1, hidden_layers+2):							#hidden layer = 2
									#model.layers[1] -> first hidden layer,   model.layers[2] -> second hidden layer, model.layers[3] -> output layer
##### extracting weights and biases for the first hidden layer
	
	weights.append(model.layers[i].get_weights()[0]) 				
	biases.append(model.layers[i].get_weights()[1])
					
	#print(len(weights), len(biases))

##### writing weights and biases of first hidden layer to file

for i in range(1, hidden_layers+2):
	#print(len(weights), len(biases))
	weights[i-1] = np.round(weights[i-1], decimals = deci_acc_weights)
	with open("weights_" +str(i) + ".txt", 'w') as f:				#writing to file just to confirm values are correct in csv file
    		print(weights[i-1], file=f)

	DF = pd.DataFrame(weights[i-1])
	DF.to_csv("weights_" +str(i) + ".csv", header=False, index=False)    	#if header/index is set true, they'll also be present in csv file


	biases[i-1] = np.round(biases[i-1], decimals = deci_acc_biases)

	DF = pd.DataFrame(biases[i-1])
	DF.to_csv("biases_" +str(i) + ".csv", header=False, index=False)
	
	############################################
	#maybe we can use weights and biases as such without performing quantization?
	
	'''
	print (biases[i-1])
	print (type(biases[i-1]))
	
	b = np.round(biases[i-1], decimals = deci_acc_biases)
	b = b.T.tolist()
	allb.append(b)
	print(allb)
	
	w = np.round(weights[i-1], decimals = deci_acc_weights)
	w = w.T.tolist()
	allw.append(w)
	'''
	
	b = np.round(biases[i-1], decimals = deci_acc_biases)
	allb.extend(b)
	
	w = np.round(weights[i-1], decimals = deci_acc_weights)
	allw.extend(w)
	
	#writing the csv file with weights/biases of multiple layers
	if(i == hidden_layers+1): #we are only considering two layers for now
		DF = pd.DataFrame(allw)
		DF.to_csv("allweights.csv", header=False, index=False) 	 #wrong here itself
		
		DF = pd.DataFrame(allb)
		DF.to_csv("allbiases.csv", header=False, index=False) 
		
	

	#formatting the weights and biases as required by HLS tool
	lib = open("weights_" +str(i) + ".csv","r")
	text=lib.read().strip().split("\n")	#whole lib is stored in text
	lib.close()	
	
	index = 0
	with open("weights_" + str(i) +"_formatted" + ".h", 'w') as f:				
		for line in text:
			number_list = line.split(",")
			for x in range(len(number_list)):
				print("ann_weights[" + str(index) +"]	=	" + number_list[x] + ";", file = f)
				index = index + 1;


	lib = open("biases_" +str(i) + ".csv","r")
	text=lib.read().strip().split("\n")	#whole lib is stored in text
	lib.close()
	
	index = 0
	with open("biases_" + str(i) +"_formatted" + ".h", 'w') as f:				
		for line in text:
			print("ann_biases[" + str(index) +"]	=	" + line + ";" , file = f)
			index = index + 1;
			
			
	if(i == hidden_layers+1): #we are only considering two layers for now
		lib = open("allweights.csv","r")
		text=lib.read().strip().split("\n")	#whole lib is stored in text
		lib.close()	
		
		index = 0
		with open("allweights_formatted" + ".h", 'w') as f:				
			for line in text:
				number_list = line.split(",")
				for x in range(len(number_list)):
					if(len(number_list[x]) == 0):
						continue
					print("ann_weights[" + str(index) +"]	=	" + number_list[x] + ";", file = f)
					index = index + 1;
					
		lib = open("allbiases.csv","r")
		text=lib.read().strip().split("\n")	#whole lib is stored in text
		lib.close()	
		
		index = 0
		with open("allbiases_formatted" + ".h", 'w') as f:				
			for line in text:
				number_list = line.split(",")
				for x in range(len(number_list)):
					print("ann_biases[" + str(index) +"]	=	" + number_list[x] + ";", file = f)
					index = index + 1;			
	
	
	

	








