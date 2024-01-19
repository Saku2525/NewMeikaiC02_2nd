/****************************************/
/*	記憶力トレーニング					*/
/*	指定された一つの桁の値を解答する	*/
/****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10
#define MAX_DIGIT 4

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

/*--- 指定された桁の値を探索 ---*/
int search_digit(int num, int digit)
{
	char buf[MAX_DIGIT + 1];
	
	sprintf(buf, "%d", num);
	
	return (int)buf[digit] - '0';
}

int main(void)
{
	int i;
	int ans, digit, no, success = 0;
	time_t start, end;

	srand(time(NULL));
	printf("4桁の数値を記憶しよう！！\n");


	start = time(NULL);

	for (i = 0; i < MAX_STAGE; i++) {
		ans = 1000 + rand() % 9000;
		printf("%d", ans);
		sleep(500);
		
		digit = rand() % MAX_DIGIT;
		printf("\r先頭から%d桁目の数字は何ですか：", digit + 1);
		scanf("%d", &no);
		ans = search_digit(ans, digit);

		if (no == ans) {
			printf("正解です。\n");
			success++;
		} else {
			printf("間違いです。\n");
		}
	}
	end = time(NULL);

	printf("%d回中%d回成功しました。\n", MAX_STAGE, success);
	printf("%.1f秒でした。\n", difftime(end, start));

	return 0;
}
