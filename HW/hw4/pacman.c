#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200

typedef enum gameState{losing, onGoing, winning} GameState;
typedef enum direction{up, down, left, right, idle} Direction;

typedef struct game {
    char** grid;     // a 2-dimensional array of characters to display the game;
    int rows;        // number of rows of the grid;
    int columns;     // number of columns of the grid;
    int foodCount;   // number of remaining food in the game;
    int score;       // current score;
    GameState state; // the state of the game, one of losing, onGoing, or winning.
    char row[30];
    char col[30];
    char cover[30];
    char ghost[30];
    Direction direction[30];
    int numberofghost;
    int rowpac;
    int colpac;
    char flag[30];//@:0 X:1
    char step[30];//10步
    char time[30];//停:0 走:1
} Game;

Game* NewGame(int rows, int columns) {
    struct game *game;
    game=(struct game*)malloc(sizeof(struct game));
    game->grid=(char**)malloc(sizeof(char*)*(rows));
    for(int i=0;i<rows;i++){
        game->grid[i]=(char*)malloc(sizeof(char)*(columns));
        memset(game->grid[i],' ',columns);
    }
    game->foodCount=0;
    game->rows=rows;
    game->columns=columns;
    game->state=onGoing;
    game->score=0;
    game->numberofghost=0;
    memset(game->time,1,sizeof(game->time));
    memset(game->flag,0,sizeof(game->flag));
    memset(game->step,0,sizeof(game->step));
    return game;
}

void EndGame(Game* game) {
    for(int i=0;i<game->rows;i++){
        free(game->grid[i]);
    }
    free(game->grid);
    free(game);
}
bool AddWall(Game* game, int r, int c) {
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->grid[r][c]==' '){
        game->grid[r][c]='#';
        return true;
    }
    else return false;
}
bool AddFood(Game* game, int r, int c) {
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->grid[r][c]==' '){
        game->grid[r][c]='.';
        game->foodCount++;
        return true;
    }
    else return false;
}
bool AddPacman(Game* game, int r, int c) {
    int numberofpacman=0;
    for(int i=0;i<game->rows;i++){
        for(int j=0;j<game->columns;j++){
            if(game->grid[i][j]=='C'){
                numberofpacman++;
            }
        }
    }
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->grid[r][c]==' '&&numberofpacman==0){
        game->grid[r][c]='C';
        return true;
    }
    else return false;
}

