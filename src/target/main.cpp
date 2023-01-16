#include <flayr/flayr.hpp>
#include <vector>

int main(){
    NetworkSimple* neuralnetwork = new NetworkSimple();

    neuralnetwork->addlayer(STEP_FUNCTION, 2);
    neuralnetwork->addlayer(STEP_FUNCTION, 2);
    neuralnetwork->connectalllayers();
    std::vector<double> inputs = {0.0f, 0.0f};
    neuralnetwork->evaluatenetwork(inputs);
}
