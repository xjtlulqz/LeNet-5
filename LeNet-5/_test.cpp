#include "lenet5.h"
using namespace lenet5;

int main(){
	Mnist_Parser m;
	m.load_testing();
	LeNet5* network = new LeNet5();
	std::cout << "start training" << std::endl;
	network -> train(m.test_sample, 60000);
	getchar();
	return 0;
}