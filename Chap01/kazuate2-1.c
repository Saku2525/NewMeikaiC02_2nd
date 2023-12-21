/****************************/
/*	数当てゲーム			*/
/*	3～999の3の倍数を当てる	*/
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX	8

int main(void)
{
	int ans;
	int count = 0, num;

	srand(time(NULL));
	do {
		ans = rand() % 997 + 3;
	} while ((ans % 3) != 0);

	puts("3～999の3の倍数を当てよう！");

	do {
		printf("残り%d回。", MAX - count);
		printf("いくつかな：");
		scanf("%d", &num);
		if ((num % 3) != 0) {
			return 1;
		}

		if (num > ans) {
			puts("もっと小さいよ。");
		} else if (num < ans) {
			puts("もっと大きいよ。");
		}
		count++;
	} while ((num != ans) && (count < MAX));

	if (num != ans) {
		printf("残念。正解は、%dでした。\n", ans);
	} else {
		puts("正解です。");
		printf("%d回で当たりましたね。\n", count);
	}

	return 0;
}
