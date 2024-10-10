#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "hangman.h"

int main(){
	int win = 0, hang = 0, attempts = 0, correct = 0, wrong = 0;
	char word[word_len] = {};
	char guess_array[word_len] = {};

	choose_word(word);
	print_beginning();
	print_hangedman(wrong);

	while(!win && !hang){
		char guess = {};
		int matches = 0, already_matched = 0;

		print_word(word, guess_array);

		printf("\n");
		printf("Guess the word:\n");
		scanf(" %c", &guess);
		guess = toupper(guess);

		verify_typed(guess, guess_array, &already_matched);
		verify_correct(already_matched, guess, word, matches, &attempts, &correct, &wrong);

		print_hangedman(wrong);

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

	add_word();

	return 0;
}

/*------------------- Functions building -------------------*/

// Choose the word
void choose_word(char word[word_len]){
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

	fclose(f);
}

// Clear the command line and print game's beginning message
void print_beginning(){
	int system(const char * command);
	system("clear");

	printf("--------------------------------------------------------------------\n");
	printf("Welcome to the Hangman Game!\n");
	printf("--------------------------------------------------------------------\n");
	printf(" _______________________\n");
	printf("|  You have 4 attempts  |\n");
	printf(" -----------------------\n\n");
}

// Print hangedman counting wrong answers
void print_hangedman(int wrong){
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %s    \n", (wrong >= 1 ? "(_)" : " "));
    printf(" |      %c%c%c   \n", (wrong >= 3 ? '/' : ' '), (wrong >= 2 ? '|' : ' '), (wrong >= 3 ? '\\' : ' '));
    printf(" |       %c     \n", (wrong >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (wrong >= 4 ? '/' : ' '), (wrong >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n");
}

// Print the dashes and the letters already typed
void print_word(char word[word_len], char guess_array[word_len]){
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
void verify_typed(char guess, char guess_array[word_len], int* already_matched){
	for(int i = 0; i < word_len; i++){
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
void verify_correct(int already_matched, char guess, char word[word_len], int matches, int * attempts, int * correct, int * wrong){
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
			(*wrong)++;
		}
	}

	if(already_matched != 1 && matches == 0){
		(*attempts)++;
	}
}

// Lose the game
void lose_game(int * hang){
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
void win_game(int * win){
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

// Adding new words to the text file
void add_word(){
	char choice;
	printf("Do you want to add a new word? (Y/N)\n");
	scanf(" %c", &choice);
	choice = toupper(choice);

	if(choice == 'Y'){
		char new_word[word_len];
		int qty = 0;

		printf("Insert the new word:\n");
		scanf("%s", new_word);

		for(int i = 0; i < strlen(new_word); i++){
			new_word[i] = toupper(new_word[i]);
		}

		FILE *f;
		// 'r' is for reading, and '+' for writing
		f = fopen("matrix.txt", "r+");
		if(f == 0){
			printf("Database not found\n");
			exit(1);
		}

		fscanf(f, "%d", &qty);
		qty++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qty);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", new_word);

		fclose(f);
	} else if(choice == 'N'){
		exit(1);
	}
}