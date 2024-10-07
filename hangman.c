#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "hangman.h"

int main(){
	int win = 0, hang = 0, attempts = 0, correct = 0;
	char word[20] = {};
	char guess_array[20] = {};

	choose_word(word);
	print_beginning();

	while(!win && !hang){
		char guess = {};
		int matches = 0, already_matched = 0;

		print_word(word, guess_array);

		printf("\n");
		printf("Guess the word:\n");
		scanf(" %c", &guess);
		guess = toupper(guess);

		verify_typed(guess, guess_array, &already_matched);
		verify_correct(already_matched, guess, word, matches, &attempts, &correct);

		printf(" _______________________\n");
		printf("|  %d attempts remaining |\n", 4 - attempts);
		printf(" -----------------------\n\n");

		if(attempts >= 4){
			lose_game(&hang);
		}
		if(correct == strlen(word)){
			win_game(&win);
		}
	}
	return 0;
}

/*------------------- Functions building -------------------*/

// Choose the word
void choose_word(char word[20]){
	FILE* f;
	f = fopen("matrix.txt", "r");

	// In case if file is not found
	if(f == 0){
		printf("Database not found\n");
		exit(1);
	}

	// See how many words is in the file
	int word_qty = 0;
	fscanf(f, "%d", &word_qty);

	// Set a random number
	srand(time(0));
	int r = rand()%word_qty;

	// Select random word
	for(int i = 0; i <= rand()%word_qty; i++){
		fscanf(f, "%s", word);
	}

	// printf("%d\n", rand());
	// printf("%d\n", word_qty);
	// printf("%d\n", r);
	// printf("%d\n", rand()%word_qty);

	fclose(f);
	// exit(1);
}

