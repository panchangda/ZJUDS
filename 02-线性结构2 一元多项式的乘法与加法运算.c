#include<stdio.h>
#include<string.h>

int main(){

    //input process 
    //p[i];p[i+1] - > ratio;index (i is even)
    int N1,N2;
    scanf("%d",&N1);
    int p1[N1*2];
    for(int i=0;i<N1;i++){
        scanf("%d",p1+2*i);
        scanf("%d",p1+2*i+1);
    }
    scanf("%d",&N2);
    int p2[N2*2];
    for(int i=0;i<N2;i++){
        scanf("%d",p2+2*i);
        scanf("%d",p2+2*i+1);
    }
    
    //***
    int result[10000];
    //memset(result,0,(sizeof(int)*length))
    memset(result,0,sizeof(result));
    int ratio,index,first;
    first = 1;
    ratio = index = 0;
    for(int i=0;i<N1;i++){
        for(int j=0;j<N2;j++){
            ratio = p1[i*2]*p2[j*2];
            index = p1[i*2+1]+p2[j*2+1];
            if(!result[index]){
                result[index] = ratio;
            }
            else{
                result[index]+=ratio;
            }
        }
    }
    for(int i=10000-1;i>=0;i--){
        if(result[i])
            if(!first)
                printf(" %d %d",result[i],i);
            else{
                first=0;
                printf("%d %d",result[i],i);
            }           
    }

    //若之前无输出则输出零多项式 0 0
    if(first){
        printf("0 0");
    }

    putchar('\n');

    //+++
    int i1,i2;
    i1=i2=0;
    first = 1;
    while(i1<N1&&i2<N2){
        if(p1[i1*2+1]!=p2[i2*2+1]){
            first = 0;
            if(i1||i2){
                putchar(' ');
            }
            if(p1[i1*2+1]>p2[i2*2+1]){
                printf("%d %d",p1[i1*2],p1[i1*2+1]);
                i1++;
            }
            else{
                printf("%d %d",p2[i2*2],p2[i2*2+1]);
                i2++;
            }
        }
        else{
            //同类合并项时若系数为0则不输出
            if(p1[i1*2]+p2[i2*2]){
                first = 0;
                if(i1||i2){
                    putchar(' ');
                }
                printf("%d %d",p1[i1*2]+p2[i2*2],p1[i1*2+1]);
            }
            i1++;
            i2++;
        }
    }
    while(i1<N1){
        first = 0;
        if(i1||i2)
            putchar(' ');
        printf("%d %d",p1[i1*2],p1[i1*2+1]);
        i1++;
    }
    while(i2<N2){
        first = 0;
        if(i1||i2)
            putchar(' ');
        printf("%d %d",p2[i2*2],p2[i2*2+1]);
        i2++;
    }

    //若之前无输出则输出零多项式 0 0
    if(first)
        printf("0 0");

    return 0;
}