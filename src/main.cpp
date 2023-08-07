#include <algorithm>
#include <iomanip>
#include <iostream>

#include "billiard.hpp"

int main()
{
	Billiard billiard{};
	std::random_device r;
	std::default_random_engine engine(r());
	std::normal_distribution<double> dist;

	int N{};
	std::cin >> "Specify the number of entries:" >> N;

	for (int n{0}; n != N; ++n)
	{
		billiard.push_back(dist(engine));
	}

	const auto stat{billiard.statistics()};
	std::cout << "- mean: " << stat.mean << '\n' << "- sigma: " << stat.sigma << '\n';
}