/********************************************************/
/*	じゃんけんゲーム				*/
/*	プレーヤの入力した回数分の手や勝敗の履歴を保存	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**********************/
/*---スコア用構造体---*/
/**********************/
typedef struct {
	int draw;	/*	引き分けた回数	*/
	int lose;	/*	勝った回数	*/
	int win;	/*	負けた回数	*/
} Score;

/************************/
/*---履歴表示用構造体---*/
/************************/
typedef struct {
	int comp;	/*	コンピュータ	*/
	int human;	/*	人間		*/
	int judge;	/*	判定		*/
} History;

/******************/
/*---プロパティ---*/
/******************/
char *mHd[] = { "グー", "チョキ", "パー" };
char *mJudge[] = { "引き分け", "負け", "勝ち" };

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

/********************/
/*---スコアを更新---*/
/********************/
void update_score(int judge, Score *score)
{
	switch (judge) {
	case 0:	score->draw++;	break;
	case 1:	score->lose++;	break;
	case 2:	score->win++;	break;
	}
}

/**********************/
/*---履歴データ格納---*/
/**********************/
void set_history(History *hist, int comp, int human, int judge)
{
	hist->comp = comp;
	hist->human = human;
	hist->judge = judge;
}

/**********************/
/*---判定結果を表示---*/
/**********************/
void disp_judge(int judge)
{
	switch (judge) {
	case 0:	printf("引き分けです。\n");	break;
	case 1:	printf("あなたの負けです。\n");	break;
	case 2:	printf("あなたの勝ちです。\n");	break;
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

/**********************/
/*---履歴データ表示---*/
/**********************/
void disp_history(History hist)
{
	printf("%6.6s　%6.6s　%s\n", mHd[hist.comp], mHd[hist.human], mJudge[hist.judge]);
}

int main(void)
{
	Score score;
	History *hist;
	int i, count = 0;
	int human, comp;
	int judge, retry;

	initialize(&score);

	do {
		printf("じゃんけんを行う回数を入力してください:");
		scanf("%d", &count);
	} while (count < 0);

	if ((hist = calloc(count, sizeof(History))) == NULL) {
		exit(0);					/*	強制終了		*/
	}
	for (i = 0; i < count; i++) {
		jyanken(&human, &comp);				/*	じゃんけん実行		*/
		printf("私は%sで、あなたは%sです。\n", mHd[comp], mHd[human]);
								/*	手を表示		*/
		judge = ((human - comp) + 3) % 3;		/*	勝敗を判定		*/
		update_score(judge, &score);			/*	スコアを更新		*/
		disp_judge(judge);				/*	判定結果を表示		*/
		set_history(&hist[i], comp, human, judge);	/*	履歴データ格納		*/
	}

	printf("%d勝%d負%d分けでした。\n\n", score.win, score.lose, score.draw);
	puts("-----------履歴-----------");
	puts("　私　　あなた　勝敗");
	puts("--------------------------");
	for (i = 0; i < count; i++) {
		disp_history(hist[i]);				/*	履歴データ表示		*/
	}
	
	free(hist);

	return 0;
}
