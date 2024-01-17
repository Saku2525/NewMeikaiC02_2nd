/************************************************/
/*	数当てゲーム				*/
/*	異なる桁が同一である数字を出さない	*/
/************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10			/*	最大入力回数	*/
#define MAX_DIGITS 3			/*	最大桁数	*/

int main(void)
{
	int i, j, chk;
	char rNum;
	char digits[MAX_DIGITS + 1];
	int ans;			/*	回答(乱数)	*/
	int no;				/*	読み込んだ数	*/
	int num[MAX_STAGE];		/*	入力履歴	*/
	int stage = 0;			/*	入力回数	*/

	srand(time(NULL));		/*	種を設定	*/

	/*	数設定	*/
	for (i = 0; i < MAX_DIGITS; i++) {
		do {
			chk = 1;
			rNum = (rand() % 10) + '0';
			for (j = 0; j < i; j++) {
				if (rNum == digits[j]) {
					chk = 0;
				}
			}
		} while (chk == 0);
		digits[i] = rNum;
	}
	digits[MAX_DIGITS] = '\0';
	ans = atoi(digits);

	printf("0～999の整数を当てよう！！\n\n");

	do {
		printf("残り%d回。いくつかな：", (MAX_STAGE - stage));
		scanf("%d", &no);
		num[stage++] = no;

		if (no < ans) {
			printf("もっと大きいよ。\a\n");
		}
		else if (no > ans) {
			printf("もっと小さいよ。\a\n");
		}
	} while ((no != ans) && (stage < MAX_STAGE));

	if (no != ans) {
		printf("残念。正解は%dでした。", ans);
	}
	else {
		printf("正解です。\n");
		printf("%d回で当たりましたね。\n", stage);
	}

	puts("\n---入力履歴---");
	for (i = 0; i < stage; i++) {
		printf(" %2d : %4d %+4d\n", (i + 1), num[i], (num[i] - ans));
	}

	return 0;
}
