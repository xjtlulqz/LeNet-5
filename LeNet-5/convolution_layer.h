#include <cassert>
#include <math.h>

#include "layer.h"
#include "mnist_parser.h"
#include "boost\random.hpp"

#pragma once

namespace lenet5 {
	class Convolutional_Layer :public Layer
	{
	public:
		Convolutional_Layer(size_t in_size_, size_t in_depth_, size_t out_depth_, size_t kernel_size_):
		in_size(in_size_), in_depth(in_depth_), kernel_size(kernel_size_), out_depth(out_depth_){
			out_size = output_size();
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
			return (in_size * in_size) * channel + in_size * x + y;
		}

		int out_index(int x, int y, int channel) {
			return (out_size * out_size) * channel + out_size * x + y;
		}

		int weight_index(int x, int y, int channel) {
			return (kernel_size * kernel_size) * channel + kernel_size * x + y;
		}

		void conv(){
			for (int in = 0; in < in_depth; in++){
				for (int out = 0; out < out_depth; out++){
					for (int x = 0; x < out_size; x++){
						for (int y = 0; y < out_size; y++){
							std::vector<float_t> v, w;
							for (int m = 0; m < kernel_size; m++){
								for (int n = 0; n < kernel_size; n++){
									v.push_back(input[in_index(x + m, y + n, in)]);
									w.push_back(weight[weight_index(x + m, y + n, in * out_depth + out)]);
								}
							}
							float_t f = _conv(v, w);
							output[out_index(x, y, out_depth)] = f;
						}
					}
				}
			}
		}

	/*private:*/

		float_t _conv(std::vector<float_t> v, std::vector<float_t> w){
			assert(v.size() == w.size());
			float_t f = 0;
			for (size_t i = 0; i < v.size(); i++){
				f += v[i] * w[i];
			}
			return f;
		}

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

