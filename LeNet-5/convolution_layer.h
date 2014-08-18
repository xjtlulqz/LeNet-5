#include "layer.h"
#include <math.h>
#include "mnist_parser.h"
#pragma once
namespace lenet5 {

#define UNIFORM_RANDOM  2 * (rand() - 0.5) - sqrt(6 / (fan_out() + fan_in()))
	
	class Convolutional_Layer :public Layer
	{
	public:
		Convolutional_Layer(){}

	private:
		size_t output_size(){
			return in_size - kernel_size + 1;
		}

		int fan_in(){
			return kernel_size * kernel_size * in_number;
		}

		int fan_out(){
			return kernel_size * kernel_size * fm_number;
		}

		void init_weight(){
			for (size_t i = 0; i < fm_number; i++){
				std::vector<std::double_t> t;
				for (size_t i = 0; i < kernel_size * kernel_size; i++){
					srand((int)time(0));
					t.push_back(UNIFORM_RANDOM);
				}
				weight.push_back(t);
				srand((int)time(0));
				bias_weight.push_back(UNIFORM_RANDOM);
			}
		}
		/*
		inline int uniform_random(){
			srand((int)time(0));
			return 2 * (rand() - 0.5) - sqrt(6 / (fan_out() + fan_in()));
		}
		*/

		std::vector<std::uint8_t> conv(std::vector<std::uint8_t> img, std::vector<std::double_t> w){
			std::vector<std::uint8_t> v;
			for (size_t i = 0; i < output_size(); i++){
				for (size_t j = 0; j < output_size(); j++){
					int f = 0;
					for (size_t k = 0; k < kernel_size *kernel_size; k++){
						if (k < kernel_size)
							f += w[k] * img[(i * in_size) + j + k];
						else
							f += w[k] * img[((i + (k / kernel_size)) * in_size) + j + (k % kernel_size)];
					}
					v.push_back(f);
				}
			}
			return v;
		}

		size_t pace; // convolve step
		size_t in_size;
		size_t in_number;
		size_t fm_number; // output feature map number
		size_t kernel_size;
		std::vector<std::vector<std::double_t>> weight;
		std::vector<std::double_t> bias_weight;
		std::vector<std::vector<std::uint8_t> > input;
		std::vector< std::vector<std::uint8_t> > output;
		
	};
}// namespace lenet5

