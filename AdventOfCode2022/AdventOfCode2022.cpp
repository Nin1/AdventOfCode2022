#include <iostream>
#include "PuzzleList.h"

void PrintPuzzleList(const PuzzleList& puzzleList)
{
	for (int i = 0; i < puzzleList.Length(); i++)
	{
		if (puzzleList.HasPuzzleAtIndex(i))
		{
			std::cout << (i + 1) << ": " << puzzleList.GetDescByIndex(i) << std::endl;
		}
	}
}

int main()
{
	PuzzleList puzzleList;
	bool exit = false;
	while (!exit)
	{
		// Print list of puzzles to select
		std::cout << "Choose a day:" << std::endl;
		std::cout << "===================" << std::endl;
		PrintPuzzleList(puzzleList);
		std::cout << "0: Exit" << std::endl << std::endl;

		// Get user input
		int selection;
		std::cout << "Selection: ";
		std::cin >> selection;

		// Validate input
		if (selection == 0)
		{
			exit = true;
			break;
		}
		if (!puzzleList.HasPuzzleAtDay(selection))
		{
			std::cout << "Invalid selection: " << selection << std::endl << std::endl;
			continue;
		}

		// Execute requested puzzle
		puzzleList.GetPuzzleByDay(selection).Execute();
		std::cout << std::endl;
	}
}