void MovePacman(Game* game, Direction direction){  
    int a=0,b=0;
    for(int i=0;i<game->rows;i++){
        for(int j=0;j<game->columns;j++){
            if(game->grid[i][j]=='C'){
                a=i;
                b=j;
                game->rowpac=i;
                game->colpac=j;
            }
        }
    }
    if(direction==idle){
        game->score--;
    }
    else if(direction==up){
        if(a-1<0) game->score--;
        else if(game->grid[a-1][b]=='#') game->score--;
        else if(game->grid[a-1][b]==' '){
            game->grid[a][b]=' ';
            game->grid[a-1][b]='C';
            game->score--;
        }
        else if(game->grid[a-1][b]=='@'){
            game->grid[a][b]=' ';
            game->score--;
            game->state=losing;
        }
        else if(game->grid[a-1][b]=='.'){
            game->grid[a-1][b]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=FOOD_SCORE-1;
            if(game->foodCount==0){
                game->state=winning;
            }    
        }
        else if(game->grid[a-1][b]=='o'){//吃到能量豆
            game->grid[a-1][b]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=49;
            for(int i=0;i<game->numberofghost;i++){
                game->step[i]=10;//接下来的10步
                game->flag[i]=1;//表示@要变成X
            } 
        }
        else if(game->grid[a-1][b]=='X'){//吃掉X
            game->grid[a-1][b]='C';
            game->grid[a][b]=' ';
            game->score+=199;
            for(int i=0;i<game->numberofghost;i++){
                if(game->row[i]==a-1&&game->col[i]==b){
                    game->ghost[i]=-1;
                    if(game->cover[i]=='.'){
                        game->score+=10;
                        game->foodCount--;
                    }
                    else if(game->cover[i]=='o'){
                        game->score+=50;
                        game->foodCount--;
                        for(int i=0;i<game->numberofghost;i++) game->step[i]=10;
                    }
                }
            }
        }
    }
    else if(direction==down){
        if(a+1>=game->rows) game->score--;
        else if(game->grid[a+1][b]=='#') game->score--;
        else if(game->grid[a+1][b]==' '){
            game->grid[a][b]=' ';
            game->grid[a+1][b]='C';
            game->score--;
        }
        else if(game->grid[a+1][b]=='@'){
            game->grid[a][b]=' ';
            game->score--;
            game->state=losing;
        }
        else if(game->grid[a+1][b]=='.'){
            game->grid[a+1][b]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=FOOD_SCORE-1;
            if(game->foodCount==0){
                game->state=winning;
            }    
        }
        else if(game->grid[a+1][b]=='o'){//吃到能量豆
            game->grid[a+1][b]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=49;
            for(int i=0;i<game->numberofghost;i++){
                game->step[i]=10;//接下来的10步
                game->flag[i]=1;//表示@要变成X
            }
        }
        else if(game->grid[a+1][b]=='X'){//吃掉X
            game->grid[a+1][b]='C';
            game->grid[a][b]=' ';
            game->score+=199;
            for(int i=0;i<game->numberofghost;i++){
                if(game->row[i]==a+1&&game->col[i]==b){
                    game->ghost[i]=-1;
                    if(game->cover[i]=='.'){
                        game->score+=10;
                        game->foodCount--;
                    }
                    else if(game->cover[i]=='o'){
                        game->score+=50;
                        game->foodCount--;
                        for(int i=0;i<game->numberofghost;i++) game->step[i]=10;
                    }
                }
            }
        }
    }   
    else if(direction==left){
        if(b-1<0) game->score--;
        else if(game->grid[a][b-1]=='#') game->score--;
        else if(game->grid[a][b-1]==' '){
            game->grid[a][b]=' ';
            game->grid[a][b-1]='C';
            game->score--;
        }
        else if(game->grid[a][b-1]=='@'){
            game->grid[a][b]=' ';
            game->score--;
            game->state=losing;
        }
        else if(game->grid[a][b-1]=='.'){
            game->grid[a][b-1]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=FOOD_SCORE-1;
            if(game->foodCount==0){
                game->state=winning;
            }    
        }
        else if(game->grid[a][b-1]=='o'){//吃到能量豆
            game->grid[a][b-1]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=49;;
            for(int i=0;i<game->numberofghost;i++){
                game->step[i]=10;//接下来的10步
                game->flag[i]=1;//表示@要变成X
            }
        }
        else if(game->grid[a][b-1]=='X'){//吃掉X
            game->grid[a][b-1]='C';
            game->grid[a][b]=' ';
            game->score+=199;
            for(int i=0;i<game->numberofghost;i++){
                if(game->row[i]==a&&game->col[i]==b-1){
                    game->ghost[i]=-1;
                    if(game->cover[i]=='.'){
                        game->score+=10;
                        game->foodCount--;
                    }
                    else if(game->cover[i]=='o'){
                        game->score+=50;
                        game->foodCount--;
                        for(int i=0;i<game->numberofghost;i++) game->step[i]=10;
                    }
                }
            }
        }
    }
    else if(direction==right){
        if(b+1>=game->columns) game->score--;
        else if(game->grid[a][b+1]=='#') game->score--;
        else if(game->grid[a][b+1]==' '){
            game->grid[a][b]=' ';
            game->grid[a][b+1]='C';
            game->score--;
        }
        else if(game->grid[a][b+1]=='@'){
            game->grid[a][b]=' ';
            game->score--;
            game->state=losing;
        }
        else if(game->grid[a][b+1]=='.'){
            game->grid[a][b+1]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=FOOD_SCORE-1;
            if(game->foodCount==0){
                game->state=winning;
            }    
        }
        else if(game->grid[a][b+1]=='o'){//吃到能量豆
            game->grid[a][b+1]='C';
            game->grid[a][b]=' ';
            game->foodCount--;
            game->score+=49;
            for(int i=0;i<game->numberofghost;i++){
                game->step[i]=10;//接下来的10步
                game->flag[i]=1;//表示@要变成X
            }
        }
        else if(game->grid[a][b+1]=='X'){//吃掉X
            game->grid[a][b+1]='C';
            game->grid[a][b]=' ';
            game->score+=199;
            for(int i=0;i<game->numberofghost;i++){
                if(game->row[i]==a&&game->col[i]==b+1){
                    game->ghost[i]=-1;
                    if(game->cover[i]=='.'){
                        game->score+=10;
                        game->foodCount--;
                    }
                    else if(game->cover[i]=='o'){
                        game->score+=50;
                        game->foodCount--;
                        for(int i=0;i<game->numberofghost;i++) game->step[i]=10;
                    }
                }
            }
        }
    }
    return; // This is incorrect.
}
//////////////////////// PART B ////////////////////////
bool AddGhost(Game* game, int r, int c, Direction direction) {
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->numberofghost<30&&game->grid[r][c]==' '){
        game->grid[r][c]='@';
        game->row[game->numberofghost]=r;
        game->col[game->numberofghost]=c;
        game->cover[game->numberofghost]=' ';
        game->direction[game->numberofghost]=direction;
        game->ghost[game->numberofghost]=game->numberofghost;
        game->numberofghost++;
        return true;
    }
    else if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->numberofghost<30&&game->grid[r][c]=='.'){
        game->grid[r][c]='@';
        game->row[game->numberofghost]=r;
        game->col[game->numberofghost]=c;
        game->cover[game->numberofghost]='.';
        game->direction[game->numberofghost]=direction;
        game->ghost[game->numberofghost]=game->numberofghost;
        game->numberofghost++;
        return true;
    }
    else if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->numberofghost<30&&game->grid[r][c]=='o'){
        game->grid[r][c]='@';
        game->row[game->numberofghost]=r;
        game->col[game->numberofghost]=c;
        game->cover[game->numberofghost]='o';
        game->direction[game->numberofghost]=direction;
        game->ghost[game->numberofghost]=game->numberofghost;
        game->numberofghost++;
        return true;
    }
    else return false; // This is not always correct.
}

