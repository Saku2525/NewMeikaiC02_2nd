/********************/
/*	日付当てゲーム	*/
/********************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//--- 各月の日数 ---//
int mday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//--- year年month月day日の曜日を求める ---//
int dayofweek(int year, int month, int day)
{
	if (month == 1 || month == 2) {
		year--;
		month += 12;
	}
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;
}

/*---閏年か判断---*/
int is_leap(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0;
}

/*---year年month月の日数---*/
int monthdays(int year, int month)
{
	if (month-- != 2) {
		return mday[month];
	}

	return mday[month] + is_leap(year);
}

int get_month(char *s)
{
	int month, i;

	month = atoi(s);
	if (month >= 1 && month <= 12) {
		return month;
	}

	return -1;
}

int main(void)
{
	time_t now = time(NULL);
	struct tm *current = localtime(&now);
	int year, month, day;
	char ans[9];
	int num, stage = 0, maxstage = 0;
	char buf[64];
	char work[5];
	char **hist;
	int judge, i;

	srand(now);
	printf("1900年1月1日～%d年%d月%d日の日付を当てよう!\n\n"
		, current->tm_year + 1900
		, current->tm_mon + 1
		, current->tm_mday);
	year = (rand() % current->tm_year) + 1900;
	month = (rand() % 12) + 1;
	day = (rand() % monthdays(year, month)) + 1;
	sprintf(ans, "%04d%02d%02d", year, month, day);
	num = current->tm_year;
	do {
		num /= 2;
		maxstage++;
	} while (num != 0);
	maxstage += 4 + 5;
	if ((hist = (char **)malloc(sizeof(char *) * maxstage)) == NULL) {
		printf("メモリ確保失敗\n");
		return 1;
	}
	for (i = 0; i < maxstage; i++) {
		if ((hist[i] = (char *)malloc(sizeof(char) * 9)) == NULL) {
			printf("メモリ確保失敗\n");
			return 1;
		}
	}

		do {
			printf("残り%d回。いつかな(YYYYMMDD)：", maxstage - stage);
				scanf("%s", buf);
				if (strlen(buf) != 8) {
					printf("入力ミスです。\n");
					continue;
				}

				/* 年チェック */
				work[0] = buf[0];
				work[1] = buf[1];
				work[2] = buf[2];
				work[3] = buf[3];
			work[4] = '\0';
			num = atoi(work);
			if ((num < 1900) || (num > current->tm_year + 1900)) {
				printf("年の値が不正です。\n");
				continue;
			}

			/* 月チェック */
			work[0] = buf[4];
			work[1] = buf[5];
			work[2] = '\0';
			if (get_month(work) == -1) {
				printf("月の値が不正です。\n");
				continue;
			}

			strcpy(hist[stage++], buf);
			judge = strcmp(buf, ans);
			if (judge > 0)	printf("もっと小さいよ。\a\n");
			if (judge < 0)	printf("もっと大きいよ。\a\n");
		} while ((strcmp(buf, ans) != 0) && (stage < maxstage));

		if (strcmp(buf, ans) != 0) {
			printf("残念。正解は、\"%4.4s年%2.2s月%2.2s日\"でした。\n", year, month, day);
		}
		else {
			printf("正解です。\n");
			printf("%d回で当たりましたね。\n", stage);
		}

		puts("\n---入力履歴---");
		for (i = 0; i < stage; i++) {
			printf(" %2d : %4.4s年%2.2s月%2.2s日\n", i, &hist[i][0], &hist[i][4], &hist[i][6]);
		}

		for (i = 0; i < maxstage; i++) {
			free(hist[i]);
		}
		free(hist);

		return 0;
}
