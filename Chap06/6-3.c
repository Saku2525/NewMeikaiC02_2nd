/********************************************************/
/*	カレンダー表示					*/
/*	表示時、横に並んだ3ヵ月の最大の週に合わせる	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	TRUE	1
#define FALSE	0

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

/*---y年m月のカレンダーを配列に格納---*/
void make_calendar(int year, int month, char s[7][22])
{
	int i, no = 0;
	int wd = dayofweek(year, month, 1);
	int days = monthdays(year, month);
	char day[4];

	/*	バッファクリア	*/
	for (i = 0; i < 7; i++) {
		s[i][0] = '\0';
	}
	sprintf(s[no], "%10d / %02d      ", year, month);
	no = 1;
	sprintf(s[no], "%*s", wd * 3, "");

	for (i = 1; i <= days; i++) {
		sprintf(day, "%3d", i);
		strcat(s[no], day);
		if (++wd % 7 == 0) {
			no++;
		}
	}

	if (wd % 7 == 0) {
		no--;
	}
	else {
		for (i = wd % 7; i < 7; i++) {
			strcat(s[no], "   ");
		}
	}

	while (++no < 7) {
		sprintf(s[no], "%21s", "");
	}
}

/*---カレンダー表示---*/
void print(char sbuf[3][7][22], int n)
{
	int i, j;
	char s[22];
	int skipFlag = FALSE;

	for (i = 0; i < n; i++) {
		printf("%s   ", sbuf[i][0]);
	}
	putchar('\n');

	for (i = 0; i < n; i++) {
		printf(" 日 月 火 水 木 金 土   ");
	}
	putchar('\n');

	for (i = 0; i < n; i++) {
		printf("------------------------");
	}
	putchar('\n');

	s[0] = '\0';
	sprintf(s, "%21s", "");
	for (i = 1; i < 7; i++) {
		for (j = 0; j < n; j++) {
			if (strcmp(sbuf[j][i], s) == 0) {
				skipFlag = TRUE;
			} else {
				skipFlag = FALSE;
			}
			if (skipFlag == FALSE)	break;
		}
		if (skipFlag == FALSE) {
			for (j = 0; j < n; j++) {
				printf("%s   ", sbuf[j][i]);
			}
			putchar('\n');
		}
	}
	putchar('\n');
}

void put_calendar(int year1, int month1, int year2, int month2)
{
	int year = year1;
	int month = month1;
	int no = 0;
	char s_buf[3][7][22];

	while (year <= year2) {
		if ((year == year2) && (month > month2)) {
			break;
		}
		make_calendar(year, month, s_buf[no++]);
		if (no == 3) {
			print(s_buf, no);
			no = 0;
		}
		month++;
		if (month == 13) {
			year++;
			month = 1;
		}
	}
	if (no != 3) {
		print(s_buf, no);
	}
}

int main(void)
{
	int year1, year2, month1, month2;

	printf("カレンダーを表示します。\n");
	printf("開始年：");		scanf("%d", &year1);
	printf("　　月：");		scanf("%d", &month1);
	printf("終了年：");		scanf("%d", &year2);
	printf("　　月：");		scanf("%d", &month2);

	put_calendar(year1, month1, year2, month2);

	return 0;
}
