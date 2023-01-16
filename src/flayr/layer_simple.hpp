#pragma once

#include <vector>

struct Layer {
	int layerindex;
	std::vector<double> inputs; // store input
	int activationfunc;
	std::vector<double> outputs; // store output
	// connections
	std::vector<int> startnodes; // starting node
	std::vector<int> targetnodes; // target node
	std::vector<double> weights; // weight of connection
	std::vector<double> biases; // bias of connection
};
