
#include "stm8s.h"
#define NB_THEME 4

void parseur(char phrase[], char words[NB_THEME][20]) 
{	
	char j=0, k, l, record=0;
	char used[NB_THEME]={0,0,0,0}; 
	
	while (phrase[j] != '\0') 
	{
		if (phrase[j] == '/') 
		{
			record=1;
			switch (phrase[j+1])
			{
				case '1':k=0;used[0]=1;break;
				case '2':k=1;used[1]=1;break;
				case '3':k=2;used[2]=1;break;
				case '4':k=3;used[3]=1;break;
			}
			l=0;
			j+=2;
		}
		if (record == 1)
		{
			words[k][l]=phrase[j];
			l++;
			
			if ((phrase[j+1] == ' ') || (phrase[j+1] == '\0'))
			{
				words[k][l]='\0';
				record=0;
			}
		}
		j++;
	}
}
