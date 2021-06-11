/*by pcd 😅*/
//jyj? pjy 
//🤡🤡🤡🤡🤡🤡
#include <stdio.h>
#include <string.h>

typedef struct Node
{
    char Address[6];
    int Data;
    char Next[6];
} Node;

int main()
{
    char head_address[6], temp_address[6],EndOfNodes[6]={'-','1'};
    int length, reverse_length;
    scanf("%s %d %d", &head_address, &length, &reverse_length);
    Node Nodes[length], temp;
    for (int i = 0; i < length; i++)
    {
        scanf("%s %d %s", &Nodes[i].Address, &Nodes[i].Data, &Nodes[i].Next);
    }

    //Sort by head_address
    for (int i = 0; i < length - 1; i++)
    {
        if (i == 0)
        {
            while (i < length)
            {
                if (!strcmp(Nodes[i].Address, head_address))
                {
                    temp = Nodes[i];
                    Nodes[i] = Nodes[0];
                    Nodes[0] = temp;
                    i = 0;
                    // printf("HeadNode Has Beend Found!\n");
                    // printf("%s %d %s\n",Nodes[0].Address,Nodes[0].Data,Nodes[0].Next);
                    break;
                }
                else
                    i++;
            }          
        }
        else
        {   
            //check if there's redundant Nodes
            if(!strcmp(Nodes[i-1].Next,EndOfNodes))
            {
                length = i;
                break;
            }

            for (int j = i; j < length; j++)
            {
                // printf("%s %s\n",Nodes[j].Address,Nodes[i - 1].Next);
                if (!strcmp(Nodes[j].Address, Nodes[i - 1].Next))
                {
                    temp = Nodes[i];
                    Nodes[i] = Nodes[j];
                    Nodes[j] = temp;
                    // printf("Node%d Has Beend Found!\n", i);
                    // printf("%s %d %s\n",Nodes[i].Address,Nodes[i].Data,Nodes[i].Next);
                    break;

                }
            }
        }      
    }

    //Reverse
    for (int i = reverse_length-1; i < length; i += reverse_length)
    {
        strcpy(temp_address, Nodes[i].Next);
        for (int j = i; j > i-reverse_length+1; j--)
        {
            strcpy(Nodes[j].Next, Nodes[j - 1].Address);
        }
        strcpy(Nodes[i-reverse_length+1].Next, temp_address);

        //123456-->321654 需要将6的Address赋值给1的next 由于此时尚未排序(排序在最后)
        //1仍在原位 第1位
        //因此需要减去 2*reverse_ength
        if(i-reverse_length+1 > 0){
            strcpy(Nodes[i-reverse_length*2+1].Next,Nodes[i].Address);
        }

        if (i == reverse_length-1)
            strcpy(head_address, Nodes[i].Address);
    }

    //Sort by head_address
    for (int i = 0; i < length - 1; i++)
    {
        if (i == 0)
        {
            while (i < length)
            {
                if (!strcmp(Nodes[i].Address, head_address))
                {
                    temp = Nodes[i];
                    Nodes[i] = Nodes[0];
                    Nodes[0] = temp;

                    //mistake: forget to set i back to 0
                    i = 0;
                    // printf("HeadNode Has Beend Found!\n");
                    // printf("%s %d %s\n",Nodes[0].Address,Nodes[0].Data,Nodes[0].Next);
                    break;
                }
                else{
                    i++;
                }
                    
            }
        }
        else
        {
            for (int j = i; j < length; j++)
            {   
                // printf("j is %d,Nodes[j].address is %s,Nodes[i - 1].Next is %s \n",j,Nodes[j].Address, Nodes[i - 1].Next);
                if (!strcmp(Nodes[j].Address, Nodes[i - 1].Next))
                {
                    temp = Nodes[i];
                    Nodes[i] = Nodes[j];
                    Nodes[j] = temp;
                    // printf("Node%d Has Beend Found!\n", i);
                    // printf("%s %d %s\n",Nodes[i].Address,Nodes[i].Data,Nodes[i].Next);
                    break;
                }
            }
        }

    }

    
    // puts("\n");
    for(int i = 0;i<length;i++)
        printf("%s %d %s\n",Nodes[i].Address,Nodes[i].Data,Nodes[i].Next);

 

}