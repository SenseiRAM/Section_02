/* This is the console executable that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain(); // boolean value of play again is set by play again function
	}
	while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	// Introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << "\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram (word with no repeating letters) I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset(); // Reset the game to defaults
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Correct letter in correct position = " << BullCowCount.Bulls;
		std::cout << ". Correct letter in wrong position = " << BullCowCount.Cows << "\n\n";
		
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Win!\n\n";
	}
	else
	{
		std::cout << "You lose...\n\n";
	}

}

// loop until user gives valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try #" << CurrentTry << "." << " Please enter a guess: ";
		std::getline(std::cin, Guess);
		std::cout << std::endl;

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n";
			break;

		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until valid until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y / n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
