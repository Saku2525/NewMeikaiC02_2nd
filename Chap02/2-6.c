/************************************************/
/*	暗算トレーニング			*/
/*	加算・減算を行えるようにする(ランダム)	*/
/************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	MAX	10
#define NUM	3

int main(void)
{
	int i, j;
	int num[NUM];				/*	10～99の乱数	*/
	int ans;				/*	解答		*/
	int space;				/*	余白の幅(0～16)	*/
	int input;				/*	入力		*/
	double dt[MAX];
	double ave = 0.0;
	time_t start, end;

	srand(time(NULL));
	printf("視野拡大暗算トレーニング開始！！\n");

	for (i = 0; i < MAX; i++) {
		start = time(NULL);
		for (j = 0; j < NUM; j++) {
			num[j] = 10 + rand() % 90;
		}
		space = rand() % 17;
		ans = num[0];
		printf("%d%*s", num[0], space, "");
		for (j = 1; j < NUM; j++) {
			if (rand() % 2 == 0) {
				printf("+%*s%d%*s", space, "", num[j], space, "");
				ans += num[j];
			} else {
				printf("-%*s%d%*s", space, "", num[j], space, "");
				ans -= num[j];
			}
		}
		putchar(':');

		do {
			scanf("%d", &input);
			if (input == ans) {
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
