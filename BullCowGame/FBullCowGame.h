#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// initializes all values to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	FBullCowGame(); // refer to constructor

	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	bool CheckGuessValidity(FString) const; // TODO make a more rich return value
	
	void Reset(); // TODO make a more rich return value
	// counts bulls and cows, and increases turn number, assuming valid guess
	FBullCowCount SubmitGuess(FString Guess);


	
// Ignore this and focus on interface
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};