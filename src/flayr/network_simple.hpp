#pragma once

#include "layer_simple.hpp"

#include <vector>

class NetworkSimple {
public:
	void addlayer(int activationfunc, int nodecount);
	// connect layers
	void connectalllayers();
	void connectlayers(Layer &layerfrom, Layer &layerto);
	// meta function
	void calculatelayeroutputs(Layer &layerfrom);
	// for each activation function
	void calculatelayeroutputsstep(Layer &layerfrom);
	void calculatelayeroutputssigmoid(Layer &layerfrom);
	void calculatelayeroutputshtan(Layer &layerfrom);
	void calculatelayeroutputssilu(Layer &layerfrom);
	void calculatelayeroutputsrelu(Layer &layerfrom);
	void calculatelayeroutputslrelu(Layer &layerfrom);
	// feed to next layer
	void feedoutputtonextlayer(Layer &layerfrom);
	// evaluate whole network
	void evaluatenetwork(std::vector<double> &inputs);

private:
	std::vector<Layer> layers;
	int layercounter = 0;
};
