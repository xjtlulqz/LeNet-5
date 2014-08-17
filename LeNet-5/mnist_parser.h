#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <exception>
#include <cassert>
#include <time.h>
using namespace std;

struct Sample
{
	uint8_t label;
	vector<uint8_t> image;
	Sample(uint8_t label_, vector<uint8_t> image_) :label(label_), image(image_){}
};


class Mnist_Parser
{
public:
	Mnist_Parser() :
		test_img_fname("t10k-images.idx3-ubyte"),
		test_lbl_fname("t10k-labels.idx1-ubyte"),
		train_img_fname("train-images.idx3-ubyte"),
		train_lbl_fname("train-labels.idx1-ubyte"){}

	vector<Sample*> load_testing(){
		test_sample = load(test_img_fname, test_lbl_fname);
		return test_sample;
	}

	vector<Sample*> load_training(){
		train_sample = load(train_img_fname, train_lbl_fname);
		return train_sample;
	}

	void display(vector<uint8_t> v){
		for (size_t i = 0; i < v.size(); i++){
			if (v[i] > 200)
				cout << 1;
			else
				cout << 0;

			if (i % 28 == 27) cout << endl;
		}
	}

	void test(){
		srand((int)time(0));
		int i = rand() % 10000;
		cout << (int)test_sample[i]->label << endl;
		display(test_sample[i]->image);
		i = rand() % 60000;
		cout << (int)train_sample[i]->label << endl;
		display(train_sample[i]->image);
	}

private:
	vector<Sample*> load(string fimage, string flabel){
		fstream in;
		in.open(fimage, ios::binary | ios::in);
		if (!in.is_open()){
			cout << "file opened failed." << endl;
		}

		uint32_t magic = 0;
		uint32_t number = 0;
		uint32_t rows = 0;
		uint32_t cols = 0;

		in.read((char*)&magic, sizeof(uint32_t));
		in.read((char*)&number, sizeof(uint32_t));
		in.read((char*)&rows, sizeof(uint32_t));
		in.read((char*)&cols, sizeof(uint32_t));

		assert(swapEndien_32(magic) == 2051);
		cout << "number:" << swapEndien_32(number) << endl;
		assert(swapEndien_32(rows) == 28);
		assert(swapEndien_32(cols) == 28);

		vector< vector<uint8_t> > images;

		uint8_t pixel = 0;
		size_t index = 0;
		vector<uint8_t> img;
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
		in.open(flabel, ios::binary || ios::in);
		if (!in.is_open()){
			cout << "failed opened label file";
		}

		in.read((char*)&magic, sizeof(uint32_t));
		in.read((char*)&number, sizeof(uint32_t));

		assert(2049 == swapEndien_32(magic));
		assert(swapEndien_32(number) == images.size());

		vector<uint8_t>	labels;

		uint8_t label;
		while (!in.eof())
		{
			in.read((char*)&label, sizeof(uint8_t));
			labels.push_back(label);
		}

		vector<Sample*> samples;
		for (int i = 0; i < swapEndien_32(number); i++){
			samples.push_back(new Sample(labels[i], images[i]));
		}

		cout << "complete" << endl;
		return samples;
	}

	uint32_t swapEndien_32(uint32_t value){
		return ((value & 0x000000FF) << 24) |
			((value & 0x0000FF00) << 8) |
			((value & 0x00FF0000) >> 8) |
			((value & 0xFF000000) >> 24);
	}

	string test_img_fname;
	string test_lbl_fname;
	string train_img_fname;
	string train_lbl_fname;

	vector<Sample*> test_sample;
	vector<Sample*> train_sample;
};

/*
int main(){
	Mnist_Parser s;
	s.load_testing();
	s.load_training();
	s.test();
	return 0;
}
*/