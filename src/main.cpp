#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

#include "../include/billiard.hpp"
#include "../include/statistics.hpp"

template <typename T>
void getInput(T& input)
{
	std::cin >> input;
	if (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		throw std::runtime_error{"input error"};
	}
}

int main()
{
	std::cout << "Insert the y-value of the left and right vertices of the billiard, and its lenght. Separate the "
				 "inputs with a space: ";
	double r1{};
	double r2{};
	double l{};

	getInput(r1);
	getInput(r2);
	getInput(l);

	Billiard billiard{r1, r2, l};

	std::default_random_engine engine{std::random_device{}()};

	double mu_y0{};
	double sigma_y0{};

	std::cout << "Insert the mean and sigma of the normal distribution of y_0: ";

	getInput(mu_y0);

	if (std::abs(mu_y0) > r1)
	{
		throw std::domain_error{"y0 mean has to be between -r1 and +r1"};
	}

	getInput(sigma_y0);

	std::normal_distribution<double> dist_y{mu_y0, std::abs(sigma_y0)};

	double mu_th0{};
	double sigma_th0{};

	std::cout << "Insert the mean and sigma of the normal distribution of theta_0: ";

	getInput(mu_th0);

	if (std::abs(mu_th0) > M_PI_2)
	{
		throw std::domain_error{"theta0 mean has to be between -pi/2 and +pi/2"};
	}

	getInput(sigma_th0);

	std::normal_distribution<double> dist_th{mu_th0, sigma_th0};

	int N{};
	std::cout << "Insert the number of particles in the simulation: ";

	getInput(N);

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
		if ((*it).x == l)
		{
			++esc_part;
		}
		++it;
	}
	const float perc_esc{static_cast<float>(esc_part * 100 / billiard.size())};

	const auto stat{statistics(billiard.getParticles())};
	std::cout << "***\n";
	std::cout << "y_f mean: " << stat.mean_y << ", y_0 mean was " << mu_y0 << '\n';
	std::cout << "y_f sigma: " << stat.sigma_y << ", y_0 sigma was " << sigma_y0 << '\n';
	std::cout << "theta_f mean: " << stat.mean_theta << ", theta_0 mean was " << mu_th0 << '\n';
	std::cout << "theta_f sigma: " << stat.sigma_theta << ", theta_0 sigma was " << sigma_th0 << '\n';
	std::cout << "Out of " << N << " particles, " << billiard.size() << " were generated with valid parameters.\n";
	std::cout << "Of those, " << esc_part << " escaped the billiard (" << perc_esc << "%).\n";
	std::cout << "***\n";
}