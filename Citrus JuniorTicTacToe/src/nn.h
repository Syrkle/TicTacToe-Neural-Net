#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <float.h>
#include "globals.h"

class Network{
public:
	Network();
	Network(int inSize, int outSize, int biasSize1, int biasSize2);
	~Network();

	//returns a vector containing the changes to be made to a layer
	std::vector<std::vector<float>> backprop(std::vector<float> target, std::vector<std::vector<float>> outputs, std::vector<std::vector<float>> biasLayers, std::vector<std::vector<float>> weightlayers, float learnRate, std::vector<float> input, Function function);
	//returns one layers outputs into a vector, returns a vector with the size of 1 if error
	std::vector<float> forwardPass(Function function, std::vector<float> input, std::vector<float> weights, std::vector<float> bias);

	std::vector<float> forwardPassToo(Function function, std::vector<float> input, std::vector<float> weights, std::vector<float> bias);

	std::vector<std::vector<float>> getWeights();
	std::vector<std::vector<float>> getBias();

	std::vector<float> convText(std::string in);
	std::string convArr(std::vector<float> in);

	int getInSize();
	int getOutSize();

private:

	constexpr static float reluRate = 0.01;

	inline static float SigmoidActivationFunction(float x, Function function){

		switch(function){
		case LRELU:
			if(x > 0){
				return x;
			}
			return x * reluRate;
		break;
		case SIGMOID:
			return 1.0 / (1.0 + std::exp(-x));
		break;
		case TANH:
			return tanh(x);
		break;
		case RELU:
			if(x > 0){
				return x;
			}
			return 0;
		break;
		default:
			return x;
		break;
		}



		/*
		if(function == LRELU){
					if(x < 0){
						return x * reluRate;
					}
					return x;
				}
		if(function == SIGMOID){
			return 1.0 / (1.0 + std::exp(-x));
		}
		if(function == TANH){
			return tanh(x);
		} */


		return x;
	}

	std::map<std::string, int> _letters = {{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}, {"i", 8}, {"j", 9}, {"k", 10}, {"l", 11}, {"m", 12}, {"n", 13}, {"o", 14}, {"p", 15}, {"q", 16}, {"r", 17}, {"s", 18}, {"t", 19}, {"u", 20}, {"v", 21}, {"w", 22}, {"x", 23}, {"y", 24}, {"z", 25}};

	int _inputSize = 0;

	int _b1Size = 0;
	int _b2Size = 0;
	int _b3Size = 0;

	int _w1Size = 0;
	int _w2Size = 0;
	int _w3Size = 0;

	std::vector<float> _weightLayer1; //these are the weight values between the input and first hidden layer
	std::vector<float> _biasLayer1; //these are the hidden "neurons" for the first layer
	std::vector<float> _weightLayer2; //these are the weight values between the first hidden layer and the second hidden layer
	std::vector<float> _biasLayer2; //these are the hidden "neurons" for the second layer
	std::vector<float> _weightLayer3; //these are the weight values between the second layer and the output layer
	std::vector<float> _biasLayer3; //these are the last bias values, end result of these act as output
	std::vector<float> _output; //these are the final results of a full forward pass



};
