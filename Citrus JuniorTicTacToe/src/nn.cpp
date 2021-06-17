#include <iostream>
#include <ctime>
#include <math.h>
#include "nn.h"
#include <sfml/Graphics.hpp>

Network::Network(){

}

Network::~Network(){

}

//1040, 687, 454, 10
Network::Network(int inSize, int biasSize1, int biasSize2, int outSize){
	std::srand(time(NULL));
	this->_inputSize = inSize;

	this->_b1Size = biasSize1;
	this->_b2Size = biasSize2;
	this->_b3Size = outSize;

	this->_w1Size = inSize * biasSize1;
	this->_w2Size = biasSize1 * biasSize2;
	this->_w3Size = biasSize2 * outSize;


	//this is technically the output layer
	for(int i = 0; i < outSize; i++){
		this->_biasLayer3.push_back(0);
	}

	//init bias arrays
	for(int i = 0; i < biasSize1; i++){
		//set value to a random number
		this->_biasLayer1.push_back(0);
	}
	for(int i = 0; i < biasSize2; i++){
		//set value to a random number
		this->_biasLayer2.push_back(0);
	}

	//init weight arrays
	for(int i = 0; i < _w1Size; i++){
		//set value to a random number
		this->_weightLayer1.push_back(((std::rand() % 3) - 1.0));
		sf::sleep(sf::milliseconds(3));
	}
	for(int i = 0; i < _w2Size; i++){
		//set value to a random number
		this->_weightLayer2.push_back(((std::rand() % 3) - 1.0));
		sf::sleep(sf::milliseconds(7));
	}
	for(int i = 0; i < _w3Size; i++){
		//set value to a random number
		this->_weightLayer3.push_back(((std::rand() % 3) - 1.0));
		sf::sleep(sf::milliseconds(5));
	}
}

//converts input word into a "12" letter input for the nn
std::vector<float> Network::convText(std::string in){
	std::vector<float> temp(312, 0.0);
	std::string letter;
	if(in.size() < 13){
		for(int i = 1; i <= (signed) in.size(); i++){
			std::cout << in.at(i - 1) << std::endl;
			letter = in.at(i - 1);
			std::cout << this->_letters[letter] << "\n";
			temp[(this->_letters[letter] + (26 * i)) - 26] = 1.0;
		}
	}
	else{
		std::cout << "STRING TOO BIG!" << std::endl;
	}
	return temp;
}

std::string Network::convArr(std::vector<float> in){
	std::string temp;
	if(in.size() == 312){
		for(int i = 0; i < 312; i++){
			if(in.at(i) == 1.0){

			}
		}
	}
	else{
		std::cout << "DOES NOT MATCH" << std::endl;
	}
	return temp;
}

int Network::getInSize(){
	return this->_inputSize;
}
int Network::getOutSize(){
	return this->_b3Size;
}


std::vector<std::vector<float>> Network::getWeights(){
	std::vector<std::vector<float>> temp;
	temp.push_back(this->_weightLayer1);
	temp.push_back(this->_weightLayer2);
	temp.push_back(this->_weightLayer3);
	return temp;
}
std::vector<std::vector<float>> Network::getBias(){
	std::vector<std::vector<float>> temp;
	temp.push_back(this->_biasLayer1);
	temp.push_back(this->_biasLayer2);
	temp.push_back(this->_biasLayer3);
	return temp;
}


std::vector<float> Network::forwardPass(Function function, std::vector<float> input, std::vector<float> weights, std::vector<float> bias){
	std::vector<float> output;
	float temp = 0;
	int s = input.size();
	if(s > 0){
		//choose which bias and weights  we are using
		for(int b = 0, wl = 0; b < (signed) bias.size() || wl < (signed) weights.size(); b++, wl += s){
			//get the input, multiply by appropriate weight and then add it to the bias
			for(int i = 0; i < s; i++){
				temp += bias.at(b) + (weights.at(i + wl) * input.at(i));
			}
			//std::cout << temp << std::endl;
			output.push_back(this->SigmoidActivationFunction(temp, function));
			temp = 0;
		}
	}
	else{
		std::cout << "The input layer is not equal to the input size!!";
		output.push_back(10.0);
	}
	return output;
}

std::vector<float> Network::forwardPassToo(Function function, std::vector<float> input, std::vector<float> weights, std::vector<float> bias){
	//                 //Electric Boogaloo
	std::vector<float> output;
	float temp = 0;
	int s = input.size();
	if(s > 0){
		//choose which bias and weights  we are using
		for(int b = 0, wl = 0; b < (signed) bias.size() || wl < (signed) weights.size(); b++, wl += s){
			//get the input, multiply by appropriate weight and then add it to the bias
			for(int i = 0; i < s; i++){
				temp += (weights.at(i + wl) * input.at(i));
			}
			//std::cout << temp << std::endl;
			temp += bias.at(b);
			output.push_back(this->SigmoidActivationFunction(temp, function));
			temp = 0;
		}
	}
	else{
		std::cout << "The input layer is not equal to the input size!!" << std::endl;
		output.push_back(10.0);
	}
	return output;
}


