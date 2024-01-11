/********************************/
/*	マスターマインド	*/
/*	入力回数に宣言を設ける	*/
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/********************************/
/*	相違なる4個の数字生成	*/
/********************************/
void make4digits(int x[])
{
	int i, j;
	int val;			/*	0～9の乱数	*/

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

/************************/
/*	入力回数設定	*/
/************************/
int set_inputcount(void)
{
	int count;

	printf("入力可能最大数:");
	scanf("%d", &count);
	putchar('\n');

	return count;
}

/********************************/
/*	入力文字チェック	*/
/********************************/
int check(const char s[])
{
	int i, j;
	int len;

	len = strlen(s);
	if (len != 4) {				/*	文字数チェック		*/
		printf("きちんと4文字で入力してください。\n");
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (isdigit(s[i] == 0)) {	/*	文字チェック		*/
			printf("数字以外の文字を入力してください。\n");
			return 0;
		}
		for (j = 0; j < i; j++) {	/*	重複チェック		*/
			if (s[i] == s[j]) {
				printf("同一の数字を複数入力しないでください。\n");
				return 0;
			}
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
				} else {
					(*blow)++;
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
	} else if (total == 0) {
		printf("	それらの数字はまったく含まれません。\n");
	} else {
		printf("	それらの数字中%d個の数字が含まれます。\n", total);
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
	int i, chk;
	int try_no = 0, count;
	int hit, blow;
	int ans[4];
	char buff[10];				/*	入力文字		*/
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、4個の数字の並びです。");
	puts("　同じ数字が複数含まれることはありません。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。\n");

	make4digits(ans);			/*	相違なる4個の数字生成	*/
	count = set_inputcount();		/*	入力回数設定		*/
	start = time(NULL);			/*	開始時刻		*/

	do {
		/************************/
		/*	数字の入力	*/
		/************************/
		printf("残り入力回数：%d回\n", count--);
		do {
			printf("入力してください：");
			scanf("%s", buff);
			chk = check(buff);	/*	入力文字チェック	*/
		} while (chk == 0);

		try_no++;
		judge(buff, ans, &hit, &blow);	/*	ヒット/ブロー判定	*/
		disp_result(hit, (hit + blow));	/*	判定結果表示		*/
	} while (hit < 4 && count > 0);

	end = time(NULL);			/*	終了時刻		*/

	if (hit == 4) {
		puts("正解です。");
		printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));
	} else {
		printf("正解は、");
		for (i = 0; i < 4; i++) {
			printf("%d", ans[i]);
		}
		puts("です。");
		printf("所要時間は%.1fでした。\n", difftime(end, start));
	}

	return 0;
}
