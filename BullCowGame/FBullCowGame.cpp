#include "FBullCowGame.h"

using int32 = int;

// this is the constructor, which sets starting values using the Reset() function
FBullCowGame::FBullCowGame()
{
	Reset();
}

//Getter functions up top
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }


void FBullCowGame::Reset() // resets all game defaults
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "glom";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

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
				if (MHWChar == GChar) // if they're in the same place
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
	if (BullCowCount.Bulls == WordLength)
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount; // give back the variable which contains both bulls and cows
}

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

	return true; // for example in cases where /0 is entered
}

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
