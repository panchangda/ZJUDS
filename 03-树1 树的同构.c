/*
树的同构 in 树(上)
*/

#include<stdio.h>

int main(){
    int n;
    scanf("%d ",&n);
    char t1[n+1],t2[n+1];
    char c1[2*n+1],c2[2*n+1];
    for(int i=0;i<n;i++){
        scanf("%c %c %c\n",&t1[i],&c1[2*i],&c1[2*i+1]);
    }
    scanf("%d ",&n);
    for(int i=0;i<n;i++){
        scanf("%c %c %c\n",&t2[i],&c2[2*i],&c2[2*i+1]);
    }
    // printf("Accept finished!\n");
    // for(int i=0;i<n;i++){
    //     printf("%c %c %c\n",t1[i],c1[2*i],c1[2*i+1]);
    // }
    // puts("\n");
    // for(int i=0;i<n;i++){
    //     printf("%c %c %c\n",t2[i],c2[2*i],c2[2*i+1]);
    // }
    // puts("\n");
    //transcribe number to letter
    for(int i=0;i<n;i++){
        if(c1[2*i]!='-'){
            c1[2*i]=t1[(c1[2*i])-'0'];
        }
        if(c1[2*i+1]!='-'){
            c1[2*i+1]=t1[c1[2*i+1]-'0'];
        }
        if(c2[2*i]!='-'){
            c2[2*i]=t2[c2[2*i]-'0'];
        }
        if(c2[2*i+1]!='-'){
            c2[2*i+1]=t2[c2[2*i+1]-'0'];
        }
    }
    // printf("Transcribe finished!\n");
    // for(int i=0;i<n;i++){
    //     printf("%c %c %c\n",t1[i],c1[2*i],c1[2*i+1]);
    // }
    // puts("\n");
    // for(int i=0;i<n;i++){
    //     printf("%c %c %c\n",t2[i],c2[2*i],c2[2*i+1]);
    // }
    // puts("\n");
    //1 = true, 0 = false
    int Isomorphism = 1;
    for(int i=0;i<n;i++){
        if(Isomorphism);
        else break;
        for(int j=0;j<n;j++){
            if(t2[j]==t1[i]){
                if((c2[2*j]==c1[2*i] && c2[2*j+1]==c1[2*i+1])
                || (c2[2*j]==c1[2*i+1] && c2[2*j+1]==c1[2*i]));
                else
                    Isomorphism=0;
                break;  
            }
            //didnt have same node
            if(j==n-1)
                Isomorphism=0;
        }
    }

    puts(Isomorphism?"Yes":"No");

    return 0;
}
