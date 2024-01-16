/****************************************************************/
/*	マスターマインド					*/
/*	人間とコンピュータが同時に出題し、交互にヒントを与え	*/
/*	先に当てたほうの勝ち					*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef enum {
	None = 0,
	Fail,
	Blow,
	Hit,
} Result;

Result mResult[][10] = { None };					/*	コンピュータ履歴		*/

/********************************/
/*	相違なる4個の数字生成	*/
/********************************/
void make4digits(int x[])
{
	int i, j;
	int val;							/*	0～9の乱数			*/

	for (i = 0; i < 4; i++) {
		do {
			val = rand() % 10;
			for (j = 0; j < i; j++) {
				if (val == x[j]) {
					break;
				}
			}
		} while (j < i);
		x[i] = val;
	}
}

/********************************/
/*	入力文字チェック	*/
/********************************/
int check(const char s[])
{
	int i, j;
	int len;

	len = strlen(s);
	if (len != 4) {							/*	文字数チェック			*/
		printf("きちんと4文字で入力してください。\n");
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (isdigit(s[i] == 0)) {				/*	文字チェック			*/
			printf("数字以外の文字を入力してください。\n");
			return 0;
		}
		for (j = 0; j < i; j++) {				/*	重複チェック			*/
			if (s[i] == s[j]) {
				printf("同一の数字を複数入力しないでください。\n");
				return 0;
			}
		}
	}

	return 1;
}

/********************************/
/*	コンピュータ入力	*/
/********************************/
void input_comp(char comp[])
{
	int i, j;
	int hit;
	int num, retry;

	/*	初期化	*/
	for (i = 0; i < 4; i++) {
		comp[i] = -1;
	}

	/*	Hitの数字格納	*/
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 10; j++) {
			if (mResult[i][j] == Hit) {
				comp[i] = j;
				break;
			}
		}
	}

	/*	コンピュータ入力	*/
	for (i = 0; i < 4; i++) {
		if (comp[i] != -1) {
			continue;
		}
		hit = 0;
		for (j = 0; j < 10; j++) {
			if (mResult[i][j] == Hit) {
				comp[i] = j;
				hit = 1;
				break;
			}
		}
		if (hit == 1) {
			continue;
		}
		do {
			do {
				retry = 1;
				num = rand() % 10;
				for (j = 0; j < 4; j++) {		/*	重複チェック			*/
					if (num == comp[j]) {
						retry = 0;
						break;
					}
				}
			} while (retry == 0);
		} while (mResult[i][num] == Fail);
		comp[i] = num;
	}
	comp[i] = '\0';
}

/********************************/
/*	ヒット/ブロー判定(人間)	*/
/********************************/
void judge_human(const char s[], const int x[], int* hit, int hitNum[], int* blow, int blowNum[])
{
	int i, j;

	*hit = *blow = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (s[i] == '0' + x[j]) {
				if (i == j) {
					hitNum[i] = 1;
					(*hit)++;
				}
				else {
					blowNum[i] = 1;
					(*blow)++;
				}
			}
		}
	}
}

/********************************/
/*	コンピュータ履歴設定	*/
/********************************/
void set_compresult(Result res, int index, int num)
{
	int i;

	switch (res) {
	case Blow:
		for (i = 0; i < 4; i++) {
			if (mResult[i][num - '0'] != Fail && mResult[i][num - '0'] != Hit) {
				mResult[i][num - '0'] = res;
			}
		}
		break;

	case Hit:
		for (i = 0; i < 4; i++) {
			if (i == index) {
				mResult[i][num - '0'] = res;
			}
			else {
				mResult[i][num - '0'] = Fail;
			}
		}
		break;

	default:
		break;
	}
}

/****************************************/
/*	ヒット/ブロー判定(コンピュータ)	*/
/****************************************/
void judge_comp(const char s[], const char x[], int* chit, int* cblow)
{
	int i, j;

	*chit = *cblow = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (s[i] == x[j] - '0') {
				if (i == j) {
					(*chit)++;
					set_compresult(Hit, i, x[i]);
				}
				else {
					(*cblow)++;
					set_compresult(Blow, i, x[i]);
				}
			}
		}
	}
}

