# neural-network-and-handwritten-digit-classifier
This is a feed-forward neural network library built upon a handmade matrix library.

This is made with the purpose of solving the classic mnist handwritten digit image classification problem dubbed the "hello world" of machine learning.

The binary compiled with xor_main found in bin is a demonstration of the neural network library in action, learning the operation xor and running xor_main.cpp as main. As for the binary program which recognizes digits, look below (unlike the xor binary this neural network is already trained at runtime).

The scope of this project is purely educational and the project does not serve as an example of a proper machine learning or matrix manipulation library.

Down below you can see the xor problem being solved and also the model being used for classification of handwritten digits (trained on the mnist dataset, with a model the shape of {784,16,12,10}).

# notes
The binaries only work on linux, in order to test for other systems this needs to be recompiled.

Delete mnist_main.cpp and xor_main.cpp and make your own main file if you only want to use the library.

The data of trained the mnist network (weights,biases,learning rate and the structure) can also be found above and can be used at will in the mnist_neural_network_final.nn file. They can be imported in a neuralNetwork object with the method import_network(std::string filepath).

# binary
Inside bin you will find a folder containing a .nn file, picture-getter.py and a binary. If you run said binary with a filepath of a 28x28 pixel picture of a digit it will be able to classify it. The .nn file is the data of the trained neural network and, picture-getter.py is used for getting image pixel data (please do not delete these files). 

In order for picture-getter.py to be ran, PIL must be installed. run the command *pip3 install pillow* , before running the mnist binary. 

# xor solved
![xor solved](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/pictures/xor_solved.png)

# neural network initialization and training
![neural network picture](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/pictures/neural_network_iandt.png)

# digit classification examples
![digit 1](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/pictures/mnist_classifier_2.jpg)
![digit 2](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/pictures/mnist_classification_problem0.png)
![digit 3](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/pictures/image.png)
