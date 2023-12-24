/****************************/
/*	数当てゲーム			*/
/*	A～Bの整数を当てる		*/
/****************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(void)
{
	int a, b, ans, dif;
	int max = 0, count = 0, num;

	srand(time(NULL));

	puts("A～Bの整数を当てよう！");
	printf("Aの値：");	scanf("%d", &a);
	do {
		printf("Bの値：");	scanf("%d", &b);
	} while (b <= a);
	ans = (rand() % ((b - a) + 1)) + a;
	dif = b - a;
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
