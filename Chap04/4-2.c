/********************************/
/*	マスターマインド	*/
/*	ヒント機能追加		*/
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
	int val;				/*	0～9の乱数	*/

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
	if (len != 4) {				/*	文字数チェック	*/
		printf("きちんと4文字で入力してください。\n");
		return 0;
	}

	for (i = 0; i < len; i++) {
		if (isdigit(s[i] == 0)) {	/*	文字チェック	*/
			printf("数字以外の文字を入力してください。\n");
			return 0;
		}
		for (j = 0; j < i; j++) {	/*	重複チェック	*/
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
void judge(const char s[], const int x[], int *hit, int hitNum[], int *blow, int blowNum[])
{
	int i, j;

	*hit = *blow = 0;
	for (i = 0; i < 4;	i++) {
		for (j = 0; j < 4; j++) {
			if (s[i] == '0' + x[j]) {
				if (i == j) {
					hitNum[i] = 1;
					(*hit)++;
				} else {
					blowNum[j] = 1;
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

/************************/
/*	ヒント表示	*/
/************************/
void disp_hint(const int x[], const int hitNum[], const int blowNum[], int num)
{
	int disp, no, i;
	int hint;
	char *s[] = { "　(0):正解の先頭の1文字目", "　(1)位置があっている数字の中で先頭側の1文字目"
							, "　(2)含まれている数字の中で末尾側の1文字目" };

	printf("ヒントを表示しますか?（はい：0, いいえ：1）:");
	scanf("%d", &disp);

	if (disp == 0) {
		for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
			printf("%s\n", s[i]);
		}
		printf("どのヒントを表示しますか？：");
		scanf("%d", &no);

		switch (no) {
			case 0:			/*	先頭の1文字を教える				*/
				printf("1個目の数字は\"%d\"です。\n", x[0]);
				break;

			case 1:			/*	ヒットした数字の中で先頭側の1文字を教える	*/
				for (i = 0; i < num; i++) {
					if (hitNum[i] == 1) {
						printf("位置があっている数字の中の先頭の数字は、\"%d\"です。\n", x[i]);
						return;
					}
				}
				puts("位置があっている数字はありません。");
				break;

			case 2:			/*	ブローした数字の中で末尾側の1文字を教える	*/
				for (i = num; i > 0; i--) {
					printf("%d\n", i);
					if (blowNum[i - 1] == 1) {
						printf("含まれている数字の中の末尾の数字は、\"%d\"です。\n", x[i - 1]);
						return;
					}
				}
				puts("含まれている数字はありません。");
				break;
				
			default:
				break;
		}
	}
}

int main(void)
{
	int i, chk;
	int try_no = 0;
	int hit, blow;
	int ans[4];
	char buff[10];						/*	入力文字		*/
	int hitNum[4], blowNum[4];
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、4個の数字の並びです。");
	puts("　同じ数字が複数含まれることはありません。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。\n");

	make4digits(ans);					/*	相違なる4個の数字生成	*/
	start = time(NULL);					/*	開始時刻		*/

	do {
		/************************/
		/*	数字の入力	*/
		/************************/
		do {
			printf("入力してください：");
			scanf("%s", buff);
			chk = check(buff);			/*	入力文字チェック	*/
		} while (chk == 0);

		for (i = 0; i < 4; i++) {
			hitNum[i] = blowNum[i] = 0;
		}
		try_no++;
		judge(buff, ans, &hit, hitNum, &blow, blowNum);	/*	ヒット/ブロー判定	*/
		disp_result(hit, (hit + blow));			/*	判定結果表示		*/
		if (hit != 4) {
			disp_hint(ans, hitNum, blowNum, sizeof(ans) / sizeof(ans[0]));
		}
	} while (hit < 4);

	end = time(NULL);					/*	終了時刻		*/

	printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));

	return 0;
}
