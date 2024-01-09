/************************************/
/*	じゃんけんゲーム				*/
/*	4人(コンピュータ3人) (n回勝負)	*/
/************************************/

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
void jyanken(int *human, int *comp1, int *comp2, int *comp3)
{
	int i;

	*comp1 = rand() % 3;
	*comp2 = rand() % 3;
	*comp3 = rand() % 3;

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
int judge_winlose(int human, int comp1, int comp2, int comp3)
{
	int judge;
	int hd[3] = { 0 };
	int i;

	hd[human] = 1;
	hd[comp1] = 1;
	hd[comp2] = 1;
	hd[comp3] = 1;

	for (i = 0; i < 3; i++) {
		if (hd[i] == 0) {
			break;
		}
		if (i == 2) {
			return 0;
		}
	}

	switch (human) {
		case 0:	judge = (comp1 == 1 || comp2 == 1 || comp3 == 1) ? 2 : 1;	break;
		case 1:	judge = (comp1 == 2 || comp2 == 2 || comp3 == 2) ? 2 : 1;	break;
		case 2:	judge = (comp1 == 0 || comp2 == 0 || comp3 == 0) ? 2 : 1;	break;
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

int main(void)
{
	Score score;
	int count;
	int human, comp1,comp2, comp3;
	int judge, retry;
	int i;

	initialize(&score);
	do {
		printf("何回勝負しますか：");
		scanf("%d", &count);
	} while (count <= 0);

	do {
		jyanken(&human, &comp1, &comp2, &comp3);			/*	じゃんけん実行	*/
		printf("コンピュータ1は%sで、コンピュータ2は%sで、コンピュータ3は%sで、あなたは%sです。\n"
											, mHd[comp1], mHd[comp2], mHd[comp3], mHd[human]);
															/*	手を表示		*/
		judge = judge_winlose(human, comp1, comp2, comp3);	/*	勝敗を判定		*/
		update_score(judge, &score);						/*	スコアを更新	*/
		disp_judge(judge);									/*	判定結果を表示	*/
	} while (score.win < count && score.lose < count);

	printf((score.win == count) ? "\nあなたの勝ちです。\n" : "\nあなたの負けです。\n");
	printf("%d勝%d負%d分けでした。\n", score.win, score.lose, score.draw);

	return 0;
}
