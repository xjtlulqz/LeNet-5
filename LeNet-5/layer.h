#include <iostream>
#pragma once
namespace lenet5 {

	struct Layer
	{
		virtual void init_weight() = 0;
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
	private:
		Layer* prev;
		Layer* next;
	};

}// namespace lenet5