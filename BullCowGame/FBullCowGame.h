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

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // refer to constructor

	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); // TODO make a more rich return value
	// counts bulls and cows, and increases turn number, assuming valid guess
	FBullCowCount SubmitValidGuess(FString Guess);


	
// Ignore this and focus on interface
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
};