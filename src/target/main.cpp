#include <flayr/flayr.hpp>
#include <vector>

int main(){
    NetworkSimple* neuralnetwork = new NetworkSimple();

    std::vector<double> inputs = {1.0f, 1.0f};
    neuralnetwork->addlayer(SIGMOID_FUNCTION, inputs.size());
    neuralnetwork->addlayer(HTAN_FUNCTION, 3);
    neuralnetwork->addlayer(SIGMOID_FUNCTION, 2);
    neuralnetwork->connectalllayers();
    neuralnetwork->evaluatenetwork(inputs);
}
