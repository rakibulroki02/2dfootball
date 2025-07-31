#include "iGraphics.h"
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include "iSound.h"

Sprite players[6],opponents[6],gk[2],fball, pauseButtons;
Image ball[1],player[1],opponent[1],field, backButton, pauseButton; 
double length=120*6 , width = 90*6, gallary=40, goalbar=160;
long long int i,ii,tracktime=0;
double gametime=0;
double timer=1;
int sec,minit;
int level,scoreplayer=0,scoreopp=0;
double constSpeed=0.5, speed=0.6 ,gkspeed=0.5, passedballspeed=1, shootballspeed=1.3, acceleration=-0.002, varAcceleration[2];
double playerradius=8,ballradius=5,collidepos=5;
double newball[4]={width/2,length/2};
double gkpointer[2][2]={ {width/2,gallary+playerradius},{width/2,length-gallary-playerradius} };
double newgk[2][2]={ {width/2,gallary+playerradius},{width/2,length-gallary-playerradius} };
double playerposition[2][6][4]={{{width/2,length*8/10,width/2,length*8/10,}, {width/6,length*8/10,width/6,length*8/10}, {width*5/6,length*8/10,width*5/6,length*8/10},{width*4/6,length*7/10,width*4/6,length*7/10},{width*2/6,length*7/10,width*2/6,length*7/10} , {width/2,length*6/10,width/2,length*6/10} },{ {width/2,length*2/10,width/2,length*2/10},{width/6,length*2/10,width/6,length*2/10},{width*5/6,length*2/10,width*5/6,length*2/10} ,{width*4/6,length*7/20,width*4/6,length*7/20} ,{width*2/6,length*7/20,width*2/6,length*7/20}, {width/2,length/2,width/2,length/2} }};
double newplayerposition[2][6][4]={{{width/2,length*8/10,width/2,length*8/10,}, {width/6,length*8/10,width/6,length*8/10}, {width*5/6,length*8/10,width*5/6,length*8/10} ,{width*4/6,length*7/10,width*4/6,length*7/10} ,{width*2/6,length*7/10,width*2/6,length*7/10}, {width/2,length*6/10,width/2,length*6/10} },{ {width/2,length*2/10,width/2,length*2/10},{width/6,length*2/10,width/6,length*2/10},{width*5/6,length*2/10,width*5/6,length*2/10},{width*4/6,length*7/20,width*4/6,length*7/20} ,{width*2/6,length*7/20,width*2/6,length*7/20}, {width/2,length/2,width/2,length/2} }};
double ballpointer[4]={width/2,length/2};
int activeplayer=5,ballstate=2,ballholder=activeplayer,activeplayeropp=5,helpingplayer=4,helpingplayeropp=4,lastTouch=1;
int page_number=0,coverpagetime=100;
double dxy=30;
double positionField[2][6][4]={{{4*width/7, 3*width/7, length-gallary, length/2}, {3*width/7, gallary, length-gallary, 10*length/20}, {width-gallary, 4*width/7,  length-gallary, 10*length/20} , {width-gallary, 4*width/7, 10*length/20, gallary}, {3*width/7, gallary, 10*length/20, gallary}, {4*width/7, 3*width/7, length/2, gallary}}, {{4*width/7, 3*width/7, length/2, gallary}, {3*width/7, gallary, 10*length/20, gallary}, {width-gallary, 4*width/7, 10*length/20, gallary},{width-gallary, 4*width/7, length-gallary, 10*length/20}, {3*width/7, gallary, length-gallary, 10*length/20},  {4*width/7, 3*width/7, length-gallary, length/2}}};
int dX=60, dY=100;
int frameCount = 0;
int previousTime = 0, previousFpsTime = 0;
int fps = 0;
double lastballswipe=0;
double dt=500;
int minutes=0;
int seconds=0;
int gameended=0;

int volume=100;
int kickoff=0;
int whistlePlayed=0;
int crowdPlaying = 0;
int passInitiated = 0;
int crowdChannel = -1;
int kickChannel = -1;
int goalChannel = -1;

typedef struct {
    char type[10]; // "Match" or "Penalty"
    int team0_score;
    int team1_score;
} ScoreEntry;

ScoreEntry *scores = NULL;
int score_count = 0;
int max_scores = 0;
void whistle_sound() {
    if (!whistlePlayed) {
        printf("Attempting to load whistle.wav\n");
        int channel = iPlaySound("whistle.wav", false, volume);
        if (channel == -1) {
            printf("Failed to play whistle.wav: %s\n", Mix_GetError());
        }
        whistlePlayed = 1;
    }
}
void crowd_sound(){
    if(whistle_sound){
        iPlaySound("crowd.wav", true, volume);
    }
}
int const max_shoot=15;
double spacing=30;
double penaltyPosition[2][6][2]={{{width/2+spacing*1,length/2},{width/2+spacing*2,length/2},{width/2+spacing*3,length/2},{width/2+spacing*4,length/2},{width/2+spacing*5,length/2},{width/2+spacing*6,length/2}},{{width/2-spacing*1,length/2},{width/2-spacing*2,length/2},{width/2-spacing*3,length/2},{width/2-spacing*4,length/2},{width/2-spacing*5,length/2},{width/2-spacing*6,length/2}}};
double penaltygk[2][2]={{width/2,length - gallary - playerradius},{width/6,length - gallary - playerradius}};
double penaltyPositionNew[2][6][2]={{{width/2+spacing*1,length/2},{width/2+spacing*2,length/2},{width/2+spacing*3,length/2},{width/2+spacing*4,length/2},{width/2+spacing*5,length/2},{width/2+spacing*6,length/2}},{{width/2-spacing*1,length/2},{width/2-spacing*2,length/2},{width/2-spacing*3,length/2},{width/2-spacing*4,length/2},{width/2-spacing*5,length/2},{width/2-spacing*6,length/2}}};
double penaltygkNew[2][2]={{width/2,length - gallary - playerradius},{width/6,length - gallary - playerradius}};
double penaltyBall[4]={0,0,0,0};
int activeTeam=0;
int gkSet=0;
int gkDirection=1;
double penGkSpeed=0.6;
int kicked=0;
double penAcceleration[2]={0,0};
int penScore[2][max_shoot]={0};
double penBallSpeedConstant=.7;
double penBallSpeed=1;
double speedFraction=50;
double barHieght=200;
int barDiraction=1;
int shootNumber=0;
int penaltyscores[2]={0,0};
double hypo=1;
double barspeed=0.35;
int penaltyended=0;