// Clear the command line and print game's beginning message
void print_beginning(){
	int system(const char *command);
	system("clear");

	printf("--------------------------------------------------------------------\n");
	printf("Welcome to the Hangman Game!\n");
	printf("--------------------------------------------------------------------\n");
	printf(" _______________________\n");
	printf("|  You have 4 attempts  |\n");
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
void verify_correct(int already_matched, char guess, char word[20], int matches, int* attempts, int* correct){
	if(already_matched == 0){
		// Verify if the guessed letter was correct
		for(int i = 0; i < strlen(word); i++){
			if(guess == word[i]){
				printf("\nThe position %d has this letter\n", i+1);
				matches++;
				(*correct)++;
			}
		}

		if(matches > 0){
			printf("\nThere's %d match(es) for this letter\n\n", matches);
		} else {
			printf("\n!!!There's no match!!!\n\n");
		}
	}

	if(already_matched != 1 && matches == 0){
		(*attempts)++;
	}
}

// Lose the game
void lose_game(int* hang){
	(*hang) = 1;
	printf("\n /$$     /$$ /$$$$$$  /$$   /$$       /$$        /$$$$$$   /$$$$$$  /$$$$$$$$       /$$\n");
	printf("|  $$   /$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$__  $$|__  $$__/      | $$\n");
	printf(" \\  $$ /$$/| $$  \\ $$| $$  | $$      | $$      | $$  \\ $$| $$  \\__/   | $$         | $$\n");
	printf("  \\  $$$$/ | $$  | $$| $$  | $$      | $$      | $$  | $$|  $$$$$$    | $$         | $$\n");
	printf("   \\  $$/  | $$  | $$| $$  | $$      | $$      | $$  | $$ \\____  $$   | $$         |__/\n");
	printf("    | $$   | $$  | $$| $$  | $$      | $$      | $$  | $$ /$$  \\ $$   | $$             \n");
	printf("    | $$   |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/|  $$$$$$/   | $$          /$$\n");
	printf("    |__/    \\______/  \\______/       |________/ \\______/  \\______/    |__/         |__/\n\n\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⠴⠶⠶⠶⠶⠶⠶⠶⠶⢤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⢀⣤⠶⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠶⣤⡀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⢀⡴⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⡄⠀⠀⠀\n");
	printf("			⠀⣰⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣦⠀⠀\n");
	printf("			⢰⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣧⠀\n");
	printf("			⣿⠀⠀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡄⠀⢹⡄\n");
	printf("			⡏⠀⢰⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⢸⡇\n");
	printf("			⣿⠀⠘⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⠀⢸⡇\n");
	printf("			⢹⡆⠀⢹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⣾⠀\n");
	printf("			⠈⢷⡀⢸⡇⠀⢀⣠⣤⣶⣶⣶⣤⡀⠀⠀⠀⠀⠀⢀⣠⣶⣶⣶⣶⣤⣄⠀⠀⣿⠀⣼⠃⠀\n");
	printf("			⠀⠈⢷⣼⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⡾⠃⠀⠀\n");
	printf("			⠀⠀⠈⣿⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⠃⠀⢸⡇⠀⠀⠀\n");
	printf("			⠀⠀⠀⣿⠀⠀⠘⢿⣿⣿⣿⣿⡿⠃⠀⢠⠀⣄⠀⠀⠙⢿⣿⣿⣿⡿⠏⠀⠀⢘⡇⠀⠀⠀\n");
	printf("			⠀⠀⠀⢻⡄⠀⠀⠀⠈⠉⠉⠀⠀⠀⣴⣿⠀⣿⣷⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⢸⡇⠀⠀⠀\n");
	printf("			⠀⠀⠀⠈⠻⣄⡀⠀⠀⠀⠀⠀⠀⢠⣿⣿⠀⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠘⣟⠳⣦⡀⠀⠀⠀⠸⣿⡿⠀⢻⣿⡟⠀⠀⠀⠀⣤⡾⢻⡏⠁⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⢻⡄⢻⠻⣆⠀⠀⠀⠈⠀⠀⠀⠈⠀⠀⠀⢀⡾⢻⠁⢸⠁⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⢸⡇⠀⡆⢹⠒⡦⢤⠤⡤⢤⢤⡤⣤⠤⡔⡿⢁⡇⠀⡿⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠘⡇⠀⢣⢸⠦⣧⣼⣀⡇⢸⢀⣇⣸⣠⡷⢇⢸⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⣷⠀⠈⠺⣄⣇⢸⠉⡏⢹⠉⡏⢹⢀⣧⠾⠋⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠻⣆⠀⠀⠀⠈⠉⠙⠓⠚⠚⠋⠉⠁⠀⠀⠀⢀⡾⠁⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡴⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠳⠶⠦⣤⣤⣤⡤⠶⠞⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\n\n");
}

// Win the game
void win_game(int* win){
	(*win) = 1;
	printf(" /$$     /$$ /$$$$$$  /$$   /$$       /$$      /$$  /$$$$$$  /$$   /$$       /$$\n");
	printf("|  $$   /$$//$$__  $$| $$  | $$      | $$  /$ | $$ /$$__  $$| $$$ | $$      | $$\n");
	printf(" \\  $$ /$$/| $$  \\ $$| $$  | $$      | $$ /$$$| $$| $$  \\ $$| $$$$| $$      | $$\n");
	printf("  \\  $$$$/ | $$  | $$| $$  | $$      | $$/$$ $$ $$| $$  | $$| $$ $$ $$      | $$\n");
	printf("   \\  $$/  | $$  | $$| $$  | $$      | $$$$_  $$$$| $$  | $$| $$  $$$$      |__/\n");
	printf("    | $$   | $$  | $$| $$  | $$      | $$$/ \\  $$$| $$  | $$| $$\\  $$$          \n");
	printf("    | $$   |  $$$$$$/|  $$$$$$/      | $$/   \\  $$|  $$$$$$/| $$ \\  $$       /$$\n");
	printf("    |__/    \\______/  \\______/       |__/     \\__/ \\______/ |__/  \\__/      |__/\n\n\n");
	printf("			⠀⠀⠀⠀⣠⠤⠤⣄⣠⣤⣤⡤⠤⠤⠤⠤⠤⠤⠤⣤⣤⣤⣠⠤⠤⣄⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⡜⢁⡶⠶⢤⡇⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠸⡦⠾⠶⡄⢳⠀⠀⠀\n");
	printf("			⠀⠀⠀⡇⢸⠀⠀⠀⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⡇⢸⡆⠀⠀\n");
	printf("			⠀⠀⠀⢧⠘⣆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠇⠀⢠⠇⣸⠀⠀⠀\n");
	printf("			⠀⠀⠀⠈⢦⡘⠦⣀⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⣀⡴⠋⡰⠃⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠙⠦⣌⡙⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠋⣁⡴⠚⠁⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠚⠳⣄⠀⠀⠀⠀⣠⠖⠓⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡀⠀⡼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⠸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡜⠀⠀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣞⣀⣀⣀⣀⣳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠉⠉⠉⠉⠉⠉⢹⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡷⠤⠤⠤⠤⠤⠤⠼⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠒⠒⠒⠒⠒⠒⠒⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("			⠀⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⢀⣀⣀⣀⣀⣀⣀⣀⣀\n");
	printf("			⣿⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\n\n");
}