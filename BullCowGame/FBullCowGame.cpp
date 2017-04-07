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


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "fart";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::CheckGuessValidity(FString) const
{
	return false;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// set up a return variable
	FBullCowCount BullCowCount;
	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
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

	return BullCowCount;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}
