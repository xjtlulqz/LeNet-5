#include <iostream>

namespace lenet5{
	class activation {
	public:
		virtual float_t f(float_t x) const = 0;
		virtual float_t df(float_t f_x) const = 0;
		virtual std::pair<float_t, float_t> scale() const = 0;
	};

	class sigmoid_activation : public activation {
	public:
		float_t f(float_t x) const { return 1.0 / (1.0 + std::exp(-x)); }
		float_t df(float_t f_x) const { return f_x * (1.0 - f_x); }
		std::pair<float_t, float_t> scale() const { return std::make_pair(0.1, 0.9); }
	};
}// namespace lenet5