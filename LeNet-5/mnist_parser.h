#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <exception>
#include <cassert>
#include <time.h>
#pragma once
namespace lenet5{

	struct Sample
	{
		uint8_t label;
		std::vector<uint8_t> image;
		Sample(uint8_t label_, std::vector<uint8_t> image_) :label(label_), image(image_){}
	};


	class Mnist_Parser
	{
	public:
		Mnist_Parser() :
			test_img_fname("t10k-images.idx3-ubyte"),
			test_lbl_fname("t10k-labels.idx1-ubyte"),
			train_img_fname("train-images.idx3-ubyte"),
			train_lbl_fname("train-labels.idx1-ubyte"){}

		std::vector<Sample*> load_testing(){
			test_sample = load(test_img_fname, test_lbl_fname);
			return test_sample;
		}

		std::vector<Sample*> load_training(){
			train_sample = load(train_img_fname, train_lbl_fname);
			return train_sample;
		}

		void display(std::vector<uint8_t> v){
			for (size_t i = 0; i < v.size(); i++){
				if (v[i] > 200)
					std::cout << 1;
				else
					std::cout << 0;

				if (i % 32 == 31) std::cout << std::endl;
			}
		}

		void test(){
			srand((int)time(0));
			int i = rand() % 10000;
			std::cout << (int)test_sample[i]->label << std::endl;
			display(test_sample[i]->image);
			i = rand() % 60000;
			std::cout << (int)train_sample[i]->label << std::endl;
			display(train_sample[i]->image);
		}

		void up2_32(){
			
			for (size_t i = 0; i < 60000; i++){
				std::vector<std::uint8_t> new_img(32 * 2, 0);
				for (size_t j = 0; j < 28; j++){
					new_img.push_back(0);
					new_img.push_back(0);
					for (size_t k = 0; k < 28; k++){
						new_img.push_back((train_sample[i]->image)[j * 28 + k]);
					}
					new_img.push_back(0);
					new_img.push_back(0);
				}
				for (size_t i = 0; i < 64; i++){
					new_img.push_back(0);
				}
				train_sample[i]->image = new_img;
			}

			for (size_t i = 0; i < 10000; i++){
				std::vector<std::uint8_t> new_img(32 * 2, 0);
				for (size_t j = 0; j < 28; j++){
					new_img.push_back(0);
					new_img.push_back(0);
					for (size_t k = 0; k < 28; k++){
						new_img.push_back((test_sample[i]->image)[j * 28 + k]);
					}
					new_img.push_back(0);
					new_img.push_back(0);
				}
				for (size_t i = 0; i < 64; i++){
					new_img.push_back(0);
				}
				test_sample[i]->image = new_img;
			}

		}

	private:
		std::vector<Sample*> load(std::string fimage, std::string flabel){
			std::fstream in;
			in.open(fimage, std::ios::binary | std::ios::in);
			if (!in.is_open()){
				std::cout << "file opened failed." << std::endl;
			}

			std::uint32_t magic = 0;
			std::uint32_t number = 0;
			std::uint32_t rows = 0;
			std::uint32_t cols = 0;

			in.read((char*)&magic, sizeof(uint32_t));
			in.read((char*)&number, sizeof(uint32_t));
			in.read((char*)&rows, sizeof(uint32_t));
			in.read((char*)&cols, sizeof(uint32_t));

			assert(swapEndien_32(magic) == 2051);
			std::cout << "number:" << swapEndien_32(number) << std::endl;
			assert(swapEndien_32(rows) == 28);
			assert(swapEndien_32(cols) == 28);

			std::vector< std::vector<uint8_t> > images;

			uint8_t pixel = 0;
			size_t index = 0;
			std::vector<uint8_t> img;
			while (!in.eof()){
				in.read((char*)&pixel, sizeof(uint8_t));
				img.push_back(pixel);
				index++;
				if (index == 28 * 28){
					index = 0;
					images.push_back(img);
					img.clear();
				}
			}

			in.close();

			assert(images.size() == swapEndien_32(number));

			//label
			in.open(flabel, std::ios::binary || std::ios::in);
			if (!in.is_open()){
				std::cout << "failed opened label file";
			}

			in.read((char*)&magic, sizeof(uint32_t));
			in.read((char*)&number, sizeof(uint32_t));

			assert(2049 == swapEndien_32(magic));
			assert(swapEndien_32(number) == images.size());

			std::vector<uint8_t>	labels;

			uint8_t label;
			while (!in.eof())
			{
				in.read((char*)&label, sizeof(uint8_t));
				std::cout << (int)label << std::endl;
				labels.push_back(label);
			}

			std::vector<Sample*> samples;
			for (int i = 0; i < swapEndien_32(number); i++){
				samples.push_back(new Sample(labels[i], images[i]));
			}

			std::cout << "complete" << std::endl;
			in.close();
			return samples;
		}

		std::uint32_t swapEndien_32(std::uint32_t value){
			return ((value & 0x000000FF) << 24) |
				((value & 0x0000FF00) << 8) |
				((value & 0x00FF0000) >> 8) |
				((value & 0xFF000000) >> 24);
		}

		std::string test_img_fname;
		std::string test_lbl_fname;
		std::string train_img_fname;
		std::string train_lbl_fname;

		std::vector<Sample*> test_sample;
		std::vector<Sample*> train_sample;
	};

} // namespace lenet5

