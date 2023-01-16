#include "network_simple.hpp"
#include "layer_simple.hpp"
#include "activation_funcs.hpp"

#include <iostream>

void NetworkSimple::addlayer(int activationfunc, int nodecount){	
	// create new layer
	Layer newlayer;
	newlayer.layerindex = this->layercounter++;
	newlayer.inputs = std::vector<double>(nodecount, 0);
	newlayer.activationfunc = activationfunc;
	newlayer.outputs = std::vector<double>();
	newlayer.outputs.reserve(nodecount); // use emplace_back alter on
	this->layers.push_back(newlayer);
}

void NetworkSimple::connectalllayers(){
	for(int i = 0; i < this->layers.size() - 1; ++i){
		this->connectlayers(this->layers.at(i), this->layers.at(i + 1));
	}
}

void NetworkSimple::connectlayers(Layer &layerfrom, Layer &layerto){
	// calculate count of connections
	int connectioncount = layerfrom.inputs.size() * layerto.inputs.size();
	
	// which nodes are connected
	layerfrom.startnodes = std::vector<int>();
	layerfrom.startnodes.reserve(connectioncount);
	layerfrom.targetnodes = std::vector<int>();
	layerfrom.targetnodes.reserve(connectioncount);
	// fill the connections
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		for(int j = 0; j < layerto.inputs.size(); ++j){
			layerfrom.startnodes.emplace_back(i);
			layerfrom.targetnodes.emplace_back(j);
		}	
	}

	// initialize weights and biases with the same value
	layerfrom.weights = std::vector<double>(connectioncount, 1);
	layerfrom.biases = std::vector<double>(connectioncount, 0);
}

void NetworkSimple::calculatelayeroutputs(Layer &layerfrom){
	for(auto output : layerfrom.inputs){
		std::cout << output << std::endl;
	}
	switch(layerfrom.activationfunc){
		case 1: this->calculatelayeroutputsstep(layerfrom); break;
		case 2: this->calculatelayeroutputssigmoid(layerfrom); break;
		case 3: this->calculatelayeroutputshtan(layerfrom); break;
		case 4: this->calculatelayeroutputssilu(layerfrom); break;
		case 5: this->calculatelayeroutputsrelu(layerfrom); break;
		case 6: this->calculatelayeroutputslrelu(layerfrom); break;
	}
	for(auto output : layerfrom.outputs){
		std::cout << output << std::endl;
	}
}

void NetworkSimple::calculatelayeroutputsstep(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(step(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::calculatelayeroutputssigmoid(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(sigmoid(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::calculatelayeroutputshtan(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(htan(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::calculatelayeroutputssilu(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(silu(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::calculatelayeroutputsrelu(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(relu(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::calculatelayeroutputslrelu(Layer &layerfrom){
	for(int i = 0; i < layerfrom.inputs.size(); ++i){
		layerfrom.outputs.emplace_back(lrelu(layerfrom.inputs.at(i)));
	}
}

void NetworkSimple::feedoutputtonextlayer(Layer &layerfrom){
	for(int i = 0; i < layerfrom.startnodes.size(); ++i){
		// get reference to next layer
		Layer &layerto = this->layers.at(layerfrom.layerindex + 1); 
		// write to input of next layer
		layerto.inputs.at(layerfrom.targetnodes.at(i)) 
			+= layerfrom.outputs.at(layerfrom.startnodes.at(i))
			* layerfrom.weights.at(i)
			+ layerfrom.biases.at(i);
	}
}

void NetworkSimple::evaluatenetwork(std::vector<double> &inputs){
	// copy inputs to input layer
	this->layers.at(0).inputs = inputs;

	for(int i = 0; i < this->layers.size() - 1; ++i){
		this->calculatelayeroutputs(this->layers.at(i));
		this->feedoutputtonextlayer(this->layers.at(i));
	}
	// calculate output for last layer
	Layer &lastlayer = this->layers.at(this->layers.size() - 1);
	this->calculatelayeroutputs(lastlayer);
	for(auto output : lastlayer.outputs){
		std::cout << output << std::endl;
	}
}
