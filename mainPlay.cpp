#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct {
    char letter[3];
}Blocks;

typedef struct {
    char letter[3];
    char times[2];
}Letters;
typedef struct {
    int hands[3];
    int time;
    int score;
}Players;
typedef struct {
    int num;
    char letters[100][3];
}Bags;
typedef struct {
    char layer1_letters[7][7][3]={{"No","No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No","No"},
						 		  {"No","No","No","No","No","No","No"},
						 		  {"No","No","No","No","No","No","No"},
								  {"No","No","No","No","No","No","No"},
								  {"No","No","No","No","No","No","No"},
								  {"No","No","No","No","No","No","No"}};
    char layer2_letters[6][6][3]={{"No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No"},
						  		  {"No","No","No","No","No","No"}};
}Boards;

Blocks block[100];
Letters letter[53];
Bags bag;
Boards board;

void shufflebag(){
	for(int i=0;i<=10000;i++){
        int n1=rand()%100;		//產生0～99的亂數
        int n2=rand()%100;
        //將陣列資料進行交換（打散）
		Blocks B_temp;
		strcpy(B_temp.letter,bag.letters[n1]);
		strcpy(bag.letters[n1],bag.letters[n2]);
		strcpy(bag.letters[n2],B_temp.letter);
    }
}

void putbag(int hand1,int hand2){
	strcpy(bag.letters[bag.num-1],block[hand1].letter);
	strcpy(bag.letters[bag.num-2],block[hand2].letter);
	bag.num-=2;
	shufflebag();
	
}
int checklayer2(int row , int col){
	if(!strcmp(board.layer1_letters[row][col],"No")||!strcmp(board.layer1_letters[row+1][col],"No")||!strcmp(board.layer1_letters[row][col+1],"No")||!strcmp(board.layer1_letters[row+1][col+1],"No"))return 0;
	else return 1;
}
int checkhands(Players player,Blocks block[100]){
	FILE *fp;
	char W_temp[50][5];
	int word_num=0;
	char word[6][5];
	strcpy(word[0],block[player.hands[0]].letter);
	strcat(word[0],block[player.hands[1]].letter);
	strcpy(word[1],block[player.hands[0]].letter);
	strcat(word[1],block[player.hands[2]].letter);
	strcpy(word[2],block[player.hands[1]].letter);
	strcat(word[2],block[player.hands[0]].letter);
	strcpy(word[3],block[player.hands[1]].letter);
	strcat(word[3],block[player.hands[2]].letter);
	strcpy(word[4],block[player.hands[2]].letter);
	strcat(word[4],block[player.hands[0]].letter);
	strcpy(word[5],block[player.hands[2]].letter);
	strcat(word[5],block[player.hands[1]].letter);
	player.time++;	
	if( ( fp = fopen(".Words.csv", "r")) == NULL) 
    {
        puts("Cannot open the file");
        system("PAUSE");
        
    }
    
    while(word_num!=50){
    	fscanf(fp,"%s",W_temp[word_num]);
    	if(!strcmp(W_temp[word_num],word[0])){
    		putbag(player.hands[0],player.hands[1]);
			player.hands[0]=101;
    		player.hands[1]=101;
    		player.score++;
    		return 2;
    	}
    	else if(!strcmp(W_temp[word_num],word[1])){
    		putbag(player.hands[0],player.hands[2]);
			player.hands[0]=101;
    		player.hands[2]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[2])){
    		putbag(player.hands[1],player.hands[0]);
			player.hands[1]=101;
    		player.hands[0]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[3])){
    		putbag(player.hands[1],player.hands[2]);
			player.hands[1]=101;
    		player.hands[2]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[4])){
    		putbag(player.hands[2],player.hands[0]);
			player.hands[2]=101;
    		player.hands[0]=101;
    		player.score++;
    		return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[5])){
    		putbag(player.hands[2],player.hands[1]);
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

int checkword(int handword){
	FILE *fp;
	char W_temp[50][5];
	int word_num=0;
	char word[170][5];
	int word_place=0;
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			strcpy(word[word_place],block[handword].letter);
			strcpy(word[word_place],board.layer1_letters[i][j]);
			word_place++;
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			strcpy(word[word_place],block[handword].letter);
			strcpy(word[word_place],board.layer2_letters[i][j]);
			word_place++;
		}
	}
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			strcpy(word[word_place],board.layer1_letters[i][j]);
			strcpy(word[word_place],block[handword].letter);
			word_place++;
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			strcpy(word[word_place],board.layer2_letters[i][j]);
			strcpy(word[word_place],block[handword].letter);
			word_place++;
		}
	}
	
	if( ( fp = fopen(".Words.csv", "r")) == NULL) 
    {
        puts("Cannot open the file");
        system("PAUSE");
    }
    while(word_num!=50){
    	fscanf(fp,"%s",W_temp[word_num]);
    	for(int i=0;i<170;i++){
    		if(!strcmp(W_temp[word_num],word[i])){
    			return 1;
    		}
    	}
		word_num++;
    }
    return 0;
}

