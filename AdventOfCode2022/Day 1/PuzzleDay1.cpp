#include "PuzzleDay1.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

struct Elf
{
	int m_index = -1;
	int m_calories = 0;

	bool IsSet() { return m_index >= 0; }
};

template<size_t N>
const std::array<Elf, N> FindBestElves(std::ifstream& rationsFile)
{
	// Best N elves found so far. Index 0 is the best elf.
	std::array<Elf, N> bestElves;
	Elf currentElf;

	// Read each line and total up each section one at a time.
	// Whenever a section is the new best, note down the elf and calorie count.
	std::string line;
	while (std::getline(rationsFile, line))
	{
		if (line.empty() || line.find_first_not_of("0123456789") != std::string::npos)
		{
			// Line is blank or non-numerical; end current elf
			// Find if this elf needs to be inserted in the best elf list
			for (size_t i = 0; i < bestElves.size(); i++)
			{
				if (currentElf.m_calories > bestElves[i].m_calories)
				{
					// Shift elves down
					for (size_t j = bestElves.size() - 1; j > i; --j)
					{
						bestElves[j] = bestElves[j - 1];
					}
					// Insert elf here
					bestElves[i] = currentElf;
					break;
				}
			}
			currentElf.m_index++;
			currentElf.m_calories = 0;
		}
		else
		{
			// Line is a number; add it to the current calorie count
			currentElf.m_calories += std::stoi(line);
		}
	}
	return bestElves;
}

void PuzzleDay1::Execute() const
{
	std::cout << "The elves have provided a list of how many calories they are each carrying." << std::endl;
	constexpr int BEST_ELF_COUNT = 3;
	std::array<Elf, BEST_ELF_COUNT> bestElves;

	// Open text file
	std::ifstream rationsFile;
	rationsFile.open("Day 1/Rations.txt", std::ios::in);
	if (rationsFile.is_open())
	{
		bestElves = FindBestElves<BEST_ELF_COUNT>(rationsFile);
		rationsFile.close();
	}

	int totalCalories = 0;
	for (int i = 0; i < bestElves.size(); i++)
	{
		std::cout << "Rank " << (i + 1) << ": Elf #" << bestElves[i].m_index << " with " << bestElves[i].m_calories << " calories." << std::endl;
		totalCalories += bestElves[i].m_calories;
	}
	
	if (totalCalories == 0)
	{
		std::cout << "Error reading elves." << std::endl;
	}
	else
	{
		std::cout << "The top " << BEST_ELF_COUNT << " elves are collectively carrying " << totalCalories << " calories." << std::endl;
	}
}