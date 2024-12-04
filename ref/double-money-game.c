// gcc double-money-game.c -Wall -Werror -Wpedantic -Iinclude
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <common.h>
#include <terminal-colors.h>

#define LOSE_NUM 999
#define NUM_CHANCE 1000

void print_intro();
void print_end_game(unsigned long money, bool lost_money, bool next_chance,
                    unsigned int current_step);

int main() {
  print_intro();
  srand(time(NULL));

  bool game_running = true;
  bool lost_money = false;

  unsigned int current_step = 0;
  unsigned long current_money = 1;
  char ch = 'y';
  unsigned int seed = time(0);
  unsigned int r = rand_r(&seed) % NUM_CHANCE;

  char *game_spacer = TERM_WHT "--------------------" TERM_CRESET;
  char *game_prompt = TERM_BLU "Double money? (Y/N) " TERM_CRESET;
  // int r = rand();

  printf("%s", game_prompt);
  while (game_running) {
    ch = getchar();
    if (ch == 'N' || ch == 'n') {
      game_running = false;
      break;
    }

    if (isspace(ch))
      continue;

    if (ch != 'Y' && ch != 'y') {
      printf("Invalid char of: %c\n", ch);
      printf("Invalid option picked. Please pick 'Y or y' for yes, or 'N or n' "
             "for no.\n");
      printf("\n\n%s\n", game_spacer);
      printf("%s", game_prompt);
      continue;
    }

    r = rand_r(&seed) % NUM_CHANCE;

    if (r == LOSE_NUM) {
      printf(TERM_RED "Ooofballs\n" TERM_CRESET);
      lost_money = true;
      game_running = false;
      current_step++;
      break;
    }

    current_step++;
    current_money *= 2;

    printf(TERM_MAG "You've now doubled your money %u times, for a total of: "
                    "%lu\n" TERM_CRESET,
           current_step, current_money);
    printf("\n\n%s\n", game_spacer);
    printf("%s", game_prompt);
  }

  r = rand_r(&seed) % NUM_CHANCE;

  printf("\n\n%s\n", game_spacer);
  printf(TERM_MAG "Doublings attempted: %u\n" TERM_CRESET, current_step);
  print_end_game(current_money, lost_money, r != LOSE_NUM, current_step);
  printf(TERM_CRESET);
}

void print_intro() {
  printf(TERM_YEL "You are given $1 to play this game with.\n");
  printf("You can choose to double the money, or accept the money.\n");
  printf("There is a 99.9%% chance that doubling the money is successful.\n");
  printf("If you don't double your money, you lose all of your money.\n");
  printf(TERM_GRN "How many times do you double your money?\n" TERM_CRESET);
}

void print_end_game(unsigned long money, bool lost_money, bool next_chance,
                    unsigned int current_step) {
  printf(TERM_BLU "Game is now over, here are your results:\n");

  char next_chance_string[BYTE_32] = TERM_UGRN "double\0";
  if (!next_chance)
    strncpy(next_chance_string, TERM_URED "lose all\0", BYTE_32);

  if (lost_money) {
    printf(TERM_RED "You get " TERM_YEL "$0.00" TERM_RED
                    ". Sadness. If this attempt were successful, you could "
                    "have made " TERM_YEL "$%lu" TERM_RED
                    ". If you kept your money, you could have made " TERM_YEL
                    "$%lu" TERM_RED
                    ". :( Your next chance was to %s your money.\n" TERM_CRESET,
           money * 2, money, next_chance_string);
    return;
  }

  printf(TERM_GRN
         "You get " TERM_MAG "$%lu" TERM_GRN
         "! AMAZEBALLS!!! Your next chance was to %s your money.\n" TERM_CRESET,
         money, next_chance_string);
  printf(TERM_YEL "Imagine tho, if you had another successful double... That "
                  "could have been " TERM_MAG "$%lu" TERM_YEL
                  "...\n" TERM_CRESET,
         money * 2);

  if (money == 0 && !lost_money) {
    printf(TERM_RED "Hold on. . .\n");
    printf(TERM_RED "You broke the economy. . .\n");
    printf(TERM_RED "For all intents and purposes, you have infinity money\n");
    printf(TERM_YEL "Yes, I know I used that wrong, and no I don't care. If I "
                    "want to say \"infinity money\" in that context I will.\n");
    printf(TERM_RED "You actually made $2^%u. That's two to the power of %u.\n",
           current_step, current_step);
    printf(TERM_RED "Anyway, thanks for ruining the entire economic system. Go "
                    "on, get out of here you monster.\n" TERM_CRESET);
  }
}
