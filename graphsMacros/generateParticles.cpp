#include <fstream>
#include <random>

int main()
{

	const int NParts{10'000'000};
	const double meanY0{-2};
	const double sigmaY0{1};
	const double meanTheta0{0.25};
	const double sigmaTheta0{1.};

	std::default_random_engine engine{std::random_device{}()};
	std::normal_distribution<double> yDistr{meanY0, sigmaY0};
	std::normal_distribution<double> thetaDistr{meanTheta0, sigmaTheta0};

	std::ofstream outFile{"initial3.txt"};

	for (int n{0}; n != NParts; ++n)
	{
		outFile << yDistr(engine) << ' ' << thetaDistr(engine) << '\n';
	}
}