void randboard(int num){
	int board_row,board_col,boardlayer;
		while(1){
			board_row=rand()%7;
			board_col=rand()%7;
			boardlayer=rand()%2;
			if((!strcmp(board.layer1_letters[board_row][board_col],"No"))&&boardlayer==1)break;
			else if(board_row<6&&board_col<6&&boardlayer==2&&checklayer2(board_row,board_col)){
				if(!strcmp(board.layer2_letters[board_row][board_col],"No"))break;
			}
		}
		if(boardlayer==1)strcpy(board.layer1_letters[board_row][board_col],block[num].letter);
		else strcpy(board.layer2_letters[board_row][board_col],block[num].letter);
}

int checkboard(Players player,int player_num){
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			if(!strcmp(board.layer1_letters[i][j],"No")){
				if(checkword(player.hands[0])){
					strcpy(board.layer1_letters[i][j],block[player.hands[0]].letter);
					player.hands[0]=101;
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[1])){
					strcpy(board.layer1_letters[i][j],block[player.hands[1]].letter);
					player.hands[0]=101;
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[2])){
					strcpy(board.layer1_letters[i][j],block[player.hands[2]].letter);
					player.hands[0]=101;
					player.score++;
					return 1;
				}
			}	
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			if(!strcmp(board.layer2_letters[i][j],"No")&&checklayer2(i,j)){
				if(checkword(player.hands[0])){
					strcpy(board.layer2_letters[i][j],block[player.hands[0]].letter);
					player.hands[0]=101;
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[1])){
					strcpy(board.layer2_letters[i][j],block[player.hands[1]].letter);
					player.hands[1]=101;
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[2])){
					strcpy(board.layer2_letters[i][j],block[player.hands[2]].letter);
					player.hands[2]=101;
					player.score++;
					return 1;
				}
			}	
		}
	}
	if(player.hands[0]!=101){	
 		randboard(player.hands[0]);
 		return 1;
 	}
 	else if(player.hands[1]!=101){
 		randboard(player.hands[1]);
 		return 1;
 	}
	else{
 		randboard(player.hands[2]);
 		return 1;
	}
}




int main(){
	FILE *fp;
    char L_temp[53][3];
    int num[53];
	srand((unsigned)time(NULL));
	int player=0;
	int count = 0;
	int block_num=0;
	bag.num=0;
	
    if( ( fp = fopen( "Letters_Time.csv", "r")) == NULL) 
    {
        puts("Cannot open the file");
    }
    
	while (count!=53)
    {	  
		fscanf( fp,"%s",L_temp[count]);
		strncpy(letter[count].letter,L_temp[count],2);
		
		strncpy(letter[count].times,L_temp[count]+3,1);         
    	count++;  
	}
	fclose(fp); 
    
    count=0;
	while(block_num<100){
		if(strcmp(letter[count].times,"2")==0){
			strcpy(block[block_num].letter,letter[count].letter);
			strcpy(block[block_num+1].letter,letter[count].letter); 
			block_num+=2;
		}
		else{
			strcpy(block[block_num].letter,letter[count].letter);
			block_num++;
		}
		count++;
	}
    
    for(int i=0;i<=10000;i++){
        int n1=rand()%100;		//產生0～99的亂數
        int n2=rand()%100;
        //將陣列資料進行交換（打散）
		Blocks B_temp;
		strcpy(B_temp.letter,block[n1].letter);
		strcpy(block[n1].letter,block[n2].letter);
		strcpy(block[n2].letter,B_temp.letter);
    }
    //for(int i=0;i<100;i++)printf("%s\n",block[i].word);
    for(int i=0;i<100;i++)strcpy(bag.letters[i],block[i].letter);
    
    printf("玩家人數:");
	scanf("%d",&player);
	if(player==4){
    	
    	int draw_num=0;
		bag.num+=player*3;
    	for(int i=0;i<player*3;i++)strcpy(bag.letters[i],"No");
		Players A,B,C,D;
		A.hands[0]=0;
		A.hands[1]=1;
		A.hands[2]=2;
		A.time=0;
		A.score=0;
		B.hands[0]=3;
		B.hands[1]=4;
		B.hands[2]=5;
		B.time=0;
		B.score=0;
		C.hands[0]=6;
		C.hands[1]=7;
		C.hands[2]=8;
		C.time=0;
		C.score=0;
		D.hands[0]=9;
		D.hands[1]=10;
		D.hands[2]=11;
		D.time=0;
		D.score=0;
		int boardspace=7*7+6*6; 
		int deck_num=0;
		while(1){
			draw_num+=checkhands(A,block);
			draw_num+=checkboard(A,player);
			//draw(A,draw_num);
			draw_num=0;
			draw_num+=checkhands(B,block);
			draw_num+=checkboard(B,player);
			//draw(B,draw_num);
			draw_num=0;
			draw_num+=checkhands(C,block);
			draw_num+=checkboard(C,player);
			//draw(C,draw_num);
			draw_num=0;
			draw_num+=checkhands(D,block);
			draw_num+=checkboard(D,player);
			//draw(D,draw_num);
			draw_num=0;
			if(deck_num==100||boardspace==0)break;
		}
		system("PAUSE"); 
		printf("%d %d %d %d",A.score,B.score,C.score,D.score);
		
    }
    
	system("PAUSE"); 
    return 0;

}


