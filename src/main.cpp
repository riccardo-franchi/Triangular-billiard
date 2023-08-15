#include <algorithm>
#include <execution>
#include <fstream>
#include <iomanip>
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

void printStars(int n)
{
	for (int i{0}; i < n; ++i)
	{
		std::cout << '*';
	}
	std::cout << '\n';
}

void generate(bs::Billiard billiard)
{
	double mu_y0{};
	double sigma_y0{};
	double mu_th0{};
	double sigma_th0{};
	int N{};
	std::default_random_engine engine{std::random_device{}()};

	std::cout << "Insert the mean and sigma of the normal distribution of y_0: ";
	getInput(mu_y0);
	if (std::abs(mu_y0) > billiard.getR1())
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
		bs::Particle particle{dist_y(engine), dist_th(engine)};

		if (std::abs(particle.y) < billiard.getR1() && std::abs(particle.theta) < M_PI_2)
		{
			billiard.push_back(particle);
		}
	}

	billiard.runSimulation();
	printStars(5);
	std::cout << "Simulation of " << N << " particles successfully run.\n";
	std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
	printStars(5);
}

void read(bs::Billiard billiard)
{
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
			if (std::abs(y) < billiard.getR1() && std::abs(theta) < M_PI_2)
			{
				bs::Particle particle{y, theta};
				billiard.push_back(particle);
			}
			else
			{
				++invalidParts;
			}
		}
		billiard.runSimulation();
		printStars(5);
		std::cout << "Input file read successfully, simulation run." << '\n';
		if (invalidParts != 0)
		{
			std::cout << invalidParts << " particles had invalid initial coordinates and have been excluded.\n";
		}
		else
		{
			std::cout << "All particles had valid initial coordinates.\n";
		}
		printStars(5);
		std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
	}
	else
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	printStars(5);
}

void printStatistics(bs::Billiard billiard)
{
	bs::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};
	printStars(5);
	std::cout << "y_f mean: " << stats.y.mean << '\n';
	std::cout << "y_f sigma: " << stats.y.sigma << '\n';
	std::cout << "y_f skewness: " << stats.y.skewness << '\n';
	std::cout << "y_f kurtosis: " << stats.y.kurtosis << '\n';
	std::cout << "theta_f mean: " << stats.theta.mean << '\n';
	std::cout << "theta_f sigma: " << stats.theta.sigma << '\n';
	std::cout << "theta_f skewness: " << stats.theta.skewness << '\n';
	std::cout << "theta_f kurtosis: " << stats.theta.kurtosis << "\n\n";
	std::cout << billiard.size() << " particles were generated with valid parameters.\n";
	std::cout << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
}

void printStatisticsOnFile(bs::Billiard billiard)
{
	bs::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};

	std::string fileName;
	std::cout << "Insert the name of the file to be created (include .txt): ";
	std::cin >> fileName;

	std::ofstream out_file{fileName.c_str()};

	if (!out_file)
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	if (out_file.is_open())
	{
		out_file << "y_f mean: " << stats.y.mean << '\n';
		out_file << "y_f sigma: " << stats.y.sigma << '\n';
		out_file << "y_f skewness: " << stats.y.skewness << '\n';
		out_file << "y_f kurtosis: " << stats.y.kurtosis << '\n';
		out_file << "theta_f mean: " << stats.theta.mean << '\n';
		out_file << "theta_f sigma: " << stats.theta.sigma << '\n';
		out_file << "theta_f skewness: " << stats.theta.skewness << '\n';
		out_file << "theta_f kurtosis: " << stats.theta.kurtosis << "\n\n";
		out_file << billiard.size() << " particles were generated with valid parameters.\n";
		out_file << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
		std::cout << "Output file written successfully. Type \'s\' to print the results onscreen.\n";
	}
	else
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	printStars(5);
}

void printValuesOnFile(bs::Billiard billiard)
{
	std::string fileName;
	std::cout << "Insert the name of the file to be created (include .txt): ";
	std::cin >> fileName;

	std::ofstream out_file{fileName.c_str()};

	if (!out_file)
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	if (out_file.is_open())
	{
		for (const auto& p : billiard.getParticles())
		{
			out_file << p.y << p.theta << '\n';
		}
		std::cout << "Output file written successfully.\n";
	}
	printStars(5);
}

int main()
{
	std::cout << "Insert the y-value of the left and right vertices of the billiard, and its length. Separate the "
				 "inputs with a space: ";
	double r1{};
	double r2{};
	double l{};

	getInput(r1);
	getInput(r2);
	getInput(l);

	bs::Billiard billiard{r1, r2, l};

	printStars(5);

	std::cout << "Enter a command:\n"
			  << "g = generate a sample of N particles and run the simulation\n"
			  << "r = read the sample's particles from a file and run the simulation\n"
			  << "s = print results' statistics onscreen\n"
			  << "f = save results' statistics on a file\n"
			  << "p = save final coordinates of each particle on a file\n"
			  << "q = quit the program\n"
			  << "h = list of commands\n";
	printStars(5);

	std::string input{};
	while (true)
	{
		getInput(input);
		if (input.size() == 1)
		{
			switch (input[0])
			{
			case 'h':
			{
				std::cout << "Commands:\n"
						  << "g = generate a sample of N particles and run the simulation\n"
						  << "r = read the sample's particles from a file and run the simulation\n"
						  << "s = print results' statistics onscreen\n"
						  << "f = save results' statistics on a file\n"
						  << "p = save final coordinates of each particle on a file\n"
						  << "q = quit the program\n";
				break;
			}
			case 'g':
			{
				billiard.clear();
				generate(billiard);
				break;
			}
			case 'r':
			{
				billiard.empty();
				read(billiard);
				break;
			}
			case 's':
			{
				printStatistics(billiard);
				break;
			}
			case 'f':
			{
				printStatisticsOnFile(billiard);
				break;
			}
			case 'p':
			{
				if (billiard.size() == 0)
				{
					std::cout << "A valid simulation must be run before! Enter another command.\n";
					printStars(5);
					break;
				}

				printValuesOnFile(billiard);
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
		else
		{
			std::cout << "Invalid input: enter only one character. Type \'h\' for a list of commands.\n";
		}
	}
}