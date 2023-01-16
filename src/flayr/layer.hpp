#pragma once

#include <vector>

struct Layer {
	int layerid;
	int layertype; // 0 input, 1 hidden, 2 output,
	std::vector<double> inputs;
	std::vector<int> activationsfuncs; // ids
	std::vector<double> outputs;
	// connections
	std::vector<int> startnodes; // starting node
	std::vector<int> layertargets; // which layer
	std::vector<int> outnodes; // to which node
	std::vector<double> weights;
	std::vector<double> biases;
};
