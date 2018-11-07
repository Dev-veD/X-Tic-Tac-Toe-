#include<bits/stdc++.h>

using namespace std;

//X=1,O=-1,empty_place=0 in tic
int tic[3][3],x=20,y=20,me,foe,cx,cy,mkmovx,mkmovy;//tic is computational board
string tac[20][20];//display board

//This Is To Draw on The Screen
int init(){
for(int i=0;i<y;i++){
    for(int j=0;j<x;j++)
    {
    if(j==x/3||j==2*x/3)\
        tac[i][j]="|";
    else if(i==y/3||i==2*y/3)
        tac[i][j]="--";
    else
        tac[i][j]="  ";
    }
}
for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    tic[i][j]=0;
return 0;
}
void draw(){
    cout<<"\tUNBEATABLE TIC-TAC-TOE\nYou : O\nMachine : X\n\n";
for(int i=0;i<y;i++)
{
    for(int j=0;j<x;j++)
        {
            cout<<tac[i][j];
        }
    cout<<endl;
}
}
int ticxtac(int j){
    if(j==0)
        return 3;
    else if(j==1)
        return 10;
    else
        return 16;

}
int ticytac(int i){
if(i==0)
    return 3;
else if(i==1)
    return 10;
else
    return 16;
}
void num_tic(int n){
switch (n){
case 1:
    cy=2,cx=0;
    break;
case 2:
    cy=2,cx=1;

    break;
case 3:
    cy=2,cx=2;
    break;
case 4 :
    cy=1,cx=0;
    break;
case 5 :
    cy=1,cx=1;
    break;
case 6 :
    cy=1,cx=2;
    break;
case 7:
    cy=0,cx=0;
    break;
case 8:
    cy=0,cx=1;
    break;
case 9 :
    cy=0,cx=2;
    break;

}
}

//This fills both the Computing Board as well as the Display Board
void fillit(int x,int y,bool pcturn){
if(pcturn)
{
    tac[ticytac(y)][ticxtac(x)]="X ";
    tic[y][x]=1;
}
else
{
    tac[ticytac(y)][ticxtac(x)]="O ";
    tic[y][x]=-1;
}
}

//This Is Going To be The AI part :
bool moveleft(){
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++)
          if(tic[i][j]==0)
            return true;
    }
return false;
}


int heuristic(){//This Check for win or loss current state of board
//Column Check
for(int i=0;i<3;i++)
    if(tic[0][i]==tic[1][i]&&tic[1][i]==tic[2][i])
    {if(tic[0][i]==foe )
        return -100;
    else if(tic[0][i]==me)
        return 100;
    }
//Row Check
for(int i=0;i<3;i++)
    if(tic[i][0]==tic[i][1]&&tic[i][1]==tic[i][2])
    {if(tic[i][0]==foe )
        return -100;
    else if(tic[i][1]==me)
        return 100;
    }
//Diagonals Check

if(tic[0][0]==tic[1][1]&&tic[1][1]==tic[2][2])
    {if(tic[0][0]==foe)
    return -100;
    else if(tic[1][1]==me)
    return 100;
    }
if(tic[2][0]==tic[1][1]&&tic[1][1]==tic[0][2])
    {if(tic[1][1]==foe)
    return -100;
    else if(tic[1][1]==me)
    return 100;

    }

return 0;
}

int mimax(int dep,bool myturn){
//cout<<"mimaxhere"<<endl;
int n=heuristic();
//cout<<"Mimax here too\n"<<n<<endl;
if(n==100)
    return 100;

if(n==-100)
    return -100;

if(moveleft()==false)
    return 0;

if(myturn==true){
    int score=INT_MIN;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tic[i][j]==0){
                tic[i][j]=me;
                 score=max(score,mimax(dep+1,!myturn)-dep);
                //cout<<"This Is Pc score : "<<score<<endl;
                tic[i][j]=0;
            }
        }
    }
    return score;
}
else{
    int score=INT_MAX;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tic[i][j]==0){
                tic[i][j]=foe;
                score=min(score,mimax(dep+1,!myturn)-dep);
                //cout<<"This Is Me score : "<<score<<endl;
                tic[i][j]=0;
            }
        }
    }
    return score;
}

}

void themove(){
mkmovx=-1;
mkmovy=-1;
int score=INT_MIN;
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        if(tic[i][j]==0){
            tic[i][j]=me;
            int crrsco=mimax(0,false);
            tic[i][j]=0;//reversing move
            //cout<<"for i , j "<<i<<" "<<j<<" score is "<<crrsco<<endl;
        if(crrsco>score)
            {
                score=crrsco;
                mkmovx=j;
                mkmovy=i;
            }

        }
    }
}

}
void pc_play(){
themove();
fillit(mkmovx,mkmovy,true);
}
//int arr[10]={0};
void me_play(){
int n;
do{
fflush(stdin);
cin>>n;
num_tic(n);
if(tic[cy][cx]!=0)
    cout<<"Invalid move\n";
}while(tic[cy][cx]!=0);
fillit(cx,cy,false);
}
void play(){
cout<<"Enter At Your Own Risk \n";
cout<<"Following Game Will Destroy Your Human EGo\n";
cout<<"Can You Win?? Against This ....\n";
cout<<"I Don't Think So....\n\n\n\n\n\n\n\n\n";
system("pause");
system("cls");

cout<<"\n\n\n\n\t\t\t\t\t\tHOW TO PLAY : \n\n\n\n";
cout<<"\t Use Numpad To Enter your Choice Of Block as They are Arranged in Same Way As A Tic-Tac-Toe Board\n";
for(int i=0;i<10;i++)
cout<<"\n\n";
system("pause");
system("cls");
for(int i=0;i<5;i++){
        draw();
me_play();
if(heuristic()==-100)
{
        system("cls");
        draw();
        cout<<"Congrats You Won ,\nI Under-estimated You\n\n";
        system("pause");
        return ;
}
pc_play();
if(heuristic()==100)
{
    system("cls");
    draw();
    cout<<"You Lost Your Machine Won, Guess Its better than You\n\n";
    system("pause");
    return ;
}
if(!moveleft())
{
    system("cls");
    draw();
    cout<<"As Always You Didn't Win\nPoor You\n";
    cout<<"Its a Tie\n\n";
    system("pause");
    return ;
}
system("cls");
}
}
int main(){
    char y='p';
    while(y!=48){
    me=1,foe=-1;
    init();
    play();
    init();
    system("cls");
    draw();
    cout<<"Would You Like To Try again enter any key except 0";
    cin>>y;
    system("cls");
    }

}
