#include <algorithm>
#include <execution>
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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

		if (std::abs(particle.y) < r1 && std::abs(particle.theta) < M_PI_2)
		{
			billiard.push_back(particle);
		}
	}

	std::cout << "Enter a command:"
			  << "g = generate a sample of N data"
			  << "r = read the sample's datas from a file"
			  << "s = calculate sample's statstics"
			  << "o = calculate sample's statics and print them on a file"
			  << "q = exit";
	/*
		char command{};
		switch (command)
		{
		case 'g':
			int N{};
			std::cout << "Insert the number of particles in the simulation: ";
			getInput(N);

			for (int n{0}; n != N; ++n)
			{
				Particle particle{dist_y(engine), dist_th(engine)};

				if (std::abs(particle.y) < r1 && std::abs(particle.theta) < M_PI_2)
				{
					billiard.push_back(particle);
				}
			}

			return N;
		case 'r':
			return;
		case 's':
			return;
		case 'o':
			return;

		case 'q':
			return 0;
		}
		*/

	billiard.runSimulation();

	int escParts{static_cast<int>(std::count_if(								 /*std::execution::par_unseq,*/
												billiard.getParticles().begin(), //
												billiard.getParticles().end(),	 //
												[l](const Particle& p) { return p.x == l; }))};

	const float escPerc{static_cast<float>(escParts * 100 / billiard.size())};

	const auto stat{statistics(billiard.getParticles(), l)};
	std::cout << "***\n";
	std::cout << "y_f mean: " << stat.mean_y << ", y_0 mean was " << mu_y0 << '\n';
	std::cout << "y_f sigma: " << stat.sigma_y << ", y_0 sigma was " << sigma_y0 << '\n';
	std::cout << "theta_f mean: " << stat.mean_theta << ", theta_0 mean was " << mu_th0 << '\n';
	std::cout << "theta_f sigma: " << stat.sigma_theta << ", theta_0 sigma was " << sigma_th0 << '\n';
	std::cout << "y_f skewness: " << stat.skewness_y << '\n';
	std::cout << "theta_f skewness: " << stat.skewness_th << '\n';
	std::cout << "y_f kurtosis: " << stat.kurtosis_y << '\n';
	std::cout << "theta_f kurtosis: " << stat.kurtosis_th << '\n';
	std::cout << "Out of " << N << " particles, " << billiard.size() << " were generated with valid parameters.\n";
	std::cout << "Of those, " << escParts << " escaped the billiard (" << escPerc << "%).\n";
	std::cout << "***\n";
}