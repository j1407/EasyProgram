#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE_MAX 8
#define DIFFICULTY 2 // Set with 1 or more

typedef struct fig {
	int x, y;
}FIG;

FIG m;

int table[SIZE_MAX][SIZE_MAX] = { 0 };
int flag[SIZE_MAX][SIZE_MAX] = { 0 };
int bag;

void init() {
	int i, j;
	m.x = m.y = 0;
	bag = 0;
	for (i = 0; i < SIZE_MAX; i++) {
		for (j = 0; j < SIZE_MAX; j++) {
			bag++;
			if (rand() % SIZE_MAX < DIFFICULTY) {
				table[i][j] = -1;
				bag--;
			}
		}
	}
}

void input() {
	m.x = m.y = -1;
	do {
		printf("What is x and y ? :");
		scanf("%d %d", &m.x, &m.y);
	} while (m.x < 0 || m.x >= SIZE_MAX || m.y < 0 || m.y >= SIZE_MAX || flag[m.y][m.x] == 1);
}

int around(int x, int y) {
	int flag_m = 0;
	// left up
	if (x > 0 && y > 0) {
		if (flag[y - 1][x - 1] == 0) {
			if (table[y - 1][x - 1] == -1) {
				flag_m++;
			}
		}
	}
	// up
	if (y > 0) {
		if (flag[y - 1][x] == 0) {
			if (table[y - 1][x] == -1) {
				flag_m++;
			}
		}
	}
	// right up
	if (x < SIZE_MAX - 1 && y > 0) {
		if (flag[y - 1][x + 1] == 0) {
			if (table[y - 1][x + 1] == -1) {
				flag_m++;
			}
		}
	}
	// left
	if (x > 0) {
		if (flag[y][x - 1] == 0) {
			if (table[y][x - 1] == -1) {
				flag_m++;
			}
		}
	}
	// right
	if (x < SIZE_MAX - 1) {
		if (flag[y][x + 1] == 0) {
			if (table[y][x + 1] == -1) {
				flag_m++;
			}
		}
	}
	// left down
	if (x > 0 && y < SIZE_MAX - 1) {
		if (flag[y + 1][x - 1] == 0) {
			if (table[y + 1][x - 1] == -1) {
				flag_m++;
			}
		}
	}
	// down
	if (y < SIZE_MAX - 1) {
		if (flag[y + 1][x] == 0) {
			if (table[y + 1][x] == -1) {
				flag_m++;
			}
		}
	}
	// right down
	if (x < SIZE_MAX - 1 && y < SIZE_MAX - 1) {
		if (flag[y + 1][x + 1] == 0) {
			if (table[y + 1][x + 1] == -1) {
				flag_m++;
			}
		}
	}
	return flag_m;
}

int open(int x, int y) {
	int flag_m;
	if (table[y][x] == -1) {
		if (x == m.x && y == m.y) {
			flag[y][x] = 1;
		}
		return -1;
	}
	flag[y][x] = 1;
	bag--;
	flag_m = around(x, y);
	table[y][x] = flag_m;
	if (flag_m == 0) {
		if (y > 0) {
			if (flag[y - 1][x] == 0) {
				open(x, y - 1);
			}
		}
		if (x > 0) {
			if (flag[y][x - 1] == 0) {
				open(x - 1, y);
			}
		}
		if (x < SIZE_MAX - 1) {
			if (flag[y][x + 1] == 0) {
				open(x + 1, y);
			}
		}
		if (y < SIZE_MAX - 1) {
			if (flag[y + 1][x] == 0) {
				open(x, y + 1);
			}
		}
		if (x > 0 && y > 0) {
			if (flag[y - 1][x - 1] == 0) {
				if ((flag_m = around(x - 1, y - 1)) != 0) {
					table[y - 1][x - 1] = flag_m;
					flag[y - 1][x - 1] = 1;
					bag--;
				}
			}
		}
		if (x < SIZE_MAX - 1 && y > 0) {
			if (flag[y - 1][x + 1] == 0){
				if ((flag_m = around(x + 1, y - 1)) != 0) {
					table[y - 1][x + 1] = flag_m;
					flag[y - 1][x + 1] = 1;
					bag--;
				}
			}
		}
		if (x > 0 && y < SIZE_MAX - 1) {
			if (flag[y + 1][x - 1] == 0) {
				if ((flag_m = around(x - 1, y + 1)) != 0) {
					table[y + 1][x - 1] = flag_m;
					flag[y + 1][x - 1] = 1;
					bag--;
				}
			}
		}
		if (x < SIZE_MAX - 1 && y < SIZE_MAX - 1) {
			if (flag[y + 1][x + 1] == 0) {
				if ((flag_m = around(x + 1, y + 1)) != 0) {
					table[y + 1][x + 1] = flag_m;
					flag[y + 1][x + 1] = 1;
					bag--;
				}
			}
		}
	}
	return 0;
}

void draw() {
	int i, j;
	printf("  |");
	for (i = 0; i < SIZE_MAX; i++) {
		printf("%2d", i);
	}
	printf("    block > %d", bag);
	printf("\n");
	printf("__|");
	for (i = 0; i < SIZE_MAX; i++) {
		printf("__");
	}
	printf("\n");
	for (i = 0; i < SIZE_MAX; i++) {
		printf("%2d|", i);
		for (j = 0; j < SIZE_MAX; j++) {
			if (flag[i][j] == 1) {
				if (table[i][j] != 0) {
					printf("%2d", table[i][j]);
				}
				else {
					printf("  ");
				}
			}
			else {
				printf("■");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int exit_flag = 0;
	srand((unsigned)time(NULL));
	init();
	draw();
	while (exit_flag == 0 && bag != 0) {
		input();
		if (open(m.x, m.y) == -1) {
			exit_flag = 1;
		}
		draw();
	}
	if (bag == 0) {
		printf("Game Clear!!\n");
	}
	else {
		printf("Game Flase!!\n");
	}
	return 0;
}
