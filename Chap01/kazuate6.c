/****************************************/
/*	数当てゲーム			*/
/*	do文をfor文を用いて書き直す	*/
/****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10		/*	最大入力回数	*/

int main(void)
{
	int i;
	int ans;			/*	回答(乱数)	*/
	int no;				/*	読み込んだ数	*/
	int num[MAX_STAGE];		/*	入力履歴	*/
	int stage;			/*	入力回数	*/

	srand(time(NULL));		/*	種を設定	*/
	ans = rand() % 1000;
	printf("0～999の整数を当てよう！！\n\n");

	for (stage = 0; stage < MAX_STAGE; stage++) {
		printf("残り%d回。いくつかな：", (MAX_STAGE - stage));
		scanf("%d", &no);
		num[stage] = no;

		if (no < ans) {
			printf("もっと大きいよ。\a\n");
		} else if (no > ans) {
			printf("もっと小さいよ。\a\n");
		} else {
			break;
		}
	}

	if (no != ans) {
		printf("残念。正解は%dでした。", ans);
	} else{
		printf("正解です。\n");
		printf("%d回で当たりましたね。\n", stage);
	}

	puts("\n---入力履歴---");
	for (i = 0; i < stage; i++) {
		printf(" %2d : %4d %+4d\n", (i + 1), num[i], (num[i] - ans));
	}

	return 0;
}
