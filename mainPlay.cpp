#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct {
    char word[3];
}Blocks;

typedef struct {
    char word[3];
    char times[2];
}Words;

Blocks block[100];
Words word[53];

int main(){
	FILE *fp;
    char W_temp[53][3];
    int num[53];
	srand((unsigned)time(NULL));	   
    if( ( fp = fopen( "Words_Time.csv", "r")) == NULL) 
    {
        puts("Cannot oepn the file");
    }
    int count = 0;
	while (count!=53)
    {	  
		fscanf( fp,"%s",W_temp[count]);
		strncpy(word[count].word,W_temp[count],2);
		
		strncpy(word[count].times,W_temp[count]+3,1);         
    	count++;  
	}
	fclose(fp); 
    int block_num=0;
    count=0;
	while(block_num<100){
		if(strcmp(word[count].times,"2")==0){
			strcpy(block[block_num].word,word[count].word);
			strcpy(block[block_num+1].word,word[count].word); 
			block_num+=2;
		}
		else{
			strcpy(block[block_num].word,word[count].word);
			block_num++;
		}
		count++;
	}
    
    for(int i=0;i<=10000;i++){
        int n1=rand()%100;		//產生0～99的亂數
        int n2=rand()%100;
        //將陣列資料進行交換（打散）
		Blocks B_temp;
		strcpy(B_temp.word,block[n1].word);
		strcpy(block[n1].word,block[n2].word);
		strcpy(block[n2].word,B_temp.word);
    }
    for(int i=0;i<100;i++)printf("%s\n",block[i].word);
    
    
	system("PAUSE"); 
    return 0;

}
