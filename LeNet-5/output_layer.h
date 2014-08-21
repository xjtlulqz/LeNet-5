#include <algorithm>
#include "layer.h"

namespace lenet5 {
	/*
	LeNet-5 output layer, apply RBF between weight vector and input.
	*/
	class Output_Layer : public Layer{
	public:
		Output_Layer(size_t in_depth, size_t out_depth) :
			Layer(1, in_depth, out_depth)
		{
			out_size = output_size();
			weight.resize(in_depth * out_depth);
			// bias_weight.resize(out_depth); // no bias
			output.resize(out_size);

			this->init_RBF_weight();
		}

		size_t fan_in(){
			return in_depth;
		}

		size_t fan_out(){
			return out_depth;
		}

		size_t output_size(){
			return out_depth;
		}

		void init_RBF_weight(){
			for (size_t i = 0; i < weight.size(); i++){
				weight[i] = (uniform_rand<float_t>(-1, 1) > 0 ? 1 : -1);
			}
		}

		int weight_index(int x, int y, int channel){
			return channel * in_depth + y;
		}

		void forward(){//forward
			std::cout << "start RBE for output" << std::endl;
			for (size_t out = 0; out < out_depth; out++){
				float sum = 0;
				for (size_t in = 0; in < in_depth; in++){
					float_t x = input[in] - weight[weight_index(0, in, out)];
					sum += x* x;
				}
				output[out] = sum;
			}
			std::cout << "RBE complete." << std::endl;
		}

	};

} // namespace lenet5