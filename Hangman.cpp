#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Random.h"

namespace WordList {
	const std::vector<std::string> wordVector{
		"luffy","eren","miyamoto","kojiro","thorffin","guts","killua","hisoka","zoro","shanks","mikasa"
	};

	std::string getRandomWord() {
		int wordIndex{};
		wordIndex = Random::get(0, static_cast<int>(wordVector.size() - 1));
		return wordVector[wordIndex];
	}

	std::string getHiddenName(const std::string& word) {
		return std::string(word.length(), '_');
	}

}

class Session {
	const std::string RandomWord;
	std::string HiddenWord;
	std::vector<char> guessedLetters{};
	int remAttempts{ 5 };

public:
	Session()
		: RandomWord{ WordList::getRandomWord() }, HiddenWord{WordList::getHiddenName(RandomWord)} {

	}

	void displayWord() {
		std::cout << "\n";
		std::cout << "The word is: " << HiddenWord << "\n";
	}

	void welcome() {
		std::cout << "Welcome to C++ Hangman Game!.\n";
		std::cout << "To win: guess the word,\tTo lose: run out of pluses(+).\n";
		std::cout << "Remaining attempts : " << std::string(remAttempts,'+') << "\n";
	}

	void getInput() {
		char input{};
		while (true) {
			std::cout << "Enter your guess: ";
			std::cin >> input;
			if (std::cin.fail() || !std::isalpha(input) || input == ' ') {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Please enter a valid character.\n";
				continue;
			}

			input = std::tolower(input);

			if (std::find(guessedLetters.begin(), guessedLetters.end(), input) != guessedLetters.end()) {
				std::cout << "You have already guessed " << input << ". Try a different letter.\n";
				continue;
			}

			guessedLetters.push_back(input);
			break;
		}
	}

	bool gameProcess(char& guess) {
		bool isCorrectGuess{ false };
		for (std::size_t i{ 0 }; i < RandomWord.length(); ++i) {
			if (RandomWord[i] == guess) {
				HiddenWord[i] = guess;
				isCorrectGuess = true;
			}
		}

		if (!isCorrectGuess) {
			--remAttempts;
		}

		return isCorrectGuess;
	}

	bool isGameOver() const {
		if (HiddenWord == RandomWord) {
			std::cout << "Congrats You win!.\n";
			return true;
		}

		if (remAttempts <= 0) {
			std::cout << "\nToo bad you lose. The word was : "<<RandomWord <<"\nTry again next time!.\n";
			return true;
		}

		return false;
	}

	void gameLoop() {
		while (!isGameOver()) {
			displayWord();
			getInput();
			
			char PreviousGuess{guessedLetters.back()};

			if (gameProcess(PreviousGuess)) {
				std::cout << "Good guess.\n";
			}
			else {
				if (remAttempts > 0) {
					std::cout << "Incorrect guess. Remaining attempt: " << std::string(remAttempts, '+') << "\n";
				}
			}
		}
	}
};


int main() {
	Session s{};
	s.welcome();
	s.gameLoop();
	std::cout << "\n";
	std::cout << "Thanks for playing!.";
	std::cout << '\n';

	return 0;
}
