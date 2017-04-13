/* This is the console executable that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// to make syntax work with Unreal Engine
using FText = std::string;
using int32 = int;

void PrintIntro();
void GetInitWord();
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
		GetInitWord();
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
	std::cout << "      }    {                ___ " << std::endl;
	std::cout << "      (0  0)               (0 0) 'Moo!'" << std::endl;
	std::cout << " /- - -\\  /            - - -\\ /   " << std::endl;
	std::cout << "/ |    |              / |   |" << std::endl;
	
	std::cout << "Can you guess the isogram I'm thinking of?\n";
	return;
}

// Function that gets number of letters for the hidden word from user
void GetInitWord()
{
	int32 NumberOfLetters;
	do
	{
		std::cout << "Would you like to guess a 3, 4, 5, or 6 letter word? (Enter 3, 4, 5, or 6)";
		std::cin >> NumberOfLetters;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		BCGame.AskWordLength(NumberOfLetters);
	} while (NumberOfLetters < 3 || NumberOfLetters > 6);
	return;
}

// plays a single game to completion once user selects word length
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

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		
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

		std::cout << "Try #" << CurrentTry << " of " << BCGame.GetMaxTries() << "." << " Please enter a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;

		default:
			// assume the guess is valid
			break;
		}
		//std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until valid until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y / n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
