#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

#define ROWS 20
#define COLS 15
#define TRUE 1
#define FALSE 0

char Table[ROWS][COLS] = {0};
int score = 0;
char GameOn = TRUE;
suseconds_t timer = 400000;
int decrease = 1000;

typedef struct {
	char **array;
	int width, row, col;
} Struct;
Struct current;

const Struct StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

Struct FunctionCopyShape(Struct shape)
{
	Struct new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
	int i, j;
	for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return new_shape;
}

void FunctionDeleteShape(Struct shape)
{
	int i;
	for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

int FunctionCheckPosition(Struct shape) //check position of copied shape
{
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= COLS || shape.row+i >= ROWS)){ //out of borders
				if(array[i][j]) //but is it just a phantom?
					return FALSE;
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void FunctionGetNewShape() //return s rondom shape
{
	Struct new_shape = FunctionCopyShape(StructsArray[rand()%7]);
	new_shape.col = rand()%(COLS-new_shape.width+1);
	new_shape.row = 0;
	FunctionDeleteShape(current);
	current = new_shape;
	if(!FunctionCheckPosition(current)){
		GameOn = FALSE;
	}
}

void FunctionRotateShape(Struct shape) //rotates clockwise
{
	Struct temp = FunctionCopyShape(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDeleteShape(temp);
}

void FunctionWriteToTable()
{
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Table[current.row+i][current.col+j] = current.array[i][j];
		}
	}
}

void FunctionCheckLines() 
{
	int n, m, sum, count=0;
	for(n=0;n<ROWS;n++){
		sum = 0;
		for(m=0;m< COLS;m++) {
			sum+=Table[n][m];
		}
		if(sum==COLS){
			count++;
			int l, k;
			for(k = n;k >=1;k--)
				for(l=0;l<COLS;l++)
					Table[k][l]=Table[k-1][l];
			for(l=0;l<COLS;l++)
				Table[k][l]=0;
			timer-=decrease--;
		}
	}
	score += 100*count;
}

void FunctionPrintTable(){
	char Buffer[ROWS][COLS] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<COLS-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < ROWS ;i++){
		for(j = 0; j < COLS ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", score);
}

void FunctionManipulateCurrent(int action)
{
	Struct temp = FunctionCopyShape(current);
	switch(action){
		case 's':
			temp.row++;  //move down
			if(FunctionCheckPosition(temp))
				current.row++;
			else {
				FunctionWriteToTable();
				FunctionCheckLines(); //check full lines, after putting it down
				FunctionGetNewShape();
			}
			break;
		case 'd':
			temp.col++; //move right
			if(FunctionCheckPosition(temp))
				current.col++;
			break;
		case 'a':
			temp.col--; //move left
			if(FunctionCheckPosition(temp))
				current.col--;
			break;
		case 'w':
			FunctionRotateShape(temp);
			if(FunctionCheckPosition(temp))
				FunctionRotateShape(current);
			break;
	}
	FunctionDeleteShape(temp);
	FunctionPrintTable();
}

struct timeval before_now, now;
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) - ((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

int main() {
	srand(time(0));
	score = 0;
	int c;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	FunctionGetNewShape();
	FunctionPrintTable();
	while(GameOn){
		if ((c = getch()) != ERR) {
			FunctionManipulateCurrent(c);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			before_now = now;
			FunctionManipulateCurrent('s');
		}
	}
	FunctionDeleteShape(current);
	endwin();
	printf("\nGame over!\n");
	printf("\nScore: %d\n", score);
	return 0;
}
