#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions Index:
void print_beginning(char word[20]);
void print_word(char word[20], char guess_array[20]);
void verify_typed(char guess, char guess_array[20], int* already_matched);
void verify_correct(int already_matched, char guess, char word[20], int matches, int* attempts);

int main(){
	int win = 0, hang = 0, attempts = 0;
	char word[20] = {};
	char guess_array[20] = {};
	sprintf(word, "NABUCODONOSOR");

	print_beginning(word);

	while(!win && !hang){
		char guess = {};
		int matches = 0, already_matched = 0;

		print_word(word, guess_array);

		printf("\n");
		printf("Guess the word:\n");
		scanf(" %c", &guess);

		verify_typed(guess, guess_array, &already_matched);
		verify_correct(already_matched, guess, word, matches, &attempts);

		printf(" _______________________\n");
		printf("| %d attempts remaining |\n", (int)strlen(word) - attempts);
		printf(" -----------------------\n\n");

		if(attempts >= strlen(word)){
			hang = 1;
			printf("--------------------------------------------------------------------\nGAME OVER!\n--------------------------------------------------------------------\n");
		}
	}

	return 0;
}

/*------------------- Functions building -------------------*/

// Clear the command line and print game's beginning message
void print_beginning(char word[20]){
	int system(const char *command);
	system("clear");

	printf("--------------------------------------------------------------------\n");
	printf("Welcome to the Hangman Game!\n");
	printf("--------------------------------------------------------------------\n");
	printf(" _______________________\n");
	printf("| You have %d attempts |\n", (int)strlen(word));
	printf(" -----------------------\n\n");
}

// Print the dashes and the letters already typed
void print_word(char word[20], char guess_array[20]){
	for(int i = 0; i < strlen(word); i++){
		int match = 0;
		for(int j = 0; j < strlen(guess_array); j++){
			if(word[i] == guess_array[j]){
				match = 1;
			}
		}
		if(match == 0){
			printf("_ ");
		} else {
			printf("%c ", word[i]);
		}
	}
	printf("	Letters already typed: ");
	for(int i = 0; i < strlen(guess_array); i++){
		printf("%c ", guess_array[i]);
	}
}

// Verify if the guessed letter was already typed
void verify_typed(char guess, char guess_array[20], int* already_matched){
	for(int i = 0; i < 20; i++){
		if(guess == guess_array[i]){
			printf("\nYou already tried this letter\n");
			(*already_matched) = 1;
				break;
		} else if(guess_array[i] == 0) {
			guess_array[i] = guess;
			break;
		}
	}
}

// Verify if the typed letter is correct
void verify_correct(int already_matched, char guess, char word[20], int matches, int* attempts){
	if(already_matched == 0){
		// Verify if the guessed letter was correct
		for(int i = 0; i < strlen(word); i++){
			if(guess == word[i]){
				printf("\nThe position %d has this letter\n", i+1);
				matches++;
			}
		}

		if(matches > 0){
			printf("\nThere's %d match(es) for this letter\n\n", matches);
		} else {
			printf("\nThere's no match\n\n");
		}
	}

	if(already_matched != 1 && matches == 0){
		(*attempts)++;
	}
}