// Moves all ghosts in their own directions.
void MoveGhosts(Game* game) {
    for(int i=0;i<game->numberofghost;i++){
        if(game->direction[i]==up&&game->ghost[i]>=0){//下一步向上
            if(game->flag[i]==0){//鬼是@的情况    
                if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='X')&&(game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X')){
                    game->grid[game->row[i]][game->col[i]]='@';
                    game->direction[i]=down;//停在原处
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='X')&&game->grid[game->row[i]+1][game->col[i]]==' '){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]=' ';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='X')&&game->grid[game->row[i]+1][game->col[i]]=='.'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]='.';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='X')&&game->grid[game->row[i]+1][game->col[i]]=='o'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]='o';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='X')&&game->grid[game->row[i]+1][game->col[i]]=='C'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]==' '){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='.'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='o'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='C'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
            }
            else if(game->flag[i]==1&&game->time[i]==1&&game->step[i]>0){//鬼是X且运动的情况    
                if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='@')&&(game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@')){
                    game->direction[i]=down;//停在原处
                    game->grid[game->row[i]][game->col[i]]='X';
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='@')&&game->grid[game->row[i]+1][game->col[i]]==' '){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]=' ';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='@')&&game->grid[game->row[i]+1][game->col[i]]=='.'){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]='.';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='@')&&game->grid[game->row[i]+1][game->col[i]]=='o'){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=down;
                    game->cover[i]='o';
                    game->row[i]++;
                }
                else if((game->row[i]==0||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='@')&&game->grid[game->row[i]+1][game->col[i]]=='C'){
                    game->grid[game->row[i]+1][game->col[i]]='C';//C把X吃掉了
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]==' '){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='.'){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='o'){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->row[i]--;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='C'){
                    game->grid[game->row[i]-1][game->col[i]]='C';
                    game->grid[game->row[i]][game->col[i]]=' ';
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                game->step[i]--;
                game->time[i]=0;//下轮该停了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
            else if(game->flag[i]==1&&game->time[i]==0&&game->step[i]>0){//鬼是X且静止的情况
                game->step[i]--;
                game->time[i]=1;//下轮该走了
                if(game->step[i]==0){
                    game->flag[i]=0;
                    game->time[i]=1;
                } 
            }
        }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////    
        else if(game->direction[i]==down&&game->ghost[i]>=0){//下一步向下
            if(game->flag[i]==0){//鬼是@的情况    
                if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='X')&&(game->rows==1||game->grid[game->row[i]-1][game->col[i]]=='@'||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='X')){
                    game->grid[game->row[i]][game->col[i]]='@';
                    game->direction[i]=up;//停在原处
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='X')&&game->grid[game->row[i]-1][game->col[i]]==' '){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]=' ';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='X')&&game->grid[game->row[i]-1][game->col[i]]=='.'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]='.';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='X')&&game->grid[game->row[i]-1][game->col[i]]=='o'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]='o';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='@'||game->grid[game->row[i]+1][game->col[i]]=='X')&&game->grid[game->row[i]-1][game->col[i]]=='C'){
                    game->grid[game->row[i]-1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]==' '){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]=='.'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]=='o'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]-1][game->col[i]]=='C'){
                    game->grid[game->row[i]+1][game->col[i]]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
            }
            else if(game->flag[i]==1&&game->time[i]==1&&game->step[i]>0){//鬼是X且运动的情况    
                if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='@')&&(game->rows==1||game->grid[game->row[i]-1][game->col[i]]=='X'||game->grid[game->row[i]-1][game->col[i]]=='#'||game->grid[game->row[i]-1][game->col[i]]=='@')){
                    game->direction[i]=up;//停在原处
                    game->grid[game->row[i]][game->col[i]]='X';
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='@')&&game->grid[game->row[i]-1][game->col[i]]==' '){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]=' ';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='@')&&game->grid[game->row[i]-1][game->col[i]]=='.'){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]='.';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='@')&&game->grid[game->row[i]-1][game->col[i]]=='o'){
                    game->grid[game->row[i]-1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=up;
                    game->cover[i]='o';
                    game->row[i]--;
                }
                else if((game->row[i]==game->rows-1||game->grid[game->row[i]+1][game->col[i]]=='#'||game->grid[game->row[i]+1][game->col[i]]=='X'||game->grid[game->row[i]+1][game->col[i]]=='@')&&game->grid[game->row[i]-1][game->col[i]]=='C'){
                    game->grid[game->row[i]-1][game->col[i]]='C';//C把X吃掉了
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]==' '){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]=='.'){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]=='o'){
                    game->grid[game->row[i]+1][game->col[i]]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->row[i]++;
                }
                else if(game->grid[game->row[i]+1][game->col[i]]=='C'){
                    game->grid[game->row[i]+1][game->col[i]]='C';
                    game->grid[game->row[i]][game->col[i]]=' ';
                    game->score+=200;
                    game->ghost[i]=-1;//该鬼失效
                }
                game->step[i]--;
                game->time[i]=0;//下轮该停了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
            else if(game->flag[i]==1&&game->time[i]==0&&game->step[i]>0){//鬼是X且静止的情况
                game->step[i]--;
                game->time[i]=1;//下轮该走了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if(game->direction[i]==left&&game->ghost[i]>=0){//下一步向左
            if(game->flag[i]==0){//鬼是@的情况     
                if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='X')&&(game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X')){
                    game->grid[game->row[i]][game->col[i]]='@';
                    game->direction[i]=right;//停在原处
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='X')&&game->grid[game->row[i]][game->col[i]+1]==' '){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]=' ';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='X')&&game->grid[game->row[i]][game->col[i]+1]=='.'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]='.';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='X')&&game->grid[game->row[i]][game->col[i]+1]=='o'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]='o';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='X')&&game->grid[game->row[i]][game->col[i]+1]=='C'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]==' '){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='.'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='o'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='C'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
            }
            else if(game->flag[i]==1&&game->time[i]==1&&game->step[i]>0){//鬼是X且运动的情况    
                if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='@')&&(game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@')){
                    game->direction[i]=right;//停在原处
                    game->grid[game->row[i]][game->col[i]]='X';
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='@')&&game->grid[game->row[i]][game->col[i]+1]==' '){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]=' ';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='@')&&game->grid[game->row[i]][game->col[i]+1]=='.'){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]='.';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='@')&&game->grid[game->row[i]][game->col[i]+1]=='o'){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=right;
                    game->cover[i]='o';
                    game->col[i]++;
                }
                else if((game->col[i]==0||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='@')&&game->grid[game->row[i]][game->col[i]+1]=='C'){
                    game->grid[game->row[i]][game->col[i]+1]='C';//C把X吃掉了
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]==' '){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='.'){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='o'){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->col[i]--;
                }
                else if(game->grid[game->row[i]][game->col[i]-1]=='C'){
                    game->grid[game->row[i]][game->col[i]-1]='C';
                    game->grid[game->row[i]][game->col[i]]=' ';
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                game->step[i]--;
                game->time[i]=0;//下轮该停了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
            else if(game->flag[i]==1&&game->time[i]==0&&game->step[i]>0){//鬼是X且静止的情况
                game->step[i]--;
                game->time[i]=1;//下轮该走了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if(game->direction[i]==right&&game->ghost[i]>=0){//下一步向右
            if(game->flag[i]==0){//鬼是@的情况     
                if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='X')&&(game->columns==1||game->grid[game->row[i]][game->col[i]-1]=='@'||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='X')){
                    game->grid[game->row[i]][game->col[i]]='@';
                    game->direction[i]=left;//停在原处
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='X')&&game->grid[game->row[i]][game->col[i]-1]==' '){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]=' ';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='X')&&game->grid[game->row[i]][game->col[i]-1]=='.'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]='.';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='X')&&game->grid[game->row[i]][game->col[i]-1]=='o'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]='o';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='@'||game->grid[game->row[i]][game->col[i]+1]=='X')&&game->grid[game->row[i]][game->col[i]-1]=='C'){
                    game->grid[game->row[i]][game->col[i]-1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]==' '){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='.'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='o'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='C'){
                    game->grid[game->row[i]][game->col[i]+1]='@';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->state=losing;
                }
            }
            else if(game->flag[i]==1&&game->time[i]==1&&game->step[i]>0){//鬼是X且运动的情况    
                if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='@')&&(game->columns==1||game->grid[game->row[i]][game->col[i]-1]=='X'||game->grid[game->row[i]][game->col[i]-1]=='#'||game->grid[game->row[i]][game->col[i]-1]=='@')){
                    game->direction[i]=left;//停在原处
                    game->grid[game->row[i]][game->col[i]]='X';
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='@')&&game->grid[game->row[i]][game->col[i]-1]==' '){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]=' ';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='@')&&game->grid[game->row[i]][game->col[i]-1]=='.'){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]='.';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='@')&&game->grid[game->row[i]][game->col[i]-1]=='o'){
                    game->grid[game->row[i]][game->col[i]-1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->direction[i]=left;
                    game->cover[i]='o';
                    game->col[i]--;
                }
                else if((game->col[i]==game->columns-1||game->grid[game->row[i]][game->col[i]+1]=='#'||game->grid[game->row[i]][game->col[i]+1]=='X'||game->grid[game->row[i]][game->col[i]+1]=='@')&&game->grid[game->row[i]][game->col[i]-1]=='C'){
                    game->grid[game->row[i]][game->col[i]-1]='C';//C把X吃掉了
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]==' '){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]=' ';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='.'){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='.';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='o'){
                    game->grid[game->row[i]][game->col[i]+1]='X';
                    game->grid[game->row[i]][game->col[i]]=game->cover[i];
                    game->cover[i]='o';
                    game->col[i]++;
                }
                else if(game->grid[game->row[i]][game->col[i]+1]=='C'){
                    game->grid[game->row[i]][game->col[i]+1]='C';
                    game->grid[game->row[i]][game->col[i]]=' ';
                    game->score+=200;
                    game->ghost[i]=-1;
                }
                game->step[i]--;
                game->time[i]=0;//下轮该停了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
            else if(game->flag[i]==1&&game->time[i]==0&&game->step[i]>0){//鬼是X且静止的情况
                game->step[i]--;
                game->time[i]=1;//下轮该走了
                if(game->step[i]==0){
                    game->flag[i]=0;//走10步之后变回@
                    game->time[i]=1;
                } 
            }
        }
    }
    return; // This is incorrect.
}
bool AddCapsule(Game *game, int r, int c) {
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->grid[r][c]==' '){
       game->grid[r][c]='o';
       game->foodCount++;
       return true; 
    }
    if(r>=0&&r<game->rows&&c>=0&&c<game->columns&&game->grid[r][c]=='.'){
       game->grid[r][c]='o';
       return true; 
    }
    else return false; // This is not always correct.
}
///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PlayGame(Game* game);

