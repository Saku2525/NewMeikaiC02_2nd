/********************************************************/
/*	プラスワントレーニング				*/
/*	数値入力に-1を入力すると一つ前の数値の入力に戻る	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEVEL_MIN 2
#define LEVEL_MAX 6

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
	int i, j, retry, cnt = 0;
	int x;
	int max_stage;
	int level, success, suc_total = 0;
	int no[LEVEL_MAX], ans[LEVEL_MAX];
	int *score;
	time_t start, end;

	srand(time(NULL));
	printf("プラスワントレーニング開始！！\n");
	printf("2桁の数値を記憶します。\n");
	printf("1を加えた値を入力してください。\n");

	do {
		printf("挑戦するレベル（%d ～ %d）：", LEVEL_MIN, LEVEL_MAX);
		scanf("%d", &level);
	} while ((level < LEVEL_MIN) || (level > LEVEL_MAX));
	putchar('\n');

	do {
		printf("トレーニング回数：");
		scanf("%d", &max_stage);
	} while (max_stage <= 0);
	putchar('\n');
	score = (int *)calloc(max_stage, sizeof(int));
	start = time(NULL);

	do {
		printf("第%dステージ開始！！\n", cnt + 1);
		success = 0;
		no[0] = '0' + (10 + rand() % 90);
		for (i = 0; i < level; i++) {
			no[i] = 10 + rand() % 90;
			printf("%d ", no[i]);
		}
		sleep(300 * level);

		printf("\r%*s\r", level * 3, "");
		fflush(stdout);

		for (i = 0; i < level; i++) {
			printf("%d番目の数：", i + 1);
			scanf("%d", &ans[i]);
			if ((i != 0) && (ans[i] == -1)) {
				i -= 2;
			}
		}

		for (i = 0; i < level; i++) {
			if (ans[i] - 1 == no[i]) {
				printf("〇 ");
				success++;
				suc_total++;
			}
			else {
				printf("× ");
			}
		}
		score[cnt++] = success;
		putchar('\n');

		for (i = 0; i < level; i++) {
			printf("%d ", no[i]);
		}
		printf("… %d個正解です。\n", success);
		putchar('\n');
	} while (cnt < max_stage);
	end = time(NULL);

	printf("%d回中%d回正解しました。\n", cnt * level, suc_total);

	printf("■□　成績　□■\n");
	for (i = level; i > 0; i--) {
		for (j = 0; j < max_stage; j++) {
			if (score[j] >= i) {
				printf("　☆　");
			}
			else {
				printf("　 　");
			}
		}
		putchar('\n');
	}
	free(score);
	printf("-----------------------------------------------------\n");
	for (i = 0; i < max_stage; i++) {
		printf("  %02d ", i + 1);
	}
	putchar('\n');

	printf("%.1f秒でした。\n", difftime(end, start));

	return 0;
}
