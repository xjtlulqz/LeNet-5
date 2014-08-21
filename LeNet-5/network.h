#include <iostream>
#include "layer.h"
#include "fully_connected_layer.h"
#include "output_layer.h"
#pragma once
namespace lenet5{

// connection table
#define X false
#define O true

	static const bool connection[] = {
		O, X, X, X, O, O, O, X, X, O, O, O, O, X, O, O,
		O, O, X, X, X, O, O, O, X, X, O, O, O, O, X, O,
		O, O, O, X, X, X, O, O, O, X, X, O, X, O, O, O,
		X, O, O, O, X, X, O, O, O, O, X, X, O, X, O, O,
		X, X, O, O, O, X, X, O, O, O, O, X, O, O, X, O,
		X, X, X, O, O, O, X, X, O, O, O, O, X, O, O, O
	};

#undef X
#undef O

	class LeNet5
	{
		LeNet5()
		{
			Convolutional_Layer C1(32, 1, 6, 5);
			Subsampling_Layer S2(28, 6, 2);
			Convolutional_Layer C3(14, 6, 16, 5, Connection_Table(connection, 6, 16));
			Subsampling_Layer S4(10, 16, 2);
			Convolutional_Layer C5(5, 16, 100, 5);
			Fully_Connected_Layer F6(100, 84);
			Output_Layer G7(84, 10);

			this->add_layer(&C1);
			this->add_layer(&S2);
			this->add_layer(&C3);
			this->add_layer(&S4);
			this->add_layer(&C5);
			this->add_layer(&F6);
			this->add_layer(&G7);
		}

		~LeNet5(){}
		
		void train(std::vector<std::vector<std::float_t>> x, std::vector<uint8_t> y){
			;
		}

		void foward(){
			for (auto layer : layers){
				/*forward calculate*/
				layer->forward();
				if (layer->next)
					layer->next->input = layer->output;
			}
		}
		
		void add_layer(Layer* layer){
			layers.back()->next = layer;
			layers.push_back(layer);
		}
	private:
		std::vector<Layer*> layers;
	};

}// namespace lenet5