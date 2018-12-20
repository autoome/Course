#include<string.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<malloc.h>
#include<bits/stdc++.h>
#define infinity 32768     //����һ�����޴��ֵ
#define MAXSIZE 100
#define N 27
typedef struct {      //���������Ľṹ��
	char ch;
    float weight;    //Ȩֵ
    unsigned int parent,lchild,rchild; 
}HTNode,*activeHuffmanTree;   //��̬��������洢��������

typedef char *HuffmanCode;    //��̬��������洢�����������

int m,s1,s2; //����ȫ�ֱ����ܽ��m����С������s1,��С������s2

/**************************************************/
/*��������Min                                     */
/*�������ܣ���������n�������Ȩֵ��С�Ľ�����   */
/*�βΣ�activeHuffmanTree t,int n                 */
/*����ֵ��flag                                    */
/**************************************************/
int Min(activeHuffmanTree t,int n)       //��������n�������Ȩֵ��С�Ľ�����
{
	int i,flag;
	float f=infinity;     //fΪһ�����޴��ֵ
	for(i=1;i<=n;i++)
		if(t[i].weight<f&&t[i].parent==0)
		{
			f=t[i].weight;flag=i;
		}
		t[flag].parent=1;     //��ѡ�еĽ���˫�׽�㸳ֵ1�������ٴβ��Ҹý��
		return flag;
}
/**********************************************************************/
/*��������Select                                                      */
/*�������ܣ���n�������ѡ������Ȩֵ��С�Ľ����ţ�����s1��С��s2��С */
/*�βΣ�activeHuffmanTree *t,int n,int *s1,int *s2                    */
/*����ֵ��s1,s2                                                       */
/**********************************************************************/
void Select(activeHuffmanTree *t,int n,int *s1,int *s2)
//��n�������ѡ������Ȩֵ��С�Ľ����ţ�����s1��С��s2��С
{
	int x;
	*s1=Min(*t,n);
	*s2=Min(*t,n); 
	if((*t)[*s1].weight>(*t)[*s2].weight)  //������s1��Ȩֵ�������s2��Ȩֵ�������߽�����ʹs1��С��s2��С
	{
		x=*s1;
		*s1=*s2;
		*s2=x;
	}
}

