/************************************/
/*	マスターマインド				*/
/*	8色の色から4色の並びを当てる	*/
/************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

typedef enum {
	White = 0,
	Black,
	Red,
	Blue,
	Yellow,
	Green,
	Orange,
	Brown,
} Color;

/****************************/
/*	相違なる4個の数字生成	*/
/****************************/
void make4digits(int x[])
{
	int i, j;
	int val;									/*	0～9の乱数			*/

	for (i = 0; i < 4; i++) {
		do {
			val = rand() % 8;
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
/*	入力文字チェック	*/
/************************/
int check(int input, int buff[], int num)
{
	int i;
	int color, chk;
	int ret = 1;

	/*	文字チェック	*/
	if (isdigit(input) == 0) {
		if (input == 0x03) {					/*	Ctrl + C			*/
			exit(0);							/*	強制終了			*/
		}
		return 0;
	}

	/*	重複チェック	*/
	for (i = 0; i < num; i++) {
		if (input - '0' == buff[i]) {
			return 0;
		}
	}
	
	switch ((Color)input - '0') {
		case White:		printf("白 ");	break;
		case Black:		printf("黒 ");	break;
		case Red:		printf("赤 ");	break;
		case Blue:		printf("青 ");	break;
		case Yellow:	printf("黄 ");	break;
		case Green:		printf("緑 ");	break;
		case Orange:	printf("橙 ");	break;
		case Brown:		printf("茶 ");	break;
		default:		ret = 0;		break;
	}

	return ret;
}

/************************/
/*	ヒット/ブロー判定	*/
/************************/
void judge(const int buff[], const int x[], int *hit, int *blow)
{
	int i, j;

	*hit = *blow = 0;
	for (i = 0; i < 4;	i++) {
		for (j = 0; j < 4; j++) {
			if (buff[i] == x[j]) {
				if (i == j) {
					(*hit)++;
				} else {
					(*blow)++;
				}
			}
		}
	}
}

/********************/
/*	判定結果表示	*/
/********************/
void disp_result(int hit, int total)
{
	if (hit == 4) {
		printf("正解です。");
	} else if (total == 0) {
		printf("	それらの色はまったく含まれません。\n");
	} else {
		printf("	それらの色中%d個の色が含まれます。\n", total);
		if (hit == 0) {
			printf("	ただし位置もあっている色はありません。\n");
		} else {
			printf("	その中の%d個は位置もあっています。\n", hit);
		}
	}
	putchar('\n');
}

int main(void)
{
	int i, chk;
	int color, try_no = 0;
	int hit, blow;
	int ans[4];
	int buff[4];								/*	入力文字			*/
	time_t start, end;

	srand(time(NULL));

	puts("・マスターマインドをしよう！！");
	puts("　当てるのは、4色の並びです。");
	puts("　同じ色が複数含まれることはありません。");
	puts("　4307のように連続して入力してください。");
	puts("　スペース文字などを入力してはいけません。\n");

	make4digits(ans);							/*	相違なる4色生成		*/
	start = time(NULL);							/*	開始時刻			*/

	do {
		/****************/
		/*	色の入力	*/
		/****************/
		printf("0:白、1:黒、2;赤、3:青、4:黄、5:緑、6:橙、7:茶\n");
		printf("入力してください：");
		for (i = 0; i < 4; i++) {
			do {
				color = getch();
				chk = check(color, buff, i);	/*	入力文字チェック	*/
			} while (chk == 0);
			buff[i] = color - '0';
		}
		putchar('\n');
		try_no++;
		judge(buff, ans, &hit, &blow);			/*	ヒット/ブロー判定	*/
		disp_result(hit, (hit + blow));			/*	判定結果表示		*/
	} while (hit < 4);

	end = time(NULL);							/*	終了時刻			*/

	printf("%d回かかりました。\n所要時間は%.1fでした。\n", try_no, difftime(end, start));

	return 0;
}
