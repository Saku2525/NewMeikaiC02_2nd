/****************************/
/*	じゃんけんゲーム		*/
/*	履歴表示あり(n回勝負)	*/
/****************************/

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

/************************/
/*	履歴表示用構造体	*/
/************************/
typedef struct {
	int human;	/*	人間			*/
	int comp;	/*	コンピュータ	*/
	int judge;	/*	勝敗			*/
} History;

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

/****************/
/*	履歴格納	*/
/****************/
void set_history(History *hist, int human, int comp, int judge)
{
	hist->human = human;
	hist->comp = comp;
	hist->judge = judge;
}

/****************/
/*	履歴表示	*/
/****************/
void disp_history(History hist)
{
	char *judge[] = { "引き分け", "負け", "勝ち" };

	printf("%6s　　", mHd[hist.human]);
	printf("%3s", mHd[hist.comp]);
	if (hist.comp == 1) {
		printf("%+15s\n", judge[hist.judge]);
	} else {
		printf("%+16s\n", judge[hist.judge]);
	}
}

int main(void)
{
	Score score;
	int count;
	int num = 0, human, comp;
	int judge, retry;
	int i;
	History *hist;

	initialize(&score);
	do {
		printf("何回勝負しますか：");
		scanf("%d", &count);
	} while (count <= 0);
	hist = calloc(count * 10, sizeof(History));

	do {
		jyanken(&human, &comp);						/*	じゃんけん実行	*/
		printf("私は%sで、あなたは%sです。\n", mHd[comp], mHd[human]);
													/*	手を表示		*/
		judge = ((human - comp) + 3) % 3;			/*	勝敗を判定		*/
		update_score(judge, &score);				/*	スコアを更新	*/
		disp_judge(judge);							/*	判定結果を表示	*/
		if (++num % (count * 10) == 0) {
			hist = (History *)realloc(hist, (num + count * 10) * sizeof(History));
		}
		set_history(&hist[num - 1], human, comp, judge);	/*	履歴格納		*/
	} while (score.win < count && score.lose < count);

	printf((score.win == count) ? "\nあなたの勝ちです。\n" : "\nあなたの負けです。\n");
	printf("%d勝%d負%d分けでした。\n\n", score.win, score.lose, score.draw);

	puts("--------------------履歴--------------------");
	puts(" 　　あなた　　コンピュータ　　結果");
	for (i = 0; i < num; i++) {
		printf("%3d. ", i + 1);
		disp_history(hist[i]);						/*	履歴表示		*/
	}

	free(hist);

	return 0;
}
