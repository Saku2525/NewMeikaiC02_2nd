/************************************************************************************************/
/*	おみくじ							                        */
/*	0～6の乱数を生成し、その値に応じて、[大吉][中吉][小吉][吉][末吉][凶][大凶]を表示すること  */
/************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	ONO	7	/*	おみくじ結果数	*/

int main(void)
{
	int omikuji;

	srand(time(NULL));
	omikuji = rand() % ONO;

	switch (omikuji) {
		case 0:	puts("大吉");	break;
		case 1:	puts("中吉");	break;
		case 2:	puts("小吉");	break;
		case 3:	puts("吉");	break;
		case 4:	puts("末吉");	break;
		case 5:	puts("凶");	break;
		case 6:	puts("大凶");	break;
		default:		break;
	}

	return 0;
}
