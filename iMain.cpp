#include "iGraphics.h"
#include<string.h>

Sprite players[6],opponents[6],gk[2],fball;
Image ball[1],player[1],opponent[1]; 
double length=120*6 , width = 90*6;
int  timer=0,i,ii,gametime=0,tracktime=0;
int level;
double speed=0.5 ,gkspeed=0.35, passedballspeed=.8, shootballspeed=1, acceleration=-0.001, varAcceleration[2];
double newplayer[6][4]={ {width/2,length*2/10},{width/6,length*2/10},{width*5/6,length*2/10},{width*2/6,length*7/20},{width*4/6,length*7/20} , {width/2,length/2} };
double newopponent[6][4]={{width/2,length*8/10}, {width/6,length*8/10}, {width*5/6,length*8/10},{width*2/6,length*7/10},{width*4/6,length*7/10} , {width/2,length*6/10} };
double newgk[2][2]={ {width/2,length/10},{width/2,length*9/10} };
double newball[4]={width/2,length/2};
double gkpointer[2][2]={ {width/2,length/20},{width/2,length*19/20} };
double playerpointer[6][4]={ {width/2,length*2/10},{width/6,length*2/10},{width*5/6,length*2/10},{width*2/6,length*7/20},{width*4/6,length*7/20} , {width/2,length/2} };
double opponentpointer[6][4]={{width/2,length*8/10}, {width/6,length*8/10}, {width*5/6,length*8/10},{width*2/6,length*7/10},{width*4/6,length*7/10} , {width/2,length*6/10} };
double ballpointer[4]={width/2,length/2};
int activeplayer=5,ballstate=1,ballholder=activeplayer,activeplayeropp;
int page_number=1,coverpagetime=100;
double playerradius=8,ballradius=5,collideposition=3;


