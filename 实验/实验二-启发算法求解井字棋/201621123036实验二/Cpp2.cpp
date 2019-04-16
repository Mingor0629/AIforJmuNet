#include<stdio.h>
#include<windows.h>
typedef struct position {
    int x;
    int y;
}POS;   //����ṹ��
#define N 3
#define STEP 9
#define COMPUTER 1
#define MANAGER -1
#define INT_MAX 4096 
int CurrentDepth;
int player;
int chess[N][N];
int TempChess[N][N];    //�����chess
int isEnd();
int Evaluate();
int CountBlank(POS SaveBlank[STEP]);
int MaxMinSearch(int depth);
void SetChess(POS MarkPos);
void RemoveChess(POS MarkPos);
void InitBoard();   //��ʼ���߽�
void WhoPlayFirst();
void ManPlay();
void ComPlay();
void DrawBoard();
POS BestPosMark;
int main()
{
    int step = 0;
    CurrentDepth = STEP-1;
    InitBoard();
    WhoPlayFirst();
    if (player == MANAGER)
    {
        for (step = 1;step <= STEP;)
        {
            ManPlay();
            DrawBoard();
            if (isEnd()==MANAGER)
            {
                printf("\n����1սʤ����2��\n");
                system("pause");
                return 0;
            }
            step++;
            CurrentDepth--;
            if (CurrentDepth == 0)
            {
                printf("\nƽ���ˣ�\n");
                system("pause");
                return 0;
            }
            player = (player == COMPUTER) ? MANAGER : COMPUTER;
            ComPlay();
            DrawBoard();
            if(isEnd()==COMPUTER)
            {
                printf("\n����2սʤ�˵���1��\n");
                system("pause");
                return 0;
            }
            step++;
            CurrentDepth--;
            if (CurrentDepth == 0)
            {
                printf("\nƽ���ˣ�\n");
                system("pause");
                return 0;
            }
            player = (player == COMPUTER) ? MANAGER : COMPUTER;
        }
    }
    if (player == COMPUTER)
    {
        for (step = 1;step <= STEP;)
        {
            ComPlay();
            DrawBoard();
            if (isEnd()==COMPUTER)
            {
                printf("\n����2սʤ�˵���1��\n");
                system("pause");
                return 0;
            }
            step++;
            CurrentDepth--;
            if (CurrentDepth == 0)
            {
                printf("\nƽ���ˣ�\n");
                system("pause");
                return 0;
            }
            player = (player == COMPUTER) ? MANAGER : COMPUTER;
            ManPlay();
            DrawBoard();
            if(isEnd()==MANAGER)
            {
                printf("\n����1սʤ����2��\n");
                system("pause");
                return 0;
            }
            step++;
            CurrentDepth--;
            if (CurrentDepth == 0)
            {
                printf("\nƽ���ˣ�\n");
                return 0;
            }
            player = (player == COMPUTER) ? MANAGER : COMPUTER;
        }
    }
    return 0;
}
void DrawBoard()
{
    int i, j;
    for (i = 0;i < N;i++)
    {
        printf("-------------\n");
        for (j = 0;j < N;j++)
        {
            if (chess[i][j] == COMPUTER)
                printf("| X ");
            else if (chess[i][j] == MANAGER)
                printf("| O ");
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printf("-------------\n");
}
int isEnd()
{
    int i, j;
    int count = 0;
    for (i = 0;i < N;i++)   //��
    {
        count = 0;
        for (j = 0;j < N;j++)
            count += chess[i][j];
        if (count == 3 || count == -3)
            return count / 3;
    }
    for (j = 0;j < N;j++)   //��
    {
        count = 0;
        for (i = 0;i < N;i++)
            count += chess[i][j];
        if (count == 3 || count == -3)
            return count / 3;
    }
    count = 0;
    count = chess[0][0] + chess[1][1] + chess[2][2];
    if (count == 3 || count == -3)
        return count / 3;
    count = chess[0][2] + chess[1][1] + chess[2][0];
    if (count == 3 || count == -3)
        return count / 3;
    return 0;
}
int CountBlank(POS SaveBlank[STEP])
{
    int i, j;
    int count = 0;
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
        {
            if (chess[i][j] == 0)   //��δ��ռ
            {
                SaveBlank[count].x = i;
                SaveBlank[count].y = j;
                count++;
            }
        }
    }
    return count;
}
int Evaluate()
{
    int flag = 1;
    int i, j;
    int count = 0;
    if (isEnd() == COMPUTER)    //���Լ�����������Ϊ���޴�
        return INT_MAX;
    if (isEnd() == MANAGER)     //���Լ�����������Ϊ���޴�
        return -INT_MAX;
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
        {
            if (chess[i][j] == 0)
                TempChess[i][j] = COMPUTER; //��ʣ��ĵط�ȫ���ϵ�������
            else
                TempChess[i][j] = chess[i][j];
        }
    }
    //����Ϊ����,��¼���������Ӻ������������ӵ�������Խ�������λ��Խ��Ҫ
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            count += chess[i][j];
        count /= 3;
    }
    for (j = 0;j < N;j++)
    {
        for (i = 0;i < N;i++)
            count += chess[i][j];
        count /= 3;
    }
    count += (TempChess[0][0] + TempChess[1][1] + TempChess[2][2]) / 3;
    count += (TempChess[0][2] + TempChess[1][1] + TempChess[2][0]) / 3;

    //����Ϊ���
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
        {
            if (chess[i][j] == 0)
                TempChess[i][j] = MANAGER;  //��ʣ��ĵط�ȫ���ϵ�������
            else
                TempChess[i][j] = chess[i][j];
        }
    }
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            count += chess[i][j];
        count /= 3;
    }
    for (j = 0;j < N;j++)
    {
        for (i = 0;i < N;i++)
            count += chess[i][j];
        count /= 3;
    }
    count += (TempChess[0][0] + TempChess[1][1] + TempChess[2][2]) / 3;
    count += (TempChess[0][2] + TempChess[1][1] + TempChess[2][0]) / 3;

    return count;   //count�Ǹ��ݶԵ��Ե����ƺͶ���ҵ���������ۺ������
}
void RemoveChess(POS MarkPos)
{
    chess[MarkPos.x][MarkPos.y] = 0;
    player = (player == COMPUTER) ? MANAGER : COMPUTER;
}
void SetChess(POS MarkPos)
{
    chess[MarkPos.x][MarkPos.y] = player;
    player = (player == COMPUTER) ? MANAGER : COMPUTER;
}
int MaxMinSearch(int depth)
{
    int BestValue = 0;
    int Value = 0;
    int i, count = 0;
    POS SaveBlank[STEP];
    if (COMPUTER == isEnd() || MANAGER == isEnd())
        return Evaluate();
    if (depth == 0)
        return Evaluate();
    if (player == COMPUTER)
        BestValue = -INT_MAX;
    if (player == MANAGER)
        BestValue = INT_MAX;
    count = CountBlank(SaveBlank);
    for (i = 0;i < count;i++)
    {
        POS MarkPos = SaveBlank[i];
        SetChess(MarkPos);
        Value = MaxMinSearch(depth - 1);
        RemoveChess(MarkPos);
        if (player == MANAGER)
        {
            if (Value < BestValue)
            {
                BestValue = Value;
                if (depth == CurrentDepth)
                {
                    BestPosMark = MarkPos;
                }
            }
        }
        else if (player == COMPUTER)
        {
            if (Value > BestValue)
            {
                BestValue = Value;
                if (depth == CurrentDepth)
                {
                    BestPosMark = MarkPos;
                }
            }
        }
    }
    return BestValue;
}
void ComPlay()
{
    MaxMinSearch(CurrentDepth);
    printf("\n����2���ӵ�λ��Ϊ��(%d,%d)\n", BestPosMark.x + 1, BestPosMark.y + 1);
    chess[BestPosMark.x][BestPosMark.y] = COMPUTER;
}
void ManPlay()
{
	MaxMinSearch(CurrentDepth);
    printf("\n����1���ӵ�λ��Ϊ��(%d,%d)\n", BestPosMark.x + 1, BestPosMark.y + 1);
    chess[BestPosMark.x][BestPosMark.y] = MANAGER;
}
void InitBoard()
{
    int i, j;
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            TempChess[i][j] = chess[i][j] = 0;
}
void WhoPlayFirst()
{
    char ch;
    printf("��ӭ����AI�����壬��ѡ����������Ⱥ�1---����1���� 2---����2����\n");
    ch = getchar();
    player = (ch == '1') ? MANAGER : COMPUTER;
}