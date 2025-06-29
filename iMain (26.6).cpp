#include "iGraphics.h"
#include<string.h>
#include<math.h>
#include<stdlib.h>

Sprite players[6],opponents[6],gk[2],fball, fields;
Image ball[1],player[1],opponent[1],field[1]; 
double length=120*6 , width = 90*6, gallary=40;
long long int  timer=0,i,ii,gametime=0,tracktime=0;
int level;
double speed=0.6 ,gkspeed=0.35, passedballspeed=0.8, shootballspeed=1, acceleration=-0.001, varAcceleration[2];
double playerradius=8,ballradius=5,collidepos=5;
double newball[4]={width/2,length/2};
double gkpointer[2][2]={ {width/2,gallary+playerradius},{width/2,length-gallary-playerradius} };
double newgk[2][2]={ {width/2,gallary+playerradius},{width/2,length-gallary-playerradius} };
double playerposition[2][6][4]={{{width/2,length*8/10,width/2,length*8/10,}, {width/6,length*8/10,width/6,length*8/10}, {width*5/6,length*8/10,width*5/6,length*8/10},{width*2/6,length*7/10,width*2/6,length*7/10},{width*4/6,length*7/10,width*4/6,length*7/10} , {width/2,length*6/10,width/2,length*6/10} },{ {width/2,length*2/10,width/2,length*2/10},{width/6,length*2/10,width/6,length*2/10},{width*5/6,length*2/10,width*5/6,length*2/10},{width*2/6,length*7/20,width*2/6,length*7/20},{width*4/6,length*7/20,width*4/6,length*7/20} , {width/2,length/2,width/2,length/2} }};
double newplayerposition[2][6][4]={{{width/2,length*8/10,width/2,length*8/10,}, {width/6,length*8/10,width/6,length*8/10}, {width*5/6,length*8/10,width*5/6,length*8/10},{width*2/6,length*7/10,width*2/6,length*7/10},{width*4/6,length*7/10,width*4/6,length*7/10} , {width/2,length*6/10,width/2,length*6/10} },{ {width/2,length*2/10,width/2,length*2/10},{width/6,length*2/10,width/6,length*2/10},{width*5/6,length*2/10,width*5/6,length*2/10},{width*2/6,length*7/20,width*2/6,length*7/20},{width*4/6,length*7/20,width*4/6,length*7/20} , {width/2,length/2,width/2,length/2} }};
double ballpointer[4]={width/2,length/2};
int activeplayer=5,ballstate=1,ballholder=activeplayer,activeplayeropp=5,helpingplayer=4,helpingplayeropp=4;
int page_number=1,coverpagetime=100;
double dxy=30;
double positionField[2][6][4]={{{4*width/7, 3*width/7, length-gallary, length/2}, {10*width/20, gallary, length-gallary, 10*length/20}, {width-gallary, 10*width/20,  length-gallary, 10*length/20}, {10*width/20, gallary, 10*length/20, gallary}, {width-gallary, 10*width/20, 10*length/20, gallary}, {10*width/20, 10*width/20, length/2, gallary}}, {{4*width/7, 3*width/7, length/2, gallary}, {10*width/20, gallary, 10*length/20, gallary}, {width-gallary, 10*width/20, 10*length/20, gallary}, {10*width/20, gallary, length-gallary, 10*length/20}, {width-gallary, 10*width/20, length-gallary, 10*length/20}, {10*width/20, 10*width/20, length-gallary, length/2}}};
double range[2][6][2]={{{7*width/20,7*width/20},{-7*width/20,7*width/20},{7*width/20,7*width/20},{-7*width/20,-7*width/20},{7*width/20,-7*width/20},{7*width/20,-7*width/20}},{{7*width/20,-7*width/20},{-7*width/20,-7*width/20},{7*width/20,-7*width/20},{-7*width/20,7*width/20},{7*width/20,7*width/20},{7*width/20,7*width/20}}};
int dX=30, dY=50;



void resetvariables()
{
    memcpy(ballpointer,newball,4*sizeof(double));
    memcpy(gkpointer,newgk,4*sizeof(double));
    memcpy(playerposition, newplayerposition,2*6*4*sizeof(double)) ;
    activeplayer=5;ballstate=1;ballholder=5;
    gametime=0;
}

bool checkcollision(double x1,double y1,double x2, double y2, double r)
{
    if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=r*r)
        return true;
    else
        return false;
}

