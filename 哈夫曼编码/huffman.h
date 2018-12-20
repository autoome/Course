#include<string.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<malloc.h>
#include<bits/stdc++.h>
#define infinity 32768     //定义一个无限大的值
#define MAXSIZE 100
#define N 27
typedef struct {      //哈夫曼树的结构体
	char ch;
    float weight;    //权值
    unsigned int parent,lchild,rchild; 
}HTNode,*activeHuffmanTree;   //动态分配数组存储哈夫曼树

typedef char *HuffmanCode;    //动态分配数组存储哈夫曼编码表

int m,s1,s2; //定义全局变量总结点m，最小结点序号s1,次小结点序号s2

/**************************************************/
/*函数名：Min                                     */
/*函数功能：返回树中n个结点中权值最小的结点序号   */
/*形参：activeHuffmanTree t,int n                 */
/*返回值：flag                                    */
/**************************************************/
int Min(activeHuffmanTree t,int n)       //返回树中n个结点中权值最小的结点序号
{
	int i,flag;
	float f=infinity;     //f为一个无限大的值
	for(i=1;i<=n;i++)
		if(t[i].weight<f&&t[i].parent==0)
		{
			f=t[i].weight;flag=i;
		}
		t[flag].parent=1;     //给选中的结点的双亲结点赋值1，避免再次查找该结点
		return flag;
}
/**********************************************************************/
/*函数名：Select                                                      */
/*函数功能：在n个结点中选择两个权值最小的结点序号，其中s1最小，s2次小 */
/*形参：activeHuffmanTree *t,int n,int *s1,int *s2                    */
/*返回值：s1,s2                                                       */
/**********************************************************************/
void Select(activeHuffmanTree *t,int n,int *s1,int *s2)
//在n个结点中选择两个权值最小的结点序号，其中s1最小，s2次小
{
	int x;
	*s1=Min(*t,n);
	*s2=Min(*t,n); 
	if((*t)[*s1].weight>(*t)[*s2].weight)  //如果序号s1的权值大于序号s2的权值，将两者交换，使s1最小，s2次小
	{
		x=*s1;
		*s1=*s2;
		*s2=x;
	}
}

/***************************************************************************/
/*函数名：createHuffmanTree                                                */
/*函数功能：构造哈弗曼树HT，哈弗曼数的编码存放在HC中，w为n个字符的权值     */
/*形参：activeHuffmanTree &HT, HuffmanCode HC[], float *w, char *ch,int n  */
/*返回值：无                                                               */
/***************************************************************************/
void createHuffmanTree(activeHuffmanTree &HT, HuffmanCode HC[], float *w, char *ch,int n)
//构造哈弗曼树HT，哈弗曼数的编码存放在HC中，w为n个字符的权值
{
int i; 

if (n<=1) return; 
m = 2 * n - 1; 
HT = (activeHuffmanTree)malloc((m+1) * sizeof(HTNode)); 
for (i=1; i<=n; i++,w++)     //初始化n个叶子结点
 {
HT[i].weight=*w;
HT[i].ch=ch[i-1];
HT[i].parent=0; 
HT[i].lchild=0; 
HT[i].rchild=0; 
} 
for (i=n+1; i<=m; i++)  //初始化其余的结点
{ 
HT[i].weight=0; 
HT[i].parent=0; 
HT[i].lchild=0; 
HT[i].rchild=0; 
} 

for (i=n+1; i<=m; i++)    //构造哈弗曼树
{ 
Select(&HT, i-1,&s1,&s2);      //查找树中权值最小的两个结点
HT[s1].parent = i; HT[s2].parent = i; //其序号分别为 s1和 s2
HT[i].lchild = s1; HT[i].rchild = s2; 
HT[i].weight = HT[s1].weight + HT[s2].weight; 
 
} 
}
/**************************************************************************/
/*函数名：activeHuffmanCoding                                             */
/*函数功能：从叶子结点到根结点求每个字符的哈弗曼树编码                    */
/*形参：activeHuffmanTree &HT, HuffmanCode HC[], float *w,char *ch ,int n */
/*返回值：无                                                              */
/**************************************************************************/
void activeHuffmanCoding(activeHuffmanTree &HT, HuffmanCode HC[], float *w,char *ch ,int n) 
{ 
int i; 
unsigned int c,f;
char *cd; 
int start; 

createHuffmanTree(HT,HC, w, ch,n);

//从叶子结点到根结点求每个字符的哈弗曼树编码
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char*));//分配n个字符编码 的头指针项链
	cd=(char*)malloc(n*sizeof(char));     //为哈弗曼编码动态分配空间
	cd[n-1]='\0'; //编码 结束符
	//求n个叶子结点的哈弗曼编码
	for(i=1;i<=n;i++)
	{
		start=n-1;         //编码结束符位置
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			//从叶子结点到根结点求编码
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));
			//为第i个字符编码分配空间
			strcpy(HC[i],&cd[start]);
			//将当前求出结点的哈弗曼编码复制到HC
	}
	free(cd);//释放空间
}
/******************************************************/
/*函数名：activeTest                                  */
/*函数功能：动态实现哈弗曼树以及字符和权值的输入输出  */
/*形参：activeHuffmanTree &HT, HuffmanCode HC[]       */
/*返回值：无                                          */
/******************************************************/
void activeTest(activeHuffmanTree &HT, HuffmanCode HC[])
{
	int n;
	int i;
	char *c;
	float *w;
    puts("\n====================================");
	printf("请输入编码字符个数：");
	scanf("%d",&n);	
	fflush(stdin);
	w=(float *)malloc(n*sizeof(float));
    c=(char *)malloc(n*sizeof(char));
   
    printf("\n请依次输入编码的字符串（无需空格）：");
    gets(c);
	fflush(stdin);
	printf("\n请依次输入字符权值（权值之间空格隔开）：");
	for(i=0;i<n;i++)
		scanf("%f",&w[i]);
	fflush(stdin);
	activeHuffmanCoding(HT,HC,w,c,n);
	printf("\n编码完成，结果如下：\n");
	puts("\n====================================");
	puts("      字符   编码            权 值"); 
    for(i = 0;i <n;i++)
	{  

	printf("%8c     :%-12s   (%-3f)\n",c[i],HC[i+1],w[i]); 
	} 
	puts("====================================");
}
/****************************************************************/
/*函数名：FileCoding                                            */
/*函数功能：根据给出的字符集频度，对一篇英文文章进行哈夫曼编码；*/
/*形参：activeHuffmanTree HT, HuffmanCode HC[]                  */
/*返回值：无                                                    */
/****************************************************************/

