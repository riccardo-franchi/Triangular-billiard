#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

int main()
{
	std::cout << "Provide the y-value of the left and right vertices of the billiard, and its lenght. Separate the "
				 "inputs with a space: ";
	double r1{};
	double r2{};
	double l{};

	std::cin >> r1;
	std::cin >> r2;
	std::cin >> l;

	Billiard billiard{r1, r2, l};

	std::random_device r;
	std::default_random_engine engine(r());

	double mu_y0{};
	double sigma_y0{};
	std::cout << "Provide the mean and sigma of the normal distribution of y_0: ";
	std::cin >> mu_y0;
	if (std::abs(mu_y0) > r1)
	{
		throw std::domain_error{"y0 mean has to be between -r1 and +r1"};
	}
	std::cin >> sigma_y0;
	std::normal_distribution<double> dist_y(mu_y0, std::abs(sigma_y0));

	double mu_th0{};
	double sigma_th0{};
	std::cout << "Provide the mean and sigma of the normal distribution of theta_0: ";
	std::cin >> mu_th0;
	std::cin >> sigma_th0;
	std::normal_distribution<double> dist_th(mu_th0, sigma_th0);

	int N{};
	std::cout << "Provide the number of particles in the simulation: ";
	std::cin >> N;

	for (int n{0}; n != N; ++n)
	{
		Particle particle{dist_y(engine), dist_th(engine)};
		billiard.push_back(particle);
	}

	billiard.runSimulation();

	// check if there is an algorithm to do this
	int esc_part{0}; // number of particles that excape the billiard
	auto it{billiard.getParticles().begin()};
	while (it != billiard.getParticles().end())
	{
		if ((*it).x == 13)
		{
			++esc_part;
		}
		++it;
	}

	const auto stat{statistics(billiard.getParticles())};
	std::cout << "y_f mean: " << stat.mean_y << ", y_0 mean was " << mu_y0 << '\n';
	std::cout << "y_f sigma: " << stat.sigma_y << ", y_0 sigma was " << sigma_y0 << '\n';
	std::cout << "theta_f mean: " << stat.mean_theta << ", theta_0 mean was " << mu_th0 << '\n';
	std::cout << "theta_f sigma: " << stat.sigma_theta << " , theta_0 sigma was " << sigma_th0 << '\n';
	std::cout << esc_part << " particles escaped the billiard, out of " << N << ".\n";
}