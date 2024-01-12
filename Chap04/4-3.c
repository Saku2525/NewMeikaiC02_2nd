/********************************/
/*	マスターマインド	*/
/*	桁数可変(1～10桁)	*/
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/********************************/
/*	相違なる数字生成	*/
/********************************/
void makedigits(int x[], int digits)
{
	int i, j;
	int val;					/*	0～9の乱数		*/

	for (i = 0; i < digits; i++) {
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
int check(const char s[], int digits)
{
	int i, j;
	int len;

	len = strlen(s);
	if (len != digits) {				/*	文字数チェック		*/
		printf("きちんと%d文字で入力してください。\n", digits);
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (isdigit(s[i] == 0)) {		/*	文字チェック		*/
			printf("数字以外の文字を入力してください。\n");
			return 0;
		}
		for (j = 0; j < i; j++) {		/*	重複チェック		*/
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
void judge(const char s[], const int x[], int digits, int *hit, int *blow)
{
	int i, j;

	*hit = *blow = 0;
	for (i = 0; i < digits;	i++) {
		for (j = 0; j < digits; j++) {
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
void disp_result(int hit, int digits, int total)
{
	if (hit == digits) {
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
	int i;
	int digits, chk;
	int try_no = 0;
	int hit, blow;
	int *ans;
	char *buff;					/*	入力文字		*/
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、複数個の数字の並びです。");
	puts("　同じ数字が複数含まれることはありません。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。\n");

	do {
		printf("何桁にしますか：");
		scanf("%d", &digits);
	} while (digits < 1 || digits > 10);
	ans = calloc(digits, sizeof(int));
	buff = malloc((int)(digits * 2.5));
	makedigits(ans, digits);			/*	相違なる数字生成	*/
	start = time(NULL);				/*	開始時刻		*/

	do {
		/************************/
		/*	数字の入力	*/
		/************************/
		do {
			printf("入力してください：");
			scanf("%s", buff);
			chk = check(buff, digits);	/*	入力文字チェック	*/
		} while (chk == 0);

		try_no++;
		judge(buff, ans, digits, &hit, &blow);	/*	ヒット/ブロー判定	*/
		disp_result(hit, digits, (hit + blow));	/*	判定結果表示		*/
	} while (hit < digits);

	end = time(NULL);				/*	終了時刻		*/

	printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));

	free(ans);
	free(buff);

	return 0;
}
