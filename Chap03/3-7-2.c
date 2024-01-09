/********************************************/
/*	じゃんけんゲーム						*/
/*	3人(コンピュータ2人) (勝負回数制限なし)	*/
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************/
/*	スコア用構造体	*/
/********************/
typedef struct {
	int draw;	/*	引き分けた回数	*/
	int lose;	/*	勝った回数		*/
	int win;	/*	負けた回数		*/
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
void jyanken(int *human, int *comp1, int *comp2)
{
	int i;

	*comp1 = rand() % 3;
	*comp2 = rand() % 3;
	do {
		printf("\nじゃんけんポン…");
		for (i = 0; i < 3; i++) {
			printf(" (%d)%s", i, mHd[i]);
		}
		printf("：");
		scanf("%d", human);
	} while (*human < 0 || *human > 2);
}

/****************/
/*---勝敗判定---*/
/****************/
int judge_winlose(int human, int comp1, int comp2)
{
	int judge;

	if ((human + comp1 + comp2) % 3 == 0) {		/*	あいこか判断	*/
		return 0;
	} else {
		switch (human) {
			case 0:	judge = (comp1 == 1 || comp2 == 1) ? 2 : 1;	break;
			case 1:	judge = (comp1 == 2 || comp2 == 2) ? 2 : 1;	break;
			case 2:	judge = (comp1 == 0 || comp2 == 0) ? 2 : 1;	break;
		}
	}

	return judge;
}

/********************/
/*---スコアを更新---*/
/********************/
void update_score(int judge, Score *score)
{
	switch (judge) {
		case 0:	score->draw++;	break;
		case 1:	score->lose++;;	break;
		case 2:	score->win++;	break;
	}
}

/**********************/
/*---判定結果を表示---*/
/**********************/
void disp_judge(int judge)
{
	switch (judge) {
		case 0:	printf("引き分けです。\n");		break;
		case 1:	printf("あなたの負けです。\n");	break;
		case 2:	printf("あなたの勝ちです。\n");	break;
	}
}

/************************/
/*---再挑戦するか確認---*/
/************************/
int confirm_retry(void)
{
	int retry;

	printf("もう一度しますか…(0)いいえ　(1)はい:");
	scanf("%d", &retry);

	return retry;
}

int main(void)
{
	Score score;
	int count;
	int human, comp1,comp2;
	int judge, retry;
	int i;

	initialize(&score);

	do {
		jyanken(&human, &comp1, &comp2);			/*	じゃんけん実行		*/
		printf("コンピュータ1は%sで、コンピュータ2は%sで、あなたは%sです。\n"
											, mHd[comp1], mHd[comp2], mHd[human]);
													/*	手を表示			*/
		judge = judge_winlose(human, comp1, comp2);	/*	勝敗を判定			*/
		update_score(judge, &score);				/*	スコアを更新		*/
		disp_judge(judge);							/*	判定結果を表示		*/
		retry = confirm_retry();					/*	再挑戦するか確認	*/
	} while (retry == 1);

	printf("%d勝%d負%d分けでした。\n", score.win, score.lose, score.draw);

	return 0;
}
