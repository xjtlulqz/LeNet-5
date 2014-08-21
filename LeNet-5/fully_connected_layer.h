#include "layer.h"

namespace lenet5{
	class Fully_Connected_Layer :public Layer
	{
	public:
		Fully_Connected_Layer(size_t in_depth, size_t out_depth) :
			Layer(1, in_depth, out_depth)
		{
			out_size = output_size();
			weight.resize(in_depth * out_depth);
			bias_weight.resize(out_depth);
			output.resize(out_size);

			this->init_weight();
		}

		size_t fan_in(){
			return in_depth;
		}

		size_t fan_out(){
			return out_depth;
		}
		
		size_t output_size(){
			return this -> out_depth;
		}

		int weight_index(int x, int y, int channel){
			return (channel * in_depth) + y;
		}

		void forward(){//connect
			std::cout << "fully connected layer" << std::endl;
			for (size_t out = 0; out < out_depth; out++){
				float f = 0;
				for (size_t in = 0; in < in_depth; in ++){
					f += input[in] * weight[weight_index(0, in, out)];
				}
				output[out] = tanh(f + bias_weight[out]);
			}
		}
	};

} // namespace lenet5