void resetvariables()
{
    memcpy(ballpointer,newball,4*sizeof(double));
    memcpy(gkpointer,newgk,4*sizeof(double));
    memcpy(playerpointer,newplayer,24*sizeof(double));
    memcpy(opponentpointer,newopponent,24*sizeof(double));
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

void defenceopponent()
{

}

void attack()
{
    if(ballpointer[1]<length*16/20)
    {
        if(activeplayer!=3)
        {
            if(playerpointer[3][1]<ballpointer[1]+length*3/20 && playerpointer[3][1]<length*18/20)
                playerpointer[3][1]+=speed*3/5;
            else if(playerpointer[3][1]>ballpointer[1]+length*3/20-5 && playerpointer[3][1]>length*6/20)
                playerpointer[3][1]-=speed*3/5;
        }
        if(activeplayer!=4)
        {
            if(playerpointer[4][1]<ballpointer[1]+length*3/20 && playerpointer[4][1]<length*18/20)
                playerpointer[4][1]+=speed*3/5;
            else if(playerpointer[4][1]>ballpointer[1]+length*3/20-5 && playerpointer[4][1]>length*6/20)
                playerpointer[4][1]-=speed*3/5;
        }
    }
    else if(ballpointer[1]<length*16/20)
    {
        
    }
    if(activeplayer!=3)
    {
         if(ballpointer[0]>=width*2/5)
        {
            if((ballpointer[0]-width/2)/2 > playerpointer[3][0]-width/4 )
                playerpointer[3][0]+=speed/4;
            else if((ballpointer[0]-width/2)/2 <= playerpointer[3][0]-width/4 )
                playerpointer[3][0]-=speed/4;
        }
    }
    if(activeplayer!=4)
    {
        
        if(ballpointer[0]<=width*3/5)
        {
            if(ballpointer[0]/2 > playerpointer[4][0]-width/2 )
                playerpointer[4][0]+=speed/4;
            else if(ballpointer[0]/2 < playerpointer[4][0]-width/2 )
                playerpointer[4][0]-=speed/4;
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
            if(checkcollision(playerpointer[i][0],playerpointer[i][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=1;
                ballholder=i;
                /*ballpointer[0]=playerpointer[i][0];
                ballpointer[1]=playerpointer[i][1];*/
            }
            else if(checkcollision(opponentpointer[i][0],opponentpointer[i][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=-1;
                ballholder=i;
            }
        }
        if(checkcollision(playerpointer[i][0],playerpointer[i][1],gkpointer[0][0],gkpointer[0][1],2*playerradius))
        {
            if(i==ballholder && ballstate==1)
            {
                ballstate=1;
                ballholder=-1;
            }
            if(playerpointer[i][0]>gkpointer[0][0])
                playerpointer[i][0]+=3;
            else if(playerpointer[i][0]<gkpointer[0][0])
                playerpointer[i][0]-=3;
            if(playerpointer[i][1]>gkpointer[0][1])
                playerpointer[i][1]+=3;
            else if(playerpointer[i][1]<gkpointer[0][1])
                playerpointer[i][1]-=3;
        }
        else if(checkcollision(playerpointer[i][0],playerpointer[i][1],gkpointer[1][0],gkpointer[1][1],2*playerradius))
        {
            if(i==ballholder && ballstate==1)
            {
                ballstate=-1;
                ballholder=-1;
            }
            if(playerpointer[i][0]>gkpointer[1][0])
                playerpointer[i][0]+=3;
            else if(playerpointer[i][0]<gkpointer[1][0])
                playerpointer[i][0]-=3;
            if(playerpointer[i][1]>gkpointer[1][1])
                playerpointer[i][1]+=3;
            else if(playerpointer[i][1]<gkpointer[1][1])
                playerpointer[i][1]-=3;
        }
        if(checkcollision(opponentpointer[i][0],opponentpointer[i][1],gkpointer[0][0],gkpointer[0][1],2*playerradius))
        {
            if(i==ballholder && ballstate==-1)
            {
                ballstate=1;
                ballholder=-1;
            }
            if(opponentpointer[i][0]>gkpointer[0][0])
                opponentpointer[i][0]+=3;
            else if(opponentpointer[i][0]<gkpointer[0][0])
                opponentpointer[i][0]-=3;
            if(opponentpointer[i][1]>gkpointer[0][1])
                opponentpointer[i][1]+=3;
            else if(opponentpointer[i][1]<gkpointer[0][1])
                opponentpointer[i][1]-=3;
        }
        else if(checkcollision(opponentpointer[i][0],opponentpointer[i][1],gkpointer[1][0],gkpointer[1][1],2*playerradius))
        {
            if(i==ballholder && ballstate==-1)
            {
                ballstate=-1;
                ballholder=-1;
            }
            if(opponentpointer[i][0]>gkpointer[1][0])
                opponentpointer[i][0]+=3;
            else if(opponentpointer[i][0]<gkpointer[1][0])
                opponentpointer[i][0]-=3;
            if(opponentpointer[i][1]>gkpointer[1][1])
                opponentpointer[i][1]+=3;
            else if(opponentpointer[i][1]<gkpointer[1][1])
                opponentpointer[i][1]-=3;
        }
        
        for(ii=0;ii<6;ii++)
        {
            if(checkcollision(playerpointer[i][0],playerpointer[i][1],playerpointer[ii][0],playerpointer[ii][1],2*playerradius))
            {
                if(ballstate==1)
                {
                    if(ballholder==i)
                        ballholder=ii;
                    else if(ballholder==ii)
                        ballholder=i;
                }
                if(playerpointer[i][0]>playerpointer[ii][0])
                {
                    playerpointer[i][0]+=collideposition;
                    playerpointer[ii][0]-=collideposition;
                }
                else if(playerpointer[i][0]<playerpointer[ii][0])
                {
                    playerpointer[i][0]-=collideposition;
                    playerpointer[ii][0]+=collideposition;
                }
                if(playerpointer[i][1]>playerpointer[ii][1])
                {
                    playerpointer[i][1]+=collideposition;
                    playerpointer[ii][1]-=collideposition;
                }
                else if(playerpointer[i][1]<playerpointer[ii][1])
                {
                    playerpointer[i][1]-=collideposition;
                    playerpointer[ii][1]+=collideposition;
                }
            }
            if(checkcollision(opponentpointer[i][0],opponentpointer[i][1],opponentpointer[ii][0],opponentpointer[ii][1],2*playerradius))
            {
                if(ballstate==-1)
                {
                    if(ballholder==i)
                        ballholder=ii;
                    else if(ballholder==ii)
                        ballholder=i;
                }
                if(opponentpointer[i][0]>opponentpointer[ii][0])
                {
                    opponentpointer[i][0]+=collideposition;
                    opponentpointer[ii][0]-=collideposition;
                }
                else if(opponentpointer[i][0]<opponentpointer[ii][0])
                {
                    opponentpointer[i][0]-=collideposition;
                    opponentpointer[ii][0]+=collideposition;
                }
                if(opponentpointer[i][1]>opponentpointer[ii][1])
                {
                    opponentpointer[i][1]+=collideposition;
                    opponentpointer[ii][1]-=collideposition;
                }
                else if(opponentpointer[i][1]<opponentpointer[ii][1])
                {
                    opponentpointer[i][1]-=collideposition;
                    opponentpointer[ii][1]+=collideposition;
                }
            }
            if(checkcollision(playerpointer[i][0],playerpointer[i][1],opponentpointer[ii][0],opponentpointer[ii][1],2*playerradius))
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
                if(playerpointer[i][0]>opponentpointer[ii][0])
                {
                    playerpointer[i][0]+=collideposition;
                    opponentpointer[ii][0]-=collideposition;
                }
                else if(playerpointer[i][0]<opponentpointer[ii][0])
                {
                    playerpointer[i][0]-=collideposition;
                    opponentpointer[ii][0]+=collideposition;
                }
                if(playerpointer[i][1]>opponentpointer[ii][1])
                {
                    playerpointer[i][1]+=collideposition;
                    opponentpointer[ii][1]-=collideposition;
                }
                else if(playerpointer[i][1]<opponentpointer[ii][1])
                {
                    playerpointer[i][1]-=collideposition;
                    opponentpointer[ii][1]+=collideposition;
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
            if((ballpointer[0]-playerpointer[activeplayer][0])*(ballpointer[0]-playerpointer[activeplayer][0])+(ballpointer[1]-playerpointer[activeplayer][1])*(ballpointer[1]-playerpointer[activeplayer][1])>(ballpointer[0]-playerpointer[i][0])*(ballpointer[0]-playerpointer[i][0])+(ballpointer[1]-playerpointer[i][1])*(ballpointer[1]-playerpointer[i][1]))
                activeplayer=i;
        }
    }
    /*else if(ballstate==-1)
    {
         
    }*/
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
            if((ballpointer[0]-opponentpointer[activeplayeropp][0])*(ballpointer[0]-opponentpointer[activeplayeropp][0])+(ballpointer[1]-opponentpointer[activeplayeropp][1])*(ballpointer[1]-opponentpointer[activeplayeropp][1])>(ballpointer[0]-opponentpointer[i][0])*(ballpointer[0]-opponentpointer[i][0])+(ballpointer[1]-opponentpointer[i][1])*(ballpointer[1]-opponentpointer[i][1]))
                activeplayeropp=i;
        }
    }
    /*else if(ballstate==-1)
    {
         
    }*/
}

void loadresources()
{
    iInitSprite(&fball,000000);
    iLoadFramesFromSheet(ball, "ball.png" ,1,1);
    iChangeSpriteFrames(&fball,ball,1);

    for(int n=0;n<6;n++)
    {
        iInitSprite(&players[n] , 000000);
        iInitSprite(&opponents[n] , 000000);
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
        iSetSpritePosition(&players[n],playerpointer[n][0],playerpointer[n][1]);
        iSetSpritePosition(&opponents[n],opponentpointer[n][0],opponentpointer[n][1]);
    }
}

/*void ballcarrier()
{
    for(i=0;i<6;i++)
    {
        if(ballstate==0)
        {
            
            if(iCheckCollision(&fball,&players[i]))
            {
                ballstate=1;
                ballholder=i;
                activeplayer=i;
                break;
            }
            else if(iCheckCollision(&fball,&opponents[i]))
            {
                ballstate=-1;
                ballholder=i;
                break;
            }
        }
        else if(ballstate==1)
        {
            if(i==ballholder)
                continue;
            if(iCheckCollision(&players[ballholder],&players[i]))
            {
                ballholder=i;
                activeplayer=i;
                break;
            }
            if(iCheckCollision(&players[ballholder],&opponents[i]))
            {
                ballstate=-1;
                ballholder=i;
                break;
            }
        }
        else if(ballstate==-1)
        {
            if(iCheckCollision(&opponents[ballholder],&opponents[i]) || iCheckCollision(&opponents[i],&opponents[ballholder]))
            {
                ballholder=i;
                break;
            }
            if(iCheckCollision(&players[i],&opponents[ballholder]) || iCheckCollision(&opponents[ballholder],&players[i]))
            {
                ballstate=1;
                ballholder=i;
                activeplayer=i;
                break;
            }
        }
    }
    if(ballholder!=-1)
    {
        if(iCheckCollision(&fball, &gk[0]))
        {
            ballstate=1;
            ballholder=-1;
        }
        else if(iCheckCollision(&fball,&gk[1]))
        {
            ballstate=-1;
            ballholder=-1;
        }
    }
}*/

void spritepositionupdate()
{
    for(i=0;i<6;i++)
    {
        iSetSpritePosition(&players[i],playerpointer[i][0]-playerradius,playerpointer[i][1]-playerradius);
        iSetSpritePosition(&opponents[i],opponentpointer[i][0]-playerradius,opponentpointer[i][1]-playerradius);
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
    if(gkpointer[0][0]<width/6)
        gkpointer[0][0]=width/6;
    else if(gkpointer[0][0]>width*5/6)
        gkpointer[0][0]=width*5/6;
    if(gkpointer[1][0]<width/6)
        gkpointer[1][0]=width/6;
    else if(gkpointer[1][0]>width*5/6)
        gkpointer[1][0]=width*5/6;
    
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
                opponentpointer[activeplayeropp][0]-=speed/2.8;
                opponentpointer[activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('d')){
                opponentpointer[activeplayeropp][0]+=speed/2.8;
                opponentpointer[activeplayeropp][1]+=speed/2.8;
            }
            else
                opponentpointer[activeplayeropp][1]+=speed;
        }
        if(isKeyPressed( 's' )){
            if(isKeyPressed('a')){
                opponentpointer[activeplayeropp][0]-=speed/2.8;
                opponentpointer[activeplayeropp][1]-=speed/2.8;
            }
            else if(isKeyPressed('d')){
                opponentpointer[activeplayeropp][0]+=speed/2.8;
                opponentpointer[activeplayeropp][1]-=speed/2.8;
            }
            else
                opponentpointer[activeplayeropp][1]-=speed;
        }
        if(isKeyPressed( 'd')){
            if(isKeyPressed('w')){
                opponentpointer[activeplayeropp][0]+=speed/2.8;
                opponentpointer[activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('s')){
                opponentpointer[activeplayeropp][0]+=speed/2.8;
                opponentpointer[activeplayeropp][1]-=speed/2.8;
            }
            else
                opponentpointer[activeplayeropp][0]+=speed;
        }
        if(isKeyPressed( 'a')){
            if(isKeyPressed('w')){
                opponentpointer[activeplayeropp][0]-=speed/2.8;
                opponentpointer[activeplayeropp][1]+=speed/2.8;
            }
            else if(isKeyPressed('s')){
                opponentpointer[activeplayeropp][0]-=speed/2.8;
                opponentpointer[activeplayeropp][1]-=speed/2.8;
            }
            else
                opponentpointer[activeplayeropp][0]-=speed;
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
                playerpointer[activeplayer][0]-=speed/2.8;
                playerpointer[activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerpointer[activeplayer][0]+=speed/2.8;
                playerpointer[activeplayer][1]+=speed/2.8;
            }
            else
                playerpointer[activeplayer][1]+=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_DOWN )){
            if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                playerpointer[activeplayer][0]-=speed/2.8;
                playerpointer[activeplayer][1]-=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerpointer[activeplayer][0]+=speed/2.8;
                playerpointer[activeplayer][1]-=speed/2.8;
            }
            else
                playerpointer[activeplayer][1]-=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_RIGHT)){
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                playerpointer[activeplayer][0]+=speed/2.8;
                playerpointer[activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                playerpointer[activeplayer][0]+=speed/2.8;
                playerpointer[activeplayer][1]-=speed/2.8;
            }
            else
                playerpointer[activeplayer][0]+=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_LEFT)){
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                playerpointer[activeplayer][0]-=speed/2.8;
                playerpointer[activeplayer][1]+=speed/2.8;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
                playerpointer[activeplayer][0]-=speed/2.8;
                playerpointer[activeplayer][1]-=speed/2.8;
            }
            else
                playerpointer[activeplayer][0]-=speed;
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
            ballpointer[0]=playerpointer[ballholder][0];
            ballpointer[1]=playerpointer[ballholder][1];
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
            ballpointer[0]=opponentpointer[ballholder][0];
            ballpointer[1]=opponentpointer[ballholder][1];
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

void functioncaller()
{
    
    if(timer%10==0)
    {
        activepassing();
        opponentpassing();
    }
    if(timer%7==0){
        if(ballstate!=-1)
            attack();
        activeplayermoveing();
        opponentplayermoveing();
        gkmoving();
        ballposition();
    }
    if(timer%3==0)
    {
        handlecollission();
    }
    //if(timer%10==0)
        //ballcarrier();
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
        chooselevel();
        functioncaller();
        spritepositionupdate();
        spriteshow();
    }
    else if(page_number==2)
    {
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

    /*for(i=0;i<6;i++){
        iSetColor(0,150,0);
        iFilledCircle(playerpointer[i][0],playerpointer[i][1],8);
        iSetColor(150,0,150);
        iFilledCircle(opponentpointer[i][0],opponentpointer[i][1],8);
    }
    iSetColor(0,150,0);
    iFilledCircle(gkpointer[0][0],gkpointer[0][1],8);
    iSetColor(150,0,150);
    iFilledCircle(gkpointer[1][0],gkpointer[1][1],8);
    iSetColor(255,255,255);
    iFilledCircle(ballpointer[0],ballpointer[1],3);*/
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
    if(key==GLUT_KEY_HOME)
        page_number=0;
    /*switch (key)
    {
    case GLUT_KEY_UP:
        if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
            playerpointer[activeplayer][0]-=speed/1.4;
            playerpointer[activeplayer][1]+=speed/1.4;
        }
        else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
            playerpointer[activeplayer][0]+=speed/1.4;
            playerpointer[activeplayer][1]+=speed/1.4;
        }
        else
            playerpointer[activeplayer][1]+=speed;
        break;
    case GLUT_KEY_DOWN:
        if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
            playerpointer[activeplayer][0]-=speed/1.4;
            playerpointer[activeplayer][1]-=speed/1.4;
        }
        else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
            playerpointer[activeplayer][0]+=speed/1.4;
            playerpointer[activeplayer][1]-=speed/1.4;
        }
        else
            playerpointer[activeplayer][1]-=speed;
        break;
    case GLUT_KEY_RIGHT:
        if(isSpecialKeyPressed(GLUT_KEY_UP)){
            playerpointer[activeplayer][0]+=speed/1.4;
            playerpointer[activeplayer][1]+=speed/1.4;
        }
        else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
            playerpointer[activeplayer][0]+=speed/1.4;
            playerpointer[activeplayer][1]-=speed/1.4;
        }
        else
            playerpointer[activeplayer][0]+=speed*1;
        break;
    case GLUT_KEY_LEFT:
        if(isSpecialKeyPressed(GLUT_KEY_UP)){
            playerpointer[activeplayer][0]-=speed/1.4;
            playerpointer[activeplayer][1]+=speed/1.4;
        }
        else if(isSpecialKeyPressed(GLUT_KEY_DOWN)){
            playerpointer[activeplayer][0]-=speed/1.4;
            playerpointer[activeplayer][1]-=speed/1.4;
        }
        else
            playerpointer[activeplayer][0]-=speed;
        break;
    // place your codes for other keys here
    default:
        break;
    }*/
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