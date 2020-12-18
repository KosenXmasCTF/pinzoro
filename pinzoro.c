#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int dice(void) {
	return rand() % 6 + 1;
}

void init_seed(void) {
	int seed;
	FILE *fp = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(seed), 1, fp);
	srand(seed);
	fclose(fp);
}

void challenge(void) {
	int results[8];
	bool pinzoro = true;

	for (int i = 0; i < 8; ++i) {
		results[i] = dice();
		if (results[i] != 1) pinzoro = false;
	}
	
	printf("8d6 => ");
	for (int i = 0; i < 8; ++i) {
		printf("%d ", results[i]);
	}
	printf("\n");
	
	if (!pinzoro) {
		puts("FAILED TO CHALLENGE...");
		return;
	}

	puts("OH!!!! YOU ARE LUCKY!!!!!!");
	system("/bin/sh");
}

void roll_one_dice(void) {
	printf("1d6 => %d\n", dice());
}

void roll_dices(void) {
	char count[128];
	printf("NUMBER: ");
	scanf("%127s%*c", count);
	if (atoi(count) > 10000000) {
		puts("Sorry, that's too big.");
		return;
	}
	for (int i = 0; i < atoi(count); ++i) {
		dice();
	}
	printf("FINISH ROLLING ");
	printf(count);
	printf(" DICES.\n");
}

int menu(void) {
	int select;
	printf(
		"1. ROLL ONE DICE (PRACTICE)\n"
		"2. ROLL DICES    (PRACTICE)\n"
		"3. PINZORO CHALLENGE\n"
		"SELECT: "
	);
	scanf("%d%*c", &select);
	return select;
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

int main(void) {
	int select;
	setup();
	init_seed();
	while (1) {
		select = menu();
		if (select == 1) roll_one_dice();
		if (select == 2) roll_dices();
		if (select == 3) {
			challenge();
			break;
		}
	}
}
