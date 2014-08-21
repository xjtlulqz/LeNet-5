#include <iostream>

#include "layer.h"

#include "fully_connected_layer.h"
#include "output_layer.h"
#include "subsampling_layer.h"
#include "convolution_layer.h"

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
	public:
		LeNet5()
		{
			this->add_layer(new Convolutional_Layer(32, 1, 6, 5));
			this->add_layer(new Subsampling_Layer(28, 6, 2));
			this->add_layer(new Convolutional_Layer(14, 6, 16, 5, Connection_Table(connection, 6, 16)));
			this->add_layer(new Subsampling_Layer(10, 16, 2));
			this->add_layer(new Convolutional_Layer(5, 16, 100, 5));
			this->add_layer(new Fully_Connected_Layer(100, 84));
			this->add_layer(new Output_Layer(84, 10));
		}

		~LeNet5(){}
		
		void train(std::vector<Sample*> s/*std::vector<std::vector<std::float_t>> x, std::vector<uint8_t> y*/, size_t number){
			for (size_t round = 16; round < 17; round++){
				std::cout << "training label:" << (int)s[round]->label << std::endl;
				layers.front() ->input = s[round]->image;
				std::vector<float_t> r = this->foward();
				for (auto i = r.begin(); i != r.end(); i++){
					std::cout << *i << std::endl;
				}
			}
		}

		std::vector<float_t> foward(){
			std::cout << "forward propagation start." << std::endl;
			for (auto layer : layers){
				/*forward calculate*/
				layer->forward();
				
				if (layer->next != nullptr)
					layer->next->input = layer->output;
			}
			return layers[6]->output;
		}
		
		void add_layer(Layer* layer){
			if (!layers.empty())
				this->layers.back()->next = layer;
			this->layers.push_back(layer);
		}

		float_t mse(float_t y, float_t t) {
			return (y - t) * (y - t) / 2;
		}

	/*private:*/
		std::vector<Layer*> layers;
	};

}// namespace lenet5