int playerOnTheWay(double x1,double y1,double x3,double y3,double x2,double y2,double r)
{
    if((abs(((y2-y1)*x3-(x2-x1)*y3+y1*(x2-x1)-x1*(y2-y1)))/ sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)))>3*r)
        return 0;
    else
    {
        if(((x3>=x1 && x2>=x3) || (x3<=x1 && x2<=x3)) && ((y3>=y1 && y2>=y3) || (y3<=y1 && y2<=y3)))
            return 1;
        else
            return -1;
    }
}

void choosePosition(int t,int m, double maxX, double minX, double maxY, double minY, double rangeX, double rangeY)//int accuracy, int urgency
{
    //X axis movement
    if(ballpointer[0]>=maxX)
    {
        if(ballpointer[0]-rangeX>=maxX)
            playerposition[t][m][2]=maxX - rand() % dX;
        else
            playerposition[t][m][2]=maxX - rand() % (int)(rangeX-ballpointer[1]+maxX);
    }
    else if(ballpointer[0]<=minX)
    {
        if(ballpointer[0]+rangeX <= minX)
            playerposition[t][m][2]=minX + rand() % dX;
        else
            playerposition[t][m][2]=minX+ rand() % (int)(ballpointer[0]+rangeX-minX);
    }
    else
    {
        if(ballpointer[0]>=minX+2*(maxX-minX)/3)
            playerposition[t][m][2]=ballpointer[0] - rand() % (int) rangeX;
        else if(ballpointer[0]<= minX+(maxX-minX)/3)
            playerposition[t][m][2]=ballpointer[0] + rand() % (int) rangeX;
        else
            playerposition[t][m][2]=minX + rand() % (int) (maxX-minX);
    }

    //Y axis movement
    if(ballpointer[1]>=maxY)
    {
        if(ballpointer[1]-rangeY >= maxY)
            playerposition[t][m][3]=maxY - rand() % dY;
        else
            playerposition[t][m][3]=maxY- rand() % (int)(rangeY-ballpointer[1]+maxY);
    }
    else if(ballpointer[1]<=minY)
    {
        if(ballpointer[1]+rangeY <= minY)
            playerposition[t][m][3]=minY + rand() % dY;
        else
            playerposition[t][m][3]=minY+ rand() % (int)(ballpointer[1]+rangeY-minY);
    }
    else
    {
        if(ballstate==1)
        {
            if(ballpointer[1]+rangeY<=maxY)
                playerposition[t][m][3]=ballpointer[1]+rand() % (int)(rangeY);
            else
                playerposition[t][m][3]=ballpointer[1]+rand() % (int)(maxY-ballpointer[1]);
        }
        else if(ballstate==-1)
        {
            if(ballpointer[1]-rangeY>=minY)
                playerposition[t][m][3]=ballpointer[1]- rand() % (int)(rangeY);
            else
                playerposition[t][m][3]=ballpointer[1]-rand() % (int)(ballpointer[1]-minY);
        }
    }
    
}

bool timetoChoosePosition(int team, int m)
{
    if(playerposition[team][m][0]<playerposition[team][m][2]+dxy && playerposition[team][m][0]>playerposition[team][m][2]-dxy && playerposition[team][m][1]<playerposition[team][m][3]+dxy && playerposition[team][m][1]>playerposition[team][m][3]-dxy)
        return 1;
    else
        return 0;
}

void chooseAndTakePosition()
{
    for(int j = 0; j < 6; j++)
    {
        if(activeplayer != j)
        {
            if (timetoChoosePosition(1,j))
            {
                if (timer % (3000 + rand() % 3000) <= 10)
                    choosePosition(1,j,positionField[1][j][0],positionField[1][j][1],positionField[1][j][2],positionField[1][j][3],5*width/20,5*length/20); // team 1
            }
            else
            {
                if((playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1])>2)
                {
                    playerposition[1][j][0]+= (3*speed/5) *(playerposition[1][j][2]-playerposition[1][j][0])/sqrt((playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1]));
                    playerposition[1][j][1]+= (3*speed/5) *(playerposition[1][j][3]-playerposition[1][j][1])/sqrt((playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1]));
                }
            }
        }
        if(activeplayeropp != j)
        {
            if (timetoChoosePosition(0,j))
            {
                if (timer % (3000 + rand() % 3000) <= 100)
                    choosePosition(0,j,positionField[0][j][0],positionField[0][j][1],positionField[0][j][2],positionField[0][j][3],4*width/20,5*length/20); // team 0
            }
            else
            {
                if((playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1])>2)
                {
                    playerposition[0][j][0]+= speed*3/5*(playerposition[0][j][2]-playerposition[0][j][0])/sqrt((playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1]));
                    playerposition[0][j][1]+= speed*3/5*(playerposition[0][j][3]-playerposition[0][j][1])/sqrt((playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1])); 
                }   
            }
        }
    }
}

