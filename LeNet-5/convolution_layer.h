#include "layer.h"
#include <math.h>
#include "mnist_parser.h"
#include "boost\random.hpp"
#pragma once
namespace lenet5 {
	class Convolutional_Layer :public Layer
	{
	public:
		Convolutional_Layer(size_t in_size_, size_t in_depth_, size_t out_depth_, size_t kernel_size_):
		in_size(in_size_), in_depth(in_depth_), kernel_size(kernel_size_), out_depth(out_depth_),
		out_size(output_size()){
			weight.resize(kernel_size * kernel_size * in_depth * out_depth);
			bias_weight.resize(out_depth);
			output.resize(out_size * out_size * out_depth);
		}

		void init_weight(){
			const float_t weight_base = 0.5 / std::sqrt(fan_in());
			uniform_rand(weight.begin(), weight.end(), -weight_base, weight_base);
			uniform_rand(bias_weight.begin(), bias_weight.end(), -weight_base, weight_base);
		}
		/*
		inline int uniform_random(){
		srand((int)time(0));
		return 2 * (rand() - 0.5) - sqrt(6 / (fan_out() + fan_in()));
		}
		*/

		size_t output_size(){
			return in_size - kernel_size + 1;
		}

		int fan_in(){
			return kernel_size * kernel_size * in_depth;
		}

		int fan_out(){
			return kernel_size * kernel_size * out_depth;
		}

		int in_index(int x, int y, int channel) {
			return (in_size * in_size) * channel + in_size * y + x;
		}

		int out_index(int x, int y, int channel){
			return (out_size * out_size) * channel + out_size * y + x;
		}

		void conv(){

		}


	private:
		size_t pace; // convolve step
		size_t in_size;
		size_t in_depth;
		size_t out_size;
		size_t out_depth; // output feature map number
		size_t kernel_size;
		std::vector<std::float_t> weight; //
		std::vector<std::float_t> bias_weight;
		std::vector<std::float_t> input;
		std::vector<std::float_t> output;
		
	};
}// namespace lenet5

