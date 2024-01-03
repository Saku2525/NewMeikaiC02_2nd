/********************************************************/
/*	じゃんけんゲーム				*/
/*	関数update_scoreと関数disp_resultをまとめる	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************/
/*	スコア用構造体	*/
/************************/
typedef struct {
	int draw;	/*	引き分けた回数	*/
	int lose;	/*	勝った回数	*/
	int win;	/*	負けた回数	*/
} Score;

char *mHd[] = { "グー", "チョキ", "パー" };

/****************/
/*---初期処理---*/
/****************/
void initialize(Score *s)
{
	s->draw = s->lose = s->win = 0;

	srand(time(NULL));

	printf("じゃんけんゲーム開始！！\n");
}

/**********************/
/*---じゃんけん実行---*/
/**********************/
void jyanken(int *human, int *comp)
{
	int i;

	*comp = rand() % 3;
	do {
		printf("\nじゃんけんポン…");
		for (i = 0; i < 3; i++) {
			printf(" (%d)%s", i, mHd[i]);
		}
		printf("：");
		scanf("%d", human);
	} while (*human < 0 || *human > 2);
}

/*********************************/
/*---スコア更新 / 判定結果表示---*/
/*********************************/
void update_disp(int judge, Score *score)
{
	switch (judge) {
		case 0:
			score->draw++;
			printf("引き分けです。\n");
			break;

		case 1:
			score->lose++;
			printf("あなたの負けです。\n");
			break;

		case 2:
			score->win++;
			printf("あなたの勝ちです。\n");
			break;
	}
}

/************************/
/*---再挑戦するか確認---*/
/************************/
int confirm_retry(void)
{
	int ret;

	printf("もう一度しますか…(0)いいえ (1)はい：");
	scanf("%d", &ret);

	return ret;
}

int main(void)
{
	Score score;
	int human, comp;
	int judge, retry;
	int i;

	initialize(&score);

	do {
		jyanken(&human, &comp);			/*	じゃんけん実行		*/
		printf("私は%sで、あなたは%sです。\n", mHd[comp], mHd[human]);
							/*	手を表示		*/
		judge = ((human - comp) + 3) % 3;	/*	勝敗を判定		*/
		update_disp(judge, &score);		/*	スコア更新/判定結果表示	*/
		retry = confirm_retry();		/*	再挑戦するか確認	*/
	} while (retry == 1);

	printf("%d勝%d負%d分けでした。\n", score.win, score.lose, score.draw);

	return 0;
}