int FileCoding(activeHuffmanTree HT, HuffmanCode HC[])
{
	FILE *fp,*fp1;
	char ch;
	char name[20];
	char c[27]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	float w[27]={186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
	printf("\n请输入文件名（测试文件：test.txt）：");
	scanf("%s",name);
	fflush(stdin);
    if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" 文件打开失败！\n");
	   exit(1);
	 }
    printf("原文如下：\n");
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
	   printf(" 文件打开失败！\n");
	   exit(1);
	}
	if((fp1=fopen("coding.cod","w"))==NULL)
	{
	   printf(" 文件打开失败！\n");
	   exit(1);
	}
	  printf("编码如下：\n");
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
	puts("文件已保存至\"coding.cod\"\n");
	fclose(fp);
	return 0;
}
/*********************************************************************/
/*函数名：FileDecoding                                               */
/*函数功能：针对哈夫曼编码后的文章进行译码，采用简单的大小写转换功能 */
/*形参：activeHuffmanTree HT, HuffmanCode HC[]                       */
/*返回值：无                                                         */
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
	printf("\n请输入文件名（测试文件：coding.cod）：");
	scanf("%s",name);
	fflush(stdin);
    if((fp=fopen(name,"r"))==NULL)
	{
	   printf(" 文件打开失败！\n");
	   exit(1);
	   }
    printf("原码如下：\n");
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
	   printf(" 文件打开失败！\n");
	   exit(1);
	   }
	  printf("译文如下：\n");
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
/*函数名：Meum                                    */
/*函数功能：系统功能菜单                          */
/*形参：无                                        */
/*返回值：choice                                  */
/**************************************************/
int Meum()
{
	int choice;
	puts("     \n\t=========================================================\n");
	puts("                       〓〓〓 哈夫曼编/译码器 〓〓〓\n  ");

	puts("     \t=========================================================\n");
	printf("     \t\t\t1-------------动态哈夫曼编码\n\n");
	printf("     \t\t\t2-------------哈夫曼编码    \n\n");
	printf("     \t\t\t3-------------哈夫曼译码    \n\n");
	printf("     \t\t\t4-------------退出          \n\n");
	puts("     \t==========================================================\n");
	printf("\t\t\t\t请选择: ");
	scanf("%d",&choice);
	fflush(stdin);
	return choice;
}
/**************************************************/
/*函数名：SystemInfo                              */
/*函数功能：显示函数功能系统信息                  */
/*形参：无                                        */
/*返回值：无                                      */
/**************************************************/
void SystemInfo()
{
	FILE *fp;
	if(!(fp=fopen("系统信息.txt","r")))
	{
		puts("说明文件丢失！");
			return ;
	}
	puts("\n\n\n\n");
	puts("--------------------------------------------------------------------------------");
	puts("                          〓〓〓 系统信息 〓〓〓\n  ");
	puts("--------------------------------------------------------------------------------");	
	while(!feof(fp))
		putchar(fgetc(fp));
	
	putchar(10);
	puts("--------------------------------------------------------------------------------");
}
