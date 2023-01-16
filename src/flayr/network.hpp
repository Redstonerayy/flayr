#pragma once

#include "layer.hpp"

#include <vector>

class Network {
public:
	void addsimplelayer(int layertype, int activationfunc, int nodecount);

private:
	std::vector<Layer> layers;
	bool hasinput;
	bool hasoutput;
	int idcounter = 0;
};
