#include <stdio.h>
#include <terminal-colors.h>

int main() {

  printf(TERM_BRED "Hey this is the color red, and it's bold! \n" TERM_reset);
  printf(TERM_RED "If" TERM_BLU "you" TERM_YEL "are" TERM_GRN "bored" TERM_CYN
                  "do" TERM_MAG "this! \n" TERM_reset);
  printf(TERM_BRED "If" TERM_BBLU "you" TERM_BYEL "are" TERM_BGRN
                   "bored" TERM_BCYN "do" TERM_BMAG "this! \n" TERM_reset);
  printf(TERM_URED "If" TERM_UBLU "you" TERM_UYEL "are" TERM_UGRN
                   "bored" TERM_UCYN "do" TERM_UMAG "this! \n" TERM_reset);
  return 0;
}
