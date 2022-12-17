#include "PuzzleList.h"
#include "Day 1/PuzzleDay1.h"
#include "Day 2/PuzzleDay2.h"
#include <algorithm>

void AddPuzzle(int day, std::string&& desc, std::unique_ptr<Puzzle>&& puzzle, std::vector<std::unique_ptr<Puzzle>>& puzzleList, std::vector<std::string>& descList)
{
	if (puzzleList.size() < day)
	{
		puzzleList.resize(day);
		descList.resize(day);
	}

	puzzleList[day - 1] = std::move(puzzle);
	descList[day - 1] = std::move(desc);
}

PuzzleList::PuzzleList()
{
	m_puzzles.reserve(NUM_DAYS);
	m_descriptions.reserve(NUM_DAYS);
	AddPuzzle(1, "Calorie Counting", std::make_unique<PuzzleDay1>(), m_puzzles, m_descriptions);
	AddPuzzle(2, "Rock-Paper-Scissors", std::make_unique<PuzzleDay2>(), m_puzzles, m_descriptions);
}