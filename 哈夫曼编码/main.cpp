#include"huffman.h"
/************************************************************/
/*函数名：main                                              */
/*函数功能：针对提供的系统功能菜单中用户的选择调用各个函数  */
/*形参：无                                                  */
/*返回值：无                                                */
/************************************************************/
int main() 
{ 
	int flag=1;
    activeHuffmanTree HT;
    HuffmanCode *HC;
    HC = (HuffmanCode *)malloc(MAXSIZE*sizeof(HuffmanCode)); 
    while((flag=Meum())<4)
	{
      switch(flag)
	  {	
         case 0:SystemInfo( );  break;
	     case 1:activeTest(HT,HC);  break;
	     case 2:FileCoding(HT,HC);  break;
         case 3:FileDecoding(HT,HC);break;
	     default:exit(0);
	  }
        printf("\n\n任意键继续...");
        getchar();
	} 
	return 0;
}