/*
std::vector<std::vector<float>> Network::backprop(std::vector<float> target, std::vector<std::vector<float>> output, std::vector<std::vector<float>> biasLayers, std::vector<std::vector<float>> weightLayers, float learnRate, std::vector<float> input, Function function){
	std::vector<float> b1New; //new values for the first bias layer
	std::vector<float> b2New; //new values for the second bias layer
	std::vector<float> b3New; //new values for the last bias layer
	std::vector<float> w1New; //new values for the first weight layer
	std::vector<float> w2New; //new values for the second weight layer
	std::vector<float> w3New; //new values for the last weight layer
	std::vector<std::vector<float>> newValues;


	/*
	//get total error
	double tError = 0.0;
	for(int i = 0; i < (signed) output[2].size(); i++){
		//tError += (0.5 * pow((target.at(i) - output[2].at(i)), 2));
		tError += output[2].at(i) - target.at(i);
		//std::cout << "TOTAL ERROR: " << tError << "\n";
	}
	//std::cout << "TOTAL ERROR: " << tError << std::endl;



	//how much the total error changes with respect to the output
	//float tErrorChange = 0.0;
	float o1ErrorChange = 0.0; //output for last layer
	float o2ErrorChange = 0.0; //output for layer 2
	float o3ErrorChange = 0.0; //output for layer 1

	float n1Change = 0.0; //how much the network affects the outputs error rate
	float n2Change = 0.0;
	float n3Change = 0.0;

	//std::vector<float> nE1ErrorChange;
	//std::vector<float> nE2ErrorChange;
	//std::vector<float> nE3ErrorChange;

	float nE1ErrorChange = 0.0;
	float nE2ErrorChange = 0.0; //how much the output affects the networks error rate
	float nE3ErrorChange = 0.0;

	float weight2 = 0.0;
	float weight3 = 0.0;

	float w1ErrorChange = 0.0;
	float w2ErrorChange = 0.0;
	float w3ErrorChange = 0.0;

	 //looks at total error change rate

	//start with last layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output
				n1Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));


				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}
	else if(function == RELU){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output

				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n1Change = 1;
				}
				else{
					n1Change = 0;
				}

				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));

				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output

				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n1Change = 1;
				}
				else{
					n1Change = oak * reluRate;
				}

				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate *  (w1ErrorChange * nE1ErrorChange)));

				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}
	if(function == TANH){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output
				n1Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));


				if(j < 1){
					//b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}




	//go back a layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				n2Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes



				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));


				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}
	}
	else if(function == RELU){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				 //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n2Change = 1;
				}
				else{
					n2Change = 0;
				}

				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));

				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate* (o2ErrorChange * n2Change)));
				}
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				 //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n2Change = 1;
				}
				else{
					n2Change = oak * reluRate;
				}

				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));

				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}
	}
	if(function == TANH){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				n2Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes



				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));


				if(j < 1){
					//b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}
	}




	//go back a layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				n3Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));


				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate* (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == RELU){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n3Change = 1;
				}
				else{
					n3Change = 0;
				}

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));

				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate * (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n3Change = 1;
				}
				else{
					n3Change = oak *  reluRate;
				}

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate * (w3ErrorChange * o3ErrorChange * n3Change)));

				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate * (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == TANH){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				n3Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));


				if(j < 1){
					//b1New.push_back(biasLayers[0].at(k) - (learnRate* (o3ErrorChange * n3Change)));
				}
			}
		}
	}





	newValues.push_back(biasLayers[0]);
	newValues.push_back(w1New);
	newValues.push_back(biasLayers[1]);
	newValues.push_back(w2New);
	newValues.push_back(biasLayers[2]);
	newValues.push_back(w3New);
	return newValues;

}

*/







