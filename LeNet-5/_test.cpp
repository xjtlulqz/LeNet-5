#include "lenet5.h"

int main(){
	lenet5::Mnist_Parser s;
	s.load_testing();
	s.load_training();
	s.up2_32();
	s.test();
	getchar();
	return 0;
}