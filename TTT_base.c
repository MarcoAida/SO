#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DIM 3

char C = 'O'; // user
char V = 'X'; // pc

void init_matrix(char matrix[DIM][DIM]) {
  printf("Tris\n");
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++)
      matrix[i][j] = '-';
  }
}

// user
int insert_o(char mat[DIM][DIM]) {
  int i, j;

  printf("\n");

  do {
    do {
      printf("inserisci riga (0-2): \t");
      scanf("%d", &i);
    } while (i < 0 || i > 2);

    do {
      printf("inserisci colonna (0-2): \t");
      scanf("%d", &j);
    } while (j < 0 || j > 2);

    printf("\n");

    if (mat[i][j] != '-') {
      printf(
          "Cell (%d, %d) is already occupied. Please enter another position.\n",
          i, j);
    }
  } while (mat[i][j] != '-');

  mat[i][j] = C;

  return mat[i][j];
}

// pc
int insert_x(char mat[DIM][DIM]) {
  int i, j;
  do {
    i = rand() % 3;
    j = rand() % 3;
  } while (mat[i][j] != '-' || mat[i][j] == C);

  mat[i][j] = V;

  printf("\nPc has put on (%d, %d):\n", i, j);

  printf("\n");

  return mat[i][j];
}

void print_matrix(char matrix[DIM][DIM]) {
  for (int i = 0; i < DIM; i++) {
    for (int j = 0; j < DIM; j++)
      printf("%c ", matrix[i][j]);
    printf("\n");
  }
}

int check_win(char matrix[DIM][DIM]) {
  // Check diagonals
  if ((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] &&
       matrix[0][0] != '-') ||
      (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] &&
       matrix[0][2] != '-')) {
    return 1;
  }

  // Check rows and columns
  for (int i = 0; i < DIM; i++) {
    if ((matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2] &&
         matrix[i][0] != '-') ||
        (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i] &&
         matrix[0][i] != '-')) {
      return 1;
    }
  }
  return 0;
}

int main(void) {
  srand(time(NULL));

  char matrix[DIM][DIM];

  init_matrix(matrix);

  print_matrix(matrix);

  while (1) {

    insert_o(matrix); // User makes a move

    print_matrix(matrix); // Print matrix after user's move

    if (check_win(matrix)) {
      printf("Hai Vinto!\n");
      break;
    }

    sleep(3); // Pause for 3 seconds

    insert_x(matrix); // Computer makes a move

    print_matrix(matrix); // Print matrix after computer's move

    if (check_win(matrix)) {
      printf("Hai Perso!\n");
      break;
    }

    sleep(5); // Pause for 3 seconds

    system("clear");

    print_matrix(matrix);
  }

  return 0;
}