/********************************************/
/*	記憶力トレーニング						*/
/*	記憶した整数の各桁を逆順に入力させる	*/
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_STAGE 10
#define LEVEL_MIN 3
#define LEVEL_MAX 20

/*---	xミリ秒経過するのを待つ ---*/
int sleep(unsigned long x)
{
	clock_t c1 = clock(), c2;

	do {
		if ((c2 = clock()) == (clock_t)-1)	// エラー
			return 0;
	} while (1000.0 * (c2 - c1) / CLOCKS_PER_SEC < x);
	return 1;
}

/*--- 入力された整数が記憶した整数の逆順であるか比較 ---*/
int cmp_num(char num[], char ans[], int level)
{
	int i;
	
	for (i = 0; i < level; i++) {
		if (num[i] != ans[level - i - 1]) {
			return 1;
		}
	}
	
	return 0;
}

int main(void)
{
	int i, j;
	int level, success = 0;
	char ans[LEVEL_MAX + 1], num[LEVEL_MAX * 2];
	time_t start, end;

	srand(time(NULL));
	printf("数値記憶トレーニング\n");

	do {
		printf("挑戦するレベル（%d ～ %d）：", LEVEL_MIN, LEVEL_MAX);
		scanf("%d", &level);
	} while ((level < LEVEL_MIN) || (level > LEVEL_MAX));

	printf("%d桁の数値を記憶しましょう！！\n", level);

	start = time(NULL);

	for (i = 0; i < MAX_STAGE; i++) {
		ans[0] = '0' + (1 + rand() % 9);
		for (j = 1; j < level; j++) {
			ans[j] = '0' + (rand() % 10);
		}
		ans[level] = '\0';

		printf("%s", ans);
		fflush(stdout);
		sleep(125 * level);

		printf("\r%*s\r入力せよ：", level, "");
		scanf("%s", num);

		if (cmp_num(num, ans, level) == 0) {
			printf("正解です。\n");
			success++;
		} else {
			printf("\a間違いです。\n");
		}
	}
	end = time(NULL);

	printf("%d回中%d回成功しました。\n", MAX_STAGE, success);
	printf("%.1f秒でした。\n", difftime(end, start));

	return 0;
}
