/********************************/
/*	ダブルナンバーサーチ		*/
/*	出題対象の数字を0～9に変更	*/
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "getputch.h"

#define MAX_STAGE 10
#define swap(type, x, y)	do { type t = x; x = y; y  = t; } while (0)

int main(void)
{
	int dgt[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int a[11] = { 0 };
	int i, j, k;
	int x, ans;
	time_t start, end;
	double msec;

	srand(time(NULL));

	printf("ダブっている数字を見つけよう！！\n");
	printf("スペースキーで開始します。\n");
	while (getch() != ' ') {
	}

	start = time(NULL);
	for (i = 0; i < MAX_STAGE; i++) {
		j = 0;
		k = 0;
		x = rand() % 10;

		/*	配列コピー	*/
		while (j < 10) {
			a[k++] = dgt[j];
			if (j == x) {
				a[k++] = dgt[j];
			}
			j++;
		}

		for (j = 10; j > 0; j--) {
			k = rand() % (j + 1);
			if (j != k) {
				swap(int, a[j], a[k]);
			}
		}

		/*	表示	*/
		for (j = 0; j < 11; j++) {
			printf("%d ", a[j]);
		}
		printf("：");

		/*	入力	*/
		do {
			ans = getch();
			if (isprint(ans) != 0) {
				putch(ans);
				if (ans != dgt[x] + '0') {
					putch('\b');
				} else {
					printf("\n");
				}
			}
		} while (ans != dgt[x] + '0');
	}
	end = time(NULL);

	msec = difftime(end, start);

	printf("%.1f秒かかりました。\n", msec);
	if (msec > 25.0) {
		printf("鈍すぎます。\n");
	} else if (msec > 20.0) {
		printf("少し鈍いですね。\n");
	} else if (msec > 17.0) {
		printf("まあまあですね。\n");
	} else {
		printf("素早いですね。\n");
	}

	return 0;
}
