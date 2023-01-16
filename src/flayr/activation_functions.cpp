// inline all of these functions
// if they don't get inlined (they should, which compiler do you use), then use macros

#include <cmath>

// step function, 1
inline double step(double input){
	return input > 0 ? 1 : 0;
}

// sigmoid, 2
inline double sigmoid(double input){
	return 1 / (1 + std::exp(input));
}

// hyperbolic tangent, 3
inline double htan(double input){
	double e2w = std::exp(2 * input);
	return (e2w - 1) / (e2w + 1);
}

// SiLU, 4
inline double silu(double input){
	return input / (1 + std::exp(-input));
}

// ReLU, 5
inline double relu(double input){
	return input > 0 ? input : 0;
}

// LReLU, 6
inline double lrelu(double input){
	return input > 0 ? input : (0.01 * input);
}

// TODO
// ELU
// SeLU
// Softsign
// Softplus