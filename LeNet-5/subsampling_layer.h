#include "layer.h"
#include <vector>
#include "activation.h"

#pragma once

namespace lenet5{
	
	class Subsampling_Layer :public Layer
	{
	public:
		Subsampling_Layer(size_t in_size_, size_t in_depth_, size_t pace_) :
			Layer(in_size_, in_depth_, in_depth_), pace(pace_)
		{
			out_size = output_size();
			weight.resize(pace * pace * in_depth);
			bias_weight.resize(out_depth);
			output.resize(out_size * out_size * out_depth);
			
			// init weight vector
			this->init_weight();
		}

		size_t output_size(){
			return in_size / pace;
		}

		size_t fan_in(){
			return pace * pace * in_depth;
		}

		size_t fan_out(){
			return pace * pace * out_depth;
		}

		int weight_index(int x, int y, int channel){
			return (pace * pace) * channel + pace * x + y;
		}

		void forward(){//pooling
			std::cout << "start pooling" << std::endl;
			std::cout << "input size:" << this->input.size() << std::endl;
			std::cout << "weight_size:" << this->weight.size() << std::endl;
			std::cout << "output_size:" << this->output.size() << std::endl;
			for (int in = 0; in < in_depth; in++){
				for (int x = 0; x < in_size; x += 2){
					for (int y = 0; y < in_size; y += 2){

						std::vector<float_t> v, w;
						for (int m = 0; m < pace; m++){
							for (int n = 0; n < pace; n++){
								//std::cout << in_index(x + m, y + n, in) << std::endl;
								//std::cout << weight_index(m, n, in) << std::endl;
								v.push_back(input[in_index(x + m, y + n, in)]);
								w.push_back(weight[weight_index(m, n, in)]);
							}
						}
						float_t f = vec_t_conv(v, w);
						// sigmod with bias
						output[out_index(x/2, y/2, in)] = sigmod(bias_weight[in] + f);
					}
				}
			}
			std::cout << "pooling complete." << std::endl;
		}

	private:
		size_t pace; // LeNet-5 S2 : 2
	};
	
} // namespace lenet5