#include <fstream>
#include <random>

int main()
{

	const int NParts{100'000};
	const double meanY0{1.5};
	const double sigmaY0{0.5};
	const double meanTheta0{-0.25};
	const double sigmaTheta0{0.5};

	std::default_random_engine engine{std::random_device{}()};
	std::normal_distribution<double> yDistr{meanY0, sigmaY0};
	std::normal_distribution<double> thetaDistr{meanTheta0, sigmaTheta0};

	std::ofstream outFile{"InitParts.txt"};

	for (int n{0}; n != NParts; ++n)
	{
		outFile << yDistr(engine) << ' ' << thetaDistr(engine) << '\n';
	}
}