/***************************************************************************/
/*��������createHuffmanTree                                                */
/*�������ܣ������������HT�����������ı�������HC�У�wΪn���ַ���Ȩֵ     */
/*�βΣ�activeHuffmanTree &HT, HuffmanCode HC[], float *w, char *ch,int n  */
/*����ֵ����                                                               */
/***************************************************************************/
void createHuffmanTree(activeHuffmanTree &HT, HuffmanCode HC[], float *w, char *ch,int n)
//�����������HT�����������ı�������HC�У�wΪn���ַ���Ȩֵ
{
int i; 

if (n<=1) return; 
m = 2 * n - 1; 
HT = (activeHuffmanTree)malloc((m+1) * sizeof(HTNode)); 
for (i=1; i<=n; i++,w++)     //��ʼ��n��Ҷ�ӽ��
 {
HT[i].weight=*w;
HT[i].ch=ch[i-1];
HT[i].parent=0; 
HT[i].lchild=0; 
HT[i].rchild=0; 
} 
for (i=n+1; i<=m; i++)  //��ʼ������Ľ��
{ 
HT[i].weight=0; 
HT[i].parent=0; 
HT[i].lchild=0; 
HT[i].rchild=0; 
} 

for (i=n+1; i<=m; i++)    //�����������
{ 
Select(&HT, i-1,&s1,&s2);      //��������Ȩֵ��С���������
HT[s1].parent = i; HT[s2].parent = i; //����ŷֱ�Ϊ s1�� s2
HT[i].lchild = s1; HT[i].rchild = s2; 
HT[i].weight = HT[s1].weight + HT[s2].weight; 
 
} 
}
/**************************************************************************/
/*��������activeHuffmanCoding                                             */
/*�������ܣ���Ҷ�ӽ�㵽�������ÿ���ַ��Ĺ�����������                    */
/*�βΣ�activeHuffmanTree &HT, HuffmanCode HC[], float *w,char *ch ,int n */
/*����ֵ����                                                              */
/**************************************************************************/
void activeHuffmanCoding(activeHuffmanTree &HT, HuffmanCode HC[], float *w,char *ch ,int n) 
{ 
int i; 
unsigned int c,f;
char *cd; 
int start; 

createHuffmanTree(HT,HC, w, ch,n);

//��Ҷ�ӽ�㵽�������ÿ���ַ��Ĺ�����������
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char*));//����n���ַ����� ��ͷָ������
	cd=(char*)malloc(n*sizeof(char));     //Ϊ���������붯̬����ռ�
	cd[n-1]='\0'; //���� ������
	//��n��Ҷ�ӽ��Ĺ���������
	for(i=1;i<=n;i++)
	{
		start=n-1;         //���������λ��
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			//��Ҷ�ӽ�㵽����������
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));
			//Ϊ��i���ַ��������ռ�
			strcpy(HC[i],&cd[start]);
			//����ǰ������Ĺ��������븴�Ƶ�HC
	}
	free(cd);//�ͷſռ�
}
/******************************************************/
/*��������activeTest                                  */
/*�������ܣ���̬ʵ�ֹ��������Լ��ַ���Ȩֵ���������  */
/*�βΣ�activeHuffmanTree &HT, HuffmanCode HC[]       */
/*����ֵ����                                          */
/******************************************************/
void activeTest(activeHuffmanTree &HT, HuffmanCode HC[])
{
	int n;
	int i;
	char *c;
	float *w;
    puts("\n====================================");
	printf("����������ַ�������");
	scanf("%d",&n);	
	fflush(stdin);
	w=(float *)malloc(n*sizeof(float));
    c=(char *)malloc(n*sizeof(char));
   
    printf("\n���������������ַ���������ո񣩣�");
    gets(c);
	fflush(stdin);
	printf("\n�����������ַ�Ȩֵ��Ȩֵ֮��ո��������");
	for(i=0;i<n;i++)
		scanf("%f",&w[i]);
	fflush(stdin);
	activeHuffmanCoding(HT,HC,w,c,n);
	printf("\n������ɣ�������£�\n");
	puts("\n====================================");
	puts("      �ַ�   ����            Ȩ ֵ"); 
    for(i = 0;i <n;i++)
	{  

	printf("%8c     :%-12s   (%-3f)\n",c[i],HC[i+1],w[i]); 
	} 
	puts("====================================");
}
/****************************************************************/
/*��������FileCoding                                            */
/*�������ܣ����ݸ������ַ���Ƶ�ȣ���һƪӢ�����½��й��������룻*/
/*�βΣ�activeHuffmanTree HT, HuffmanCode HC[]                  */
/*����ֵ����                                                    */
/****************************************************************/

