#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 1000  /*�������ֵΪ1000*/
#define MIN -1000  /*������СֵΪ-1000*/
#define NONE 0     /* �������������������ΪNONE*/
#define DRAW 1     /* �綨��ƽ��DRAW Ϊ1*/
#define C_WIN 2    /*����ӮΪ2*/
#define M_WIN 3    /*��ӮΪ3*/
#define QUIT 4     /*����Ϊ4*/
#define MAN -1     /*����-1��ʾ*/
#define COM 1      /*������1��ʾ*/
#define TRUE 1

/*����b[10]�����洢���̣�board��,step��ʾ�����µĲ�����
r��ʾ�������ʼֵΪNONE��w��ʾ����Ӯ��λ��*/
int b[10]={0},step=9,r=NONE,w=0;

/*checkWin���������ж�ʤ���������ʤ��������ʤ�������򷵻�NONE*/
int checkWin(int t[], int p){
	if(t[1]==p && t[1]==t[2] && t[2]==t[3]) return(p);
	if(t[4]==p && t[4]==t[5] && t[5]==t[6]) return(p);
	if(t[7]==p && t[7]==t[8] && t[8]==t[9]) return(p);
	if(t[1]==p && t[1]==t[4] && t[4]==t[7]) return(p);
	if(t[2]==p && t[2]==t[5] && t[5]==t[8]) return(p);
	if(t[3]==p && t[3]==t[6] && t[6]==t[9]) return(p);
	if(t[1]==p && t[1]==t[5] && t[5]==t[9]) return(p);
	if(t[3]==p && t[3]==t[5] && t[5]==t[7]) return(p);
	return(NONE);
} 
 
 /*search������������������˿������Ļ��ᣬ������������ֵ��*/
 int search(int t[]){
 	
 	int f=0,k=0;
 	k=checkWin(t,MAN);
	if(k==MAN)/*���ж����Ƿ����Ӯ*/
		return MIN;/*������Է���һ����Сֵ*/
	if(t[1]>=0 && t[2]>=0 && t[3]>=0) f++;
	if(t[4]>=0 && t[5]>=0 && t[6]>=0) f++;
	if(t[7]>=0 && t[8]>=0 && t[9]>=0) f++;
	if(t[1]>=0 && t[4]>=0 && t[7]>=0) f++;
	if(t[2]>=0 && t[5]>=0 && t[8]>=0) f++;
	if(t[3]>=0 && t[6]>=0 && t[9]>=0) f++;
	if(t[1]>=0 && t[5]>=0 && t[9]>=0) f++;
	if(t[3]>=0 && t[5]>=0 && t[7]>=0) f++;

	if(t[1]<=0 && t[2]<=0 && t[3]<=0) f--;
	if(t[4]<=0 && t[5]<=0 && t[6]<=0) f--;
	if(t[7]<=0 && t[8]<=0 && t[9]<=0) f--;
	if(t[1]<=0 && t[4]<=0 && t[7]<=0) f--;
	if(t[2]<=0 && t[5]<=0 && t[8]<=0) f--;
	if(t[3]<=0 && t[6]<=0 && t[9]<=0) f--;
	if(t[1]<=0 && t[5]<=0 && t[9]<=0) f--;
	if(t[3]<=0 && t[5]<=0 && t[7]<=0) f--;
		return f;/*��������ֵ������������ֵ*/	
 }
 
 
 int checkWinning(int p,int t[]){
	int i,k=10;
	for(i=1;i<10;i++){
		if(t[i]==0){
			t[i]=p;
			if(checkWin(t,p)==p){
				t[i]=0;
				k=i;
				w++;
			}
			t[i]=0;
		}
	}	
 	return k;
 } 
 
 
 /*display����������ʾ���̣�����ʾ���*/
 void display(int type){
//	printf("������\n");
	printf("ѧ�ţ�201621123003\n");

	char dis[10]={""};
	int i;
	for(i=1;i<10;i++){
		if(b[i]<0)
	 		dis[i]='X';
		if(b[i]>0)
			 dis[i]='O'; 		
	}
 	printf("\n%c|%c|%c\n",dis[1],dis[2],dis[3]);
 	printf("-----\n");
 	printf("%c|%c|%c\n",dis[4],dis[5],dis[6]);
 	printf("-----\n");
 	printf("%c|%c|%c\n",dis[7],dis[8],dis[9]);
 
	if(type==NONE) printf("�����");
	
	if(type==DRAW) printf("ƽ��");
 
 	if(type==C_WIN) printf("������");
 
 	if(type==M_WIN) printf("��ϲ��Ӯ��");
 
 	if(type==QUIT) printf("��ֹͣ����Ϸ");
 }
 
