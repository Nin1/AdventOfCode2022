#include "PuzzleDay2.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

// An elf has handed us a secret code that indicates how to win the rock-paper-scissors tournament.
// Each line follows the pattern <A/B/C> <X/Y/Z>, e.g. "A X".
// To avoid suspicion, the code does not tell us to win every time. It just tells us how to get the highest believable score.

// Scoring:
// +1 if you select rock
// +2 if you select paper
// +3 if you select scissors
// +0 if you lost
// +3 if you draw
// +6 if you win

/** Score values for each outcome */
constexpr int SCORE_WIN = 6;
constexpr int SCORE_TIE = 3;
constexpr int SCORE_LOSE = 0;
constexpr int SCORE_ROCK = 1;
constexpr int SCORE_PAPER = 2;
constexpr int SCORE_SCISSORS = 3;
// Opponent indices are 1, 2, 3 for rock, paper, scissors respectively
constexpr int OPP_ROCK = ((int)'A' & 0b11);
constexpr int OPP_PAPER = ((int)'B' & 0b11);
constexpr int OPP_SCISSORS = ((int)'C' & 0b11);
// Self indices are 0, 1, 2 for rock, paper, scissors respectively
constexpr int SELF_ROCK = ((int)'X' & 0b11);
constexpr int SELF_PAPER = ((int)'Y' & 0b11);
constexpr int SELF_SCISSORS = ((int)'Z' & 0b11);
// Self indices are 0, 1, 2 for lose, tie, and win respectively
constexpr int SELF_LOSE = ((int)'X' & 0b11);
constexpr int SELF_TIE = ((int)'Y' & 0b11);
constexpr int SELF_WIN = ((int)'Z' & 0b11);

// Combine opponent and self indices into a single 4-bit index
inline int CombineIndex(int oppIndex, int selfIndex)
{
	return (oppIndex << 2) | selfIndex;
}

/** Calculates a lookup table of possible scores for each possible outcome, using the first understanding of the secret code. */
std::array<int, 16> CalculateScoreTable1()
{
	std::array<int, 16> scoreTable;
	scoreTable[CombineIndex(OPP_ROCK, SELF_ROCK)] = SCORE_TIE + SCORE_ROCK;
	scoreTable[CombineIndex(OPP_ROCK, SELF_PAPER)] = SCORE_WIN + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_ROCK, SELF_SCISSORS)] = SCORE_LOSE + SCORE_SCISSORS;
	scoreTable[CombineIndex(OPP_PAPER, SELF_ROCK)] = SCORE_LOSE + SCORE_ROCK;
	scoreTable[CombineIndex(OPP_PAPER, SELF_PAPER)] = SCORE_TIE + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_PAPER, SELF_SCISSORS)] = SCORE_WIN + SCORE_SCISSORS;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_ROCK)] = SCORE_WIN + SCORE_ROCK;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_PAPER)] = SCORE_LOSE + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_SCISSORS)] = SCORE_TIE + SCORE_SCISSORS;
	return scoreTable;
}

/** Calculates a lookup table of possible scores for each possible outcome, using the second understanding of the secret code. */
std::array<int, 16> CalculateScoreTable2()
{
	std::array<int, 16> scoreTable;
	// Table indices are ((oppIndex << 2) | selfIndex)
	scoreTable[CombineIndex(OPP_ROCK, SELF_LOSE)] = SCORE_LOSE + SCORE_SCISSORS;
	scoreTable[CombineIndex(OPP_ROCK, SELF_TIE)] = SCORE_TIE + SCORE_ROCK;
	scoreTable[CombineIndex(OPP_ROCK, SELF_WIN)] = SCORE_WIN + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_PAPER, SELF_LOSE)] = SCORE_LOSE + SCORE_ROCK;
	scoreTable[CombineIndex(OPP_PAPER, SELF_TIE)] = SCORE_TIE + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_PAPER, SELF_WIN)] = SCORE_WIN + SCORE_SCISSORS;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_LOSE)] = SCORE_LOSE + SCORE_PAPER;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_TIE)] = SCORE_TIE + SCORE_SCISSORS;
	scoreTable[CombineIndex(OPP_SCISSORS, SELF_WIN)] = SCORE_WIN + SCORE_ROCK;
	return scoreTable;
}

/**
 * Returnes the accumulated score from each round, calculated from the passed-in lookup table.
 */
const int CalculateScore(std::ifstream& strategyFile, const std::array<int, 16>& scoreTable)
{
	int score = 0;

	// Line format is: <Opponent> <You>
	std::string line;
	while (std::getline(strategyFile, line))
	{
		if (line.length() >= 3)
		{
			// Create an index from the 
			int oppIndex = (line[0] & 0b11);
			int selfIndex = (line[2] & 0b11);
			score += scoreTable[(oppIndex << 2) | selfIndex];
		}
	}
	return score;
}

void PuzzleDay2::Execute() const
{
	std::cout << "An elf has given you a stretegy guide for the upcoming Rock-Paper-Scissors tournament." << std::endl;

	// Open text file
	std::ifstream strategyFile;
	strategyFile.open("Day 2/Strategy.txt", std::ios::in);
	if (strategyFile.is_open())
	{
		const std::array<int, 16> scoreTable = CalculateScoreTable1();
		int score = CalculateScore(strategyFile, scoreTable);
		std::cout << "Following your first strategy, you would score " << score << " points." << std::endl;
		strategyFile.close();
	}

	strategyFile.open("Day 2/Strategy.txt", std::ios::in);
	if (strategyFile.is_open())
	{
		const std::array<int, 16> scoreTable = CalculateScoreTable2();
		int score = CalculateScore(strategyFile, scoreTable);
		std::cout << "Following the actual strategy, you would score " << score << " points." << std::endl;
		strategyFile.close();
	}
}