int FileCoding(activeHuffmanTree HT, HuffmanCode HC[])
{
	FILE *fp,*fp1;
	char ch;
	char name[20];
	char c[27]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	float w[27]={186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
	printf("\n�������ļ����������ļ���test.txt����");
	scanf("%s",name);
	fflush(stdin);
    if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" �ļ���ʧ�ܣ�\n");
	   exit(1);
	 }
    printf("ԭ�����£�\n");
	puts("===============================================================================\n");
    ch=fgetc(fp);
	while(ch!=EOF)
	{	 
	 putchar(ch);
	 ch=fgetc(fp);
	}
	puts("\n===============================================================================\n");
	fclose(fp);

	activeHuffmanCoding(HT,HC,w,c,27); 

	if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" �ļ���ʧ�ܣ�\n");
	   exit(1);
	}
	if((fp1=fopen("coding.cod","w"))==NULL)
	{
	   printf(" �ļ���ʧ�ܣ�\n");
	   exit(1);
	}
	  printf("�������£�\n");
	  puts("===============================================================================\n");
	  ch= tolower(fgetc(fp));
	while(ch!=EOF)
	{
	
     if(ch==10)
     {
		 putchar(10);
		 fputc(10,fp1);
	 }
	 else 
		 if(ch==' ')
		 {
	    	printf("%s",HC[1]);
			fprintf(fp1,"%s",HC[1]);
		 }

	 else
		 if(ch>96&&ch<123)
		 {
		   printf("%s",HC[ch-95]);
		   fprintf(fp1,"%s",HC[ch-95]);
		 }

	 else
	 {
		putchar(ch);
		fputc(ch,fp1);
	 }
		
	 ch=tolower(fgetc(fp));
	}
    fclose(fp1);
	puts("\n===============================================================================\n");
	puts("�ļ��ѱ�����\"coding.cod\"\n");
	fclose(fp);
	return 0;
}
/*********************************************************************/
/*��������FileDecoding                                               */
/*�������ܣ���Թ��������������½������룬���ü򵥵Ĵ�Сдת������ */
/*�βΣ�activeHuffmanTree HT, HuffmanCode HC[]                       */
/*����ֵ����                                                         */
/*********************************************************************/
int FileDecoding(activeHuffmanTree HT, HuffmanCode HC[])
{
    int p=2*N-1;
    FILE *fp;
	char ch;
	char name[20];
	char c[27]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	float w[27]={186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
	int change=0;
	printf("\n�������ļ����������ļ���coding.cod����");
	scanf("%s",name);
	fflush(stdin);
    if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" �ļ���ʧ�ܣ�\n");
	   exit(1);
	   }
    printf("ԭ�����£�\n");
	puts("===============================================================================\n");
    ch=fgetc(fp);
	while(ch!=EOF)
	{	 
	 putchar(ch);
	 ch=fgetc(fp);
	}
	puts("\n===============================================================================\n");
	fclose(fp);

	createHuffmanTree(HT,HC,w,c,27);

	if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" �ļ���ʧ�ܣ�\n");
	   exit(1);
	   }
	  printf("�������£�\n");
	  puts("===============================================================================\n");
	  ch= fgetc(fp);

while(ch!=EOF)
{
       if(ch=='0') 
         p=HT[p].lchild;
       else 
		   if(ch=='1') 
         p=HT[p].rchild;
	   else 
		   if(ch==10||ch=='.'||ch=='?')
	   {
		  putchar(ch);
		  change=1;
	   }
	  else
		putchar(ch);

       if(p<=N)
	   {
				if(change)
				{
				 printf("%c",toupper(HT[p].ch));
				 change=0;
				 }
				 else
				 printf("%c",HT[p].ch);
 
             p=2*N-1;
	   }
      ch=fgetc(fp);
}

fclose(fp);

	puts("\n===============================================================================\n");
	
	return 0;

}
/**************************************************/
/*��������Meum                                    */
/*�������ܣ�ϵͳ���ܲ˵�                          */
/*�βΣ���                                        */
/*����ֵ��choice                                  */
/**************************************************/
int Meum()
{
	int choice;
	puts("     \n\t=========================================================\n");
	puts("                       ������ ��������/������ ������\n  ");

	puts("     \t=========================================================\n");
	printf("     \t\t\t1-------------��̬����������\n\n");
	printf("     \t\t\t2-------------����������    \n\n");
	printf("     \t\t\t3-------------����������    \n\n");
	printf("     \t\t\t4-------------�˳�          \n\n");
	puts("     \t==========================================================\n");
	printf("\t\t\t\t��ѡ��: ");
	scanf("%d",&choice);
	fflush(stdin);
	return choice;
}
/**************************************************/
/*��������SystemInfo                              */
/*�������ܣ���ʾ��������ϵͳ��Ϣ                  */
/*�βΣ���                                        */
/*����ֵ����                                      */
/**************************************************/
void SystemInfo()
{
	FILE *fp;
	if(!(fp=fopen("ϵͳ��Ϣ.txt","r")))
	{
		puts("˵���ļ���ʧ��");
			return ;
	}
	puts("\n\n\n\n");
	puts("--------------------------------------------------------------------------------");
	puts("                          ������ ϵͳ��Ϣ ������\n  ");
	puts("--------------------------------------------------------------------------------");	
	while(!feof(fp))
		putchar(fgetc(fp));
	
	putchar(10);
	puts("--------------------------------------------------------------------------------");
}
