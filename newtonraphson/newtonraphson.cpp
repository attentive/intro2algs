#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
		typedef double (*DoubleFunc)(double);

		double function1(double n)
		{
				return 100*n*n - pow(2, n);
		}

		double deriv1(double n)
		{
				static const double LOG2 = log(2);
				return 200*n - pow(2, n)*LOG2;
		}

		double function2(double n)
		{
				return 8*log10(n) - n;
		}

		double deriv2(double n)
		{
				static const double K = 8/log(10);
				return K/n - n;
		}

		// we have y = x * f'(x) + C
		// so C = y - x * f'(x)
		// we have 0 = x' * f'(x) + C
		// so x' = -C/f'(x)
		//       = (x*f'(x) - y)/f'(x)
		//       = x - y/f'(x)

		double estimate_zero(DoubleFunc func, DoubleFunc deriv, double current)
		{
				return current - (func(current) / deriv(current));
		}

		const double MAX_ERROR = 0.0005;
		const double INIT = 0.0;
		const int MAX_TRIES = 1000;

		double get_root(DoubleFunc func, DoubleFunc deriv, double init)
		{
				double val = func(init);
				double root = init;
				int iterations = 0;

				while (fabs(val) >= MAX_ERROR && iterations < MAX_TRIES)
				{
						root = estimate_zero(func, deriv, root);
						std::cout << "new root: " << root << std::endl;
						val = func(root);
						std::cout << "new val: " << val << std::endl;
						iterations++;
				}
				return root;
		}

		struct Applier
		{
				Applier(const DoubleFunc& f): func_(f) {}
				double operator()(double val) const { return func_(val); }
				const DoubleFunc& func_;
		};

		struct Generator
		{
				Generator(): val_(0.0) {}
				double operator()() { return val_+=1.0; }
				double val_;
		};
}

int main(int, char*[])
{
		std::vector<double> inputs;
		std::generate_n(std::back_inserter(inputs), Generator(), 20);
		std::cout << "Inputs: ";
		std::copy(inputs.begin(), inputs.end(), std::ostream_iterator<double>(std::cout, " "));
		std::cout << std::endl;

		std::cout << "Func1: ";
		std::vector<double> outputs;
		outputs.reserve(inputs.size());
		std::transform(inputs.begin(), outputs.begin(), std::back_inserter(outputs), Applier(function1));
		std::copy(outputs.begin(), outputs.end(), std::ostream_iterator<double>(std::cout, " "));
		std::cout << std::endl;

		std::cout << "Func2: ";
		outputs.clear();
		std::transform(inputs.begin(), outputs.begin(), std::back_inserter(outputs), Applier(function2));
		std::copy(outputs.begin(), outputs.end(), std::ostream_iterator<double>(std::cout, " "));
		std::cout << std::endl;


		const double FIRST_N = get_root(function1, deriv1, INIT);
		const double SECOND_N = get_root(function2, deriv2, INIT);
		std::cout << "Solution of 100n^2 = 2^n: " << FIRST_N << std::endl;
		std::cout << "Solution of n = 8logn: " << SECOND_N << std::endl;
		return 0;
}


