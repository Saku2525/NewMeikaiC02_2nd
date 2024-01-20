/****************************/
/*	記憶力トレーニング		*/
/*	英字を逆順に入力させる	*/
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_STAGE 10
#define LEVEL_MIN 3
#define LEVEL_MAX 20
#define swap(type, x, y) do { type t = x; x = y; y = t; } while(0)

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
	int level, success = 0;
	char ltr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
	char mstr[LEVEL_MAX + 1], ans[LEVEL_MAX * 2];
	time_t start, end;

	srand(time(NULL));
	printf("英字記憶トレーニング\n");

	do {
		printf("挑戦するレベル（%d ～ %d）：", LEVEL_MIN, LEVEL_MAX);
		scanf("%d", &level);
	} while ((level < LEVEL_MIN) || (level > LEVEL_MAX));

	printf("%d個の英字を記憶しましょう！！\n", level);
	printf("入力は逆順に入力してください。\n");

	start = time(NULL);

	for (i = 0; i < MAX_STAGE; i++) {
		for (j = 0; j < level; j++) {
			mstr[j] = ltr[rand() % strlen(ltr)];
		}
		mstr[level] = '\0';

		printf("%s", mstr);
		fflush(stdout);
		sleep(125 * level);

		printf("\r%*s\r入力せよ：", level, "");
		scanf("%s", ans);

		for (j = 0; j < level / 2; j++) {
			swap(char, mstr[j], mstr[level - j - 1]);
		}

		if (strcmp(mstr, ans) == 0) {
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
