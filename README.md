# neural-network-and-handwritten-digit-classifier
This is a feed-forward neural network library built upon a handmade matrix library.

This is made with the purpose of solving the classic mnist handwritten digit image classification problem dubbed the "hello world" of machine learning.

The binary compiled with xor_main found in bin is a demonstration of the neural network library in action, learning the operation xor and running xor_main.cpp as main.

The scope of this project is purely educational and the project does not serve as an example of a proper machine learning or matrix manipulation library.

Down below you can see the xor problem being solved and also the model being used for classification of handwritten digits (trained on the mnist dataset, with a model the shape of {784,16,12,10}).

# notes
The picture-getter.py file was used in order to get data in regards to the images used for the training.

The binary only works on linux, in order to test for other systems this needs to be recompiled.

In order to make picture-getter.py work you need to download PIL. Use the command pip3 install pillow.

Delete mnist_main.cpp and xor_main.cpp and make your own main file if you only want to use the library.

The data of trained the mnist network (weights,biases,learning rate and the structure) can also be found above and can be used at will in the mnist_neural_network_final.nn file. They can be imported in a neuralNetwork object with the method import_network(std::string filepath).

# binary

(WIP) A folder, with a binary, a .nn file and an improved version of the picture-getter.py file will be available in bin to be ran locally on the machine with the purpose of classifying 28x28 pixel images which contain handwritten digits.

This is useful if you are not interested in the source code and you just want to classify numbers or test the accuracy of the neural network model. NOTE, this model will be trained more than mnist_neural_network_final.nn and it may use a different structure (more hidden layers). This is in the hopes of achieving better accuracy.

# xor solved
![xor solved](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/xor_solved.png)

# neural network initialization and training
![neural network picture](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/neural_network_iandt.png)

# digit classification examples
![digit 1](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/mnist_classification_problem0.png)
![digit 2](https://github.com/david-cons/neural-network-and-handwritten-digit-classifier/blob/master/mnist_classifier_2.jpg)
