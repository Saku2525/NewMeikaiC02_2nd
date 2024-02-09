/********************************/
/*	ラックナンバーサーチ		*/
/*	出題をフラッシュ形式で表示	*/
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "getputch.h"

#define MAX_STAGE 10
#define swap(type, x, y)	do { type t = x; x = y; y  = t; } while (0)

int sleep(unsigned long x)
{
	clock_t start = clock(), end;

	do {
		if ((end = clock()) == (clock_t)-1) {
			return 0;
		}
	} while ((1000.0 * (end - start) / CLOCKS_PER_SEC) < x);

	return 1;
}

int main(void)
{
	int dgt[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int a[8] = { 0 };
	int i, j, k;
	int x, ans;
	time_t start, end;
	double msec;

	srand(time(NULL));

	printf("欠けている数字を見つけよう！！\n");

	start = time(NULL);
	for (i = 0; i < MAX_STAGE; i++) {
		j = 0;
		k = 0;
		x = rand() % 9;

		/*	配列コピー	*/
		while (j < 9) {
			if (j != x) {
				a[k++] = dgt[j];
			}
			j++;
		}

		for (j = 7; j > 0; j--) {
			k = rand() % (i + 1);
			if (i != j) {
				swap(int, a[j], a[k]);
			}
		}

		/*	表示	*/
		for (j = 0; j < 8; j++) {
			printf("\r \r%d", a[j]);
			sleep((unsigned long)500);
		}
		printf("：");

		/*	入力	*/
		do {
			ans = getch();
			if (isprint(ans) != 0) {
				putch(ans);
				if (ans != dgt[x] + '0') {
					putch('\b');
				}
				else {
					printf("\n");
				}
			}
		} while (ans != dgt[x] + '0');
		putchar('\n');
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
