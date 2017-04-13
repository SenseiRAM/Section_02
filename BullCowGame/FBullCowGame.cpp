#pragma once
#include "FBullCowGame.h"
#include <map>

// used to make syntax Unreal Engine friendly
#define TMap std::map
using int32 = int;

// this is the constructor, which sets starting values using the Reset() function
FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getter functions
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

// returns correct word based on length chosen by user
FString FBullCowGame::InitWordLength() const
{
	TMap <int32, FString> NumberOfLetters{ { 3, "car" },{ 4, "glom" },{ 5, "plane" },{ 6, "flunks" } };
	return NumberOfLetters[AskWordLength];
}

// maximum number of tries based on word length chosen
int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3, 6}, {4, 7}, {5, 10}, {6, 15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() // resets all game defaults
{
	MyHiddenWord = InitWordLength();
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

// return values to pass into valid guess switch statement in main
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; // if guess isn't lowercase
	}
	else if (!IsLowercase(Guess))// if guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	
	else if (GetHiddenWordLength() != Guess.length()) // if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn number, returns bull and cow count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters in guess against hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if letters match
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) // if guess letter is in same position as hidden word letter
				{
					BullCowCount.Bulls++;
				}
				else // if they're not
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) // if number of bulls is same as overall word length YOU WIN
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount; // give back the variable which contains both bulls and cows
}

// helper function to determine if user guess is isogram
bool FBullCowGame::IsIsogram(FString Guess) const
{ 
	// treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }
	
	// setup map
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Guess) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])
		{
			return false; // not an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add letter to the map
		}
	}

	return true; // for example in cases where \0 is entered
}

// helper function to determine if word is all lowercase
bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) // for all letters of the word
	{
		if (!islower(Letter))
		{
			return false; // not lowercase
		}
	}
	return true;
}