void handlecollission()
{
    if(ballstate==0)
    {
        if(checkcollision(gkpointer[0][0],gkpointer[0][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=1;
                ballholder=-1;
            }
        else if(checkcollision(gkpointer[1][0],gkpointer[1][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=-1;
                ballholder=-1;
            }
    }
    for(i=0;i<6;i++)
    {
        if(ballstate==0)
        {
            if(checkcollision(playerposition[1][i][0],playerposition[1][i][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=1;
                ballholder=i;
            }
            else if(checkcollision(playerposition[0][i][0],playerposition[0][i][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=-1;
                ballholder=i;
            }
        }
        if(checkcollision(playerposition[1][i][0],playerposition[1][i][1],gkpointer[0][0],gkpointer[0][1],2*playerradius))
        {
            if(i==ballholder && ballstate==1)
            {
                ballstate=1;
                ballholder=-1;
            }
            if(playerposition[1][i][0]>gkpointer[0][0])
                playerposition[1][i][0]+=3;
            else if(playerposition[1][i][0]<gkpointer[0][0])
                playerposition[1][i][0]-=3;
            if(playerposition[1][i][1]>gkpointer[0][1])
                playerposition[1][i][1]+=3;
            else if(playerposition[1][i][1]<gkpointer[0][1])
                playerposition[1][i][1]-=3;
        }
        else if(checkcollision(playerposition[1][i][0],playerposition[1][i][1],gkpointer[1][0],gkpointer[1][1],2*playerradius))
        {
            if(i==ballholder && ballstate==1)
            {
                ballstate=-1;
                ballholder=-1;
            }
            if(playerposition[1][i][0]>gkpointer[1][0])
                playerposition[1][i][0]+=3;
            else if(playerposition[1][i][0]<gkpointer[1][0])
                playerposition[1][i][0]-=3;
            if(playerposition[1][i][1]>gkpointer[1][1])
                playerposition[1][i][1]+=3;
            else if(playerposition[1][i][1]<gkpointer[1][1])
                playerposition[1][i][1]-=3;
        }
        if(checkcollision(playerposition[0][i][0],playerposition[0][i][1],gkpointer[0][0],gkpointer[0][1],2*playerradius))
        {
            if(i==ballholder && ballstate==-1)
            {
                ballstate=1;
                ballholder=-1;
            }
            if(playerposition[0][i][0]>gkpointer[0][0])
                playerposition[0][i][0]+=3;
            else if(playerposition[0][i][0]<gkpointer[0][0])
                playerposition[0][i][0]-=3;
            if(playerposition[0][i][1]>gkpointer[0][1])
                playerposition[0][i][1]+=3;
            else if(playerposition[0][i][1]<gkpointer[0][1])
                playerposition[0][i][1]-=3;
        }
        else if(checkcollision(playerposition[0][i][0],playerposition[0][i][1],gkpointer[1][0],gkpointer[1][1],2*playerradius))
        {
            if(i==ballholder && ballstate==-1)
            {
                ballstate=-1;
                ballholder=-1;
            }
            if(playerposition[0][i][0]>gkpointer[1][0])
                playerposition[0][i][0]+=3;
            else if(playerposition[0][i][0]<gkpointer[1][0])
                playerposition[0][i][0]-=3;
            if(playerposition[0][i][1]>gkpointer[1][1])
                playerposition[0][i][1]+=3;
            else if(playerposition[0][i][1]<gkpointer[1][1])
                playerposition[0][i][1]-=3;
        }
        
        for(ii=0;ii<6;ii++)
        {
            if(checkcollision(playerposition[1][i][0],playerposition[1][i][1],playerposition[1][ii][0],playerposition[1][ii][1],2*playerradius))
            {
                if(ballstate==1)
                {
                    if(ballholder==i)
                        ballholder=ii;
                    else if(ballholder==ii)
                        ballholder=i;
                }
                if(playerposition[1][i][0]>playerposition[1][ii][0])
                {
                    playerposition[1][i][0]+=rand()% (int)collidepos;
                    playerposition[1][ii][0]-=rand()% (int)collidepos;
                }
                else if(playerposition[1][i][0]<playerposition[1][ii][0])
                {
                    playerposition[1][i][0]-=rand()% (int)collidepos;
                    playerposition[1][ii][0]+=rand()% (int)collidepos;
                }
                if(playerposition[1][i][1]>playerposition[1][ii][1])
                {
                    playerposition[1][i][1]+=rand()% (int)collidepos;
                    playerposition[1][ii][1]-=rand()% (int)collidepos;
                }
                else if(playerposition[1][i][1]<playerposition[1][ii][1])
                {
                    playerposition[1][i][1]-=rand()% (int)collidepos;
                    playerposition[1][ii][1]+=rand()% (int)collidepos;
                }
            }
            if(checkcollision(playerposition[0][i][0],playerposition[0][i][1],playerposition[0][ii][0],playerposition[0][ii][1],2*playerradius))
            {
                if(ballstate==-1)
                {
                    if(ballholder==i)
                        ballholder=ii;
                    else if(ballholder==ii)
                        ballholder=i;
                }
                if(playerposition[0][i][0]>playerposition[0][ii][0])
                {
                    playerposition[0][i][0]+=rand()% (int)collidepos;
                    playerposition[0][ii][0]-=rand()% (int)collidepos;
                }
                else if(playerposition[0][i][0]<playerposition[0][ii][0])
                {
                    playerposition[0][i][0]-=rand()% (int)collidepos;
                    playerposition[0][ii][0]+=rand()% (int)collidepos;
                }
                if(playerposition[0][i][1]>playerposition[0][ii][1])
                {
                    playerposition[0][i][1]+=rand()% (int)collidepos;
                    playerposition[0][ii][1]-=rand()% (int)collidepos;
                }
                else if(playerposition[0][i][1]<playerposition[0][ii][1])
                {
                    playerposition[0][i][1]-=rand()% (int)collidepos;
                    playerposition[0][ii][1]+=rand()% (int)collidepos;
                }
            }
            if(checkcollision(playerposition[1][i][0],playerposition[1][i][1],playerposition[0][ii][0],playerposition[0][ii][1],2*playerradius))
            {
                if(ballholder!=-1)
                {
                    if(ballstate==1 && ballholder==i)
                    {
                        ballstate=-1;
                        ballholder=ii;
                    }
                    else if(ballstate==-1 && ballholder==ii)
                    {
                        ballstate=1;
                        ballholder=i;
                    }
                }
                if(playerposition[1][i][0]>playerposition[0][ii][0])
                {
                    playerposition[1][i][0]+=rand()% (int)collidepos;
                    playerposition[0][ii][0]-=rand()% (int)collidepos;
                }
                else if(playerposition[1][i][0]<playerposition[0][ii][0])
                {
                    playerposition[1][i][0]-=rand()% (int)collidepos;
                    playerposition[0][ii][0]+=rand()% (int)collidepos;
                }
                if(playerposition[1][i][1]>playerposition[0][ii][1])
                {
                    playerposition[1][i][1]+=rand()% (int)collidepos;
                    playerposition[0][ii][1]-=rand()% (int)collidepos;
                }
                else if(playerposition[1][i][1]<playerposition[0][ii][1])
                {
                    playerposition[1][i][1]-=rand()% (int)collidepos;
                    playerposition[0][ii][1]+=rand()% (int)collidepos;
                }
            }
        }
    }
}

void chooseactiveplayer()
{
    if(ballstate==1)
    {
        activeplayer=ballholder;
    }
    else if(ballstate==0 || ballstate==-1)
    {
        for(i=0;i<6;i++)
        {
            if((ballpointer[0]-playerposition[1][activeplayer][0])*(ballpointer[0]-playerposition[1][activeplayer][0])+(ballpointer[1]-playerposition[1][activeplayer][1])*(ballpointer[1]-playerposition[1][activeplayer][1])>(ballpointer[0]-playerposition[1][i][0])*(ballpointer[0]-playerposition[1][i][0])+(ballpointer[1]-playerposition[1][i][1])*(ballpointer[1]-playerposition[1][i][1]))
                helpingplayer=i;
        }
        if(isKeyPressed('o'))
            activeplayer=helpingplayer;
    }
    
}

void chooseopponentactiveplayer()
{
    if(ballstate==-1)
    {
        activeplayeropp=ballholder;
    }
    else if(ballstate==0 || ballstate==1)
    {
        for(i=0;i<6;i++)
        {
            if((ballpointer[0]-playerposition[0][activeplayeropp][0])*(ballpointer[0]-playerposition[0][activeplayeropp][0])+(ballpointer[1]-playerposition[0][activeplayeropp][1])*(ballpointer[1]-playerposition[0][activeplayeropp][1])>(ballpointer[0]-playerposition[0][i][0])*(ballpointer[0]-playerposition[0][i][0])+(ballpointer[1]-playerposition[0][i][1])*(ballpointer[1]-playerposition[0][i][1]))
                helpingplayeropp=i;
        }
        if(isKeyPressed('c'))
            activeplayeropp=helpingplayeropp;
    }
}

void loadresources()
{
    iInitSprite(&fields,0x000000);
    iLoadFramesFromSheet(field,"field.png",1,1);
    iChangeSpriteFrames(&fields,field,1);
    iSetSpritePosition(&fields,0,0);
    iInitSprite(&fball,0x000000);
    iLoadFramesFromSheet(ball, "ball.png" ,1,1);
    iChangeSpriteFrames(&fball,ball,1);

    for(int n=0;n<6;n++)
    {
        iInitSprite(&players[n] , 0x000000);
        iInitSprite(&opponents[n] , 0x000000);
        iLoadFramesFromSheet(player, "player.png" ,1,1);
        iChangeSpriteFrames(&players[n],player,1);
        if(n==0)
        {
            iChangeSpriteFrames(&gk[n],player,1);
            iSetSpritePosition(&gk[n],gkpointer[n][0],gkpointer[n][1]);
        }
        iLoadFramesFromSheet(opponent, "opponent.png" ,1,1);
        iChangeSpriteFrames(&opponents[n],opponent,1);
        if(n==1)
        {
            iChangeSpriteFrames(&gk[n],opponent,1);
            iSetSpritePosition(&gk[n],gkpointer[n][0],gkpointer[n][1]);
        }
        iSetSpritePosition(&players[n],playerposition[1][n][0],playerposition[1][n][1]);
        iSetSpritePosition(&opponents[n],playerposition[0][n][0],playerposition[0][n][1]);
    }
}

void spritepositionupdate()
{
    for(i=0;i<6;i++)
    {
        iSetSpritePosition(&players[i],playerposition[1][i][0]-playerradius,playerposition[1][i][1]-playerradius);
        iSetSpritePosition(&opponents[i],playerposition[0][i][0]-playerradius,playerposition[0][i][1]-playerradius);
        if(i==0 || i==1)
            iSetSpritePosition(&gk[i],gkpointer[i][0]-playerradius,gkpointer[i][1]-playerradius);
    }
    iSetSpritePosition(&fball,ballpointer[0]-ballradius,ballpointer[1]-ballradius);
}

void timerupdate(){
    timer+=1;
}

void gkmoving(){
    if(ballholder!=-1 || (ballholder==-1 && ballstate==0))
    {
        if(ballpointer[1]<length/2)
        {
            if(gkpointer[0][0]-ballpointer[0]>0)
                gkpointer[0][0]=gkpointer[0][0]-gkspeed;
            else if(gkpointer[0][0]-ballpointer[0]<0)
                gkpointer[0][0]=gkpointer[0][0]+gkspeed;
        }
        if(ballpointer[1]>length/2)
        {
            if(gkpointer[1][0]-ballpointer[0]>0)
                gkpointer[1][0]=gkpointer[1][0]-gkspeed;
            else if(gkpointer[1][0]-ballpointer[0]<0)
                gkpointer[1][0]=gkpointer[1][0]+gkspeed;
        }
    }
    if(gkpointer[0][0]<width/2-80)
        gkpointer[0][0]=width/2-80;
    else if(gkpointer[0][0]>width/2+80)
        gkpointer[0][0]=width/2+80;
    if(gkpointer[1][0]<width/2-80)
        gkpointer[1][0]=width/2-80;
    else if(gkpointer[1][0]>width/2+80)
        gkpointer[1][0]=width/2+80;
    
}

void activepassing()
{
    if(ballstate==1)
    {
        if(isKeyPressed('p'))
            passedballspeed=passedballspeed;
        else if(isKeyPressed('l'))
            passedballspeed=shootballspeed;
        
        if(isKeyPressed('p') || isKeyPressed('l'))
        {
            ballstate=0;
            ballpointer[2]=0;
            ballpointer[3]=0;
            varAcceleration[0]=0;
            varAcceleration[1]=0;
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else{
                    ballpointer[1]+=playerradius*10/6;
                    ballpointer[3]=passedballspeed;
                    varAcceleration[1]=acceleration;
                }
            }
            if(isSpecialKeyPressed( GLUT_KEY_DOWN )){
                ballstate=0;
                if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else{
                    ballpointer[1]-=playerradius*10/6;
                    ballpointer[3]=-passedballspeed;
                    varAcceleration[1]=-acceleration;
                }
            }
            if(isSpecialKeyPressed( GLUT_KEY_RIGHT)){
                ballstate=0;
                if(isSpecialKeyPressed(GLUT_KEY_UP)){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else{
                    ballpointer[0]+=playerradius*10/6;
                    ballpointer[2]=passedballspeed;
                    varAcceleration[0]=acceleration;
                }
            }
            if(isSpecialKeyPressed( GLUT_KEY_LEFT)){
                ballstate=0;
                if(isSpecialKeyPressed(GLUT_KEY_UP)){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else{
                    ballpointer[0]-=ballradius*10/6;
                    ballpointer[2]=-passedballspeed;
                    varAcceleration[0]=-acceleration;
                }
            }
            }
    }
}

void opponentpassing()
{
    if(ballstate==-1)
    {
        if(isKeyPressed('t'))
            passedballspeed=passedballspeed;
        else if(isKeyPressed('g'))
            passedballspeed=shootballspeed;
        
        if(isKeyPressed('t') || isKeyPressed('g'))
        {
            ballstate=0;
            ballpointer[2]=0;
            ballpointer[3]=0;
            varAcceleration[0]=0;
            varAcceleration[1]=0;
            if(isKeyPressed('w')){
                if(isKeyPressed('a')){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isKeyPressed('d')){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else{
                    ballpointer[1]+=playerradius*10/6;
                    ballpointer[3]=passedballspeed;
                    varAcceleration[1]=acceleration;
                }
            }
            if(isKeyPressed( 's' )){
                ballstate=0;
                if(isKeyPressed('a')){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else if(isKeyPressed('d')){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else{
                    ballpointer[1]-=playerradius*10/6;
                    ballpointer[3]=-passedballspeed;
                    varAcceleration[1]=-acceleration;
                }
            }
            if(isKeyPressed( 'd')){
                ballstate=0;
                if(isKeyPressed('w')){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isKeyPressed('s')){
                    ballpointer[0]+=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else{
                    ballpointer[0]+=playerradius*10/6;
                    ballpointer[2]=passedballspeed;
                    varAcceleration[0]=acceleration;
                }
            }
            if(isKeyPressed( 'a')){
                ballstate=0;
                if(isKeyPressed('w')){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]+=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=acceleration/1.4;
                }
                else if(isKeyPressed('s')){
                    ballpointer[0]-=playerradius*4/6;
                    ballpointer[1]-=playerradius*4/6;
                    ballpointer[2]=-passedballspeed/1.4;
                    ballpointer[3]=-passedballspeed/1.4;
                    varAcceleration[0]=-acceleration/1.4;
                    varAcceleration[1]=-acceleration/1.4;
                }
                else{
                    ballpointer[0]-=ballradius*10/6;
                    ballpointer[2]=-passedballspeed;
                    varAcceleration[0]=-acceleration;
                }
            }
            }
    }
}

void opponentplayermoveing()
{
    chooseopponentactiveplayer();
    if(activeplayeropp==-1)
    {
        if(isKeyPressed( 'a'))
            gkpointer[1][0]=gkpointer[1][0]-gkspeed;
        else if(isKeyPressed( 'd'))
            gkpointer[1][0]=gkpointer[1][0]+gkspeed;
    }
    else
    {
        if(isKeyPressed('w')){
            if(isKeyPressed('a')){
                playerposition[0][activeplayeropp][0]-=speed/2.8;
                playerposition[0][activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('d')){
                playerposition[0][activeplayeropp][0]+=speed/2.8;
                playerposition[0][activeplayeropp][1]+=speed/2.8;
            }
            else
                playerposition[0][activeplayeropp][1]+=speed;
        }
        if(isKeyPressed( 's' )){
            if(isKeyPressed('a')){
                playerposition[0][activeplayeropp][0]-=speed/2.8;
                playerposition[0][activeplayeropp][1]-=speed/2.8;
            }
            else if(isKeyPressed('d')){
                playerposition[0][activeplayeropp][0]+=speed/2.8;
                playerposition[0][activeplayeropp][1]-=speed/2.8;
            }
            else
                playerposition[0][activeplayeropp][1]-=speed;
        }
        if(isKeyPressed( 'd')){
            if(isKeyPressed('w')){
                playerposition[0][activeplayeropp][0]+=speed/2.8;
                playerposition[0][activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('s')){
                playerposition[0][activeplayeropp][0]+=speed/2.8;
                playerposition[0][activeplayeropp][1]-=speed/2.8;
            }
            else
                playerposition[0][activeplayeropp][0]+=speed;
        }
        if(isKeyPressed( 'a')){
            if(isKeyPressed('w')){
                playerposition[0][activeplayeropp][0]-=speed/2.8;
                playerposition[0][activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('s')){
                playerposition[0][activeplayeropp][0]-=speed/2.8;
                playerposition[0][activeplayeropp][1]-=speed/2.8;
            }
            else
                playerposition[0][activeplayeropp][0]-=speed;
        }
    }
}

void activeplayermoveing()
{
    chooseactiveplayer();
    if(activeplayer==-1)
    {
        if(isSpecialKeyPressed( GLUT_KEY_LEFT))
            gkpointer[0][0]=gkpointer[0][0]-gkspeed;
        else if(isSpecialKeyPressed( GLUT_KEY_RIGHT))
            gkpointer[0][0]=gkpointer[0][0]+gkspeed;
    }
    else
    {
        if(isSpecialKeyPressed(GLUT_KEY_UP)){
            if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                playerposition[1][activeplayer][0]-=speed/2.8;
                playerposition[1][activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerposition[1][activeplayer][0]+=speed/2.8;
                playerposition[1][activeplayer][1]+=speed/2.8;
            }
            else
                playerposition[1][activeplayer][1]+=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_DOWN )){
            if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                playerposition[1][activeplayer][0]-=speed/2.8;
                playerposition[1][activeplayer][1]-=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerposition[1][activeplayer][0]+=speed/2.8;
                playerposition[1][activeplayer][1]-=speed/2.8;
            }
            else
                playerposition[1][activeplayer][1]-=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_RIGHT)){
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                playerposition[1][activeplayer][0]+=speed/2.8;
                playerposition[1][activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                playerposition[1][activeplayer][0]+=speed/2.8;
                playerposition[1][activeplayer][1]-=speed/2.8;
            }
            else
                playerposition[1][activeplayer][0]+=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_LEFT)){
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                playerposition[1][activeplayer][0]-=speed/2.8;
                playerposition[1][activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                playerposition[1][activeplayer][0]-=speed/2.8;
                playerposition[1][activeplayer][1]-=speed/2.8;
            }
            else
                playerposition[1][activeplayer][0]-=speed;
        }
    }
}

void ballposition()
{
    if(ballstate==1)
    {
        if(ballholder==-1)
        {
            ballpointer[0]=gkpointer[0][0];
            ballpointer[1]=gkpointer[0][1];
        }
        else
        {
            ballpointer[0]=playerposition[1][ballholder][0];
            ballpointer[1]=playerposition[1][ballholder][1];
        }
    }
    else if(ballstate==-1)
    {
        if (ballholder==-1)
        {
            ballpointer[0]=gkpointer[1][0];
            ballpointer[1]=gkpointer[1][1];
        }
        else
        {
            ballpointer[0]=playerposition[0][ballholder][0];
            ballpointer[1]=playerposition[0][ballholder][1];
        }
    }
    else if(ballstate==0)
    {
        if(!(ballpointer[2]==0 || (varAcceleration[0]>0 && ballpointer[2]>0) || (varAcceleration[0]<0 && ballpointer[2]<0)))
        {
            ballpointer[0]+=ballpointer[2];
            ballpointer[2]+=varAcceleration[0];
        }
        if(!(ballpointer[3]==0 || (varAcceleration[1]>0 && ballpointer[3]>0) || (varAcceleration[1]<0 && ballpointer[3]<0)))
        {
            ballpointer[1]+=ballpointer[3];
            ballpointer[3]+=varAcceleration[1];
        }
    }
}

void spriteshow()
{
    //iShowImage(0,0,"field.png");
    //iShowSprite(&fields);
    for(i=0;i<6;i++)
    {
        iShowSprite(&players[i]);
        iShowSprite(&opponents[i]);
    }
    iShowSprite(&gk[0]);
    iShowSprite(&gk[1]);
    iShowSprite(&fball);
    iShowImage(width-15,length-15,"pause.png");
}

void backbutton()
{
    iShowImage(5,50,"back.png");
}

void drawfield()
{
    iSetLineWidth(3);
    iSetColor(35,181,78);
    iFilledRectangle(0,0,width,gallary);
    iFilledRectangle(0,gallary+80,width,80);
    iFilledRectangle(0,gallary+3*80,width,80);
    iFilledRectangle(0,gallary+5*80,width,80);
    iFilledRectangle(0,gallary+7*80,width,80);
    iSetColor(45,232,100);
    iFilledRectangle(0,gallary+0*80,width,80);
    iFilledRectangle(0,gallary+2*80,width,80);
    iFilledRectangle(0,gallary+4*80,width,80);
    iFilledRectangle(0,gallary+6*80,width,80);
    iFilledRectangle(0,gallary+8*80,width,gallary);
    iSetColor(255,255,255);
    iRectangle(gallary,gallary,width-2*gallary,length-2*gallary);
    iLine(gallary,length/2,width-gallary,length/2);
    iFilledCircle(width/2,length/2,4);
    iCircle(width/2,length/2,80);
    iRectangle(width/2-130,gallary,130*2,130);
    iRectangle(width/2-130,length-gallary-130,130*2,130);
    iRectangle(width/2-80,gallary/2,160,gallary/2);
    iRectangle(width/2-80,length-gallary,160,gallary/2);
    //iPolygon({width/2-80,width/2-50,width/2+110,width/2+80},{gallary,gallary-20,gallary-20,gallary},4);
    iSetColor(255,0,0);
    iSetLineWidth(4);
    iLine(width/2-80,gallary,width/2+80,gallary);
    iLine(width/2-80,length-gallary,width/2+80,length-gallary);
}

void functioncaller()
{
    
    if(timer%10==0)
    {
        if (timer%1000==0)
            printf("%lld\n",timer/1000);
        activepassing();
        opponentpassing();
    }
    if(timer%5==0){
        chooseAndTakePosition();
        activeplayermoveing();
        opponentplayermoveing();
        gkmoving();
        ballposition();
    }
    if(timer%3==0)
    {
        handlecollission();
    }
}

void chooselevel()
{

}

/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    if(page_number==0)
    {
        if(timer<=coverpagetime)
            iShowImage(0,0,"opener.jpg");
        else
            iShowImage(0,0,"navigation.jpg");
    }
    else if(page_number==11)
    {
        iShowImage(0,0,"level.png");
        backbutton();
    }
    else if(page_number==1)
    {
        drawfield();
        chooselevel();
        functioncaller();
        spritepositionupdate();
        spriteshow();
    }
    else if(page_number==2)
    {
        drawfield();
        functioncaller();
        spritepositionupdate();
        spriteshow();
    }

    /*else if(page_number==3)

    else if(page_number==4)

    else if(page_number==5)*/

    else if(page_number==6)
    {
        iShowImage(0,0,"exitpage.jpg");
        if(tracktime+75<=timer)
            exit(0);

    }

}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
        if(page_number==0 && timer>coverpagetime)
        {
            if(mx>=134 && mx<=405)
            {
                if(my>=720-403  && my<=720-360)
                    {page_number=11;}
                else if(my>=720-450  && my<=720-408)
                    page_number=2;
                else if(my>=720-495  && my<=720-455)
                    page_number=3;
                else if(my>=720-542  && my<=720-502)
                    page_number=4;
                else if(my>=720-588  && my<=720-548)
                    page_number=5;
                else if(my>=720-635  && my<=720-594)
                    page_number=6;
            }
            tracktime=timer;
        }
        else if(page_number==11)
        {
            if(mx>63 && mx<472)
            {
                if(my<720-196 && my>720-263)
                    {level=1;page_number=1;resetvariables();}
                else if(my<720-304 && my>720-368)
                    {level=2;page_number=1;resetvariables();}
                else if(my<720-400 && my>720-460)
                    {level=3;page_number=1;resetvariables();}
            }
            else if(mx<65 && mx>5 && my<72 && my>50)
                page_number=0;
        }
        else if(page_number==1 || page_number==2)
        {
            if(mx<width && mx>width-20 && my<length && my>length-20)
                page_number=0;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    switch (key)
    {
    case 'q':
        // do something with 'q'
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    // place your own initialization codes here.
    loadresources();
    iSetTimer(1, timerupdate);
    iInitialize(width, length, "2D Football");
    return 0;
}