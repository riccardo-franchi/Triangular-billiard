#include <iostream>

#include "../include/commands.hpp"

int main()
{

	const std::string commands{"g = generate a sample of N particles and run the simulation\n"
							   "r = read the sample's particles from a file and run the simulation\n"
							   "s = print results' statistics onscreen\n"
							   "f = save results' statistics on a file\n"
							   "p = save final coordinates of each particle on a file\n"
							   "q = quit the program\n"
							   "h = list of commands\n"};

	std::cout << "Enter a command:\n" << commands;
	printStars(5);

	tb::Billiard billiard{};
	std::string input{};
	while (true)
	{
		try
		{
			getInput(input);
			if (input.size() == 1)
			{
				switch (input[0])
				{
				case 'b':
				{
					billiard = billiardParameters();
					break;
				}
				case 'h':
				{
					std::cout << "Commands:\n" << commands;
					break;
				}
				case 'g':
				{
					billiard.clear();
					generateParticles(billiard);
					break;
				}
				case 'r':
				{
					billiard.clear();
					readFromFile(billiard);
					break;
				}
				case 's':
				{
					printStatistics(billiard);
					break;
				}
				case 'f':
				{
					printStatsToFile(billiard);
					break;
				}
				case 'p':
				{
					if (billiard.size() == 0)
					{
						std::cout << "A valid simulation must be run before! Enter another command.\n";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						printStars(5);
						break;
					}
					printValuesToFile(billiard);
					break;
				}
				case 'q':
				{
					return 0;
				}
				default:
				{
					std::cout << "Invalid input. Type \'h\' to see a list of commands.\n";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				}
			}
			else
			{
				std::cout << "Invalid input: enter only one character. Type \'h\' for a list of commands.\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << ".\nPlease enter another command.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		catch (...)
		{
			std::cout << "An unknown error occurred.\n";
		}
	}
}