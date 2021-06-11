#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
int main(){
    char c;
    char code[63];
    int M;
    for(scanf("%d\n",&M);M>0;M--){
        scanf("%c %s ",&c,code);
        printf("%c %s\n",c,code);
    }
    return 0;
}