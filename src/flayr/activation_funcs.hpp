#pragma once

enum ACTIVATIONS_FUNCTIONS {
	STEP_FUNCTION = 1,
	SIGMOID_FUNCTION,
	HTAN_FUNCTION,
	SILU_FUNCTION,
	RELU_FUNCTION,
	LRELU_FUNCTION
};

// activation funcs
double step(double input);
double sigmoid(double input);
double htan(double input);
double silu(double input);
double relu(double input);
double lrelu(double input);
