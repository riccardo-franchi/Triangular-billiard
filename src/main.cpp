#include "../include/commands.hpp"

int main()
{
	const std::string commands{"b = set the parameters of the billiard, if you don't select this option default "
							   "parameters (5., 3., 13.) will be used\n"
							   "g = generate a sample of N particles and run the simulation\n"
							   "r = read the sample particles from a file and run the simulation\n"
							   "s = compute and print statistics onscreen\n"
							   "f = compute and save statistics on a file\n"
							   "p = save the final coordinates of each particle on a file\n"
							   "x = run multiple simulations increasing billiard's length l with fixed step, with the "
							   "same particle sample, and save result statistics on a file\n"
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
				break;
			}
			case 'h':
			{
				std::cout << "Commands:\n" << commands;
				break;
			}
			case 'g':
			{
				generateParticles(billiard);
				billiard.runSimulation();

				printStars(5);
				std::cout << "Simulation successfully run.\n";
				std::cout << "Type \'s\' to compute and print statistics, or \'f\' to save them on a file.\n";
				printStars(5);
				break;
			}
			case 'r':
			{
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