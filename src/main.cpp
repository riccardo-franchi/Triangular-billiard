#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

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

	std::cout << "Enter a command:\n"
			  << "g = generate a sample of N particles and run the simulation\n"
			  << "r = read the sample's particles from a file and run the simulation\n"
			  << "s = print results' statistics onscreen\n"
			  << "f = save results' statistics on a file\n"
			  << "q = quit the program\n"
			  << "h = list of commands\n";

	double mu_y0{};
	double sigma_y0{};
	double mu_th0{};
	double sigma_th0{};
	int N{};

	char command{};
	while (true)
	{
		getInput(command);
		switch (command)
		{
		case 'h':
		{
			std::cout << "Commands:\n"
					  << "g = generate a sample of N particles and run the simulation\n"
					  << "r = read the sample's particles from a file and run the simulation\n"
					  << "s = print results' statistics onscreen\n"
					  << "f = save results' statistics on a file\n"
					  << "q = quit the program\n";
			break;
		}
		case 'g':
		{
			billiard.clear();
			// static_assert(billiard.size() == 0);

			std::default_random_engine engine{std::random_device{}()};

			std::cout << "Insert the mean and sigma of the normal distribution of y_0: ";
			getInput(mu_y0);
			if (std::abs(mu_y0) > r1)
			{
				throw std::domain_error{"y0 mean has to be between -r1 and +r1"};
			}
			getInput(sigma_y0);
			std::normal_distribution<double> dist_y{mu_y0, std::abs(sigma_y0)};

			std::cout << "Insert the mean and sigma of the normal distribution of theta_0: ";
			getInput(mu_th0);
			if (std::abs(mu_th0) > M_PI_2)
			{
				throw std::domain_error{"theta0 mean has to be between -pi/2 and +pi/2"};
			}
			getInput(sigma_th0);
			std::normal_distribution<double> dist_th{mu_th0, sigma_th0};

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

			billiard.runSimulation();
			std::cout << "***\n";
			std::cout << "Simulation of " << N << " particles successfully run.\n";
			std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
			std::cout << "***\n";
			break;
		}
		case 'r':
		{
			billiard.empty();

			std::string fileName;
			std::cout << "Insert the file name: ";
			std::cin >> fileName;

			std::ifstream in_file(fileName.c_str());
			if (!in_file)
			{
				throw std::runtime_error{"File not found!"};
			}
			if (in_file.is_open())
			{
				double y;
				double theta;
				int invalidParts{0};
				while (in_file >> y >> theta)
				{
					if (std::abs(y) < r1 && std::abs(theta) < M_PI_2)
					{
						Particle particle{y, theta};
						billiard.push_back(particle);
					}
					else
					{
						++invalidParts;
					}
				}
				billiard.runSimulation();
				std::cout << "***\n";
				std::cout << "Input file read successfully, simulation run." << '\n';
				if (invalidParts != 0)
				{
					std::cout << invalidParts << " particles had invalid initial coordinates and have been excluded.\n";
				}
				else
				{
					std::cout << "All particles had valid initial coordinates.\n";
				}
				std::cout << "***\n";
				std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
			}
			else
			{
				throw std::runtime_error{"Impossible to open file!"};
			}
			std::cout << "***\n";
			break;
		}
		case 's':
		{
			const auto stat{statistics(billiard.getParticles(), l)};
			std::cout << "***\n";
			std::cout << "y_f mean: " << stat.mean_y << '\n';
			std::cout << "y_f sigma: " << stat.sigma_y << '\n';
			std::cout << "theta_f mean: " << stat.mean_theta << '\n';
			std::cout << "theta_f sigma: " << stat.sigma_theta << '\n';
			std::cout << "y_f skewness: " << stat.skewness_y << '\n';
			std::cout << "theta_f skewness: " << stat.skewness_th << '\n';
			std::cout << "y_f kurtosis: " << stat.kurtosis_y << '\n';
			std::cout << "theta_f kurtosis: " << stat.kurtosis_th << '\n';
			std::cout << /* "Out of " << N << " particles, " <<*/ billiard.size()
					  << " particles were generated with valid parameters.\n";
			const float escPerc{static_cast<float>(stat.escPartsNum * 100 / billiard.size())};
			std::cout << "Of those, " << stat.escPartsNum << " escaped the billiard (" << escPerc << "%).\n";
			std::cout << "***\n";
			break;
		}
		case 'f':
		{
			const auto stat{statistics(billiard.getParticles(), l)};
			std::ofstream out_file{"results.txt"};
			if (!out_file)
			{
				throw std::runtime_error{"Impossible to open file!"};
			}
			if (out_file.is_open())
			{
				out_file << "y_f mean: " << stat.mean_y << '\n';
				out_file << "y_f sigma: " << stat.sigma_y << '\n';
				out_file << "theta_f mean: " << stat.mean_theta << '\n';
				out_file << "theta_f sigma: " << stat.sigma_theta << '\n';
				out_file << "y_f skewness: " << stat.skewness_y << '\n';
				out_file << "theta_f skewness: " << stat.skewness_th << '\n';
				out_file << "y_f kurtosis: " << stat.kurtosis_y << '\n';
				out_file << "theta_f kurtosis: " << stat.kurtosis_th << '\n';
				std::cout << "Output file written successfully. Type \'s\' to print the results onscreen.\n";
			}
			else
			{
				throw std::runtime_error{"Impossible to open file!"};
			}
			std::cout << "***\n";
			break;
		}
		case 'q':
		{
			return 0;
		}
		default:
		{
			std::cout << "Invalid input. Type \'h\' to see a list of commands.\n";
			break;
		}
		}
	}
}