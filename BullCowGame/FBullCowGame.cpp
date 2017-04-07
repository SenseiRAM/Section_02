#include "FBullCowGame.h"

using int32 = int;

// this is the constructor, which sets starting values using the Reset() function
FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }


void FBullCowGame::Reset() // resets all game defaults
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "fart";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)// if guess isn't lowercase
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

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// set up a return variable that contains both bulls and cows
	FBullCowCount BullCowCount;
	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length(); // get length of hidden word for loop
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
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

	return BullCowCount; // give back the variable which contains both bulls and cows
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}