bool checkcollision(double x1,double y1,double x2, double y2, double r)
{
    if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=r*r)
        return true;
    else
        return false;
}

void iShowSpeed(double x, double y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    frameCount++;
    if (previousFpsTime == 0)
    {
        previousFpsTime = currentTime; // Initialize on first call
        frameCount = 0;
    }
    else
    {
        int elapsedFpsTime = currentTime - previousFpsTime;

        if (elapsedFpsTime > 1000)
        {
            fps = (frameCount * 1000.0f) / elapsedFpsTime;
            frameCount = 0;
            previousFpsTime = currentTime;
        }
    }

    char fpsText[20];
    sprintf(fpsText, "FPS: %d", fps);
    iText(x, y, fpsText);
}

void loadresources()
{
    
    iLoadImage(&backButton , "back.png");

    iLoadFramesFromSheet(ball, "ball.png" ,1,1);
    iChangeSpriteFrames(&fball,ball,1);

    for(int n=0;n<6;n++)
    {
        //iInitSprite(&players[n],0xFFFFFF);
        iLoadFramesFromSheet(player, "player.png" ,1,1);
        iChangeSpriteFrames(&players[n],player,1);
        if(n==0)
        {
            //iInitSprite(&gk[n],0xFFFFFF);
            iChangeSpriteFrames(&gk[n],player,1);
            iSetSpritePosition(&gk[n],gkpointer[n][0],gkpointer[n][1]);
        }

        //iInitSprite(&opponents[n],-1);
        iLoadFramesFromSheet(opponent, "opponent.png" ,1,1);
        iChangeSpriteFrames(&opponents[n],opponent,1);
        if(n==1) 
        {
            //iInitSprite(&gk[n],-1);
            iChangeSpriteFrames(&gk[n],opponent,1);
            iSetSpritePosition(&gk[n],gkpointer[n][0],gkpointer[n][1]);
        }
        iSetSpritePosition(&players[n],playerposition[1][n][0],playerposition[1][n][1]);
        iSetSpritePosition(&opponents[n],playerposition[0][n][0],playerposition[0][n][1]);

        
        iLoadFramesFromSheet(&pauseButton , "pause.png", 1,1);
        iChangeSpriteFrames(&pauseButtons, &pauseButton, 1);
    }
}

void resetvariables() 
{
    memcpy(ballpointer, newball, 4 * sizeof(double));
    memcpy(gkpointer, newgk, 4 * sizeof(double));
    memcpy(playerposition, newplayerposition, 2 * 6 * 4 * sizeof(double));
    activeplayer = 5;
    ballstate = 2;
    ballholder = 5;
    gametime = 0;
    whistlePlayed = 0;
    crowdPlaying = 0;
    passInitiated = 0;
    crowdChannel = -1;
    kickChannel = -1;
    goalChannel = -1;
    gameended=0;
    iStopAllSounds();
}

int playerOnTheWay(double x1,double y1,double x3,double y3,double x2,double y2,double r)
{
    if((abs((int)((y2-y1)*x3-(x2-x1)*y3+y1*(x2-x1)-x1*(y2-y1)))/ sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)))>3*r)
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
    //if(ballstate==t*2-1 || ballstate==0)
    {
        //X axis movement
        if(ballpointer[0]>=maxX)
        {
            if(ballpointer[0]-rangeX>=maxX)
                playerposition[t][m][2]=maxX - rand() % dX;
            else
                playerposition[t][m][2]=maxX - rand() % (int)(rangeX-ballpointer[0]+maxX+1);
            
        }
        else if(ballpointer[0]<=minX)
        {
            if(ballpointer[0]+rangeX <= minX)
                playerposition[t][m][2]=minX + rand() % dX;
            else
                playerposition[t][m][2]=minX+ rand() % (int)(ballpointer[0]+rangeX-minX+1);
            
        }
        else
        {
            if(ballpointer[0]>=minX+2*(maxX-minX)/3)
                playerposition[t][m][2]=ballpointer[0] - rand() % (int)rangeX;
            else if(ballpointer[0]<= minX+(maxX-minX)/3)
                playerposition[t][m][2]=ballpointer[0] + rand() % (int)rangeX;
            else
                playerposition[t][m][2]=minX + rand() % (int) (maxX-minX);
        }

        //Y axis movement
        if(ballpointer[1]>=maxY)
        {
            if(ballpointer[1]-rangeY >= maxY)
                playerposition[t][m][3]=maxY - rand() % dY;
            else
                playerposition[t][m][3]=maxY- rand() % (int)(rangeY-ballpointer[1]+maxY+1);
            
        }
        else if(ballpointer[1]<=minY)
        {
            if(ballpointer[1]+rangeY <= minY)
                playerposition[t][m][3]=minY + rand() % dY;
            else
                playerposition[t][m][3]=minY+ rand() % (int)(ballpointer[1]+rangeY-minY+1);
            
        }
        else
        {
            if(ballstate==1)
            {
                if(ballpointer[1]+rangeY<=maxY)
                    playerposition[t][m][3]=ballpointer[1]+rand() % (int)(rangeY);
                else
                    playerposition[t][m][3]=ballpointer[1]+rand() % (int)(maxY-ballpointer[1]+1);
                
            }
            else if(ballstate==-1)
            {
                if(ballpointer[1]-rangeY>=minY)
                    playerposition[t][m][3]=ballpointer[1]- rand() % (int)(rangeY);
                else
                    playerposition[t][m][3]=ballpointer[1]-rand() % (int)(ballpointer[1]-minY+1);
                
            }
        }
    }
    /*else
    {
        if(ballpointer[0]==playerposition[!t][5-m][0])
            playerposition[t][m][2]=ballpointer[0];
        else if(ballpointer[0]<playerposition[!t][5-m][0])
        {
            if(ballpointer[0]<minX)
                playerposition[t][m][2]=playerposition[!t][5-m][0]- rand() % (int)(playerposition[!t][5-m][0]-minX+1);
            else if(ballpointer[0]>minX)
                playerposition[t][m][2]=playerposition[!t][5-m][0]+ rand() % (int)(playerposition[!t][5-m][0] - ballpointer[0] + 1);
            //playerposition[t][m][2]=ballpointer[0]+ rand() % (int)(playerposition[!t][5-m][0]-ballpointer[0]+1);
        }
        else if(ballpointer[0]>playerposition[!t][5-m][0])
        {
            if(ballpointer[0]>maxX)
                playerposition[t][m][2]=playerposition[!t][5-m][0]+ rand() % (int)(maxX-playerposition[!t][5-m][0]+1);
            else if(ballpointer[0]>maxX)
                playerposition[t][m][2]=playerposition[!t][5-m][0]+ rand() % (int)(ballpointer[0] - playerposition[!t][5-m][0]+1);
        }

        playerposition[t][m][3]=ballpointer[1]+(playerposition[t][m][2]-ballpointer[0])*(playerposition[!t][5-m][1]-ballpointer[1])/(playerposition[!t][5-m][0]-ballpointer[0]) ;//+ pow(-1,(rand()-rand()))*15 ;
    }*/

}

