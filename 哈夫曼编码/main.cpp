#include"huffman.h"
/************************************************************/
/*��������main                                              */
/*�������ܣ�����ṩ��ϵͳ���ܲ˵����û���ѡ����ø�������  */
/*�βΣ���                                                  */
/*����ֵ����                                                */
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
        printf("\n\n���������...");
        getchar();
	} 
	return 0;
}
