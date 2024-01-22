/****************************************/
/*	記憶力トレーニング		*/
/*	指定された文字の番目を解答する	*/
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
	int i, j, k;
	int level, retry, success = 0;
	char c;
	char ltr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
	char mstr[LEVEL_MAX + 1];
	int digit, ans;
	time_t start, end;

	srand(time(NULL));
	printf("英字記憶トレーニング\n");

	do {
		printf("挑戦するレベル（%d ～ %d）：", LEVEL_MIN, LEVEL_MAX);
		scanf("%d", &level);
	} while ((level < LEVEL_MIN) || (level > LEVEL_MAX));

	printf("%d個の英字を記憶しましょう！！\n", level);

	start = time(NULL);

	for (i = 0; i < MAX_STAGE; i++) {
		for (j = 0; j < level; j++) {
			do {
				retry = 0;
				c = ltr[rand() % strlen(ltr)];
				for (k = 0; k < j; k++) {
					if (c == mstr[k]) {
						retry = 1;
						break;
					}
				}
			} while (retry == 1);
			mstr[j] = c;
		}
		mstr[level] = '\0';

		printf("%s", mstr);
		//fflush(stdout);
		sleep(125 * level);

		digit = rand() % level;
		printf("\r%*s\r%cは何文字目ですか：", level, "", mstr[digit]);
		scanf("%d", &ans);

		if (ans - 1 == digit) {
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
