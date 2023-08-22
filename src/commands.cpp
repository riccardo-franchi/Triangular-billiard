#include "../include/commands.hpp"

#include "../include/statistics.hpp"

#include <algorithm>
#include <execution>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

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
	std::cout << "Parameters successfully entered.\n"
			  << "Type \'g\' to generate a gaussian sample of N particles and run the simulation, or \'r\' "
				 "to read "
				 "the sample's particles from a file and run the simulation.\n";
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

	billiard.clear();
	billiard.reserve(N);
	for (int n{0}; n != N; ++n)
	{
		tb::Particle p{yDistr(engine), thetaDistr(engine)};

		if (billiard.isParticleValid(p))
		{
			billiard.push_back(p);
		}
	}
	billiard.shrink_to_fit();

	if (billiard.size() == 0)
	{
		throw std::runtime_error{"No valid particles generated"};
	}
}

void readFromFile(tb::Billiard& billiard)
{
	std::string fileName{};
	std::cout << "Insert the file name: ";
	getInput(fileName);

	printStars(5);

	std::ifstream inFile(fileName);
	if (!inFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	double y{};
	double theta{};
	int invalidParts{0};
	std::string line;
	billiard.clear();
	for (int nLines{0}; std::getline(inFile, line); ++nLines)
	{
		if (line.empty())
		{
			continue;
		}
		std::istringstream iss{line};
		if ((iss >> y >> theta) && iss.eof())
		{
			tb::Particle p{y, theta};
			if (billiard.isParticleValid(p))
			{
				billiard.push_back(p);
			}
			else
			{
				++invalidParts;
			}
		}
		else
		{
			std::cout << "Invalid input: " << line << " (line " << nLines + 1 << ")\n";
		}
	}
	billiard.runSimulation();

	printStars(5);
	std::cout << "Input file read successfully, simulation run." << '\n';
	if (invalidParts != 0)
	{
		std::cout << invalidParts << " particle(s) had invalid initial coordinates and have been excluded.\n";
	}

	std::cout << "Type \'s\' to compute and print statistics, or \'f\' to save them on a file.\n";

	printStars(5);
}

void printStatistics(const tb::Billiard& billiard)
{
	const auto stats{statistics(billiard.getEscapedParticles())};

	const double escPerc{stats.n * 100. / billiard.size()};

	std::cout << tb::statsToString(stats) << '\n';
	std::cout << billiard.size() << " particles were generated with valid parameters.\n";
	std::cout << "Of those, " << stats.n << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
	printStars(5);
}

void printStatsToFile(const tb::Billiard& billiard)
{

	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);

	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	const auto stats{statistics(billiard.getEscapedParticles())};

	const double escPerc{stats.n * 100. / billiard.size()};

	outFile << tb::statsToString(stats) << '\n';

	outFile << billiard.size() << " particles were generated with valid parameters.\n";
	outFile << "Of those, " << stats.n << std::setprecision(4) << " escaped the billiard (" << escPerc << "%).\n";
	std::cout << "Output file written successfully. Type \'s\' to print the results onscreen.\n";
	printStars(5);
}

void printValuesToFile(const tb::Billiard& billiard)
{
	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);

	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	for (const auto& p : billiard.getEscapedParticles())
	{
		outFile << p.y << ' ' << p.theta << '\n';
	}
	std::cout << "Output file written successfully.\n";

	printStars(5);
}

void generateL(tb::Billiard& billiard)
{
	generateParticles(billiard);

	printStars(5);
	std::string fileName{};
	std::cout << "Insert the name of the file to be created: ";
	getInput(fileName);
	std::ofstream outFile{fileName};

	if (!outFile)
	{
		throw std::runtime_error{"Cannot open file"};
	}

	double lf{};
	std::cout << "Insert the final value of l: ";
	getInput(lf);

	double step{};
	std::cout << "Insert the step with which l will be incremented (or decremented): ";
	getInput(step);

	double l{billiard.getL()};
	if (l > lf)
	{
		step = -step;
	}

	int i{0};
	const tb::Billiard startBilliard{billiard};

	for (; (step > 0) ? l < lf : lf < l; l += step)
	{
		billiard = startBilliard;

		billiard.setL(l);
		billiard.runSimulation();
		const auto stats{statistics(billiard.getEscapedParticles())};

		outFile << l << ' ' << stats.y.mean << ' ' << stats.y.sigma << ' ' << stats.theta.mean << ' '
				<< stats.theta.sigma << ' ' << stats.y.skewness << ' ' << stats.y.kurtosis << ' '
				<< stats.theta.skewness << ' ' << stats.theta.kurtosis << ' ' << stats.n << '\n';

		++i;
	}
	printStars(5);
	std::cout << "Output file written successfully. " << i << " simulations have been run.\n";
	std::cout << "From left to right you'll find:\nvalue of l, y_f mean, y_f st. dev., theta_f mean, theta_f st. dev, "
				 "y_f skwness, y_f kurtosis, theta_f skewness, theta_f kurtosis, no. of escaped particles.\n";
	printStars(5);
}