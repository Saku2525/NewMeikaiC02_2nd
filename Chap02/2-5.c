/****************************************/
/*	暗算トレーニング					*/
/*	各回の所要時間とその平均時間を表示	*/
/****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	MAX	10

int main(void)
{
	int i;
	int a, b, c;			/*	10～99の乱数	*/
	int ans;
	int space;				/*	余白の幅(0～16)	*/
	double dt[MAX];
	double ave = 0.0;
	time_t start, end;

	srand(time(NULL));
	printf("視野拡大暗算トレーニング開始！！\n");

	for (i = 0; i < MAX; i++) {
		start = time(NULL);
		a = 10 + rand() % 90;
		b = 10 + rand() % 90;
		c = 10 + rand() % 90;
		space = rand() % 17;

		printf("%d%*s+%*s%d%*s+%*s%d：", a, space, "", space, "", b, space, "", space, "", c);
		do {
			scanf("%d", &ans);
			if (ans == (a + b + c)) {
				break;
			}
			printf("\a違います。再入力してください。：");
		} while (1);
		end = time(NULL);
		dt[i] = difftime(end, start);
	}

	puts("---所要時間---");
	for (i = 0; i < MAX; i++) {
		printf("%d回目：%.1f秒かかりました。\n", i + 1, dt[i]);
		ave += dt[i];
	}
	putchar('\n');
	puts("---平均時間---");
	printf("%.1f秒\n", ave / MAX);

	return 0;
}
