#include "layer.h"
#include <vector>
#include "activation.h"

namespace lenet5{
	/*
	class Subsampling_Layer :public Layer
	{
	public:

	private:

		vector<float_t> pooling(vector<std::float_t> in){
			vector<float_t> f;
			for (size_t i = 0; i < in_size; i += 2){
				for (size_t j = 0; j < in_size; j += 2){
					float_t sum = 0.0;
					for (size_t k = 0; k < 4; k++){
						if (k < 2){
							sum += in[(i * in_size) + j + k];
						}
						else{
							sum += in[(i + 1) *in_size + j + k];
						}
					}
					f.push_back(func->f(sum))// + bias));
						
			}
			return f;
		}

		size_t pooling_size;
		size_t in_size;
		size_t in_number;
		std::vector<std::vector<std::uint8_t>> input;
		activation *func;
		
	};
	*/
} // namespace lenet5