/****************************/
/*	数当てゲーム			*/
/*	-999～999の整数を当てる	*/
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX 10

int main(void)
{
	int ans;
	int count = 0, num;

	srand(time(NULL));
	ans = (rand() % 1999) - 999;

	puts("-999～999の整数を当てよう！");

	do {
		printf("残り%d回。", MAX - count);
		printf("いくつかな：");
		scanf("%d", &num);

		if (num > ans) {
			puts("もっと小さいよ。");
		} else if (num < ans) {
			puts("もっと大きいよ。");
		}
		count++;
	} while ((num != ans) && (count < MAX));

	if (ans != num) {
		printf("残念。正解は、%dでした。", ans);
	} else {
		puts("正解です。");
		printf("%d回で当たりましたね。\n", count);
	}

	return 0;
}
