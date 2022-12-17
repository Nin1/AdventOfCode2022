#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Puzzle.h"

/** A list of all the puzzles. */
class PuzzleList
{
public:
	PuzzleList();
	virtual ~PuzzleList() { }

	size_t Length() const { return m_puzzles.size(); }
	bool HasPuzzleAtIndex(size_t index) const { return index < Length() && m_puzzles[index] != nullptr; }
	bool HasPuzzleAtDay(int day) const { return HasPuzzleAtIndex(day - 1); }

	const Puzzle& GetPuzzleByIndex(size_t index) const { return *m_puzzles[index]; }
	const Puzzle& GetPuzzleByDay(int day) const { return GetPuzzleByIndex(day - 1); }

	const std::string& GetDescByIndex(size_t index) const { return m_descriptions[index]; }
	const std::string& GetDescByDay(int day) const { return GetDescByIndex(day - 1); }

private:
	static constexpr int NUM_DAYS = 25;
	std::vector<std::unique_ptr<Puzzle>> m_puzzles;
	std::vector<std::string> m_descriptions;
};

