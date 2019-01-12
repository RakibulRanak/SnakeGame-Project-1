#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include<MMsystem.h>

using namespace std;

void help();
void game();
void check();
void dead();
void level();
void high();
int snake_x[500],snake_y[500],snake_size = 5,score,highscore,spd = 80,l;
bool checkdied = false,BONUS = false;
bool easy=true,medium=false,hard=false,morse=false;
int maxx = getmaxx();
int  maxy = getmaxy()-50;
bool up=false;
bool down=true;
int y1=130,y2=150;
int *q;
int a=0,b=0;
int x = 40,y = 40;
string key = "right";


main()
{
    int gd = DETECT,gm;  /* request autodetection */
    initgraph(&gd,&gm,""); /* initialize graphics and local variables */
    int cursor_y = 130;
    char ch;
    setcolor(3);
    settextstyle(4,0,4);
    outtextxy(80,2," Project-1: Snake");
    settextstyle(6,0,2);
    setcolor(YELLOW);
    rectangle(18,90,460,195);
    line(18,120,460,120);
    setcolor(WHITE);
    outtextxy(20,95," SUBMITTED BY:");


    outtextxy(20,150,"MD. RAKIBUL HASAN");
    outtextxy(20,170,"REGISTRATION NO: 2017831005");

    setcolor(YELLOW);
    rectangle(18,235,460,345);
    line(18,265,460,265);
    setcolor(WHITE);
    outtextxy(20,240,"SUBMITTED TO: ");
    outtextxy(20,280,"ASIF MOHAMMED SAMIR SIR ");
    outtextxy(20,300,"ASSISTANT PROFESSOR");
    outtextxy(20,320,"IICT,SUST");
    outtextxy(40,420,"PRESS ANY KEY TO CONTINUE");

    ch=getch();
    PlaySound("welcome.wav",NULL,SND_FILENAME | SND_SYNC);

    while(1)
    {

        clearviewport();
        setcolor(YELLOW);
        settextstyle(5,0,6);
        outtextxy(180,30," Snake ");
        setcolor(9);
        settextstyle(3,0,3); /*this part prints menu again but inside while loop,because other functions will return here*/
        outtextxy(200,130,"New Game");
        outtextxy(200,160,"Help");
        outtextxy(200,190,"Select Level");
        outtextxy(200,220,"Highscore");
        outtextxy(200,250,"Exit");
        outtextxy(160,cursor_y,">");
        setcolor(WHITE);
        settextstyle(3,0,3);
        outtextxy(110,380,"Please Select Level First");

        if(kbhit)
        {

            ch = getch();
            setcolor(BLACK);
            outtextxy(160,cursor_y,">");
            if(ch == 13)
            {
                PlaySound("enter.wav",NULL,SND_FILENAME | SND_SYNC);
                if(cursor_y==250)
                    exit(0);
                else if(cursor_y==160)
                    help();
                else if(cursor_y==130)
                    game();
                else if(cursor_y==190)
                    level();
                else if(cursor_y==220)
                    high();
            }
        }
        setcolor(WHITE);
        if(ch==80)
        {
            PlaySound("select.wav",NULL,SND_FILENAME | SND_SYNC);
            cursor_y+=30;
            if(cursor_y > 250)
            {
                cursor_y=130;
            }
        }
        if(ch==72)
        {
            PlaySound("select.wav",NULL,SND_FILENAME | SND_SYNC);
            cursor_y-=30;
            if(cursor_y < 130)
            {
                cursor_y=250;
            }
        }
        outtextxy(160,cursor_y,">");
    }

    return 0;
}
void help()
{
    setcolor(WHITE);
    outtextxy(50,300,"Move the snake using the Arrow keys.");
    outtextxy(150,330,"Press 'Alt' to Pause");
    char ch = getch();
    clearviewport();
    return;
}
void game()
{

    clearviewport();
    freopen("GameData.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    key = "right";
    int maxx = getmaxx();
    int maxy = getmaxy()-50;
    x = 40,y = 40;

    int food_x = rand()%(maxx-10),food_y = rand()%(maxy-10);
    int temp;
    temp = food_x%20;
    food_x-=temp;
    temp = food_y%20;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    morse=false;
    int p=0;
    a=0;
    b=0;
    score=0;
    int page=0;
    while(true)
    {
        clearviewport();
        if(medium||hard)
        {
            //clearviewport();
            setcolor(15);

            rectangle(0,0,maxx,maxy);
            rectangle(10,10,maxx-10,maxy-10);
            setfillstyle(8, 14);
            floodfill(7,7,15);

            if(!hard)
            {
                setcolor(15);
                rectangle(305,80,315,340);
                setfillstyle(8, 14);
                floodfill(306,81,15);
            }


            if(hard)
            {
                int y1=130,y2=150;
                bar(125,y1+p,135,y1+160+p);
                bar(305,y2-p,315,y2+140-p);
                bar(505,y1+p,515,y1+160+p);
                if(up)
                {

                    p=p-3;
                    q=&p;
                }
                else
                {

                    p=p+3;
                    q=&p;
                }

                if(p==69)
                {
                    up=true;
                    down=false;

                }
                if(p==-69)
                {
                    up=false;
                    down=true;

                }

            }

        }
        if(score >0 && score%5==4)
            BONUS = true;
        else
        {
            bonus = 500;
            BONUS = false;
        }
        if(!BONUS || bonus == 0)
        {

            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,MAGENTA);
            circle(food_x,food_y,5); //x position,y position,size
            floodfill(food_x,food_y,MAGENTA);

        }
        else
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL,BLUE);
            circle(food_x,food_y,8);
            floodfill(food_x,food_y,BLUE);

            char spp[1000];
            sprintf(spp,"Hurry!! %d",bonus);
            setcolor(MAGENTA);
            outtextxy(250,10,spp);
            // clears
        }

        if(kbhit())
        {
            ch = getch();
            if(ch == 0)
                ch = getch();
            if(ch == 72 && key != "down" )
                key = "up";
            if(ch == 80 && key != "up")
                key = "down";
            if(ch == 75 && key != "right")
                key = "left";
            if(ch == 77 && key != "left")
                key = "right";
            if(ch == 27)
            {
                for(i=0; i<snake_size; i++)
                {
                    snake_x[i]=0;
                    snake_y[i]=0;
                }
                    snake_size=5;
                cleardevice();
                return;
            }

        }

        for(int _size = snake_size-2; _size >= 0; _size--)
        {
            snake_x[_size+1] = snake_x[_size];
            snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(RED);
        circle(snake_x[0],snake_y[0],8);//snake head
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(snake_x[0],snake_y[0],RED);


        setcolor(GREEN);
        for(int _size = 1; _size < snake_size; _size++)
        {
            circle(snake_x[_size],snake_y[_size],5);
            setfillstyle(SOLID_FILL,GREEN);
            floodfill(snake_x[_size],snake_y[_size],GREEN);
        }
        setcolor(YELLOW);
        line(0,maxy+3,maxx,maxy+3);

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(YELLOW);
        outtextxy(00,maxy+10,ara);
        sprintf(ara,"Bestscore: %d",highscore);
        setcolor(YELLOW);
        outtextxy(395,maxy+10,ara);

        delay(spd);
        if(snake_x[0] == food_x && snake_y[0]== food_y)
        {


            snake_size++;
            score++;
            //PlaySound("fruit3.wav",NULL,SND_FILENAME | SND_SYNC);
            Beep(1000,100);
            /* Snake eats food*/
            if(score%5==0 && score>0)
                score+=bonus;

            food_x = rand()%(maxx-10),food_y = rand()%(maxy-10);
            temp = food_x%20;
            food_x-=temp;
            temp = food_y%20;
            food_y-=temp;

        }

        while(food_x < 20 || food_x > maxx - 20 || food_y < 20 || food_y > maxy - 20)
        {
            food_x = rand()%(maxx-10),food_y = rand()%(maxy-10);
            temp = food_x%20;
            food_x-=temp;
            temp = food_y%20;
            food_y-=temp;
        }

        if(key == "right")
            x = x+10;
        if(x > maxx)
            x =0;
        if(key == "left")
            x = x-10;
        if(x < 0)
            x = maxx-(maxx%10);
        if(key == "up")
            y = y-10;
        if(y < 0)
            y = maxy-(maxy%10);
        if(key == "down")
            y = y+10;
        if(y > maxy)
            y = 0;

        check();
        if(checkdied)
        {
            dead();
            clearviewport();
            for(int i=0; i<5; i++)
            {
                snake_x[i]=0;
                snake_y[i]=0;
            }
            return;
        }

        if(BONUS)
        {
            if(bonus>0)
                bonus-=10;
        }

    }
    //clearviewport();
}
void check()
{
    freopen("GameData.dat","w",stdout);
    int maxx = getmaxx();
    int  maxy = getmaxy()-50;
    if(highscore < score)
        cout << score << endl;
    else
        cout << highscore << endl;

    for(int i = 1; i < snake_size; i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {
            morse=true;
            goto here;
        }
    }
    if(medium||hard)
    {
        if(snake_x[0]<=10||snake_x[0]>=maxx-15||snake_y[0]<=10||snake_y[0]>=maxy-10)
        {
            morse=true;
            goto here;


        }
        if(medium)
        {
            if(snake_x[0]==310 && snake_y[0]>=80 && snake_y[0]<=340)
            {
                morse=true;
                goto here;
            }
        }
        if(hard)
        {
            for(int i=0; i<snake_size; i++)
            {
                if(snake_x[i]==130 && snake_y[i]>=(y1+*q) &&snake_y[i]<=(y1+160+*q))
                {
                    morse=true;
                    goto here;
                }
                if(snake_x[i]==310 && snake_y[i]>=(y2-*q) &&snake_y[i]<=(y2+140-*q))
                {
                    morse=true;
                    goto here;
                }
                if(snake_x[i]==510 && snake_y[i]>=(y1+*q) &&snake_y[i]<=(y1+160+*q))
                {
                    morse=true;
                    goto here;
                }
            }

        }

    }

here:
    ;
    if(morse)
    {
        delay(1000);
        setcolor(WHITE);
        for(int i = 0; i < snake_size; i++)
        {
            circle(snake_x[i],snake_y[i],5);
            setfillstyle(SOLID_FILL,RED);
            floodfill(snake_x[i],snake_y[i],WHITE);
        }
        settextstyle(8,HORIZ_DIR,9);
        outtextxy(70,120,"GAME OVER");
        setcolor(YELLOW);
        settextstyle(6,HORIZ_DIR,2);
        outtextxy(140,380,"Press Enter for start menu");


        PlaySound("gameover.wav",NULL,SND_FILENAME | SND_SYNC);

        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if(ch == 13)
                {
                    checkdied = true;
                    return;
                }
            }
        }
    }
    if(score>500&&easy)
    {
        easy=false;
        medium=true;
        hard=false;
        spd=70;
        if(a==0)
        {
            setcolor(YELLOW);
            outtextxy(150,130,"NEW LEVEL UNLOCKED!!!");
            PlaySound("tada.wav",NULL,SND_FILENAME | SND_SYNC);
            a=1;
            for(int i=0; i<snake_size; i++)
            {
                snake_x[i]=0;
                snake_y[i]=0;
            }
            snake_size=5;
            x=40;
            y=40;
            key="right";

        }

    }
    if (score>950&&medium)
    {
        medium=false;
        hard=true;
        easy=false;
        if(b==0)
        {
            setcolor(YELLOW);
            outtextxy(110,130,"NEW LEVEL UNLOCKED!!!");
            PlaySound("tada.wav",NULL,SND_FILENAME | SND_SYNC);
            b=1;
            for(int i=0; i<snake_size; i++)

            {
                snake_x[i]=0;
                snake_y[i]=0;
            }
            snake_size=5;
            x=40;
            y=40;
            key = "right";


        }
    }

}
void dead()
{
    checkdied = false;
    snake_size = 5;
    score = 0;
//    clearviewport();
}
void level()
{
    clearviewport();
    char ch;
    char ara[100];
    int cursor_y=130;
    while(true)
    {
        clearviewport();
        setcolor(9);
        outtextxy(200,130,"Easy");
        outtextxy(200,160,"Medium");
        outtextxy(200,190,"Hard");
        outtextxy(160,cursor_y,">");
        if(kbhit)
        {
            ch = getch();
            setcolor(BLACK);
            outtextxy(160,cursor_y,">");
            if(ch == 13)
            {
                PlaySound("enter.wav",NULL,SND_FILENAME | SND_SYNC);
                if(cursor_y==130)
                {
                    easy=true;
                    spd=80;
                    medium=false;
                    hard=false;
                    return;
                }
                else if(cursor_y==160)
                {
                    medium=true;
                    spd=70;
                    easy=false;
                    hard=false;
                    return;
                }

                else if(cursor_y==190)
                {
                    hard=true;
                    spd=70;
                    easy=false;
                    medium=false;
                    return;
                }

            }
        }
        if(ch==80)
        {
            PlaySound("select.wav",NULL,SND_FILENAME | SND_SYNC);
            cursor_y+=30;
            if(cursor_y > 190)
            {
                cursor_y=130;
            }
        }
        if(ch==72)
        {
            PlaySound("select.wav",NULL,SND_FILENAME | SND_SYNC);
            cursor_y-=30;
            if(cursor_y < 130)
            {
                cursor_y=190;
            }
        }
        setcolor(BLUE);
        outtextxy(160,cursor_y,">");
    }

    clearviewport();
}
void high()
{
    freopen("GameData.dat","r",stdin);
    cin >> highscore;
    char ara[100];
    sprintf(ara,"Highscore: %d",highscore);
    setcolor(WHITE);
    outtextxy(170,350,ara);
    char ch = getch();
    clearviewport();
}
