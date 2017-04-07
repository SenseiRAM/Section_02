/* This is the console executable that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interafction. For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	// Introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << "\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once done validating tries
	for (int32 i = 1; i <= MaxTries; i++)
	{
		FText Guess = GetGuess(); // TODO make loop checking valid
		
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		
	}

	// TODO add a game summary
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();

	std::cout << "Try #" << CurrentTry << "." << " Please enter a guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	std::cout << std::endl;

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y / n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
