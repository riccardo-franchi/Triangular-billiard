#include <fstream>
#include <iostream>
#include <random>

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

int main()
{
	double r1{};
	double r2{};
	double l{};

	std::cin >> r1;
	std::cin >> r2;
	std::cin >> l;

	Billiard billiard{r1, r2, l};
	std::random_device r;
	std::default_random_engine engine(r());
	std::normal_distribution<double> dist;

	int N{};
	std::cin >> N;

	for (int n{0}; n != N; ++n)
	{
		Particle particle{dist(engine), dist(engine)};
		billiard.push_back(particle);
	}

	const auto stat{statistics(billiard.getParticles())};
	std::cout << "- mean: " << stat.mean << '\n' << "- sigma: " << stat.sigma << '\n';
}