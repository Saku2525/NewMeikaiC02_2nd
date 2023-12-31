/********************************/
/*	文字列表示					*/
/*	文字列をテロップ表示する	*/
/********************************/

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

void telop(const char *s, int direction, int speed, int n)
{
	int i, j;
	int len, count = 0;

	len = strlen(s);

	for (i = 0; i < n; i++) {
		for (j = 0; j < len; j++) {
			if (count + j < len) {
				putchar(s[count + j]);
			} else {
				putchar(s[count + j - len]);
			}
		}
		putchar('\r');
		sleep(speed);

		switch (direction) {
			case 0:				/*	テロップ方向（左）	*/
				count--;
				if (count < 0) {
					count = len - 1;
				}
				break;

			case 1:				/*	テロップ方向（右）	*/
				count++;
				if (count == len) {
					count = 0;
				}
				break;

			default:
				break;
		}
	}
	putchar('\n');
}

int main(void)
{
	char *s;
	int direction, speed, n;

	printf("表示する文字列：");					scanf("%s", s);
	printf("テロップの方向（0:左, 1:右）：");	scanf("%d", &direction);
	printf("表示速度(ms)：");					scanf("%d", &speed);
	printf("表示回数：");						scanf("%d", &n);

	telop(s, direction, speed, n);

	return 0;
}
