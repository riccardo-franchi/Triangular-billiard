#include <iostream>

#include "../include/commands.hpp"

int main()
{

	const std::string commands{"b = set the parameters of the billiard, if you don't select this option default "
							   "parameters (1., 1., 1.) will be used in your simulation\n"
							   "g = generate a sample of N particles and run the simulation\n"
							   "r = read the sample's particles from a file and run the simulation\n"
							   "s = print results' statistics onscreen\n"
							   "f = save results' statistics on a file\n"
							   "p = save final coordinates of each particle on a file\n"
							   "x = run N simulations varying billiard's lenght L, with the same particle sample\n"
							   "q = quit the program\n"
							   "h = list of commands\n"};

	std::cout << "Enter a command:\n" << commands;
	printStars(5);

	tb::Billiard billiard{};
	char input{};
	while (true)
	{
		try
		{
			getInput(input);
			switch (input)
			{
			case 'b':
			{
				setBilliardParams(billiard);
				std::cout << "Parameters successfully entered.\n";
				std::cout << "Type \'g\' to generate a sample of N particles and run the simulation, or \'r\' to read "
							 "the sample's "
							 "particles from a file and run the simulation.\n";
				printStars(5);
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
				billiard.runSimulation();

				printStars(5);
				std::cout << "Simulation successfully run.\n";
				std::cout << "Type \'s\' to print onscreen statistics, or \'f\' to save them on a file.\n";
				printStars(5);
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
			case 'x':
			{
				generateL(billiard);
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
		catch (std::exception& e)
		{
			std::cout << e.what() << ".\nPlease enter another command.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		catch (...)
		{
			std::cout << "An unknown error occurred.\n";
		}
	}
}