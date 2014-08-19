#include "layer.h"
#include <math.h>
#include "mnist_parser.h"
#include "boost\random.hpp"
#pragma once
namespace lenet5 {


	
	class Convolutional_Layer :public Layer
	{
	public:
		Convolutional_Layer(size_t in_size_, size_t in_number_, size_t fm_number_, size_t kernel_size_):
		in_size(in_size_), in_number(in_number_), kernel_size(kernel_size_), fm_number(fm_number_){}

		void init_weight(){
			for (size_t i = 0; i < fm_number; i++){
				std::vector<std::float_t> t;
				for (size_t i = 0; i < kernel_size * kernel_size; i++){
					
					t.push_back(uniform_rand<float_t>(-1, 1));
				}
				weight.push_back(t);
				srand((int)time(0));
				bias_weight.push_back(uniform_rand<float_t>(-1, 1));
			}
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
			return kernel_size * kernel_size * in_number;
		}

		int fan_out(){
			return kernel_size * kernel_size * fm_number;
		}

		template<typename T>
		inline T uniform_rand(T min, T max) {
			static boost::mt19937 gen(0);
			boost::uniform_real<T> dst(min, max);
			return dst(gen);
		}

		/*
		std::vector<std::float_t> conv(std::vector<std::float_t> img, std::vector<std::float_t> w){
			std::vector<std::float_t> v;
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
		*/
	private:
		size_t pace; // convolve step
		size_t in_size;
		size_t in_number;
		size_t fm_number; // output feature map number
		size_t kernel_size;
		std::vector<std::vector<std::float_t>> weight;
		std::vector<std::float_t> bias_weight;
		std::vector<Image*> input;
		std::vector< std::vector<std::float_t> > output;
		
	};
}// namespace lenet5

