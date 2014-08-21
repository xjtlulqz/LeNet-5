#include "lenet5.h"
using namespace lenet5;

int main(){
	/*
	lenet5::Mnist_Parser s;
	s.load_testing();
	s.load_training();
	s.test();
	
	Mnist_Parser m;
	m.load_testing();
	std::vector<std::vector<std::float_t>> v = m.test_sample[0]->image->img;
	vector<float_t> n_v;
	for (auto i : v){
		for (auto j : i){
			n_v.push_back(j);
		}
	}
	
	Convolutional_Layer c(32, 1, 6, 5);
	c.init_weight();
	c.input = n_v;
	c.conv();
	n_v = c.output;
	int index = 0;
	for (int i = 0; i < 32 * 32; i++){
		if (n_v[i] > 0)
			std::cout << 1;
		else
			std::cout << 0;
		//std::cout << n_v[i];
		index++;
		if (index == 32){
			index = 0;
			std::cout << std::endl;
		}
	}
	*/
	getchar();
	return 0;
}