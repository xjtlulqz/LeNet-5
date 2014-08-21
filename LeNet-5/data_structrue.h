#include <vector>
#include <cstdint>
#include <iostream>
#include <assert.h>

namespace lenet5{
	struct Image {
		std::vector< std::vector<std::float_t> > img;// a image is represented by a 2-dimension vector  
		size_t size; // width or height

		// construction
		Image(size_t size_, std::vector< std::vector<std::float_t> > img_) :img(img_), size(size_){}

		// display the image
		void display(){
			for (size_t i = 0; i < size; i++){
				for (size_t j = 0; j < size; j++){
					if (img[i][j] > 200)
						std::cout << 1;
					else
						std::cout << 0;
				}
				std::cout << std::endl;
			}
		}

		// up size to 32, make up with 0
		void upto_32(){
			assert(size < 32);

			std::vector<std::float_t> row(32, 0);

			for (size_t i = 0; i < size; i++){
				img[i].insert(img[i].begin(), 0);
				img[i].insert(img[i].begin(), 0);
				img[i].push_back(0);
				img[i].push_back(0);
			}
			img.insert(img.begin(), row);
			img.insert(img.begin(), row);
			img.push_back(row);
			img.push_back(row);

			size = 32;
		}
	};

	typedef Image* Img;

	struct Sample
	{
		uint8_t label; // label for a specific digit
		Img image;
		Sample(float_t label_, Img image_) :label(label_), image(image_){}
	};

	// tiny-cnn connection_table
	struct Connection_Table {
		Connection_Table() : rows_(0), cols_(0) {}
		Connection_Table(size_t rows, size_t cols) :rows_(rows), cols_(cols), connected_(rows * cols, true){}
		Connection_Table(const bool *ar, size_t rows, size_t cols) : connected_(rows * cols), rows_(rows), cols_(cols) {
			std::copy(ar, ar + rows * cols, connected_.begin());
		}

		bool is_connected(int x, int y) const {
			return is_empty() ? true : connected_[y * cols_ + x];
		}

		bool is_empty() const {
			return rows_ == 0 && cols_ == 0;
		}

		std::vector<bool> connected_;
		size_t rows_;
		size_t cols_;
	};
}