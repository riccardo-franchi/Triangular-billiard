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

	std::cout << "Enter a command:\n"
			  << "g = generate a sample of N particles and run the simulation\n"
			  << "r = read the sample's particles from a file and run the simulation\n"
			  << "s = print results' statistics onscreen\n"
			  << "f = save results' statistics on a file\n"
			  << "q = quit the program\n"
			  << "h = list of commands\n";

	int N{};
	char command{};
	switch (command)
	{
	case 'h':
		std::cout << "Commands:\n"
				  << "g = generate a sample of N particles and run the simulation\n"
				  << "r = read the sample's particles from a file and run the simulation\n"
				  << "s = print results' statistics onscreen\n"
				  << "f = save results' statistics on a file\n"
				  << "q = quit the program\n";
		break;
	case 'g':
		std::cout << "Insert the number of particles in the simulation: ";
		int k{};
		getInput(k);
		N = k;

		for (int n{0}; n != N; ++n)
		{
			Particle particle{dist_y(engine), dist_th(engine)};

			if (std::abs(particle.y) < r1 && std::abs(particle.theta) < M_PI_2)
			{
				billiard.push_back(particle);
			}
		}

		billiard.runSimulation();

		std::cout << "Simulation of " << N << " particles successfully run.\n";
		std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
		break;
	case 'r':
	/*
	std::ifstream in_file("data.txt");
  if (!in_file) {
	throw std::runtime_error{"Impossible to open file!"};
  }
  double x;
  while (in_file >> x) {
	data.add(x);
  }
  std::cout << "Input file read successfully" << '\n';
  const auto stat{data.statistics()};
  std::cout << "- mean: " << stat.mean << '\n'
			<< "- mean error: " << stat.mean_err << '\n'
			<< "- sigma: " << stat.sigma << '\n'
			<< "- median: " << stat.median << '\n';

  std::ofstream out_file{"results.txt"};
  if (!out_file) {
	throw std::runtime_error{"Impossible to open file!"};
  }
  out_file << "- Read data:" << data.size() << '\n';
  out_file << "- mean: " << stat.mean << '\n'
		   << "- sigma: " << stat.sigma << '\n'
		   << "- mean error: " << stat.mean_err << '\n'
		   << "- median: " << stat.median << '\n';
  std::cout << "Output file written successfully" << '\n';
		return;
		*/
	case 's':
		return;
	case 'f':
		return;
	case 'q':
		return 0;
	default:
		std::cout << "Invalid input. Type \'h\' to see a list of commands.\n";
		break;
	}

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