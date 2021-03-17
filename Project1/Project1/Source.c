#include <stdio.h>
#include <stdlib.h>
#define N 100
#include <time.h>

int gameboard[N][N];
typedef enum {true, false} bool;
void genGameBoard(int gameboard[N][N], int x, int y);
void PrintGameBoard(int gameboard[N][N], int x, int y);
void fillUp(int gameboard[N][N], int x, int y);
bool checkSimilar(int gameboard[N][N], int x, int y);
void swap(int gameboard[N][N], int i, int j, int k, int l);
void scoreCount(int gameboard[N][N], int x, int y, int *score);
bool hint(int gameboard[N][N], int x, int y);
bool hintchecker(int gameboard[N][N], int x, int y);


void genGameBoard(int gameboard[N][N], int x, int y) {
	srand(time(0));
	int a;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a = rand() % 6 + 1;
			gameboard[i][j] = a;
		}
	}
}


void PrintGameBoard(int gameboard[N][N], int x, int y) {
	
	printf("\n");
	printf_s("%3c|", ' ');
	for (int j = 1; j <= y; j++) {
		printf_s("%3d|", j);
	}
	printf("\n");
	printf_s("%3c", '___');
	for (int j = 1; j <= (4*y); j++) {
		printf_s("%c", '_');
	}
	printf("\n");
	for (int i = 0; i < x; i++) {
		
		printf_s("%3d|", i+1);
		for (int j = 0; j < y; j++) {

			printf_s("%3d ", gameboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void swap(int gameboard[N][N], int i, int j, int k, int l) {
	int temp = gameboard[i - 1][j - 1];
	gameboard[i - 1][j - 1] = gameboard[k - 1][l - 1];
	gameboard[k - 1][l - 1] = temp;
	
}


void fillUp(int gameboard[N][N], int x, int y) {
	srand(time(0));
	int a, candy;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			candy = gameboard[i][j];
			if (candy == -1) {
				a = i;
				while (a >= 0) {
					if (a != 0) {
						gameboard[a][j] = gameboard[a - 1][j];
					}
					else {
						gameboard[a][j] = rand() % 6 + 1;
					}
					a--;
				}
			}
		}
	}

}


bool checkSimilar(int gameboard[N][N], int x, int y) {
	int counth = 0, countv = 0;
	int candy;
	bool checked = false;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			candy = gameboard[i][j];
			if (candy != -1) {
				
				counth = 0;
				for (int a = i + 1; a < x; a++) {

					if (gameboard[a][j] == candy) {
						counth++;
					}
					else {
						break;
					}
				}
				countv = 0;
				for (int b = j + 1; b < y; b++) {
					if (gameboard[i][b] == candy) {
						countv++;
					}
					else {
						break;
					}
				}

				if (counth >= 2) {
					checked = true;
					for (int a = i; a <= i + counth; a++) {
						gameboard[a][j] = -1;
						
					}
					
				}
				if (countv >= 2) {
					checked = true;
					for (int b = j; b <= j + countv; b++) {
						gameboard[i][b] = -1;
						
					}
							
				}
			}
		}
	}
	return checked;
}


void scoreCount(int gameboard[N][N], int x, int y, int *score) {

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (gameboard[i][j] == -1) {
				*score = *score + 1;
			}
		}
	}
}

bool hintchecker(int gameboard[N][N], int x, int y) {
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (gameboard[i][j] == gameboard[i + 1][j] && gameboard[i][j] == gameboard[i + 2][j]) {
				return true;
			}
			else if (gameboard[i][j] == gameboard[i][j + 1] && gameboard[i][j] == gameboard[i][j + 2]) {
				return true;
			}
		}
	}
	return false;
}

bool hint(int gameboard[N][N], int x, int y){

	bool possible = false;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (possible == false) {
				
				swap(gameboard, i, j, i - 1, j);
				possible = hintchecker(gameboard, x, y);
				swap(gameboard, i, j, i - 1, j);
				if (possible == true) {
					printf_s("swap possible at index %d , %d and %d , %d \n", i, j, i - 1, j );
				}
			}
			if (possible == false) {
				swap(gameboard, i, j, i + 1, j);
				possible = hintchecker(gameboard, x, y);
				swap(gameboard, i, j, i + 1, j);
				if (possible == true) {

					printf_s("swap possible at index %d , %d and %d , %d \n", i, j, i + 1, j);
					
				}
			}
			if (possible == false) {
				swap(gameboard, i, j, i, j - 1);
				possible = hintchecker(gameboard, x, y);
				swap(gameboard, i, j, i, j - 1);
				if (possible == true) {

					printf_s("swap possible at index %d , %d and %d , %d \n", i, j, i, j - 1);
					
				}
			}
			if (possible == false) {
				swap(gameboard, i, j, i, j + 1);
				possible = hintchecker(gameboard, x, y);
				swap(gameboard, i, j, i, j + 1);
				if (possible == true) {

					printf_s("swap possible at index %d , %d and %d , %d \n", i, j, i, j + 1);
				}
			}
		}
	}
	
	return possible;
}





void main() {
	int x = 0, y = 0, score = 0;
	int i = 0, j = 0, k = 0, l = 0;
	bool possible = true;
	printf("Input the dimentions of the gameboard. Between 3 and 100 \n");
	scanf_s("%d %d", &x, &y);
	while ((x <= 3 && x >= 100) && (y <= 3 && y >= 100)) {
		printf("Incorrect dimentions entered \n");
		printf("Input the dimentions of the gameboard. Between 3 and 100 \n");
		scanf_s("%d %d", &x, &y);
	}

	bool checked = true;
	
	// Create gameboard
	genGameBoard(gameboard, x, y);

	// print game board
	PrintGameBoard(gameboard, x, y);
	printf("\n");

	// check if there is any similars.
	while(checked == true) {
		while (checked == true) {
			checked = checkSimilar(gameboard, x, y);
			scoreCount(gameboard, x, y, &score);
			if (checked == true) {
				PrintGameBoard(gameboard, x, y);
				fillUp(gameboard, x, y);
				PrintGameBoard(gameboard, x, y);
				printf_s("Score: %d\n", score);
			}
		}
		possible = hint(gameboard, x, y);
		
		if (possible == true) {
			//Swap
			

			printf("Input the index of candies to be swapped \n");
			scanf_s("%d", &i);
			scanf_s("%d", &j);
			scanf_s("%d", &k);
			scanf_s("%d", &l);

			swap(gameboard, i, j, k, l);
			PrintGameBoard(gameboard, x, y);

			checked = checkSimilar(gameboard, x, y);
			scoreCount(gameboard, x, y, &score);
			if (checked == true) {
				PrintGameBoard(gameboard, x, y);
				fillUp(gameboard, x, y);
				PrintGameBoard(gameboard, x, y);
				printf("Score: %d\n", score);
			}
			else {
				printf("Incorrect Swap. Please swap again. \n");
				swap(gameboard, i, j, k, l);
				checked = true;
			}
		
		}
		else {
			printf("No more swaps possible. Your total score = %d \n", score);
			break;
		}
	}

	system("pause");
}
