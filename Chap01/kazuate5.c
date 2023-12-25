/********************************************************/
/*	数当てゲーム					*/
/*	入力履歴表示で、0に対しては符号をつけない	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10		/*	最大入力回数	*/

int main(void)
{
	int i;
	int ans;			/*	回答(乱数)		*/
	int no;				/*	読み込んだ数		*/
	int num[MAX_STAGE];		/*	入力履歴		*/
	int stage = 0;			/*	入力回数		*/
	int dif;			/*	正解との差		*/

	srand(time(NULL));		/*	種を設定		*/
	ans = rand() % 1000;
	printf("0～999の整数を当てよう！！\n\n");

	do {
		printf("残り%d回。いくつかな：", (MAX_STAGE - stage));
		scanf("%d", &no);
		num[stage++] = no;

		if (no < ans) {
			printf("もっと大きいよ。\a\n");
		} else if (no > ans) {
			printf("もっと小さいよ。\a\n");
		}
	} while((no != ans) && (stage < MAX_STAGE));

	if (no != ans) {
		printf("残念。正解は%dでした。", ans);
	} else{
		printf("正解です。\n");
		printf("%d回で当たりましたね。\n", stage);
	}

	puts("\n---入力履歴---");
	for (i = 0; i < stage; i++) {
		dif = num[i] - ans;
		printf(" %2d : %4d ", (i + 1), num[i]);
		if (dif == 0) {
			printf("%4d\n", dif);
		} else {
			printf("%+4d\n", dif);
		}
	}

	return 0;
}
