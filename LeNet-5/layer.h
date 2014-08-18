#include <iostream>
#pragma once
namespace lenet5 {

	struct Layer
	{
	private:
		virtual void init_weight() = 0;
	};

}// namespace lenet5