/*���µ�ʱ��ִ��man����*/
int man(){
	int c;
	/*��ʾ��Ϣ*/
	printf("\n�����������µ�λ�ã�����0����������1-9�ֱ����9�������ڵ�λ�ã�\n");
	for(c=getche();;printf("\n",c=getche())) 
	if(isdigit(c) && b[c-48]==0){
		
		/*����û��������"0"���ͽ�������*/
		if(c=='0'){
		r=QUIT;return 0;	
		} 
	
	/*�����û������λ�ã�������1*/
	step--;
	b[c-48]=MAN;
	 
	/*�������Ϊ0�����Ϊƽ��*/
	if(step==0) 
		r=DRAW;
	
	/*��Ӯ�ˣ����ΪM_WIN*/
	if(checkWin(b,MAN)==MAN)
		r=M_WIN;
	
	return 0;
	}	
} 
 
 
int com(){
	int i,j,t[10];
	int temp,max=MIN-1,f=0,best=1,k,flag;
	system("cls");
	
	/*������Կ���Ӯ���ڸ�λ��*/
	flag=checkWinning(COM,b);
	if(flag<10){
		b[flag]=COM;
		r=C_WIN;
		step--;
		return 0;
	} 
	
	/*����˿���Ӯ��Ҳ������Ӧ��λ��*/
	flag=checkWinning(MAN,b);
	if(flag<10){
		b[flag]=COM;
		step--;
		return 0;	
	} 

    /*��t��ʱ�洢����*/
    for(i=1;i<10;i++){
    	t[i]=b[i];
	} 
    for(i=1;i<10;i++){
		if(t[i]==0){
			t[i]=COM;
			f=MAX;
			k=checkWinning(COM,t);/*������������˵�i����˿���Ӯ*/
								  /*�Ͷ��㷨���м�֧��ֻ����kλ�õ�����ֵ*/
		    for(j=1;j<10;j++){
		    	if(k<10){
		    		t[k]=MAN;
		    	    f=search(t);
		    	    t[k]=0;
		    	    break;
				}
			
			/*�������ÿ�����ɵĽ�������ֵ*/
			if(t[j]==0){
				t[j]=MAN;
				temp=search(t); 
				if(temp<f){    /*ÿ�ζ�������С����ֵ������ */
					f=temp;
				}
				t[j]=0;
				if(f==MIN)
				    break;
			} 
			}
			t[i]=0;
			if(f>max){/* ��������ѡ����������ֵ*/ 
				best=i;
				max=f; 
			}
		} 
	} 
	b[best]=COM;/*����������������ֵ����λ��*/
	step--;
	if(step==0) 
		r=DRAW;
}
 
 
main(){
char c;
int i;
system("cls");
printf("���201621123003���\n"); 
for(i=0;i<20;i++)
printf("*");
//printf("\n �Ƿ������£��Լ���������1��\n");
for(c=getche();c!='1' && c!='2';c=getche());
if(c=='1'){
	man();
	if(step<=0||r!=NONE){
		system("cls");
		display(r);
		getch();
		return 0;
	}
}
/*�������������*/
while(TRUE){
	com();
	display(r);
	if(step<=0||r!=NONE)
			break;
	man();
	if(step<=0|| r!=NONE)
	{
		system("cls");
		display(r);
		break;
	 } 
}
getch();
}	