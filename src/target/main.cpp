#include <flayr/flayr.hpp>
#include <vector>

int main(){
    NetworkSimple* neuralnetwork = new NetworkSimple();

    neuralnetwork->addlayer(SIGMOID_FUNCTION, 2);
    neuralnetwork->addlayer(SIGMOID_FUNCTION, 2);
    neuralnetwork->connectalllayers();
    std::vector<double> inputs = {0, 0};
    neuralnetwork->evaluatenetwork(inputs);
}
