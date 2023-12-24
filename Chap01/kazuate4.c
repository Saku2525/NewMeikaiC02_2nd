/****************************/
/*	数当てゲーム			*/
/*	レベルを選択させる		*/
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(void)
{
	int levelMax[] = { 9, 99, 999, 9999 };	/*	レベルごとの最大値	*/
	int level, ans, dif;
	int max = 0, count = 0, num;

	srand(time(NULL));

	puts("数当てゲーム！");
	printf("レベルを選んでください　(1)1～9　(2)1～99　(3)1～999　(4)1～9999:");
	do {
		scanf("%d", &level);
	} while ((level < 1) || (level > 4));
	printf("1～%dの整数を当てよう！\n", levelMax[level - 1]);

	ans = (rand() % levelMax[level - 1]) + 1;
	dif = levelMax[level - 1] - 1;
	while (dif > 1) {
		dif /= 2;
		max++;
	}

	do {
		printf("残り%d回。", max - count);
		printf("いくつかな：");
		scanf("%d", &num);

		if (num > ans) {
			puts("もっと小さいよ。");
		} else if (num < ans) {
			puts("もっと大きいよ。");
		}
		count++;
	} while ((num != ans) && (count < max));

	if (ans != num) {
		printf("残念。正解は、%dでした。", ans);
	} else {
		puts("正解です。");
		printf("%d回で当たりましたね。\n", count);
	}

	return 0;
}
