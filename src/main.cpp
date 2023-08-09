#include <fstream>
#include <iostream>
#include <random>

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

int main()
{
	std::cout << "Provide the y-value of the left and right verteces of the billiard" double r1{};
	double r2{};
	double l{};

	std::cin >> r1;
	std::cin >> r2;
	std::cin >> l;

	Billiard billiard{r1, r2, l};

	std::random_device r;
	std::default_random_engine engine(r());

	double mu_y{};
	double sigma_y{};
	std::normal_distribution<double> dist_y(mu_y, sigma_y);
	double mu_th{};
	double sigma_th{};
	std::normal_distribution<double> dist_th(mu_th, sigma_th);

	int N{};
	std::cin >> N;

	for (int n{0}; n != N; ++n)
	{
		Particle particle{dist_y(engine), dist_th(engine)};
		billiard.push_back(particle);
	}

	const auto stat{statistics(billiard.getParticles())};
	std::cout << "y_f mean: " << stat.mean_y << '\n'; // add << "y_0 mean was ..." etc.
	std::cout << "y_f sigma: " << stat.sigma_y << '\n';
	std::cout << "theta_f mean: " << stat.mean_theta << '\n';
	std::cout << "theta_f sigma: " << stat.sigma_theta << '\n';
}