bool timetoChoosePosition(int t, int m)
{
    //if(playerposition[team][m][0]<playerposition[team][m][2]+dxy && playerposition[team][m][0]>playerposition[team][m][2]-dxy && playerposition[team][m][1]<playerposition[team][m][3]+dxy && playerposition[team][m][1]>playerposition[team][m][3]-dxy)
    if((playerposition[t][m][2]-playerposition[t][m][0])*(playerposition[t][m][2]-playerposition[t][m][0])+(playerposition[t][m][3]-playerposition[t][m][1])*(playerposition[t][m][3]-playerposition[t][m][1])<dxy*dxy)
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
                if ((int)timer % (100+rand() % 4000) <= 10)
                    choosePosition(1,j,positionField[1][j][0],positionField[1][j][1],positionField[1][j][2],positionField[1][j][3],5*width/20,5*length/20); // team 1
            }
            else
            {
                if((playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1])>0)
                {
                    playerposition[1][j][0]+= (constSpeed) *(playerposition[1][j][2]-playerposition[1][j][0])/sqrt(1+(playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1]));
                    playerposition[1][j][1]+= (constSpeed) *(playerposition[1][j][3]-playerposition[1][j][1])/sqrt(1+(playerposition[1][j][2]-playerposition[1][j][0])*(playerposition[1][j][2]-playerposition[1][j][0])+(playerposition[1][j][3]-playerposition[1][j][1])*(playerposition[1][j][3]-playerposition[1][j][1]));
                }
            }
        }
        else
        {
            playerposition[1][j][2]=playerposition[1][j][0];
            playerposition[1][j][3]=playerposition[1][j][1];
        }
        if(activeplayeropp != j)
        {
            if (timetoChoosePosition(0,j))
            {
                if ((int)timer % (100+rand() % 4000) <= 10)
                    choosePosition(0,j,positionField[0][j][0],positionField[0][j][1],positionField[0][j][2],positionField[0][j][3],4*width/20,5*length/20); // team 0
            }
            else
            {
                if((playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1])>0)
                {
                    playerposition[0][j][0]+= constSpeed*(playerposition[0][j][2]-playerposition[0][j][0])/sqrt(1+(playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1]));
                    playerposition[0][j][1]+= constSpeed*(playerposition[0][j][3]-playerposition[0][j][1])/sqrt(1+(playerposition[0][j][2]-playerposition[0][j][0])*(playerposition[0][j][2]-playerposition[0][j][0])+(playerposition[0][j][3]-playerposition[0][j][1])*(playerposition[0][j][3]-playerposition[0][j][1])); 
                }
            }
        }
        else
        {
            playerposition[0][j][2]=playerposition[0][j][0];
            playerposition[0][j][3]=playerposition[0][j][1];
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
                lastTouch=1;
            }
        else if(checkcollision(gkpointer[1][0],gkpointer[1][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=-1;
                ballholder=-1;
                lastTouch=-1;
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
                lastTouch=1;
            }
            else if(checkcollision(playerposition[0][i][0],playerposition[0][i][1],ballpointer[0],ballpointer[1],ballradius+playerradius))
            {
                ballstate=-1;
                ballholder=i;
                lastTouch=-1;
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
                if(timer-lastballswipe>dt)
                {
                    if(ballstate==1)
                    {
                        if(ballholder==i)
                            ballholder=ii;
                        else if(ballholder==ii)
                            ballholder=i;
                    }
                    lastballswipe=0;
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
                if(timer-lastballswipe>dt)
                {
                    if(ballstate==-1)
                    {
                        if(ballholder==i)
                            ballholder=ii;
                        else if(ballholder==ii)
                            ballholder=i;
                    }
                    lastballswipe=0;
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
                if(timer-lastballswipe>dt)
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
                    lastballswipe=0;
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
    if(ballstate!=0)
    {
        lastTouch=ballstate/abs(ballstate);
    }
}

void chooseactiveplayer()
{
    if(ballstate==1 || ballstate==2)
    {
        activeplayer=ballholder;
    }
    else if(ballstate==0 || ballstate==-1 || ballstate==-2)
    {
        helpingplayer=activeplayer==0?1:0;
        for(i=0;i<6;i++)
        {
            if(i==activeplayer)
                continue;
            if((ballpointer[0]-playerposition[1][helpingplayer][0])*(ballpointer[0]-playerposition[1][helpingplayer][0])+(ballpointer[1]-playerposition[1][helpingplayer][1])*(ballpointer[1]-playerposition[1][helpingplayer][1])>(ballpointer[0]-playerposition[1][i][0])*(ballpointer[0]-playerposition[1][i][0])+(ballpointer[1]-playerposition[1][i][1])*(ballpointer[1]-playerposition[1][i][1]))
                helpingplayer=i;
        }
        if(isKeyPressed('o'))
            activeplayer=helpingplayer++;
    }
    
}

void chooseopponentactiveplayer()
{
    if(ballstate==-1 || ballstate==-2)
    {
        activeplayeropp=ballholder;
    }
    else if(ballstate==0 || ballstate==1 || ballstate==2)
    {
        helpingplayeropp=activeplayeropp==0?1:0;
        for(i=0;i<6;i++)
        {
            if(i==activeplayeropp)
                continue;
            if((ballpointer[0]-playerposition[0][helpingplayeropp][0])*(ballpointer[0]-playerposition[0][helpingplayeropp][0])+(ballpointer[1]-playerposition[0][helpingplayeropp][1])*(ballpointer[1]-playerposition[0][helpingplayeropp][1])>(ballpointer[0]-playerposition[0][i][0])*(ballpointer[0]-playerposition[0][i][0])+(ballpointer[1]-playerposition[0][i][1])*(ballpointer[1]-playerposition[0][i][1]))
                helpingplayeropp=i;
        }
        if(isKeyPressed('c'))
            activeplayeropp=helpingplayeropp++;
    }
}

void drawScoreboard()
{
    char score_text[50];
    char time_text[20];
    minutes = 15*(gametime / (60*120)); // Convert milliseconds to minutes
    seconds = (15*(int)(gametime / 120) % 60); // Convert milliseconds to seconds
    sprintf(score_text, "Pla %d - %d Opp", scoreplayer, scoreopp);
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    //iSetColor(0,0,255);
    //iFilledRectangle(0,length-gallary,100,gallary);
    iSetColor(255, 255, 255);
    iTextAdvanced(10, length - 30, score_text , .1, 2);
    iTextAdvanced(10, length - 15, time_text, .1, 2);
}

void throwCornerOutGoal()
{
    //throw
    if(ballpointer[0]<gallary-ballradius || ballpointer[0]>width-gallary+ballradius)
    {
        iDelay(2);
        if(ballstate!=0)
            playerposition[(lastTouch+1)/2][ballholder][0]+=((width/2-playerposition[(lastTouch+1)/2][ballholder][0])/(width/2-gallary))*100;
        ballstate=lastTouch==1?-2:2;
        ballholder=-lastTouch==1?activeplayer:activeplayeropp;
        playerposition[(-lastTouch+1)/2][ballholder][0]=ballpointer[0]>width/2?ballpointer[0]-ballradius:ballpointer[0]+ballradius;
        playerposition[(-lastTouch+1)/2][ballholder][1]=ballpointer[1];
    }
    //out or corner
    if((ballpointer[1]<gallary-ballradius || ballpointer[1]>length-gallary+ballradius))
    {
        if(ballpointer[0]<width/2-goalbar/2+ballradius/2 || ballpointer[0]>width/2+ goalbar/2-ballradius/2)
        {
            iDelay(2);
            if(ballstate!=0)
                playerposition[(lastTouch+1)/2][ballholder][1]+=((length/2-playerposition[(lastTouch+1)/2][ballholder][1])/(length/2-gallary))*200;
            if(ballpointer[1]<gallary-ballradius)
            {
                if(lastTouch==1)
                {
                    ballstate=-2;
                    ballholder=activeplayeropp==-1?helpingplayeropp:activeplayeropp;
                    playerposition[0][ballholder][0]=ballpointer[0]<width/2?gallary:width-gallary;
                    playerposition[0][ballholder][1]=gallary;
                }
                else if(lastTouch==-1)
                {
                    ballstate=1;
                    ballholder=-1;
                }
            }
            else if(ballpointer[1]>length-gallary+ballradius)
            {
                if(lastTouch==-1)
                {
                    ballstate=2;
                    ballholder=activeplayer==-1?helpingplayer:activeplayer;
                    playerposition[1][ballholder][0]=ballpointer[0]<width/2?gallary:width-gallary;
                    playerposition[1][ballholder][1]=length-gallary;
                }
                else if(lastTouch==1)
                {
                    ballstate=-1;
                    ballholder=-1;
                }
            }
        }
        //goal
        else if(ballpointer[0]>width/2-goalbar/2+ballradius/2 && ballpointer[0]<width/2+ goalbar/2-ballradius/2)
        {
            iDelay(3);
            memcpy(gkpointer,newgk,4*sizeof(double));
            memcpy(playerposition, newplayerposition,2*6*4*sizeof(double)) ;
            if(ballpointer[1]<gallary-ballradius)
            {
                scoreopp+=1;
                printf("Attempting to load goal.wav\n");
            goalChannel = iPlaySound("goal.wav", false, volume);
            if (goalChannel == -1) {
                printf("Failed to play goal.wav: %s\n", Mix_GetError());
            }
                ballstate=2;ballholder=5;
            }
            else if(ballpointer[1]>length-gallary+ballradius)
            {
                scoreplayer+=1;
                printf("Attempting to load goal.wav\n");
            goalChannel = iPlaySound("goal.wav", false, volume);
            if (goalChannel == -1) {
                printf("Failed to play goal.wav: %s\n", Mix_GetError());
            }
                playerposition[0][5][0]=width/2;
                playerposition[0][5][1]=length/2;
                playerposition[1][5][0]=width/2;
                playerposition[1][5][1]=4*length/10;
                ballstate=-2;ballholder=5;
            }
            memcpy(ballpointer,newball,4*sizeof(double));
        }
    }
}

void spritepositionupdate()
{
    if(page_number==1 || page_number==2)
    {
        for(i=0;i<6;i++)
        {
            iSetSpritePosition(&players[i],playerposition[1][i][0]-playerradius,playerposition[1][i][1]-playerradius);
            iSetSpritePosition(&opponents[i],playerposition[0][i][0]-playerradius,playerposition[0][i][1]-playerradius);
            if(i==0 || i==1)
                iSetSpritePosition(&gk[i],gkpointer[i][0]-playerradius,gkpointer[i][1]-playerradius);
        }
        iSetSpritePosition(&fball,ballpointer[0]-ballradius,ballpointer[1]-ballradius);
        iSetSpritePosition(&pauseButtons,width-15,length-15);
    }
    else if(page_number==3)
    {
        for(i=0;i<6;i++)
        {
            iSetSpritePosition(&players[i],penaltyPosition[1][i][0]-playerradius,penaltyPosition[1][i][1]-playerradius);
            iSetSpritePosition(&opponents[i],penaltyPosition[0][i][0]-playerradius,penaltyPosition[0][i][1]-playerradius);
            if(i==0 || i==1)
                iSetSpritePosition(&gk[i],penaltygk[!i][0]-playerradius,penaltygk[!i][1]-playerradius);
        }
        iSetSpritePosition(&fball,penaltyBall[0]-ballradius,penaltyBall[1]-ballradius);
        iSetSpritePosition(&pauseButtons,width-15,length-15);
    }
}

void timeUpdater(){
    if(fps!=0)
    {
        timer=timer+(120.0/(fps));
        if((page_number==1 || page_number==2) && !(ballstate==2 || ballstate==-2) && gameended!=1)
        {
            gametime=gametime+(120.0/(fps));
        }
    }
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
    if(gkpointer[0][0]<width/2-goalbar/2)
        gkpointer[0][0]=width/2-goalbar/2;
    else if(gkpointer[0][0]>width/2+goalbar/2)
        gkpointer[0][0]=width/2+goalbar/2;
    if(gkpointer[1][0]<width/2-goalbar/2)
        gkpointer[1][0]=width/2-goalbar/2;
    else if(gkpointer[1][0]>width/2+goalbar/2)
        gkpointer[1][0]=width/2+goalbar/2;
    
}

void activepassing()
{
    if(ballstate==1 || ballstate==2)
    {
        if(isKeyPressed('p')){
            passInitiated = 1;
            iPlaySound("kick.wav",false,volume);
            whistle_sound();
            crowd_sound();        
        }
        else if(isKeyPressed('l')){
            passInitiated = 1;
            iPlaySound("kick.wav",false,volume);
            
        }
        
        if(isKeyPressed('p') || isKeyPressed('l'))
        {
            ballpointer[2]=0;
            ballpointer[3]=0;
            varAcceleration[0]=0;
            varAcceleration[1]=0;
            if(isSpecialKeyPressed(GLUT_KEY_UP)){
                ballstate=0;
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
    if(ballstate==-1 || ballstate==-2)
    {
        if(isKeyPressed('t')){
            iPlaySound("kick.wav",false,volume);
            passedballspeed=passedballspeed;
        }
        else if(isKeyPressed('g')){
            iPlaySound("kick.wav",false,volume);
            passedballspeed=shootballspeed;
        }
        if(isKeyPressed('t') || isKeyPressed('g'))
        {
            ballpointer[2]=0;
            ballpointer[3]=0;
            varAcceleration[0]=0;
            varAcceleration[1]=0;
            if(isKeyPressed('w')){
                ballstate=0;
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

void activeplayermoveing()
{
    if(isKeyPressed('k'))
        speed=constSpeed*2;
    else
        speed=constSpeed;
    if((int)timer%25==0)chooseactiveplayer();
    if(activeplayer==-1)
    {
        if(isSpecialKeyPressed( GLUT_KEY_LEFT))
            gkpointer[0][0]=gkpointer[0][0]-gkspeed;
        else if(isSpecialKeyPressed( GLUT_KEY_RIGHT))
            gkpointer[0][0]=gkpointer[0][0]+gkspeed;
    }
    else if(isSpecialKeyPressed(GLUT_KEY_UP) || isSpecialKeyPressed( GLUT_KEY_DOWN ))
    {
        if(isSpecialKeyPressed(GLUT_KEY_UP)){
            if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                playerposition[1][activeplayer][0]-=speed/1.4;
                playerposition[1][activeplayer][1]+=speed/1.4;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerposition[1][activeplayer][0]+=speed/1.4;
                playerposition[1][activeplayer][1]+=speed/1.4;
            }
            else
                playerposition[1][activeplayer][1]+=speed;
        }
        if(isSpecialKeyPressed( GLUT_KEY_DOWN )){
            if(isSpecialKeyPressed(GLUT_KEY_LEFT)){
                playerposition[1][activeplayer][0]-=speed/1.4;
                playerposition[1][activeplayer][1]-=speed/1.4;
            }
            else if(isSpecialKeyPressed(GLUT_KEY_RIGHT)){
                playerposition[1][activeplayer][0]+=speed/1.4;
                playerposition[1][activeplayer][1]-=speed/1.4;
            }
            else
                playerposition[1][activeplayer][1]-=speed;
        }
    }
    else if(isSpecialKeyPressed( GLUT_KEY_RIGHT)){
        playerposition[1][activeplayer][0]+=speed;
    }
    else if(isSpecialKeyPressed( GLUT_KEY_LEFT)){
        playerposition[1][activeplayer][0]-=speed;
    }
}

void opponentplayermoveing()
{
    if(isKeyPressed('f'))
        speed=constSpeed*2;
    else
        speed=constSpeed;
    if((int)timer%25==0)chooseopponentactiveplayer();
    if(activeplayeropp==-1)
    {
        if(isKeyPressed( 'a'))
            gkpointer[1][0]=gkpointer[1][0]-gkspeed;
        else if(isKeyPressed( 'd'))
            gkpointer[1][0]=gkpointer[1][0]+gkspeed;
    }
    else if(isKeyPressed('w') || isKeyPressed( 's' ))
    {
        if(isKeyPressed('w')){
            if(isKeyPressed('a')){
                playerposition[0][activeplayeropp][0]-=speed/1.4;
                playerposition[0][activeplayeropp][1]+=speed/1.4;
            }
            else if(isKeyPressed('d')){
                playerposition[0][activeplayeropp][0]+=speed/1.4;
                playerposition[0][activeplayeropp][1]+=speed/1.4;
            }
            else
                playerposition[0][activeplayeropp][1]+=speed;
        }
        else if(isKeyPressed( 's' )){
            if(isKeyPressed('a')){
                playerposition[0][activeplayeropp][0]-=speed/1.4;
                playerposition[0][activeplayeropp][1]-=speed/1.4;
            }
            else if(isKeyPressed('d')){
                playerposition[0][activeplayeropp][0]+=speed/1.4;
                playerposition[0][activeplayeropp][1]-=speed/1.4;
            }
            else
                playerposition[0][activeplayeropp][1]-=speed;
        }
    }
    else if(isKeyPressed( 'd')){
        playerposition[0][activeplayeropp][0]+=speed;
    }
    else if(isKeyPressed( 'a')){
        playerposition[0][activeplayeropp][0]-=speed;
    }
}

void ballposition()
{
    if(ballstate==1 || ballstate==2)
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
    else if(ballstate==-1 || ballstate==-2)
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
    //iShowLoadedImage(width-15,length-15,&pauseButton);
    iShowSprite(&pauseButtons);
}

void backbutton()
{
    iShowLoadedImage(width-70,50, &backButton);
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
    
    if((int)timer%10==0)
    {
        throwCornerOutGoal(); 
        activepassing();
        opponentpassing();
    }
    if((int)timer%5==0){
        if(!(ballstate==2 || ballstate==-2))
            chooseAndTakePosition();
        if(ballstate!=2 && ballstate!=-2)
        {
            activeplayermoveing();
            opponentplayermoveing();
        }
        gkmoving();
        ballposition();
    }
    if((int)timer%4==0)
    {
        handlecollission();
    }
}

void chooselevel()
{

}



void resetPenaltyVariables()
{
    activeTeam = 0;
    gkSet = 0;
    gkDirection = 1;
    kicked = 0;
    penAcceleration[0] = 0;
    penAcceleration[1] = 0;
    memset(penScore, 0, sizeof(penScore));
    penBallSpeed = penBallSpeedConstant;
    barDiraction = 1;
    shootNumber = 0;
    penaltyscores[0] = 0;
    penaltyscores[1] = 0;
    hypo = 1;
    penaltyended = 0;
    whistlePlayed = 0;
    crowdPlaying = 0;
    passInitiated = 0;
    crowdChannel = -1;
    kickChannel = -1;
    goalChannel = -1;
    iStopAllSounds();
}
void resetflags()
{
    activeTeam=1-activeTeam;
    gkSet=0;
    kicked=0;
    speedFraction=50;
}

void gkAndPlayerPosition()
{
    if(!kicked)
    {
        penaltyBall[0]=penaltyPosition[activeTeam][5][0];
        penaltyBall[1]=penaltyPosition[activeTeam][5][1];
    }
    penaltyPosition[activeTeam][5][0]=width/2;
    penaltyPosition[activeTeam][5][1]=length - gallary - (length * .15);

    penaltyPosition[!activeTeam][5][0]=width/2- pow(-1,activeTeam)*spacing*6;
    penaltyPosition[!activeTeam][5][1]=length/2;
    penaltygk[activeTeam][0]=width/6;
    penaltygk[activeTeam][1]=length*15.0/16.0;
    if(gkSet==0)
    {
        penaltygk[!activeTeam][0]=width/2;
        penaltygk[!activeTeam][1]=length-gallary;
        gkSet=1;
    }
    else
    {
        if(penaltygk[!activeTeam][0]>width/2+goalbar/2)
        {
            penaltygk[!activeTeam][0]=width/2+goalbar/2;
            gkDirection=-1;
        }
        else if(penaltygk[!activeTeam][0]<width/2-goalbar/2)
        {
            penaltygk[!activeTeam][0]=width/2-goalbar/2;
            gkDirection=1;
        }
        else
        {
            penaltygk[!activeTeam][0]+=gkDirection*penGkSpeed;
        }
    }
}

void penaltyBallMoving()
{
    if(kicked==1)
    {
        //if(!(penaltyBall[2]==0 || (penAcceleration[0]>0 && penaltyBall[2]>0) || (penAcceleration[0]<0 && penaltyBall[2]<0)))
        {
            penaltyBall[0]+=penaltyBall[2];
            penaltyBall[2]+=penAcceleration[0];
        }
        //if(!(ballpointer[3]==0 || (penAcceleration[1]>0 && penaltyBall[3]>0) || (penAcceleration[1]<0 && penaltyBall[3]<0)))
        {
            penaltyBall[1]+=penaltyBall[3];
            penaltyBall[3]+=penAcceleration[1];
        }
    }
}

void ballDirection(double x,double y)
{
    if(!kicked)
    {
        if(speedFraction>30)
            penBallSpeed=(penBallSpeedConstant*speedFraction/100)+penBallSpeedConstant*0.5;
        else
            penBallSpeed=penBallSpeedConstant*speedFraction/100;
        hypo=sqrt(pow((penaltyBall[0]-ballradius-x),2)+pow((penaltyBall[1]-ballradius-y),2));
        if(hypo<1)
            return;
        penaltyBall[2]=penBallSpeed*(x-penaltyBall[0]+ballradius)/hypo;
        penaltyBall[3]=penBallSpeed*(y-penaltyBall[1]+ballradius)/hypo;
        penAcceleration[0]=0.3*acceleration*(x-penaltyBall[0]+ballradius)/hypo;
        penAcceleration[1]=0.3*acceleration*(y-penaltyBall[1]+ballradius)/hypo;
    }
    kicked=1;
}

void penaltyScore()
{
    if(kicked==1)
    {
        if(checkcollision(penaltyBall[0],penaltyBall[1],penaltygk[!activeTeam][0],penaltygk[!activeTeam][1],(playerradius+ballradius)))
        {
            penScore[activeTeam][shootNumber]=-1;
            if(activeTeam==1)
                shootNumber+=1;
            resetflags();
            iDelay(2);
        }
        else
        {
            if(penaltyBall[1]-1.5*ballradius>=length-gallary && penaltyBall[0]+ballradius>=width/2-goalbar/2 && penaltyBall[0]-ballradius<=width/2+goalbar/2)
            {
                penScore[activeTeam][shootNumber]=1;
                penaltyscores[activeTeam]++;
                printf("Attempting to load goal.wav\n");
                goalChannel = iPlaySound("goal.wav", false, volume);
                if (goalChannel == -1) {
                    printf("Failed to play goal.wav: %s\n", Mix_GetError());
                }
                if(activeTeam==1)
                    shootNumber+=1;
                resetflags();
                iDelay(1);
            }
            else if((abs((int)(penaltyBall[2]*10))<0.1 && abs((int)(penaltyBall[3]*10))<0.1))
            {
                penScore[activeTeam][shootNumber]=-1;
                if(activeTeam==1)
                    shootNumber+=1;
                resetflags();
                iDelay(1);
            }
            else if(penaltyBall[0]<gallary*2 || penaltyBall[0]>width-gallary*2 || penaltyBall[1]<length/2 || penaltyBall[1]>length )
            {
                penScore[activeTeam][shootNumber]=-1;
                if(activeTeam==1)
                    shootNumber+=1;
                resetflags();
                iDelay(1);
            }
        }
    }
}

void drawscoremarks()
{
    iSetColor(255,255,0);
    char score[10];
    sprintf(score,"Yello  %d",penaltyscores[0]);
    iTextAdvanced(1.5*gallary,100-5,score,0.1,1.5);
    iSetColor(0,0,255);
    sprintf(score,"Green %d",penaltyscores[1]);
    iTextAdvanced(1.5*gallary,100-30-5,score,0.1,1.5);

    for(int sc=0;sc<shootNumber+1;sc++)
    {
        if(penScore[0][sc]==-1)
        {
            iSetColor(255,0,0);
            iFilledCircle((4*gallary+sc*30),100,9);
        }
        else if(penScore[0][sc]==1)
        {
            iSetColor(255,255,0);
            iFilledCircle((4*gallary+sc*30),100,9);
        }
        if(penScore[1][sc]==-1)
        {
            iSetColor(255,0,0);
            iFilledCircle((4*gallary+sc*30),100-30,9);
        }
        else if(penScore[1][sc]==1)
        {
            iSetColor(0,0,255);
            iFilledCircle((4*gallary+sc*30),100-30,9);
        }
    }
}

void speedBar()
{
    if(speedFraction<=0.5)
    {
        speedFraction=1;
        barDiraction=+1;
    }
    else if(speedFraction>=99.5)
    {
        speedFraction=99;
        barDiraction=-1;
    }
    else
    {
        speedFraction=speedFraction+barDiraction*barspeed;
    }
}

void drawSpeedBar()
{
    iSetColor(255,255,255);
    iRectangle(width-2*gallary,length/2+barHieght/3,8,barHieght+2);
    iSetColor(255*(speedFraction)/100,115,0);
    iFilledRectangle(width-2*gallary+1,length/2+barHieght/3+1,6,barHieght*speedFraction/100);
}

int result()
{
    if(page_number==3)
    {
        if(shootNumber==max_shoot)
        {
            iSetColor(255,255,255);
            iTextAdvanced(120,400," DRAW",0.5,3.5);
        }
        else if(shootNumber>=5 && penaltyscores[0]!=penaltyscores[1] && activeTeam==0 && kicked==0)
        {
            if(penaltyscores[0]>=penaltyscores[1])
            {
                iSetColor(255,255,0);
            }
            else if(penaltyscores[0]<penaltyscores[1])
                iSetColor(0,0,255);
            iTextAdvanced(120,400,"YOU WON",0.5,3.5);
            backbutton();
            penaltyended=1;
            return 1;
        }
        else
            return 0;
    }
    else if(page_number==1 || page_number==2)
    {
        if(gametime>90*60*8)
        {
            if(scoreopp==scoreplayer)
            {
                iSetColor(255,255,255);
                iTextAdvanced(120,400," DRAW",0.5,3.5);
            }
            else
            {
                if(scoreopp>scoreplayer)
                {
                    iSetColor(255,255,0);
                }
                else if(scoreopp<scoreplayer)
                    iSetColor(0,0,255);
                iTextAdvanced(120,400,"YOU WON",0.5,3.5);
            }
            backbutton();
            gameended=1;
            return 1;
        }
        else
            return 0;
    }
}

void volumeMark() {
    if (volume == 100) {
        iSetColor(0, 255, 0); // Green for sound ON
        iFilledRectangle(300, 160, 110, 40);
        iSetColor(255, 255, 255);
        iText(330, 170, "ON", GLUT_BITMAP_HELVETICA_18);
    } else {
        iSetColor(255, 0, 0); // Red for sound OFF
        iFilledRectangle(300, 160, 110, 40);
        iSetColor(255, 255, 255);
        iText(330, 170, "OFF", GLUT_BITMAP_HELVETICA_18);
    }
}
int scoreSave() {
    FILE *ifp = fopen("scores.txt", "a+");
    if (ifp == NULL) {
        printf("Error opening scores.txt for writing: %s\n", strerror(errno));
        return 0;
    }
    if (page_number == 1 || page_number == 2) {
        fprintf(ifp, "Match - Team 0: %d  Team 1: %d\n", scoreopp, scoreplayer);
    } else if (page_number == 3) {
        fprintf(ifp, "Penalty - Team 0: %d  Team 1: %d\n", penaltyscores[0], penaltyscores[1]);
    }
    fclose(ifp);
    return 1;
}
void high_score() {
    FILE *ofp = fopen("scores.txt", "r");
    if (ofp == NULL) {
        printf("Error opening scores.txt: %s\n", strerror(errno));
        score_count = 0;
        return;
    }

    // Free previous scores
    if (scores != NULL) {
        free(scores);
        scores = NULL;
        score_count = 0;
        max_scores = 0;
    }

    char line[100];
    score_count = 0;
    max_scores = 10;
    scores = (ScoreEntry *)malloc(max_scores * sizeof(ScoreEntry));
    if (scores == NULL) {
        printf("Initial memory allocation failed\n");
        fclose(ofp);
        return;
    }

    while (fgets(line, sizeof(line), ofp)) {
        printf("Reading line: %s", line);
        char type[10];
        int team0, team1;
        line[strcspn(line, "\n")] = 0;
        if (sscanf(line, "%9s - Team 0: %d Team 1: %d", type, &team0, &team1) == 3) {
            printf("Parsed: Type=%s, Team0=%d, Team1=%d\n", type, team0, team1);
            if (score_count >= max_scores) {
                max_scores *= 2;
                ScoreEntry *temp = (ScoreEntry *)realloc(scores, max_scores * sizeof(ScoreEntry));
                if (!temp) {
                    printf("Realloc failed at score_count=%d\n", score_count);
                    free(scores);
                    scores = NULL;
                    score_count = 0;
                    max_scores = 0;
                    fclose(ofp);
                    return;
                }
                scores = temp;
            }
            strncpy(scores[score_count].type, type, sizeof(scores[score_count].type) - 1);
            scores[score_count].type[sizeof(scores[score_count].type) - 1] = '\0';
            scores[score_count].team0_score = team0;
            scores[score_count].team1_score = team1;
            score_count++;
        } else {
            printf("Failed to parse line: %s\n", line);
        }
    }
    fclose(ofp);
    printf("Loaded %d scores\n", score_count);
}
void drawHighScores() {
    // Draw white rectangle background (width=540, length=720)
    iSetColor(255, 255, 255); // White
    iFilledRectangle(50, 300, 440, 360); // Rectangle from (50, 300) to (490, 660)
    printf("Drawing white rectangle at (50, 300, 440, 360)\n");

    // Test text to confirm iText rendering
    iSetColor(0, 0, 0); // Black text for contrast
    iText(60, 640, "HIGH SCORES", GLUT_BITMAP_HELVETICA_18);
    printf("Drawing test text 'HIGH SCORES' at (60, 640)\n");

    // Draw scores or error message
    if (scores == NULL || score_count == 0) {
        iText(60, 610, "No scores loaded or file error", GLUT_BITMAP_HELVETICA_18);
        printf("No scores to display (score_count=%d, scores=%p)\n", score_count, (void*)scores);
        return;
    }

    char score_text[100];
    int y = 610; // Start scores below title
    for (int i = 0; i < score_count; i++) {
        sprintf(score_text, "%s - Team 0: %d  Team 1: %d", scores[i].type, scores[i].team0_score, scores[i].team1_score);
        iText(60, y, score_text, GLUT_BITMAP_HELVETICA_18);
        printf("Rendering score %d: %s at (60, %d)\n", i, score_text, y);
        y -= 30; // Space scores vertically
    }
}
/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    timeUpdater();
    iClear();
    if(page_number==0)
    {
        if(timer<=coverpagetime)
            iShowImage(0,0,"opener.jpg");
        else
            iShowImage(0,0,"newnavigation.jpg");
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
        if(!gameended)
        {
            functioncaller();
        }
        drawScoreboard();
        spritepositionupdate();
        spriteshow();
        result();
    }
    else if(page_number==2)
    {
        drawfield();
        functioncaller();
        spritepositionupdate();
        spriteshow();
        drawScoreboard();
        result();
    }
    else if(page_number==3)
    {
        drawfield();
        if(!result())
        {
            if((int)timer%2==0)
                gkAndPlayerPosition();
            if((int)timer%4==0)
                penaltyBallMoving();
            spritepositionupdate();
            drawSpeedBar();
        }
        if((int)timer%2==0 &&  !kicked)
            speedBar();
        spriteshow();  
        penaltyScore();
        drawscoremarks();
    }
    else if(page_number==4)
    { 
        iShowImage(0,0,"highscores.png");
                drawHighScores();
        backbutton();
    }
    else if(page_number==5)
    {
        iShowImage(0,0,"settings.png");
        volumeMark();
        backbutton();
    }
    else if(page_number==6)
    {
        iShowImage(0,0,"help.jpg");
        backbutton();
    }
    else if(page_number==7)
    {
        iShowImage(0,0,"exitpage.jpg");
        if(tracktime+75<=timer)
            exit(0);

    }
    iShowSpeed(10,10);
    char timertext[20];
    sprintf(timertext, "Timer: %lf", timer);
    iText(10,30,timertext);
    char fpss[20];
    sprintf(fpss,"gametime %lf",gametime);
    iText(50,50,fpss);
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
            if(mx>=136 && mx<=401)
            {
                if(my<=412  && my>=377)
                {
                    page_number=1;
                    resetvariables();
                }
                else if(my<=370  && my>=333)
                {
                    page_number=2;
                }
                else if(my<=328  && my>=290)
                {
                    page_number=3;
                }
                else if(my<=284  && my>=248)
                    page_number=4;
                else if(my<=241  && my>=205)
                    page_number=5;
                else if(my<=199  && my>=163)
                    page_number=6;
                else if(my<=157  && my>=120 )
                    page_number=7;
            }
            tracktime=timer;
        }
        else if(page_number==1 || page_number==2)
        {
            if(gameended==1)
            {
                if(mx>=width-70 && mx<=width-10 && my>=50 && my<=72)
                {
                    scoreSave();
                    page_number=0;
                    resetvariables();
                }
            }
            if(mx<width && mx>width-20 && my<length && my>length-20)
            {
                scoreSave();
                page_number=0;
                iStopAllSounds();
                gametime+=timer-tracktime;
            }
        }
        else if(page_number==3)
        {
            //crowd_sound();
            if(mx<width && mx>width-20 && my<length && my>length-20)
            {
                scoreSave();
                page_number=0;
                resetPenaltyVariables();
            }
            else
            ballDirection(mx,my);
            if(penaltyended==1)
            {
                if(mx>=width-70 && mx<=width-10 && my>=50 && my<=72)
                {
                    scoreSave();
                    page_number=0;
                    resetPenaltyVariables();
                }
            }
        }
        else if(page_number==5){
            if (mx >= 300 && mx <= 400 && my >= 160 && my <= 200) { // Sound button
                if (volume == 100) {
                    volume = 0; // Turn sound OFF
                    iStopAllSounds(); // Stop all sounds immediately
                    printf("Sound turned OFF\n");
                } else {
                    volume = 100; // Turn sound ON
                    printf("Sound turned ON\n");
                }
            }
            if(mx>=(width-70) && mx<=(width-10) && my>=50 && my<=72){
            page_number=0;
            }
        }
        else if(page_number==4){
                                if(mx>=(width-70) && mx<=(width-10) && my>=50 && my<=72){
                            page_number=0;
                    }
        }
        else if(page_number==6){
                                if(mx>=(width-70) && mx<=(width-10) && my>=50 && my<=72){
                            page_number=0;
                    }
        }
        else if(page_number==7){
                                if(mx>=(width-70) && mx<=(width-10) && my>=50 && my<=72){
                            page_number=0;
                    }
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
    //iSetTimer(1, timeUpdater);
    iInitializeSound();
    iInitialize(width, length, "2D Football");
    return 0;
}