int main(){

       Game *game = NewGame(20, 20);
   // test pacman
   for (int i = 0; i < 3; i++) {
       AddFood(game, i, 0);
       AddFood(game, i, 2);
   }
   AddPacman(game, 3, 0);
   AddFood(game, 3, 2);
   AddFood(game, 0, 1);
   AddFood(game, 3, 1);
   AddWall(game, 1, 1);
   AddWall(game, 2, 1);
   AddGhost(game, 0, 0, up);
   AddCapsule(game, 3, 2);
   AddCapsule(game, 2, 2);
   // test ghost
   for (int i = 0; i < 3; i++) {
       AddFood(game, i, 0);
       AddFood(game, i, 2);
   }
   AddPacman(game, 3, 0);
   AddFood(game, 3, 2);
   AddFood(game, 0, 1);
   AddFood(game, 3, 1);
   AddWall(game, 1, 1);
   AddWall(game, 2, 1);
   AddGhost(game, 0, 2, up);
   AddGhost(game, 0, 2, down);
   AddCapsule(game, 1, 0);
   AddCapsule(game, 2, 0);
   // large test
   for (int i = 0; i < 20; i++) {
       for (int j = 0; j < 19; j++) {
           if (i == 7 && j == 7)
               AddPacman(game, i, j);
           else if (i & 1 || j == 3 || j == 5) {
               AddFood(game, i, j);
               // if (i==j&&i!=1) AddGhost(game,i,j,down);
           } else
               AddWall(game, i, j);
       }
   }
   AddGhost(game, 2, 3, up);
   AddGhost(game, 3, 2, left);
   AddGhost(game, 3, 1, left);
   AddGhost(game, 3, 0, left);
   AddGhost(game, 5, 0, right);
   AddGhost(game, 19, 19, down);
   AddGhost(game, 11, 0, right);
   AddCapsule(game, 5, 5);
   AddCapsule(game, 6, 5);
   AddCapsule(game, 7, 5);
    

    // Game* game = NewGame(8, 8);
    // AddWall(game,1,2);
    // AddWall(game,3,3);
    // AddWall(game,7,5);
    // AddWall(game,6,5);
    // AddWall(game,5,5);
    // AddWall(game,4,5);
    // AddWall(game,3,3);
    // AddFood(game,3,4);
    // AddFood(game,3,6);
    // AddFood(game,3,7);
    // AddFood(game,4,6);
    // AddPacman(game,3,2);
    // AddGhost(game,0,2,right);
    // AddGhost(game,1,4,left);
    // AddGhost(game,1,3,up);
    // AddGhost(game,5,2,up);
    // AddGhost(game,2,2,left);
    // AddGhost(game,4,3,down);
    // AddGhost(game,6,7,up);
    // AddCapsule(game,2,7);
    // AddCapsule(game,3,1);
    // AddCapsule(game,2,1);
    
    
    
    
  // Game* game = NewGame(8, 8);     
//     AddWall(game, 0, 0);AddWall(game, 0, 2);
//  AddWall(game, 1, 2);AddWall(game, 1, 3);AddWall(game, 1, 5);AddWall(game, 1, 6);AddWall(game, 1, 7);
//   AddWall(game, 2, 0);AddWall(game, 2, 7);
//   AddWall(game, 3, 0);AddWall(game, 3, 1);AddWall(game, 3, 5);
// AddWall(game, 4, 1);AddWall(game, 4, 3);AddWall(game, 4, 5);AddWall(game, 4, 6);AddWall(game, 4, 7);
// AddWall(game, 5, 3);
//  AddWall(game, 6, 2);AddWall(game, 6, 3);AddWall(game, 6, 4);AddWall(game, 6, 6);
// AddWall(game, 7, 0);AddWall(game, 7, 6);
 
//  AddFood(game, 0, 1);AddFood(game, 0, 3);AddFood(game, 0, 6);AddFood(game, 0, 7);
//  AddFood(game, 1, 0);AddFood(game, 1, 1);AddFood(game, 1, 4);
//  AddFood(game, 2, 3);AddFood(game, 2, 4);AddFood(game, 2, 5);AddFood(game, 2, 6);
//  AddFood(game, 3, 2);AddFood(game, 3, 3);AddFood(game, 3, 4);AddFood(game, 3, 6);AddFood(game, 3, 7);
//  AddFood(game, 4, 0);AddFood(game, 4, 2);AddFood(game, 4, 4);
//  AddFood(game, 5, 1);AddFood(game, 5, 2);AddFood(game, 5, 5);AddFood(game, 5, 6);AddFood(game, 5, 7);
//  AddFood(game, 6, 0);AddFood(game, 6, 1);AddFood(game, 6, 5);AddFood(game, 6, 7);
//  AddFood(game, 7, 1);AddFood(game, 7, 2);AddFood(game, 7, 3);AddFood(game, 7, 4);AddFood(game, 7, 7);

//  AddPacman(game, 7, 5);
// AddCapsule(game,7,4);
//  AddCapsule(game, 0, 5);
// AddCapsule(game, 2, 2);
//  AddCapsule(game, 5, 0);AddCapsule(game, 5, 4);
// AddGhost(game,0,5,left);
// AddGhost(game, 0, 4,left);
//  AddGhost(game, 2, 1, right);
//  AddGhost(game,2,3,right);


// Game* game = NewGame(9, 18);
// AddPacman(game, 7, 5);

//  AddCapsule(game, 2, 2);
//  AddCapsule(game, 3, 17);
// AddCapsule(game, 5, 4);
//  AddCapsule(game, 7, 10);

// AddGhost(game, 0, 4, up);
//  AddGhost(game, 2, 17, up);
//  AddGhost(game, 3, 6, left);
//  AddGhost(game,3,5,left);
//  AddGhost(game, 5, 9, right);

// AddWall(game, 0, 0);AddWall(game, 0, 2);AddFood(game, 0, 5);AddWall(game, 0, 9);AddWall(game, 0, 10);AddFood(game, 0, 12);AddWall(game, 0, 14);AddWall(game, 0, 16);AddWall(game, 0, 17);
//  AddWall(game, 1, 2);AddWall(game, 1, 3);AddWall(game, 1, 5);AddWall(game, 1, 6);AddWall(game, 1, 7);AddWall(game, 1, 12);AddWall(game, 1, 14);
//  AddWall(game, 2, 0);AddWall(game, 2, 7);AddWall(game, 2, 8);AddWall(game, 2, 9);AddWall(game, 2, 10);AddWall(game, 2, 12);AddWall(game, 2, 14);
// AddWall(game, 3, 0);AddWall(game, 3, 1);AddWall(game, 3, 16);
//  AddWall(game, 4, 1);AddWall(game, 4, 3);AddWall(game, 4, 5);AddWall(game, 4, 6);AddWall(game, 4, 7);AddWall(game, 4, 8);AddWall(game, 4, 9);AddWall(game, 4, 10);AddWall(game, 4, 11);AddWall(game, 4, 12);AddWall(game, 4, 13);AddWall(game, 4, 15);AddWall(game, 4, 16);
//  AddWall(game, 5, 3);AddWall(game, 5, 13);AddWall(game, 5, 16);
//  AddWall(game, 6, 2);AddWall(game, 6, 3);AddWall(game, 6, 4);AddWall(game, 6, 6);AddWall(game, 6, 16);
//  AddWall(game, 7, 0);AddWall(game, 7, 6);AddWall(game, 7, 8);AddWall(game, 7, 9);AddWall(game, 7, 11);AddWall(game, 7, 12);AddWall(game, 7, 14);
//  AddWall(game, 8, 4);AddWall(game, 8, 6);AddWall(game, 8, 9);AddWall(game, 8, 14);

// AddFood(game, 0, 1);AddFood(game, 0, 3);AddFood(game, 0, 6);AddFood(game, 0, 7);AddFood(game, 0, 8);AddFood(game, 0, 11);AddFood(game, 0, 13);AddFood(game, 0, 15);
//  AddFood(game, 1, 0);AddFood(game, 1, 1);AddFood(game, 1, 4);AddFood(game, 1, 8);AddFood(game, 1, 9);AddFood(game, 1, 10);AddFood(game, 1, 11);AddFood(game, 1, 13);AddFood(game, 1, 15);AddFood(game, 1, 16);AddFood(game, 1, 17);
//  AddFood(game, 2, 1);AddFood(game, 2, 3);AddFood(game, 2, 4);AddFood(game, 2, 5);AddFood(game, 2, 6);AddFood(game, 2, 11);AddFood(game, 2, 13);AddFood(game, 2, 15);AddFood(game, 2, 16);
//  AddFood(game, 3, 2);AddFood(game, 3, 3);AddFood(game, 3, 4);AddFood(game, 3, 6);AddFood(game, 3, 7);AddFood(game, 3, 8);AddFood(game, 3, 9);AddFood(game, 3, 10);AddFood(game, 3, 11);AddFood(game, 3, 12);AddFood(game, 3, 13);AddFood(game, 3, 14);AddFood(game, 3, 15);
//  AddFood(game, 4, 0);AddFood(game, 4, 2);AddFood(game, 4, 4);AddFood(game, 4, 13);AddFood(game, 4, 14);AddFood(game, 4, 17);
//  AddFood(game, 5, 1);AddFood(game, 5, 2);AddFood(game, 5, 0);AddFood(game, 5, 5);AddFood(game, 5, 6);AddFood(game, 5, 7);AddFood(game, 5, 8);AddFood(game, 5, 10);AddFood(game, 5, 11);AddFood(game, 5, 12);AddFood(game, 5, 13);AddFood(game, 5, 14);AddFood(game, 5, 15);AddFood(game, 5, 17);
//  AddFood(game, 6, 0);AddFood(game, 6, 1);AddFood(game, 6, 5);AddFood(game, 6, 7);AddFood(game, 6, 8);AddFood(game, 6, 9);AddFood(game, 6, 10);AddFood(game, 6, 11);AddFood(game, 6, 12);AddFood(game, 6, 13);AddFood(game, 6, 14);AddFood(game, 6, 15);AddFood(game, 6, 17);
// AddFood(game, 7, 1);AddFood(game, 7, 2);AddFood(game, 7, 3);AddFood(game, 7, 4);AddFood(game, 7, 7);AddFood(game, 7, 13);AddFood(game, 7, 15);AddFood(game, 7, 16);AddFood(game, 7, 17);
// AddFood(game, 8, 0);AddFood(game, 8, 1);AddFood(game, 8, 2);AddFood(game, 8, 3);AddFood(game, 8, 5);AddFood(game, 8, 7);AddFood(game, 8, 8);AddFood(game, 8, 10);AddFood(game, 8, 11);AddFood(game, 8, 12);AddFood(game, 8, 13);AddFood(game, 8, 15);AddFood(game, 8, 16);AddFood(game, 8, 17);




    PlayGame(game);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game* game){
    if(!game || !game->grid) return;

// If Windows, clear console.
#ifdef _WIN32 
    system("cls");
#else
// Clears terminal screen
    fflush(stdout);
    system("clear");
#endif
    
    // The game grid
    printf(" ");
    for(int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for(int i = 0; i < game->rows; i++){
        printf("|");
        for(int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for(int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch(game->state){
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

/* Plays the game, and calls EndGame on winning or losing.
 */
void PlayGame(Game* game){
    
    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while(true){
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf("%[^\n]", input);
        // Handles the '\n'.
        getchar();
        Direction direction;
        switch(input[0]){
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if(game->state != onGoing){
            break;
        }
        
        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman.
        if(game->state != onGoing){
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}
