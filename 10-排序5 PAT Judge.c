/*
compiler:Clang
if gcc:unknown reason error 
gcc=shit!
^^^^
||||
totally idiot words
gcc error reason: sort too slow
test point3: Minimum M, Big N, hence many "fw" need to be sorted
*/
#include <stdio.h>

typedef struct user
{   
    /*
    -2: not submitted
    -1: submitted, cannot pass compiler
     0: submitted, pass compiler, cannot pass test points
    */
    int s[6];
    int total_score;
    int fullscores;
    int id;
    /*
    fw: flag for those have never submitted any solution that can pass the compiler, 
    or has never submitted any solution
    */
    int fw;
} users;

users u[10001];
int FullScore[6];

int main()
{
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);

    //initialize
    for (int i = 1; i <= N; i++)
    {
        for(int j = 1;j<=K;j++)
            u[i].s[j] = -2;
        u[i].total_score = 0;
        u[i].fullscores = 0;
        u[i].id = i;
        u[i].fw = 1;
    }

    //get fullscores
    for (int i = 1; i <= K; i++)
    {
        scanf("%d", &FullScore[i]);
    }

    //get s[]
    for (int i = 1; i <= M; i++)
    {
        int user, number, score;
        scanf("%d %d %d", &user, &number, &score);
        if (u[user].s[number] < score)
            u[user].s[number] = score;
    }

    //count total_score
    for (int i = 1; i <= N; i++)
    {
        int sum = 0;
        for (int j = 1; j <= K; j++)
            if (u[i].s[j] >= 0)//if submitted and pass the compiler 
            {   
                //flag: no longer a fw!
                u[i].fw = 0;
                sum += u[i].s[j];

                //count the fullscores
                if (u[i].s[j] == FullScore[j])
                    u[i].fullscores++;
            }

        u[i].total_score = sum;
    }

    // //test intialize conditions
    // for (int i = 0; i < N; i++)
    // {
    //     printf("%05d %d", u[i].id, u[i].total_score);
    //     for (int j = 1; j <= K; j++)
    //     {
    //         printf(" %d", u[i].s[j]);
    //     }
    //     putchar('\n');
    // }

    //sort and ouput
    int max = -1;
    int max_last = -1;
    int max_idx = 0;
    int samerank = 1;
    int rank = 0;

    for (int i = 1; i <= N; i++)
    {
        //find a max
        for (int j = i; j <= N; j++)
        {
            if (u[j].total_score > max
            ||(u[j].total_score == max&&u[j].fullscores > u[max_idx].fullscores)
            ||(u[j].total_score == max&&u[j].fullscores == u[max_idx].fullscores&&u[j].id < u[max_idx].id)
            //the 'break condition' below is if the chosen one is fw then quit
            //this if is to ensure those 0 score non-fw will be chosen earlier 
            ||(u[j].total_score == max&&max==0&&!u[j].fw))
            {
                max = u[j].total_score;
                max_idx = j;
            }
        }

        //output
        if (!u[max_idx].fw)
        {   
            if (max == max_last)
            {
             samerank++;
            }
            else
            {
                rank += samerank;
             samerank = 1;
                max_last = max;
            }
            printf("%d %05d %d", rank, u[max_idx].id, u[max_idx].total_score);
            for (int i = 1; i <= K; i++)
            {   
                //never submitted, output should be '-'
                if (u[max_idx].s[i] == -2)
                    printf(" -");
                //once submitted,even cannot pass the compiler
                //the score should be '0'
                else if(u[max_idx].s[i] == -1)
                    printf(" 0");
                else
                    printf(" %d", u[max_idx].s[i]);
            }

            putchar('\n');
        }

        // with this break gcc can pass for the sort algs() are way too slow
        // but need to change the 'max condition' above
        // dont change can also pass => test points are incomplete
        else{
            break;
        }

        //swap the max to the front
        users tmp;
        tmp = u[max_idx];
        u[max_idx] = u[i];
        u[i] = tmp;
        
        max = -1;

    }

    return 0;
}