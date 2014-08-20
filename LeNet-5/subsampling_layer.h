#include "layer.h"
#include <vector>
#include "activation.h"

namespace lenet5{
	
	class Subsampling_Layer :public Layer
	{
	public:
		Subsampling_Layer(size_t in_size_, size_t in_depth_, size_t pace_) :
			Layer(in_size_, in_depth_, in_depth_), pace(pace_)
		{
			out_size = in_size/ pace;
			weight.resize(pace * pace * in_depth);
			bias_weight.resize(out_depth);
			output.resize(out_size * out_size * out_depth);
		}

		int weight_index(int x, int y, int channel){
			return (pace * pace) * channel + pace * x + y;
		}

		void pooling(){
			for (int in = 0; in < in_depth; in++){
				for (int x = 0; x < in_size; x += 2){
					for (int y = 0; y < in_size; y += 2){

						std::vector<float_t> v, w;
						for (int m = 0; m < pace; m++){
							for (int n = 0; n < pace; n++){
								v.push_back(input[in_index(x + m, y + n, in)]);
								w.push_back(weight[weight_index(m, n, in)]);
							}
						}
						float_t f = vec_t_conv(v, w);
						// sigmod with bias
						output[out_index(x, y, in)] = sigmod(bias_weight[in] + f);
					}
				}
			}
		}

	private:
		size_t pace; // LeNet-5 S2 : 2
	};
	
} // namespace lenet5