std::vector<std::vector<float>> Network::backprop(std::vector<float> target, std::vector<std::vector<float>> output, std::vector<std::vector<float>> biasLayers, std::vector<std::vector<float>> weightLayers, float learnRate, std::vector<float> input, Function function){
	std::vector<float> b1New; //new values for the first bias layer
	std::vector<float> b2New; //new values for the second bias layer
	std::vector<float> b3New; //new values for the last bias layer
	std::vector<float> w1New; //new values for the first weight layer
	std::vector<float> w2New; //new values for the second weight layer
	std::vector<float> w3New; //new values for the last weight layer
	std::vector<std::vector<float>> newValues;


	/*
	//get total error
	double tError = 0.0;
	for(int i = 0; i < (signed) output[2].size(); i++){
		//tError += (0.5 * pow((target.at(i) - output[2].at(i)), 2));
		tError += output[2].at(i) - target.at(i);
		//std::cout << "TOTAL ERROR: " << tError << "\n";
	}
	//std::cout << "TOTAL ERROR: " << tError << std::endl;
	 */



	//how much the total error changes with respect to the output
	//float tErrorChange = 0.0;
	float o1ErrorChange = 0.0; //output for last layer
	float o2ErrorChange = 0.0; //output for layer 2
	float o3ErrorChange = 0.0; //output for layer 1

	float n1Change = 0.0; //how much the network affects the outputs error rate
	float n2Change = 0.0;
	float n3Change = 0.0;

	//std::vector<float> nE1ErrorChange;
	//std::vector<float> nE2ErrorChange;
	//std::vector<float> nE3ErrorChange;

	float nE1ErrorChange = 0.0;
	float nE2ErrorChange = 0.0; //how much the output affects the networks error rate
	float nE3ErrorChange = 0.0;

	float weight2 = 0.0;
	float weight3 = 0.0;

	float w1ErrorChange = 0.0;
	float w2ErrorChange = 0.0;
	float w3ErrorChange = 0.0;


	if(function == SIGMOID){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output
				n1Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));


				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}

		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				n2Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes



				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));


				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}

		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				n3Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));


				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate* (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == RELU){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output

				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n1Change = 1;
				}
				else{
					n1Change = 0;
				}

				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));

				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}

		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				 //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n2Change = 1;
				}
				else{
					n2Change = 0;
				}

				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));

				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate* (o2ErrorChange * n2Change)));
				}
			}
		}

		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n3Change = 1;
				}
				else{
					n3Change = 0;
				}

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));

				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate * (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output

				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n1Change = 1;
				}
				else{
					n1Change = oak * reluRate;
				}

				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate *  (w1ErrorChange * nE1ErrorChange)));

				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}

		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				 //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n2Change = 1;
				}
				else{
					n2Change = oak * reluRate;
				}

				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));

				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}

		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak > 0){
					n3Change = 1;
				}
				else{
					n3Change = oak *  reluRate;
				}

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate * (w3ErrorChange * o3ErrorChange * n3Change)));

				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (learnRate * (o3ErrorChange * n3Change)));
				}
			}
		}
	}
	else if(function == TANH){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output
				n1Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (learnRate * (w1ErrorChange * nE1ErrorChange)));


				if(j < 1){
					//b3New.push_back(biasLayers[2].at(k) - (learnRate * (nE1ErrorChange)));
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}

		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				n2Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes



				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (learnRate *  (w2ErrorChange * o2ErrorChange * n2Change)));


				if(j < 1){
					//b2New.push_back(biasLayers[1].at(k) - (learnRate * (o2ErrorChange * n2Change)));
				}
			}
		}

		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				n3Change = (1 - (std::pow(tanh(oak), 2))); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (learnRate *  (w3ErrorChange * o3ErrorChange * n3Change)));


				if(j < 1){
					//b1New.push_back(biasLayers[0].at(k) - (learnRate* (o3ErrorChange * n3Change)));
				}
			}
		}
	}





	newValues.push_back(biasLayers[0]);
	newValues.push_back(w1New);
	newValues.push_back(biasLayers[1]);
	newValues.push_back(w2New);
	newValues.push_back(biasLayers[2]);
	newValues.push_back(w3New);
	return newValues;

}
























