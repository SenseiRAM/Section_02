/*
The game logic (no view or user interaction). The game is a simple word game similar to Mastermind.
*/

#pragma once
#include <string>
#include <map>
#define TMap std::map

// to make code friendly for Unreal Engine
using FString = std::string;
using int32 = int;

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
	/*
	See function definitions for explanation
	*/
	
	FBullCowGame(); // refer to constructor

	void AskWordLength(int32);
	FString InitWordLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	// See constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	
	int32 WordDifficulty;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};