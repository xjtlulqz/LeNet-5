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
	for (int i = 0; i < 100000; i++)
		std::cout << c.uniform_rand<float>(-1, 1) << std::endl;;
	getchar();
	return 0;
}