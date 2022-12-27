#! /usr/bin/python

import os
import sys

def clearHash(text):			#text is array of strings
    text1=[]					#text1 empty string
    for i in text:
        if "#" not in i  :
            if i.strip():		
               newstring=i.split()
               text1.append(" ".join(newstring))
    return text1  
    
def helpMenu():
	if(sys.argv[1] == '-h'):
    		print("\nUsage: top.py [OPTION] [CONFIG_FILE]\n")
    		print("Options:\n")
    		print(" -h			display this help and exit")
    		print(" -v			output version information and exit")
    		print(" -infile		create ANN model based on config file\n")
    		quit()

def versionMenu():
	if(sys.argv[1] == '-v'):
		print(sys.argv[0] + " version " + "1.0")
		quit()
		
def checkInfile():
	if(sys.argv[1] == '-infile'):
		return
	else:
		quit()	


def BuildANN():
    cmd = 'python mnist.py '+nhiddenlayers+' '+ ','.join(nlayer)+' '+noutputlayer+' '+ ','.join(aflayer)+' '+afoutputlayer+' '+lossfunc+' '+optimizer+' '+metrics+' '+nepochs+' '+deci_weights+' '+deci_biases+' '
    os.system(cmd)
    os.system('mv allbiases_formatted.h outputs/biases.h')
    os.system('mv allweights_formatted.h outputs/weights.h')
    #os.system('mv input_image.txt outputs/.')
    os.system('mv input_image_normalised.txt outputs/image.txt')


helpMenu()
versionMenu()
checkInfile()

if(len(sys.argv) == 2):
	print("top.py: Missing CONFIG_FILE operand")
	print("Try 'top.py -h' for more information.")
	quit()
	
########## For reading the define.txt file as an argument	
lib = open(sys.argv[2],"r")
text=lib.read().strip().split("\n")	#whole lib is stored in text
lib.close()

nlayer = []				#empty list for storing neurons in each hidden layer
aflayer = []				#empty list for storing activation function of each hidden layer

finalText=clearHash(text)
#print(finalText)
for line in finalText:
	#print(line)
	words = line.split()	
	
	###### Creating Neural Network Model
	if(words[0] == "nhiddenlayers"):
		nhiddenlayers = words[1]
	elif(words[0][0:6] == "nlayer"):
		nlayer.append(words[1])
	
	elif(words[0] == "noutputlayer"):
		noutputlayer = words[1]
	elif(words[0][0:7] == "aflayer"):
		aflayer.append(words[1])	
	elif(words[0] == "afoutputlayer"):
		afoutputlayer = words[1]
	
	###### Compiling and Training the Model
	elif(words[0] == "lossfunc"):
		lossfunc = words[1]		
	elif(words[0] == "optimizer"):
		optimizer = words[1]			
	elif(words[0] == "metrics"):
		metrics = words[1]	
		
	elif(words[0] == "nepochs"):
		nepochs = words[1]
	
	###### Extracting weights and biases	
	elif(words[0] == "deci_weights"):
		deci_weights = words[1]
	elif(words[0] == "deci_biases"):
		deci_biases = words[1]	
		

BuildANN()


#write code after this to create systemC model and run for a given image
#we only need input_image_normalised, weights.h, biases.h

#then once systemc is compiled, we can go through the terminal commands for hls
#scpars, bdltran, and then get the QOR

#full flow
#given ANN definition file -> get the Area, Latency for the ANN

#you should be able to get here ASAP once tensorflow and cwb are working in the same machine
#####################################


#then the actual the research portion of your project starts...hope to complete the thesis in full swing!!

#given required accuracy -> create respective ANN definition file?
#			  -> respectively decide the bit width that we should allocate for the neuron in systemc model -> for required area








