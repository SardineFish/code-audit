// https://github.com/re0560/BuBu/blob/master/%E5%A0%B1%E5%91%8A/main.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int number[10] = {};
	int a;
    int i = 0, j = 0;
    int temp = 0;
    srand(time(NULL));
    for(i=0; i<10; i++){
    	a = rand()%100+1;
    	number[i] = a ;
    	printf("���ƧǡG%d " ,number[i]);
	}
    for( i = 0; i < 10; i++) {
        for( j = i; j < 10; j++) {
            if( number[j] < number[i] ) {
                temp = number[j];
                number[j] = number[i];
                number[i] = temp;
            }
        }
    }
	printf("\n");
    for( i = 0; i < 10; i++ ) {
        printf("�ƧǡG%d " ,number[i]);
    }
	
	return 0;
}
