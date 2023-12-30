/****************************************************************/
/*	文字列表示						*/
/*	文字列をdミリ秒表示しeミリ秒消去するのをn回繰り返す	*/
/****************************************************************/

#include <stdio.h>
#include <time.h>
#include <string.h>

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

void bput(const char *s, int d, int e, int n)
{
	int i;
	int len;

	len = strlen(s);

	for (i = 0; i < n; i++) {
		printf("%s\r", s);
		sleep((unsigned long)d);
		printf("%*s\r", len, "");
		sleep((unsigned long)e);
	}
}

int main(void)
{
	char *s;
	int disp, hide, count;

	printf("表示する文字列：");	scanf("%s", s);
	printf("表示時間(ms)：");	scanf("%d", &disp);
	printf("消去時間(ms)：");	scanf("%d", &hide);
	printf("繰り返し回数：");	scanf("%d", &count);

	bput(s, disp, hide, count);

	return 0;
}
