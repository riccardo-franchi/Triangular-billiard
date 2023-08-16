#include <iostream>

#include "../include/interface.hpp"

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

	const std::string commands{"g = generate a sample of N particles and run the simulation\n"
							   "r = read the sample's particles from a file and run the simulation\n"
							   "s = print results' statistics onscreen\n"
							   "f = save results' statistics on a file\n"
							   "p = save final coordinates of each particle on a file\n"
							   "q = quit the program\n"
							   "h = list of commands\n"};

	std::cout << "Enter a command:\n" << commands;
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
				// billiard.clear();
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