/************************/
/*	判定結果表示	*/
/************************/
void disp_result(int hit, int total)
{
	if (hit == 4) {
		printf("正解です。");
	}
	else if (total == 0) {
		printf("	それらの数字はまったく含まれません。\n");
	}
	else {
		printf("	それらの数字中%d個の数字が含まれます。\n", total);
		if (hit == 0) {
			printf("	ただし位置もあっている数字はありません。\n");
		}
		else {
			printf("	その中の%d個は位置もあっています。\n", hit);
		}
	}
	putchar('\n');
	fflush(stdout);
}

/************************/
/*	ヒント表示	*/
/************************/
void disp_hint(const char buff[], const int ans[], const char comp[], const int hitNum[], const int blowNum[], int num)
{
	int no, i;
	char* s[] = { "　(0):正解の先頭の1文字目", "　(1)位置があっている数字の中で先頭側の1文字目"
					, "　(2)含まれている数字の中で末尾側の1文字目", "　(3)表示しない" };

	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s\n", s[i]);
	}
	printf("どのヒントを表示しますか？：");
	scanf("%d", &no);

	switch (no) {
	case 0:			/*	先頭の1文字を教える				*/
		printf("1個目の数字は\"%d\"です。\n", ans[0]);
		mResult[0][comp[0] - '0'] = Hit;
		for (i = 1; i < 4; i++) {
			mResult[i][comp[0] - '0'] = Fail;
		}
		break;

	case 1:			/*	ヒットした数字の中で先頭側の1文字を教える	*/
		for (i = 0; i < num; i++) {
			if (hitNum[i] == 1) {
				printf("位置があっている数字の中の先頭の数字は、\"%d\"です。\n", buff[i] - '0');
				return;
			}
		}
		puts("位置があっている数字はありません。");
		break;

	case 2:			/*	ブローした数字の中で末尾側の1文字を教える	*/
		for (i = num; i > 0; i--) {
			printf("%d\n", i);
			if (blowNum[i - 1] == 1) {
				printf("含まれている数字の中の末尾の数字は、\"%d\"です。\n", buff[i - 1] - '0');
				return;
			}
		}
		puts("含まれている数字はありません。");
		break;

	default:
		break;
	}
}

int main(void)
{
	int i, j, chk;
	int try_no = 0;
	int hit, blow, chit, cblow;
	int ans[4];
	char comp[10];							/*	入力文字(コンピュータへの出題)	*/
	char buff[10];							/*	入力文字(人間解答)		*/
	char cbuff[5];							/*	入力文字(コンピュータ解答)	*/
	int hitNum[4], blowNum[4];
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、4個の数字の並びです。");
	puts("　同じ数字が複数含まれることはありません。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。");
	puts("　コンピュータにも数字を出題し、先に当てたほうを勝者とします。\n");

	/*	解答作成	*/
	make4digits(ans);						/*	相違なる4個の数字生成		*/
	do {
		printf("コンピュータに出題する4個の数字を入力してください:");
		scanf("%s", comp);
		chk = check(comp);
	} while (chk == 0);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < sizeof(mResult[i]) / sizeof(mResult[i][0]); j++) {
			mResult[i][j] = None;
		}
	}

	start = time(NULL);						/*	開始時刻			*/
	do {
		/*	数字の入力	*/
		do {
			printf("入力してください：");
			scanf("%s", buff);
			chk = check(buff);				/*	入力文字チェック		*/
		} while (chk == 0);
		input_comp(cbuff);					/*	コンピュータ入力		*/

		for (i = 0; i < 4; i++) {
			hitNum[i] = blowNum[i] = 0;
		}
		try_no++;
		puts("あなた");
		judge_human(buff, ans, &hit, hitNum, &blow, blowNum);	/*	ヒット/ブロー判定(人間)		*/
		disp_result(hit, (hit + blow));				/*	判定結果表示			*/
		puts("コンピュータ");
		printf("%s", cbuff);
		judge_comp(cbuff, comp, &chit, &cblow);			/*	ヒット/ブロー判定		*/
		disp_result(chit, (chit + cblow));			/*	判定結果表示			*/
		/**/
		if (hit < 4 && chit < 4) {
			disp_hint(buff, ans, comp, hitNum, blowNum, sizeof(ans) / sizeof(ans[0]));
		}
	} while (hit < 4 && chit < 4);
	end = time(NULL);						/*	終了時刻			*/

	if (hit == 4) {
		puts("あなたの勝ちです。");
		printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));
	}
	else {
		puts("コンピュータの勝ちです。");
		printf("正解は、%sです。", comp);
	}

	return 0;
}
