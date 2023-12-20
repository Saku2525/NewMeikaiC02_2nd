/********************************************************/
/*	おみくじ					*/
/*	出る運勢が均等にならないように改良する	      	*/
/*	[末吉][凶][大凶]を出にくくする			*/
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	ONO	7	       /*	おみくじ結果数		 	*/
#define	DNO	4	       /*	表示しやくするおみくじ結果数	*/
				/*	[大吉][中吉][小吉][吉]		*/

int main(void)
{
	int omikuji;

	srand(time(NULL));
	omikuji = rand() % ONO;

	if (omikuji >= DNO) {
		omikuji = rand() % ONO;
	}

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
