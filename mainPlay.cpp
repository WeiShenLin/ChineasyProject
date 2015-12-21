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
    char hands[3][3];
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

void drawone(Players player,int draw_place){
	for(int i=0;i<100;i++){
		if(strcmp(bag.letters[i],"No"))strcpy(player.hands[draw_place],bag.letters[i]);
	}
	bag.num++;
}
void draw(Players player){
	for(int i=0;i<3;i++){
		if(strcmp(player.hands[i],"No"))drawone(player,i);
	}
}

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

void putbag(char hand1[3],char hand2[3]){
	strcpy(bag.letters[bag.num-1],hand1);
	strcpy(bag.letters[bag.num-2],hand2);
	bag.num-=2;
	shufflebag();
	
}
int checklayer2(int row , int col){
	if(!strcmp(board.layer1_letters[row][col],"No")||!strcmp(board.layer1_letters[row+1][col],"No")||!strcmp(board.layer1_letters[row][col+1],"No")||!strcmp(board.layer1_letters[row+1][col+1],"No"))return 0;
	else return 1;
}
int checkhands(Players player){
	FILE *fp;
	char W_temp[50][5];
	int word_num=0;
	char word[6][5];
	strcpy(word[0],player.hands[0]);
	strcat(word[0],player.hands[1]);
	strcpy(word[1],player.hands[0]);
	strcat(word[1],player.hands[2]);
	strcpy(word[2],player.hands[1]);
	strcat(word[2],player.hands[0]);
	strcpy(word[3],player.hands[1]);
	strcat(word[3],player.hands[2]);
	strcpy(word[4],player.hands[2]);
	strcat(word[4],player.hands[0]);
	strcpy(word[5],player.hands[2]);
	strcat(word[5],player.hands[1]);
	player.time++;	
	if( ( fp = fopen("Words.csv", "r")) == NULL) 
    {
        puts("Cannot open the file");
        //system("PAUSE");
        
    }
    
    while(word_num!=50){
    	fscanf(fp,"%s",W_temp[word_num]);
    	if(!strcmp(W_temp[word_num],word[0])){
    		putbag(player.hands[0],player.hands[1]);
			strcpy(player.hands[0],"No");
    		strcpy(player.hands[1],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
    	else if(!strcmp(W_temp[word_num],word[1])){
    		putbag(player.hands[0],player.hands[2]);
			strcpy(player.hands[0],"No");
    		strcpy(player.hands[2],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[2])){
    		putbag(player.hands[1],player.hands[0]);
			strcpy(player.hands[1],"No");
    		strcpy(player.hands[0],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[3])){
    		putbag(player.hands[1],player.hands[2]);
			strcpy(player.hands[1],"No");
    		strcpy(player.hands[2],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[4])){
    		putbag(player.hands[2],player.hands[0]);
			strcpy(player.hands[2],"No");
    		strcpy(player.hands[0],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
		else if(!strcmp(W_temp[word_num],word[5])){
    		putbag(player.hands[2],player.hands[1]);
			strcpy(player.hands[2],"No");
    		strcpy(player.hands[1],"No");
    		player.score++;
    		fclose(fp);
			return 2;
    	}
		else
		    word_num++;
    }
    fclose(fp);
	return 0;
}

int checkword(char handword[3]){
	FILE *fp;
	char W_temp[50][5];
	int word_num=0;
	char word[170][5];
	int word_place=0;
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			strcpy(word[word_place],handword);
			strcpy(word[word_place],board.layer1_letters[i][j]);
			word_place++;
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			strcpy(word[word_place],handword);
			strcpy(word[word_place],board.layer2_letters[i][j]);
			word_place++;
		}
	}
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			strcpy(word[word_place],board.layer1_letters[i][j]);
			strcpy(word[word_place],handword);
			word_place++;
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			strcpy(word[word_place],board.layer2_letters[i][j]);
			strcpy(word[word_place],handword);
			word_place++;
		}
	}
	
	if( ( fp = fopen("Words.csv", "r")) == NULL) 
    {
        puts("Cannot open the file");
        //system("PAUSE");
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
    fclose(fp);
	return 0;
}

void randboard(char num[3]){
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
		if(boardlayer==1)strcpy(board.layer1_letters[board_row][board_col],num);
		else strcpy(board.layer2_letters[board_row][board_col],num);
}

int checkboard(Players player,int player_num){
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			if(!strcmp(board.layer1_letters[i][j],"No")){
				if(checkword(player.hands[0])){
					strcpy(board.layer1_letters[i][j],player.hands[0]);
					strcpy(player.hands[0],"No");
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[1])){
					strcpy(board.layer1_letters[i][j],player.hands[1]);
					strcpy(player.hands[1],"No");
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[2])){
					strcpy(board.layer1_letters[i][j],player.hands[2]);
					strcpy(player.hands[2],"No");
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
					strcpy(board.layer2_letters[i][j],player.hands[0]);
					strcpy(player.hands[0],"No");
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[1])){
					strcpy(board.layer2_letters[i][j],player.hands[1]);
					strcpy(player.hands[1],"No");
					player.score++;
					return 1;
				}
				else if(checkword(player.hands[2])){
					strcpy(board.layer2_letters[i][j],player.hands[2]);
					strcpy(player.hands[2],"No");
					player.score++;
					return 1;
				}
			}	
		}
	}
	if(strcmp(player.hands[0],"No")){	
 		randboard(player.hands[0]);
 		strcpy(player.hands[0],"No");
 		return 1;
 	}
 	else if(strcmp(player.hands[1],"No")){
 		randboard(player.hands[1]);
 		strcpy(player.hands[1],"No");
 		return 1;
 	}
	else{
 		randboard(player.hands[2]);
 		strcpy(player.hands[2],"No");
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
	
    if( ( fp = fopen("Letters_Time.csv", "r")) == NULL) 
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
		if(!strcmp(letter[count].times,"2")){
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
    
    //for(int i=0;i<100;i++)printf("%s\n",block[i].word);
    for(int i=0;i<100;i++)strcpy(bag.letters[i],block[i].letter);
    shufflebag();
    
    
    printf("玩家人數:");
	scanf("%d",&player);
	if(player==4){
    	
    	int draw_num=0;
		bag.num+=player*3;
    	for(int i=0;i<player*3;i++)strcpy(bag.letters[i],"No");
    	
		Players A,B,C,D;
		strcpy(A.hands[0],bag.letters[0]);
		strcpy(A.hands[1],bag.letters[1]);
		strcpy(A.hands[2],bag.letters[2]);
		A.time=0;
		A.score=0;
		strcpy(B.hands[0],bag.letters[3]);
		strcpy(B.hands[1],bag.letters[4]);
		strcpy(B.hands[2],bag.letters[5]);
		B.time=0;
		B.score=0;
		strcpy(C.hands[0],bag.letters[6]);
		strcpy(C.hands[1],bag.letters[7]);
		strcpy(C.hands[2],bag.letters[8]);
		C.time=0;
		C.score=0;
		strcpy(D.hands[0],bag.letters[9]);
		strcpy(D.hands[1],bag.letters[10]);
		strcpy(D.hands[2],bag.letters[11]);
		D.time=0;
		D.score=0;
		int boardspace=7*7+6*6; 
		int deck_num=0;
		while(1){
			checkhands(A);
		    checkboard(A,player);
			draw(A);
			boardspace--;
			if(deck_num==100||boardspace<=0)break;
			checkhands(B);
			checkboard(B,player);
			draw(B);
			boardspace--;
			if(deck_num==100||boardspace<=0)break;
			checkhands(C);
			checkboard(C,player);
			draw(C);
			boardspace--;
			if(deck_num==100||boardspace<=0)break;
			checkhands(D);
			checkboard(D,player);
			draw(D);
			boardspace--;
			if(bag.num>=100||boardspace<=0)break;
			
			
			
		}
		system("PAUSE"); 
		printf("%d %d %d %d",A.score,B.score,C.score,D.score);
		
    }
    
	system("PAUSE"); 
    return 0;

}


