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
	const FString HIDDEN_WORD = "fart";
	
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
	else if (false)// if guess isn't lowercase // TODO write function to check lowercase
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

bool FBullCowGame::IsIsogram(FString Word) const
{ 
	// treat 0 and 1 letter words as isograms
	
	// for loop to iterate through letters of the guess
		// check letters against table
		// if letter is in the map
			// NOT an isogram
		// else
			// add the letter to the map as seen

	return true; // for example in cases where /0 is entered
}
