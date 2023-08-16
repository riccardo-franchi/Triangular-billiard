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

void generateParticles(bs::Billiard& billiard)
{
	double meanY0{};
	double sigmaY0{};
	double meanTheta0{};
	double sigmaTheta0{};
	int N{};

	std::default_random_engine engine{std::random_device{}()};

	std::cout << "Insert the mean and sigma of the normal distribution of y_0: ";
	getInput(meanY0);
	if (std::abs(meanY0) > billiard.getR1())
	{
		throw std::domain_error{"y0 mean has to be between -r1 and +r1"};
	}

	getInput(sigmaY0);
	std::normal_distribution<double> yDistr{meanY0, std::abs(sigmaY0)};

	std::cout << "Insert the mean and sigma of the normal distribution of theta_0: ";
	getInput(meanTheta0);
	if (std::abs(meanTheta0) > M_PI_2)
	{
		throw std::domain_error{"theta0 mean has to be between -pi/2 and +pi/2"};
	}

	getInput(sigmaTheta0);
	std::normal_distribution<double> thetaDistr{meanTheta0, std::abs(sigmaTheta0)};

	std::cout << "Insert the number of particles in the simulation: ";
	getInput(N);

	for (int n{0}; n != N; ++n)
	{
		bs::Particle particle{yDistr(engine), thetaDistr(engine)};

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

bool isValidInput(const std::string& line)
{
	std::istringstream iss(line);
	double y{};
	double theta{};
	return (iss >> y >> theta) && iss.eof();
}

int read(bs::Billiard& billiard)
{
	billiard.clear();

	std::string fileName{};
	std::cout << "Insert the file name: ";
	getInput(fileName);

	printStars(5);

	std::ifstream inFile(fileName.c_str());
	if (!inFile)
	{
		throw std::runtime_error{"File not found!"};
	}
	if (inFile.is_open())
	{
		double y;
		double theta;
		int invalidParts{0};
		int lineNum{0};
		int invalidLines{0};
		std::string line;
		while ((std::getline(inFile, line)))
		{
			++lineNum;
			if (line.empty()) // skips empty line
			{
				continue;
			}
			if (isValidInput(line))
			{
				std::istringstream(line) >> y >> theta;
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
			else
			{
				++invalidLines;
				if (invalidLines < 10)
				{
					std::cout << "Invalid input: " << line << " (line " << lineNum << ")\n";
				}
			}
		}
		billiard.runSimulation();
		printStars(5);
		std::cout << "Input file read successfully, simulation run." << '\n';
		if (invalidLines != 0)
		{
			std::cout << invalidLines << " lines had invalid input.\n";
		}
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
	return billiard.size();
}

void printStatistics(bs::Billiard& billiard)
{
	bs::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};
	printStars(5);
	std::cout << bs::Statistics::statsToString(stats) << '\n';
	std::cout << billiard.size() << " particles were generated with valid parameters.\n";
	std::cout << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
}

void printStatisticsOnFile(bs::Billiard& billiard)
{
	bs::Statistics statistics{billiard.getL()};

	const auto stats{statistics(billiard.getParticles())};

	const int escParts{statistics.getN()};
	const double escPerc{escParts * 100. / billiard.size()};

	std::string fileName{};
	std::cout << "Insert the name of the file to be created (include .txt): ";
	getInput(fileName);

	std::ofstream outFile{fileName.c_str()};

	if (!outFile)
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	if (outFile.is_open())
	{
		outFile << bs::Statistics::statsToString(stats) << '\n';

		outFile << billiard.size() << " particles were generated with valid parameters.\n";
		outFile << "Of those, " << escParts << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
		std::cout << "Output file written successfully. Type \'s\' to print the results onscreen.\n";
	}
	else
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	printStars(5);
}

void printValuesOnFile(bs::Billiard& billiard)
{
	std::string fileName{};
	std::cout << "Insert the name of the file to be created (include .txt): ";
	getInput(fileName);

	std::ofstream outFile{fileName.c_str()};

	if (!outFile)
	{
		throw std::runtime_error{"Impossible to open file!"};
	}
	if (outFile.is_open())
	{
		for (const auto& p : billiard.getParticles())
		{
			outFile << p.y << ' ' << p.theta << '\n';
		}
		std::cout << "Output file written successfully.\n";
	}
	printStars(5);
}