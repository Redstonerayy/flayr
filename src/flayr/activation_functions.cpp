// inline all of these functions
// if they don't get inlined (they should, which compiler do you use), then use macros

// step function
// input > 0 ? 1 : 0;

// sigmoid
// 1 / (1 + std::exp(input))

// hyperbolic tangent
// e2w = std::exp(2 * input) 
// (e2w - 1) / (e2w + 1)

// SiLU
// input / (1 + std::exp(-input))

// ReLU
// std::max(0, input)

// LReLU
// input > 0 ? input : (0.01 * input)

// TODO
// ELU
// SeLU
// Softsign
// Softplus