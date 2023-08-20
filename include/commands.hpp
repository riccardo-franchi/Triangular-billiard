#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <stdexcept>

#include "billiard.hpp"

template <typename T>
void getInput(T& input)
{
	std::cin >> input;
	if (!std::cin)
	{
		throw std::runtime_error{"input error"};
	}
}

inline void printStars(int n)
{
	for (int i{0}; i < n; ++i)
	{
		std::cout << '*';
	}
	std::cout << '\n';
}

void setBilliardParams(tb::Billiard& billiard);

void generateParticles(tb::Billiard& billiard);

void readFromFile(tb::Billiard& billiard);

void printStatistics(const tb::Billiard& billiard);

void printStatsToFile(const tb::Billiard& billiard);

void printValuesToFile(const tb::Billiard& billiard);

void generateL(tb::Billiard& billiard);

#endif // BILLIARD_HPP