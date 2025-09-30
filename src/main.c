#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { SPOCK = 0, SCISSORS = 1, PAPER = 2, ROCK = 3, LIZARD = 4 } Move;
typedef enum { TIE = 2, USER_WINS = 1, AGENT_WINS = 0 } Outcome;

static const char *move_name[] = {"Spock", "Scissors", "Paper", "Rock",
                                  "Lizard"};
int game_counter = 0;
int WINNING_SCORE = 3;
bool winner = 0;
bool valid_input = 0;

int user_score = 0;
int agent_score = 0;

void WelcomeText() {
  puts("Welcome to Rock, Paper, Scissors, Spock, Lizard!\n"
       "(s) Single player\n"
       "(e) Exit");
  printf("Select an item: ");
}

Outcome game_result(Move p1, Move p2) {
  if (p1 == p2)
    return TIE;
  switch (p1) {
  case SPOCK:
    return (p2 == SCISSORS || p2 == ROCK) ? USER_WINS : AGENT_WINS;
  case SCISSORS:
    return (p2 == PAPER || p2 == SPOCK) ? USER_WINS : AGENT_WINS;
  case PAPER:
    return (p2 == ROCK || p2 == SPOCK) ? USER_WINS : AGENT_WINS;
  case ROCK:
    return (p2 == LIZARD || p2 == SCISSORS) ? USER_WINS : AGENT_WINS;
  case LIZARD:
    return (p2 == SPOCK || p2 == PAPER) ? USER_WINS : AGENT_WINS;
  default:
    return TIE;
  }
}

void score_counter(int game_outcome) {
  switch (game_outcome) {
  case USER_WINS:
    user_score++;

    break;
  case AGENT_WINS:
    agent_score++;
    break;
  default:
    break;
  }
}

int main(void) {

  char choice;

  srand((unsigned)time(NULL)); // Seed for the agent

  WelcomeText(); // Function where welcome/menu-text is printet out before the
                 // program starts.

  // Do-while loop -> Checking if the user input is valid or if the user want to
  // play 's' or exit 'e'
  do {
    if (scanf(" %c", &choice) != 1) {
      puts("Input error");
      return 1;
    }
    choice = (char)tolower((unsigned char)choice); // ensuring lower case

    if (choice == 'e') {
      puts("Exiting...");
      return 0;
    }
    if (choice != 's') {
      puts("Please, try another input.");
      printf("\nSelect an item: ");
    }
  } while (choice != 's');

  puts("Starting game");

  // The game part
  while (user_score < WINNING_SCORE && agent_score < WINNING_SCORE) {
    char user_input;
    int valid_input = 0;
    int user_shape = -1;
    int agent_shape = -1;

    // Do-while loop -> Checking if the input is valid or if the user want to
    // exit
    do {

      puts("\nSelect a shape:");
      puts("0: Spock || 1: Scissors || 2: Paper || 3: Rock || 4: Lizard");

      if (scanf(" %c", &user_input) != 1) {
        puts("Input error.");
        return 0;
      }
      if (user_input == 'e') {
        puts("Exiting...");
        return 1;
      } else if (user_input >= '0' && user_input <= '4') {
        user_shape = user_input - '0'; // 0..4
        valid_input = 1;
      } else {
        printf("Shape key %c does not exist.Try again.\n", user_input);
      }
    } while (!valid_input);

    agent_shape = rand() % 5; // Agents choice

    // Function that determines the outcome of the game.
    int outcome = game_result(user_shape, agent_shape);
    score_counter(outcome); // Function which add a point for the winner.
    printf("Your score: %d || Agent score: %d\n", user_score, agent_score);

    if (agent_score == WINNING_SCORE) {
      winner = 1;
      printf("Agent won");
    } else if (user_score == WINNING_SCORE) {
      winner = 1;
      printf("You won");
    }
  }

  return 0;
}
