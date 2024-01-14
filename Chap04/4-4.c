/********************************/
/*	マスターマインド	*/
/*	数字の重複を許す	*/
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/************************/
/*	4個の数字生成	*/
/************************/
void make4digits(int x[])
{
	int i, j;
	int val;						/*	0～9の乱数		*/

	for (i = 0; i < 4; i++) {
		val = rand() % 10;
		x[i] = val;
	}
}

/*******************************/
/*	入力文字チェック	*/
/*******************************/
int check(const char s[])
{
	int i, j;
	int len;

	len = strlen(s);
	if (len != 4) {						/*	文字数チェック		*/
		printf("きちんと4文字で入力してください。\n");
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (isdigit(s[i] == 0)) {			/*	文字チェック		*/
			printf("数字以外の文字を入力してください。\n");
			return 0;
		}
	}

	return 1;
}

/********************************/
/*	ヒット/ブロー判定	*/
/********************************/
void judge(const char s[], const int x[], int *hit, int *blow)
{
	int i, j;

	*hit = *blow = 0;
	for (i = 0; i < 4;	i++) {
		for (j = 0; j < 4; j++) {
			if (s[i] == '0' + x[j]) {
				if (i == j) {
					(*hit)++;
					(*blow)++;
					break;
				} else {
					if (i > j) {
						continue;
					}
					(*blow)++;
					break;
				}
			}
		}
	}
}

/************************/
/*	判定結果表示	*/
/************************/
void disp_result(int hit, int blow)
{
	if (hit == 4) {
		printf("正解です。");
	} else if ((hit + blow) == 0) {
		printf("	それらの数字はまったく含まれません。\n");
	} else {
		printf("	それらの数字中%d個の数字が含まれます。\n", blow);
		if (hit == 0) {
			printf("	ただし位置もあっている数字はありません。\n");
		} else {
			printf("	その中の%d個は位置もあっています。\n", hit);
		}
	}
	putchar('\n');
}

int main(void)
{
	int chk;
	int try_no = 0;
	int hit, blow;
	int ans[4];
	char buff[10];						/*	入力文字		*/
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、4個の数字の並びです。");
	puts("　同じ数字が複数含まれることはあります。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。\n");

	make4digits(ans);					/*	4個の数字生成		*/
	start = time(NULL);					/*	開始時刻		*/
	printf("%d%d%d%d", ans[0], ans[1], ans[2], ans[3]);

	do {
		/************************/
		/*	数字の入力	*/
		/************************/
		do {
			printf("入力してください：");
			scanf("%s", buff);
			chk = check(buff);			/*	入力文字チェック	*/
		} while (chk == 0);

		try_no++;
		judge(buff, ans, &hit, &blow);			/*	ヒット/ブロー判定	*/
		disp_result(hit, blow);				/*	判定結果表示		*/
	} while (hit < 4);

	end = time(NULL);					/*	終了時刻		*/

	printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));

	return 0;
}
