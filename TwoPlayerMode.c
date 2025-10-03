#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint16_t inputMask(int pos);
void printBoard(uint16_t x, uint16_t o);
bool haveWon(uint16_t current_values);

const uint16_t WINCONDITIONS[8] = {
  0x1C0, // 111000000 rows: top
  0x038, // 000111000       mid
  0x007, // 000000111       bot
  0x124, // 100100100 cols: left
  0x092, // 010010010       mid
  0x049, // 001001001       right
  0x111, // 100010001 diag: TL-BR
  0x054  // 001010100 diag: TR-BL
};

int main()
{
  uint16_t user[2] = {0x000, 0x000};
  int pos = 0;

  printf("Starting Positions (Input digits):\n1 2 3 \n4 5 6\n7 8 9\n=====\n");

  // loop through user interaction
  int turn = 0; // 0 -> X, 1 -> O
  while (1)
  {
    printBoard(user[0], user[1]);
    if (haveWon(user[0]))
    {
      printf("X Won!\n");
      break;
    }
    else if (haveWon(user[1]))
    {
      printf("O Won!\n");
      break;
    }
    else
    {
      printf("%c turn: ", turn == 0 ? 'X' : 'O');
      if (scanf("%d", &pos) != 1)
      {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        continue;
      }
      uint16_t mask = inputMask(pos);

      // check if this position is already occupied
      if ((user[0] & mask) || (user[1] & mask))
      {
        printf("That position is already taken! Try again.\n");
        continue; // skip turn until valid input
      }
      user[turn] |= mask;
      turn = 1 - turn; // swap turns
    }
  }

  return 0;
}

bool haveWon(uint16_t current_values)
{
  for (int i = 0; i < 8; ++i)
  {
    if ((current_values & WINCONDITIONS[i]) == WINCONDITIONS[i])
    {
      return true;
    }
  }
  return false;
}

uint16_t inputMask(int pos)
{
  return (uint16_t) (0x100 >> (pos - 1));
  // 0x100 >> (pos - 1) -> converts decimal value to binary, 1u to ensure it is unsigned
}

void printBoard(uint16_t x, uint16_t o)
{
  printf("=====\nBoard:\n");
  for (int pos = 0; pos < 9; pos++)
  {
    uint16_t mask = 0x100 >> pos;
    if (x & mask)
    {
      printf("X ");
    }
    else if (o & mask)
    {
      printf("O ");
    }
    else
    {
      printf(". "); // empty
    }
  
    // new line every 3 cells
    if ((pos + 1) % 3 == 0)
    {
      printf("\n");
    }
  }
}


// #include <stdint.h>
// #include <stdbool.h>

// static inline uint16_t mask9_from_pos(int pos) {
//     // pos: 1..9  (1 = top-left / MSB)
//     return (uint16_t)(0x100u >> (pos - 1));
// }

// static inline bool in_range_pos(int pos) {
//     return pos >= 1 && pos <= 9;   // fast guard
// }

// static inline bool is_taken(uint16_t X, uint16_t O, int pos) {
//     uint16_t m = mask9_from_pos(pos);
//     return (X | O) & m;
// }

// static inline bool has_win(uint16_t b) {
//     // 8 winning masks (rows, cols, diags) — all immediate constants
//     return
//       ((b & 0x1C0) == 0x1C0) |  // rows
//       ((b & 0x038) == 0x038) |
//       ((b & 0x007) == 0x007) |
//       ((b & 0x124) == 0x124) |  // cols
//       ((b & 0x092) == 0x092) |
//       ((b & 0x049) == 0x049) |
//       ((b & 0x111) == 0x111) |  // diags
//       ((b & 0x054) == 0x054);
// }

// static inline bool is_draw(uint16_t X, uint16_t O) {
//     return (X | O) == 0x1FF;   // all 9 cells filled
// }

// #include <stdio.h>

// static void print_board(uint16_t X, uint16_t O) {
//     static const char sym[3] = {'.','X','O'};
//     uint16_t m = 0x100;
//     for (int r = 0; r < 3; ++r) {
//         char a = sym[(X & m) ? 1 : (O & m) ? 2 : 0]; m >>= 1;
//         char b = sym[(X & m) ? 1 : (O & m) ? 2 : 0]; m >>= 1;
//         char c = sym[(X & m) ? 1 : (O & m) ? 2 : 0]; m >>= 1;
//         printf("%c %c %c\n", a, b, c);
//     }
// }
// // assume: uint16_t user[2] = {0,0}; int turn = 0; // 0=X, 1=O
// int pos;
// prompt + read pos here, validate:
// if (!in_range_pos(pos))
// {
//   puts("Invalid (1-9)"); /* retry */
// }
// else if (is_taken(user[0], user[1], pos))
// {
//   puts("Taken"); /* retry */
// }
// else
// {
//   uint16_t m = mask9_from_pos(pos);
//   user[turn] |= m;
//   turn ^= 1;
// }

// if (has_win(user[0]))
//   puts("X wins!");
// else if (has_win(user[1]))
//   puts("O wins!");
// else if (is_draw(user[0], user[1]))
//   puts("Draw");

// all these is to aim to have total game state remaining at 4 bytes and 0(1) checks for all computations