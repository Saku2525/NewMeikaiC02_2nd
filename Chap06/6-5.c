/********************************************************/
/*	カレンダー表示										*/
/*	綴りの一致/不一致判定を3文字以降の綴りも判定する	*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//--- 各月の日数 ---//
int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//--- year年month月day日の曜日を求める ---//
int dayofweek(int year, int month, int day)
{
	if (month == 1 || month == 2) {
		year--;
		month += 12;
	}
	return (year + year/4 - year/100 + year/400 + (13*month+8)/5 + day) % 7;
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

void put_calendar(int year, int month)
{
	int wd = dayofweek(year, month, 1);
	int days = monthdays(year, month);
	int i;

	printf(" 日 月 火 水 木 金 土\n");
	printf("---------------------\n");

	printf("%*s", wd * 3, " ");

	for (i = 1; i <= days; i++) {
		printf("%3d", i);
		if (++wd % 7 == 0) {
			putchar('\n');
		}
	}
	if (wd % 7 != 0) {
		putchar('\n');
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
	char *months[] = {"", "January", "February", "March", "April",
					 "May", "June", "July", "August", "September",
					 "October", "November", "December"};

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
	int year, month;

	year = current->tm_year + 1900;
	month = current->tm_mon + 1;

	if (argc >= 2) {
		month = get_month(argv[1]);
		if (month < 0 || month > 12) {
			fprintf(stderr, "月の値が不正です。\n");
			return 1;
		}
	}
	if (argc >= 3) {
		year = atoi(argv[2]);
		if (year < 0) {
			fprintf(stderr, "年の値が不正です。\n");
		}
	}

	printf("%d年%d月\n\n", year, month);

	put_calendar(year, month);

	return 0;
}
