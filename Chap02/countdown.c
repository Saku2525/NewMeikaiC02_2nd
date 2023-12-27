/********************************/
/*	カウントダウン				*/
/*	経過秒数とクロック数を表示	*/
/********************************/

#include <stdio.h>
#include <time.h>

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
	int i;
	clock_t c;

	for (i = 10; i > 0; i--) {
		printf("\r%2d", i);
		fflush(stdout);
		sleep(1000);
	}
	printf("\rFIRE!!\a\n");

	c = clock();
	printf("プログラム開始から%.1f秒経過しました。\n"
			, ((double)c / CLOCKS_PER_SEC));
	printf("クロック数：%d\n", (unsigned)c);

	return 0;
}
