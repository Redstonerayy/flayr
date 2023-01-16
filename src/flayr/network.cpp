#include "network.hpp"
#include "layer.hpp"

void Network::addsimplelayer(int layertype, int activationfunc, int nodecount){
	// check for layers types
	if(layertype == 0 && this->hasinput)
		return;
	if(layertype == 2 && this->hasoutput)
		return;
	
	Layer newlayer;
	newlayer.layerid = this->idcounter++; // set id and increment counter
	newlayer.layertype = layertype;
	newlayer.inputs = std::vector<double>(nodecount, 0);
	newlayer.activationsfuncs = std::vector<int>(nodecount, activationfunc);
	newlayer.outputs =  std::vector<double>(nodecount, 0);
	// cant initialize connections yet, later with method
	this->layers.push_back(newlayer);
}