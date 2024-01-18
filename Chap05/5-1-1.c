/************************************************/
/*	記憶力トレーニング			*/
/*	記憶した整数の各桁を逆順に入力させる	*/
/************************************************/

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

/*--- 逆順に並べた整数を作成 ---*/
int create_rnum(int num)
{
	int i;
	char buf[MAX_DIGIT + 1], rNum[MAX_DIGIT + 1];
	
	sprintf(buf, "%d", num);
	for (i = 0; i < MAX_DIGIT; i++) {
		rNum[i] = buf[MAX_DIGIT - 1 - i];
	}
	rNum[i] = '\0';
	
	return atoi(rNum);
}

int main(void)
{
	int i;
	int ans, no, success = 0;
	time_t start, end;

	srand(time(NULL));
	printf("%d桁の数値を記憶しよう！！\n", MAX_DIGIT);

	start = time(NULL);

	for (i = 0; i < MAX_STAGE; i++) {
		ans = 1000 + rand() % 9000;
		printf("%d", ans);
		sleep(500);
		printf("\r入力せよ：");
		scanf("%d", &no);
		ans = create_rnum(ans);

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
