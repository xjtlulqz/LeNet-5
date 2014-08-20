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
		Convolutional_Layer(size_t in_size_, size_t in_depth_, size_t out_depth_, size_t kernel_size_) :
			Layer(in_size_, in_depth_, out_depth_), kernel_size(kernel_size_)
		{
			out_size = output_size();
			weight.resize(kernel_size * kernel_size * in_depth * out_depth);
			bias_weight.resize(out_depth);
			output.resize(out_size * out_size * out_depth);
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

		size_t fan_in(){
			return kernel_size * kernel_size * in_depth;
		}

		size_t fan_out(){
			return kernel_size * kernel_size * out_depth;
		}

		int weight_index(int x, int y, int channel) {
			return (kernel_size * kernel_size) * channel + kernel_size * x + y;
		}

		void conv(){
			for (int out = 0; out < out_depth; out++){
				for (int in = 0; in < in_depth; in++){
					for (int x = 0; x < out_size; x++){
						for (int y = 0; y < out_size; y++){
							
							std::vector<float_t> v, w;
							for (int m = 0; m < kernel_size; m++){
								for (int n = 0; n < kernel_size; n++){
									//std::cout << weight_index(m, n, in * out_depth + out) << std::endl;
									v.push_back(input[in_index(x + m, y + n, in)]);
									w.push_back(weight[weight_index(m, n, in * out_depth + out)]);
								}
							}
							float_t f = vec_t_conv(v, w);
							
							//std::cout <<output.size() << std::endl;
							output[out_index(x, y, out)] += f;
						}
					}
				}
				for (int x = 0; x < out_size; x++){
					for (int y = 0; y < out_size; y++){
						output[out_index(x, y, out)] = sigmod(output[out_index(x, y, out)] + bias_weight[out]);
					}
				}
			}
		}

	/*private:*/
		size_t pace; // convolve step
		size_t kernel_size;
	};
} // namespace lenet5

