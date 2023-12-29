/****************************************************************/
/*	文字列表示						*/
/*	表示速度を設定し、文字列を先頭から1文字ずつ表示する	*/
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

void gput(const char *s, int speed)
{
	int i;
	int len = strlen(s);

	for (i = 0; i < len; i++) {
		putchar(s[i]);
		sleep((unsigned long)speed);
	}
}

int main(void)
{
	char *s;
	int speed;

	printf("表示する文字列：");
	scanf("%s", s);
	printf("表示速度(ms)：");
	scanf("%d", &speed);

	gput(s, speed);

	return 0;
}
