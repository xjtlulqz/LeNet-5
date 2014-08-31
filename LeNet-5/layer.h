#include <iostream>
#include "boost\random.hpp"
#pragma once
namespace lenet5 {

	struct Layer
	{
		Layer(size_t in_size_, size_t in_depth_, size_t out_depth_) :
			in_size(in_size_), in_depth(in_depth_), out_depth(out_depth_), prev(nullptr), next(nullptr){}
		
		virtual size_t fan_in() = 0;
		virtual size_t fan_out() = 0;
		virtual size_t output_size() = 0;
		
		void init_weight(){
			const float_t weight_base = 0.5 / std::sqrt(fan_in());
			uniform_rand(weight.begin(), weight.end(), -weight_base, weight_base);
			uniform_rand(bias_weight.begin(), bias_weight.end(), -weight_base, weight_base);
		}

		template<typename T>
		inline T uniform_rand(T min, T max) {
			static boost::mt19937 gen(0);
			boost::uniform_real<T> dst(min, max);
			return dst(gen);
		}

		template<typename Iter>
		void uniform_rand(Iter begin, Iter end, float_t min, float_t max) {
			for (Iter it = begin; it != end; ++it)
				*it = uniform_rand(min, max);
		}

		int in_index(int x, int y, int channel) {
			return (in_size * in_size) * channel + in_size * x + y;
		}

		int out_index(int x, int y, int channel) {
			return (out_size * out_size) * channel + out_size * x + y;
		}

		virtual int weight_index(int x, int y, int channel) = 0;

		float_t vec_t_conv(std::vector<float_t> v, std::vector<float_t> w){
			assert(v.size() == w.size());
			float_t f = 0;
			for (size_t i = 0; i < v.size(); i++){
				f += v[i] * w[v.size() - 1- i];
			}
			return f;
		}

		float_t sigmod(float_t x) const { return 1.0 / (1.0 + std::exp(-x)); }

		float_t tanh(float_t x) const {
			const float_t ep = std::exp(x);
			const float_t em = std::exp(-x);
			return (ep - em) / (ep + em);
		}

		virtual void forward() = 0;

		size_t in_size;
		size_t in_depth;
		size_t out_size;
		size_t out_depth; // output feature map number
		std::vector<std::float_t> weight; //
		std::vector<std::float_t> bias_weight;
		std::vector<std::float_t> input;
		std::vector<std::float_t> output;

		Layer* prev;
		Layer* next;
	};

} // namespace lenet5