#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <algorithm>
#include <execution>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

#include "billiard.hpp"
#include "statistics.hpp"

template <typename T>
void getInput(T& input)
{
	std::cin >> input;
	if (!std::cin)
	{
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

void setBilliardParams(tb::Billiard& billiard)
{
	std::cout << "Insert the y-value of the left and right vertices of the billiard, and its length. Separate the "
				 "inputs with a space: ";
	double r1{};
	double r2{};
	double l{};

	getInput(r1);
	getInput(r2);
	getInput(l);

	billiard = tb::Billiard{r1, r2, l};

	printStars(5);
}

void generateParticles(tb::Billiard& billiard)
{
	double meanY0{};
	double sigmaY0{};
	double meanTheta0{};
	double sigmaTheta0{};
	int N{};

	std::cout << "Insert the mean and sigma of the normal distribution of y_0: ";
	getInput(meanY0);
	if (std::abs(meanY0) > billiard.getR1())
	{
		throw std::domain_error{"y0 mean has to be between -r1 and +r1"};
	}
	getInput(sigmaY0);

	std::cout << "Insert the mean and sigma of the normal distribution of theta_0: ";
	getInput(meanTheta0);
	if (std::abs(meanTheta0) > M_PI_2)
	{
		throw std::domain_error{"theta0 mean has to be between -pi/2 and +pi/2"};
	}
	getInput(sigmaTheta0);

	std::cout << "Insert the number of particles in the simulation: ";
	getInput(N);

	std::default_random_engine engine{std::random_device{}()};

	std::normal_distribution<double> yDistr{meanY0, std::abs(sigmaY0)};
	std::normal_distribution<double> thetaDistr{meanTheta0, std::abs(sigmaTheta0)};

	for (int n{0}; n != N; ++n)
	{
		tb::Particle particle{yDistr(engine), thetaDistr(engine)};

		if (std::abs(particle.y) < billiard.getR1() && std::abs(particle.theta) < M_PI_2)
		{
			billiard.push_back(particle);
		}
	}

	if (billiard.size() == 0)
	{
		throw std::runtime_error{"No valid particles generated"};
	}
}

int readFromFile(tb::Billiard& billiard)
{

	std::string fileName{};
	std::cout << "Insert the file name: ";
	getInput(fileName);

	printStars(5);

	std::ifstream inFile(fileName);
	if (!inFile)
	{
		throw std::runtime_error{"File not found"};
	}

	double y;
	double theta;
	int invalidParts{0};
	int invalidLines{0};
	std::string line;
	billiard.clear();
	for (int nLines{0}; std::getline(inFile, line); ++nLines)
	{
		if (line.empty()) // skips empty line
		{
			continue;
		}
		std::istringstream iss{line};
		if ((iss >> y >> theta) && iss.eof())
		{
			if (std::abs(y) < billiard.getR1() && std::abs(theta) < M_PI_2)
			{
				tb::Particle particle{y, theta};
				billiard.push_back(particle);
			}
			else
			{
				++invalidParts;
			}
		}
		else
		{
			++invalidLines;
			std::cout << "Invalid input: " << line << " (line " << nLines << ")\n";
		}
	}
	billiard.runSimulation();

	printStars(5);
	std::cout << "Input file read successfully, simulation run." << '\n';
	if (invalidLines != 0)
	{
		std::cout << invalidLines << " line(s) had invalid input.\n";
	}
	if (invalidParts != 0)
	{
		std::cout << invalidParts << " particle(s) had invalid initial coordinates and have been excluded.\n";
	}
	printStars(5);
	std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";

	printStars(5);
	return billiard.size();
}

void printStatistics(const tb::Billiard& billiard)
{
	tb::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};
	printStars(5);
	std::cout << tb::Statistics::statsToString(stats) << '\n';
	std::cout << billiard.size() << " particles were generated with valid parameters.\n";
	std::cout << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
}

void printStatsToFile(const tb::Billiard& billiard)
{
	tb::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};

	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);

	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	outFile << tb::Statistics::statsToString(stats) << '\n';

	outFile << billiard.size() << " particles were generated with valid parameters.\n";
	outFile << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
	std::cout << "Output file written successfully. Type \'s\' to print the results onscreen.\n";

	printStars(5);
}

void printValuesToFile(const tb::Billiard& billiard)
{
	std::string fileName{};
	std::cout << "Insert the name of the file to be created (include .txt): ";
	getInput(fileName);

	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Could not open file"};
	}

	for (const auto& p : billiard.getParticles())
	{
		if (p.x == billiard.getL())
		{
			outFile << p.y << ' ' << p.theta << '\n';
		}
	}
	std::cout << "Output file written successfully.\n";

	printStars(5);
}

void generateL(tb::Billiard& billiard)
{
	setBilliardParams(billiard);
	double l{billiard.getL()};
	generateParticles(billiard);

	const tb::Billiard startBilliard{billiard};

	printStars(5);
	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);
	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	double lF{};
	std::cout << "Insert the final value of l: ";
	getInput(lF);

	double step{};
	std::cout << "Insert the step with which l will be incremented (or decremented): ";
	getInput(step);

	if (l > lF)
	{
		step = -step;
	}

	int i{0};

	for (; (step > 0) ? l < lF : lF < l; l += step)
	{
		billiard = startBilliard; // reset billiard

		billiard.setL(l);
		billiard.runSimulation();
		tb::Statistics statistics{billiard.getL()};
		const auto stats{statistics(billiard.getParticles())};
		const int escParts{statistics.getN()};

		outFile << l << ' ' << stats.y.mean << ' ' << stats.y.sigma << ' ' << stats.theta.mean << ' '
				<< stats.theta.sigma << ' ' << stats.y.skewness << ' ' << stats.y.kurtosis << ' '
				<< stats.theta.skewness << ' ' << stats.theta.kurtosis << ' ' << escParts << '\n';

		++i;
	}
	printStars(5);
	std::cout << "Output file written successfully. " << i << " simulations have been run.\n";
	std::cout << "From left to right you'll have: value of l, y_f mean, y_f st. dev., theta_f mean, theta_f st. dev, "
				 "y_f skwness, y_f kurtosis, theta_f skewness, theta_f kurtosis and the number of escaped particles.\n";
	printStars(5);
}

#endif // BILLIARD_HPP