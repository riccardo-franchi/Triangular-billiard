#include <fstream>
#include <random>

int main() {
  double const meanY0{2.};
  double const sigmaY0{0.5};
  double const meanTheta0{-0.3};
  double const sigmaTheta0{0.5};
  int const NParts{100'000};

  std::default_random_engine engine{std::random_device{}()};

  std::normal_distribution<double> yDistr{meanY0, std::abs(sigmaY0)};
  std::normal_distribution<double> thetaDistr{meanTheta0,
                                              std::abs(sigmaTheta0)};

  std::ofstream outFile{"particles.txt"};

  double y{};
  double theta{};

  for (int i{0}; i < NParts; ++i) {
    y = yDistr(engine);
    theta = thetaDistr(engine);
    outFile << y << " " << theta << '\n';
  }
}