/* ORIGINAL CODE
std::vector<std::vector<float>> Network::backprop(std::vector<float> target, std::vector<std::vector<float>> output, std::vector<std::vector<float>> biasLayers, std::vector<std::vector<float>> weightLayers, float learnRate, std::vector<float> input, Function function){
	std::vector<float> b1New; //new values for the first bias layer
	std::vector<float> b2New; //new values for the second bias layer
	std::vector<float> b3New; //new values for the last bias layer
	std::vector<float> w1New; //new values for the first weight layer
	std::vector<float> w2New; //new values for the second weight layer
	std::vector<float> w3New; //new values for the last weight layer
	std::vector<std::vector<float>> newValues;


	/*
	//get total error
	double tError = 0.0;
	for(int i = 0; i < (signed) output[2].size(); i++){
		//tError += (0.5 * pow((target.at(i) - output[2].at(i)), 2));
		tError += output[2].at(i) - target.at(i);
		//std::cout << "TOTAL ERROR: " << tError << "\n";
	}
	//std::cout << "TOTAL ERROR: " << tError << std::endl;



	//how much the total error changes with respect to the output
	float tErrorChange = 0.0;
	float o1ErrorChange = 0.0; //output for last layer
	float o2ErrorChange = 0.0; //output for layer 2
	float o3ErrorChange = 0.0; //output for layer 1

	float n1Change = 0.0; //how much the network affects the outputs error rate
	float n2Change = 0.0;
	float n3Change = 0.0;

	//std::vector<float> nE1ErrorChange;
	//std::vector<float> nE2ErrorChange;
	//std::vector<float> nE3ErrorChange;

	float nE1ErrorChange = 0.0;
	float nE2ErrorChange = 0.0; //how much the output affects the networks error rate
	float nE3ErrorChange = 0.0;

	float weight2 = 0.0;
	float weight3 = 0.0;

	float w1ErrorChange = 0.0;
	float w2ErrorChange = 0.0;
	float w3ErrorChange = 0.0;

	 //looks at total error change rate

	//start with last layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output
				n1Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (w1ErrorChange * nE1ErrorChange) * learnRate);


				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (nE1ErrorChange) * learnRate);
				}

				//tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) output[1].size(); j++){
			w1ErrorChange = (output[1].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[2].size(); k++){
				oak = output[2].at(k);
				o1ErrorChange = -(target.at(k) - oak); //looks at total error change rate relative to the current output

				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak >= 0){
					n1Change = 1;
				}
				else{
					n1Change = oak * reluRate;
				}

				nE1ErrorChange = (o1ErrorChange * n1Change); //looks at net error change rate
				//update the vector
				w3New.push_back(weightLayers[2].at(k + (j * output[2].size())) - (w1ErrorChange * nE1ErrorChange) * learnRate);

				if(j < 1){
					b3New.push_back(biasLayers[2].at(k) - (nE1ErrorChange) * learnRate);
				}

				tErrorChange += -(target.at(k) - output[2].at(k));
			}
		}
	}











	//go back a layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				n2Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes



				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (w2ErrorChange * o2ErrorChange * n2Change) * learnRate);


				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (o2ErrorChange * n2Change) * learnRate);
				}
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) output[0].size(); j++){
			w2ErrorChange = (output[0].at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[1].size(); k++){
				oak = output[1].at(k);
				 //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak >= 0){
					n2Change = 1;
				}
				else{
					n2Change = oak *  reluRate;
				}

				o2ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[2].size(); i++){
					weight2 = weightLayers[2].at(i);
					nE2ErrorChange = (nE1ErrorChange * weight2);
					o2ErrorChange += nE2ErrorChange;
				}
				//update the vector
				w2New.push_back(weightLayers[1].at(k + (j * output[1].size())) - (w2ErrorChange * o2ErrorChange * n2Change) * learnRate);

				if(j < 1){
					b2New.push_back(biasLayers[1].at(k) - (o2ErrorChange * n2Change) * learnRate);
				}
			}
		}
	}




	//go back a layer
	if(function == SIGMOID){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				n3Change = (oak * (1 - oak)); //looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (w3ErrorChange * o3ErrorChange * n3Change) * learnRate);


				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (o3ErrorChange * n3Change) * learnRate);
				}
			}
		}
	}
	else if(function == LRELU){
		for(int j = 0; j < (signed) input.size(); j++){
			w3ErrorChange = (input.at(j)); //looks at the change relative to previous weight layer
			//update the vector
			float oak = 0.0; //make a variable so there isn't constant vector access
			for(int k = 0; k < (signed) output[0].size(); k++){
				oak = output[0].at(k);
				//looks at output change rate relative to its previous layer input //also derivative of activation function, should change when activation functions changes
				if(oak >= 0){
					n3Change = 1;
				}
				else{
					n3Change = oak *  reluRate;
				}

				o3ErrorChange = 0.0;
				for(int i = 0; i < (signed) output[1].size(); i++){
					weight3 = weightLayers[1].at(i);
					nE3ErrorChange = (nE2ErrorChange * weight3);
					o3ErrorChange += nE3ErrorChange;
				}
				//update the vector
				w1New.push_back(weightLayers[0].at(k + (j * output[0].size())) - (w3ErrorChange * o3ErrorChange * n3Change) * learnRate);

				if(j < 1){
					b1New.push_back(biasLayers[0].at(k) - (o3ErrorChange * n3Change) * learnRate);
				}
			}
		}
	}




	newValues.push_back(b1New);
	newValues.push_back(w1New);
	newValues.push_back(b2New);
	newValues.push_back(w2New);
	newValues.push_back(b3New);
	newValues.push_back(w3New);
	return newValues;

}



*/

















