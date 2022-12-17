#pragma once
#include <algorithm>

/** Base puzzle class. Override for each day to create the puzzle. */
class Puzzle
{
public:
	Puzzle() {}
	virtual ~Puzzle() {}

	virtual void Execute() const = 0;
private:
};

