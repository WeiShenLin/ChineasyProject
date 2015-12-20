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
typedef struct {
    int hands[3];
    int time;
    int score;
}Players;

Blocks block[100];
Words word[53];

int main(){
	FILE *fp;
    char L_temp[53][3];
    int num[53];
	srand((unsigned)time(NULL));
	int player=0;
	int count = 0;
	int block_num=0;
		   
    if( ( fp = fopen( "Letters_Time.csv", "r")) == NULL) 
    {
        puts("Cannot oepn the file");
    }
    
	while (count!=53)
    {	  
		fscanf( fp,"%s",L_temp[count]);
		strncpy(word[count].word,L_temp[count],2);
		
		strncpy(word[count].times,L_temp[count]+3,1);         
    	count++;  
	}
	fclose(fp); 
    
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
    //for(int i=0;i<100;i++)printf("%s\n",block[i].word);
    scanf("玩家人數:%d",&player);
    if(player==4){
		Players A,B,C,D;
		A.hands={0,1,2};
		A.time=0;
		A.score=0;
		B.hands={3,4,5};
		B.time=0;
		B.score=0;
		C.hands={6,7,8};
		C.time=0;
		C.score=0;
		D.hands={9,10,11};
		D.time=0;
		D.score=0;
		deck_num=player*3;
		boardspace=7*7+6*6;
		while(1){
			draw_num+=checkhands(A,block);
			draw_num+=checkboard(A);
			draw(A);
			draw_num+=checkhands(B,block);
			draw_num+=checkboard(B);
			draw(A);
			draw_num+=checkhands(C,block);
			draw_num+=checkboard(C);
			draw(A);
			draw_num+=checkhands(D,block);
			draw_num+=checkboard(D);
			draw(A);
			if(deck_num==100||boardspace==0)break;
		}
		
    }
    
	system("PAUSE"); 
    return 0;

}
int checkhands(Players player,Blocks block[100]){
	FILE *fp;
	char W_temp[50][5];
	int word_num=0;
	char word[6][5];
	strcpy(word[0],block[player.hands[0]]);
	strcat(word[0],block[player.hands[1]]);
	strcpy(word[1],block[player.hands[0]]);
	strcat(word[1],block[player.hands[2]]);
	strcpy(word[2],block[player.hands[1]]);
	strcat(word[2],block[player.hands[0]]);
	strcpy(word[3],block[player.hands[1]]);
	strcat(word[3],block[player.hands[2]]);
	strcpy(word[4],block[player.hands[2]]);
	strcat(word[4],block[player.hands[0]]);
	strcpy(word[5],block[player.hands[2]]);
	strcat(word[5],block[player.hands[1]]);
	player.time++;	
	if( ( fp = fopen( "Words.csv", "r")) == NULL) 
    {
        puts("Cannot oepn the file");
    }
    
    while(word_num!=50){
    	fscanf(fp,"%s",W_temp[word_num]);
    	if(!strcmp(W_temp[word_num],word[0])){
    		player.hands[0]=101;
    		player.hands[1]=101;
    		player.score++;
    		return 2;
    	}
    	else if(!strcmp(W_temp[word_num],word[1])){
    		player.hands[0]=101;
    		player.hands[2]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[2])){
    		player.hands[1]=101;
    		player.hands[0]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[3])){
    		player.hands[1]=101;
    		player.hands[2]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[4])){
    		player.hands[2]=101;
    		player.hands[0]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[5])){
    		player.hands[2]=101;
    		player.hands[1]=101;
    		player.score++;
    		return 2;
    	}
		else
		    word_num++;
    }
	return 0;
}
