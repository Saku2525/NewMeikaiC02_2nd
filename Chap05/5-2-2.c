/****************************************/
/*	記憶力トレーニング					*/
/*	指定された一つの桁の値を解答する	*/
/****************************************/

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

int main(void)
{
	int i, j;
	int level, digit, no, success = 0;
	char ans[LEVEL_MAX + 1];
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

		digit = rand() % level;
		printf("\r%*s\r先頭から%d桁目の数字は何ですか：", level, "", digit + 1);
		scanf("%d", &no);

		if (no + '0' == ans[digit]) {
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
