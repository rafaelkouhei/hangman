#define word_len 20
void choose_word(char word[20]);
void print_beginning();
void print_hangedman(int wrong);
void print_word(char word[20], char guess_array[20]);
void verify_typed(char guess, char guess_array[20], int * already_matched);
void verify_correct(int already_matched, char guess, char word[20], int matches, int * attempts, int * correct, int * wrong);
void lose_game(int * hang);
void win_game(int * win);
void add_word();