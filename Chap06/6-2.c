/****************************************************/
/*	カレンダー表示									*/
/*	開始年月と終了年月の整合性のチェック処理追加	*/
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
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
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;	/*	ツェラーの公式	*/
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

/*---スペース文字数出力---*/
int put_space(int def, int count, int max)
{
	return (count != max) ? def : 0;
}

/*---カレンダー表示---*/
void print(char sbuf[3][7][22], int n)
{
	int i, j;
	int def = 2;
	int space;

	for (i = 0; i < n; i++) {
		space = put_space(def, i, n - 1);
		printf("%s%*s", sbuf[i][0], space, "");
	}
	putchar('\n');

	for (i = 0; i < n; i++) {
		space = put_space(def, i, n - 1);
		printf(" 日 月 火 水 木 金 土%*s", space, "");
	}
	putchar('\n');

	for (i = 0; i < n; i++) {
		space = put_space(def, i, n - 1);
		printf("---------------------%.*s", space, "---");
	}
	putchar('\n');

	for (i = 1; i < 7; i++) {
		for (j = 0; j < n; j++) {
			space = put_space(def, j, n - 1);
			printf("%s%*s", sbuf[j][i], space, "");
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

/*---月の値の整合性チェック---*/
int check_month(int month)
{
	if (month < 1 || month > 12) {
		printf("月に1～12以外の値が入力されました。\n");
		return 0;
	}

	return 1;
}

/*---開始年月と終了年月の整合性チェック---*/
int check_yearmonth(int year1, int month1, int year2, int month2)
{
	/*	開始年と終了年の整合性チェック	*/
	if (year1 > year2) {
		printf("終了年が開始年より前の年になっています。\n");
		return 0;
	}

	/*	開始月と終了月の整合性チェック	*/
	if (month1 > month2) {
		printf("終了月が開始月より前の月になっています。\n");
		return 0;
	}

	return 1;
}

/*---開始年月と終了年月の入力---*/
void input_yearmonth(int *year1, int *month1, int *year2, int *month2)
{
	for ( ; ; ) {
		printf("カレンダーを表示します。\n");
		printf("開始年：");		scanf("%d", year1);
		printf("　　月：");		scanf("%d", month1);
		printf("終了年：");		scanf("%d", year2);
		printf("　　月：");		scanf("%d", month2);

		if ((check_month(*month1) == 0) || (check_month(*month2) == 0)) {
			continue;
		}
		if (check_yearmonth(*year1, *month1, *year2, *month2) == 0) {
			continue;
		} else {
			break;
		}
	}

}

int main(void)
{
	int year1, year2, month1, month2;

	input_yearmonth(&year1, &month1, &year2, &month2);
	put_calendar(year1, month1, year2, month2);

	return 0;
}
