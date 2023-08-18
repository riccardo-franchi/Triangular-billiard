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
	std::cout << "Parameters successfully entered.\n";
	std::cout << "Type \'g\' to generate a sample of N particles and run the simulation, or \'r\' to read the sample's "
				 "particles from a file and run the simulation.\n";
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

	/*billiard.runSimulation();
	printStars(5);
	std::cout << "Simulation of " << N << " particles successfully run.\n";
	std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
	printStars(5);*/
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
	generateParticles(billiard);

	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);
	std::ofstream outFile{fileName};

	int NLoops{};
	std::cout << "How many simulations have to be run?\n";
	getInput(NLoops);

	double step{};
	std::cout << "With which step has to be incremented L?\n";
	getInput(step);

	for (int i{0}; i < NLoops; i++)
	{
		double l{billiard.getL()};
		l = l + step;
		billiard.setL(l);
		billiard.runSimulation();
		tb::Statistics statistics{billiard.getL()};
		const auto stats{statistics(billiard.getParticles())};

		int escParts{statistics.getN()};
		double escPerc{escParts * 100. / billiard.size()};

		if (!outFile)
		{
			throw std::runtime_error{"Cannot open file"};
		}

		outFile << tb::Statistics::statsToString(stats) << '\n';

		outFile << billiard.size() << " particles were generated with valid parameters.\n";
		outFile << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
	}
	std::cout << "Output file written successfully.\n";
	printStars(5);
}

#endif // BILLIARD_HPP