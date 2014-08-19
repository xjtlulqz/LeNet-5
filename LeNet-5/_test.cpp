#include "lenet5.h"
using namespace lenet5;

int main(){
	/*
	lenet5::Mnist_Parser s;
	s.load_testing();
	s.load_training();
	s.test();
	*/
	Convolutional_Layer c(32, 1, 6, 5);
	vector<float> v(1000, 0);
	c.uniform_rand(v.begin(), v.end(), -1, 1);
	for (auto i = v.begin(); i != v.end(); i++){
		std::cout << *i << endl;
	}
	getchar();
	return 0;
}