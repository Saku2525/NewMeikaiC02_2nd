/************************************************************/
/*	カレンダー表示											*/
/*	コマンドラインから指定された年月間のカレンダーを表示	*/
/************************************************************/

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

	for (i = 1; i < 7; i++) {
		for (j = 0; j < n; j++) {
			printf("%s   ", sbuf[j][i]);
		}
		putchar('\n');
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

int strncmpx(char *s1, char *s2, size_t n)
{
	while (n != 0 && toupper(*s1) != 0 && toupper(*s2) != 0) {
		if (toupper(*s1) != toupper(*s2)) {
			return (unsigned int)*s1 - (unsigned int)*s2;
		}
		s1++;
		s2++;
		n--;
	}

	if (n == 0) {
		return 0;
	}
	if (*s1 != "\0") {
		return 1;
	}

	return -1;
}

int get_month(char *s)
{
	int month, i;
	char *months[] = { "", "January", "February", "March", "April",
					 "May", "June", "July", "August", "September",
					 "October", "November", "December" };

	month = atoi(s);
	if (month >= 1 && month <= 12) {
		return month;
	}

	for (i = 1; i <= 12; i++) {
		if (strncmpx(months[i], s, strlen(months[i])) == 0) {
			return i;
		}
	}

	return -1;
}

int main(int argc, char *argv[])
{
	time_t now = time(NULL);
	struct tm *current = localtime(&now);
	int year1, year2, month1, month2;

	year1 = year2 = current->tm_year + 1900;
	month1 = month2 = current->tm_mon + 1;

	switch (argc) {
	case 2:
		month1 = month2 = get_month(argv[1]);
		break;

	case 3:
		month1 = month2 = get_month(argv[1]);
		year1 = year2 = atoi(argv[2]);
		break;

	case 4:
		month1 = get_month(argv[1]);
		year1 = year2 = atoi(argv[2]);
		month2 = get_month(argv[3]);
		break;

	case 5:
		month1 = get_month(argv[1]);
		year1 = atoi(argv[2]);
		month2 = get_month(argv[3]);
		year2 = atoi(argv[4]);
		break;

	default:
		break;
	}

	if ((year1 < 0 || year2 < 0) || (year2 - year1 < 0)) {
		fprintf(stderr, "年の値が不正です。\n");
		return 1;
	}

	if ((month1 < 0 || month1 > 12) || (month2 < 0 || month2 > 12)
		|| ((year1 == year2) && (month2 - month1 < 0))) {
		fprintf(stderr, "月の値が不正です。\n");
		return 1;
	}

	put_calendar(year1, month1, year2, month2);

	return 0;
}
