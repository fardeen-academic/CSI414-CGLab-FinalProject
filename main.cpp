
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include<math.h>

GLfloat isOpening = 0, isOpen=0, isClosing = 0, shipIsMoving=1;

GLfloat translateX = 0, translateY = 0, translateRiver = 0;

GLfloat carMoveX=-1, shipMoveY = 0;

int dayState = 1;
GLfloat sun1 = 255, sun2=145, sun3=0;
GLfloat sky1 = 103, sky2=178, sky3=255;


int j;
int triangleAmount=30;
GLfloat twicePi = 2.0*3.1416;


GLfloat tRed1=255, tRed2 = 255, tRed3 = 255;
GLfloat tYellow1=255, tYellow2 = 255, tYellow3 = 255;
GLfloat tGreen1=0, tGreen2 = 150, tGreen3 = 136;

GLfloat river1=29, river2=128, river3=255;

GLfloat shipResize = 1;

int trafficState = 2;

void changeColor(){
    if(dayState==0){
        dayState=1;
        sun1 = 255;
        sun2=145;
        sun3=0;
        sky1=103;
        sky2=178;
        sky3=255;
        river1=29;
        river2=128;
        river3=255;
    }else{
        dayState=0;
        sun1=255;
        sun2=255;
        sun3=255;
        sky1=40;
        sky2=55;
        sky3=71;
        river1=0;
        river2=93;
        river3=142;
    }
}


void sky(){

    glBegin(GL_QUADS);
    glColor3ub(sky1, sky2, sky3);
    glVertex2f(800,800);
    glVertex2f(800,500);
    glVertex2f(-800,500);
    glVertex2f(-800,800);
    glEnd();

    //sun or moon
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(sun1, sun2, sun3);
    glVertex2f(600,625);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            600+(60*cos(j*twicePi/triangleAmount)),
            625+(60*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();
}

void trafficLight(){

    //lighting
    if(trafficState==0){
        tRed1=255;
        tRed2=0;
        tRed3=0;
    }else{
        tRed1=255;
        tRed2=255;
        tRed3=255;
    }

    if(trafficState==2){
        tGreen1 = 0;
        tGreen2 = 150;
        tGreen3 = 135;
    }else{
        tGreen1 = 255;
        tGreen2 = 255;
        tGreen3 = 255;
    }

    if(trafficState==1){
        tYellow1 = 255;
        tYellow2 = 255;
        tYellow3 = 0;
    }else{
        tYellow1 = 255;
        tYellow2 = 255;
        tYellow3 = 255;
    }

    //light
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(380,115);
    glVertex2d(410,115);
    glVertex2d(410,180);
    glVertex2d(380,180);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(395,50);
    glVertex2d(400,50);
    glVertex2d(400,120);
    glVertex2d(395,120);
    glEnd();

    //red light
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(tRed1, tRed2, tRed3);
    glVertex2f(395,170);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            395+(6*cos(j*twicePi/triangleAmount)),
            170+(6*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();

    //yellow light
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(tYellow2,tYellow2,tYellow3);
    glVertex2f(395,150);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            395+(6*cos(j*twicePi/triangleAmount)),
            150+(6*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(tGreen1, tGreen2, tGreen3);
    glVertex2f(395,130);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            395+(6*cos(j*twicePi/triangleAmount)),
            130+(6*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();
}

void drawShip(){

    glPushMatrix();
    glTranslatef(0,200+shipMoveY, 0);
    glScalef(2/shipResize,1.7/shipResize,1);


    //black outer shell
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(0, -380);
    glVertex2d(-40, -330);
    glVertex2d(0, -400);
    glVertex2d(40, -330);
    glEnd();
    //orange ship

    glBegin(GL_POLYGON);
    glColor3ub(204, 128, 38);
    glVertex2d(0, -380);
    glVertex2d(-40, -330);
    glVertex2d(-40, -260);
    glVertex2d(-20, -240);
    glVertex2d(0, -220);
    glVertex2d(0, -380);
    glVertex2d(40, -330);
    glVertex2d(40, -260);
    glVertex2d(20, -240);
    glVertex2d(0, -220);
    glEnd();

    //black lines
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2d(0, -360);
    glVertex2d(-30, -330);

    glVertex2d(-30, -330);
    glVertex2d(-30, -260);

    glVertex2d(-30, -260);
    glVertex2d(0, -230);

    glVertex2d(0, -360);
    glVertex2d(30, -330);

    glVertex2d(30, -330);
    glVertex2d(30, -260);

    glVertex2d(30, -260);
    glVertex2d(0, -230);
    glEnd();

    //black inner shell
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(-15, -310);
    glVertex2d(15, -310);
    glVertex2d(15, -270);
    glVertex2d(-15, -270);
    glEnd();


    glPopMatrix();
    if(shipIsMoving==1){
        if(shipMoveY<900){
            shipMoveY+=0.02;
        }
    }

    if (shipMoveY >= 800){
        shipMoveY=-730;
        shipResize=1;
    }

}

void drawCar(){
    glPushMatrix();

    glTranslatef(800+carMoveX, 90, 0);
    glScalef(0.7,0.7,1);
    //upper part
    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex2f(50,70);
    glVertex2f(0,35);
    glVertex2f(150,35);
    glVertex2f(120,70);
    glEnd();

    //window
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(55,65);
    glVertex2f(15,40);
    glVertex2f(140,40);
    glVertex2f(110,65);
    glEnd();

    //lower part
    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex2f(0,35);
    glVertex2f(-10,10);
    glVertex2f(150,10);
    glVertex2f(150,35);
    glEnd();

    //line between
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(0,35);
    glVertex2f(150,35);
    glEnd();


    //wheel


    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    GLfloat x = 30, y = 10, radius = 20;
    glVertex2f(x,y);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            x+(radius*cos(j*twicePi/triangleAmount)),
            y+(radius*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    x = 120;
    glVertex2f(x,y);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            x+(radius*cos(j*twicePi/triangleAmount)),
            y+(radius*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();



    glPopMatrix();

    if(carMoveX==0){
        changeColor();
    }
}

void drawCar2(){
    glPushMatrix();

    glTranslatef(-800-carMoveX, 90, 0);
    glScalef(0.7,0.7,1);
    //upper part
    glBegin(GL_QUADS);
    glColor3ub(0,0,255);
    glVertex2f(-50,70+110);
    glVertex2f(-0,35+110);
    glVertex2f(-150,35+110);
    glVertex2f(-120,70+110);
    glEnd();

    //window
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(-55,65+110);
    glVertex2f(-15,40+110);
    glVertex2f(-140,40+110);
    glVertex2f(-110,65+110);
    glEnd();

    //lower part
    glBegin(GL_QUADS);
    glColor3ub(0,0,255+110);
    glVertex2f(0,35+110);
    glVertex2f(10,10+110);
    glVertex2f(-150,10+110);
    glVertex2f(-150,35+110);
    glEnd();

    //line between
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(0,35+110);
    glVertex2f(-150,35+110);
    glEnd();


    //wheel


    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    GLfloat x = -30, y = 10+110, radius = 20;
    glVertex2f(x,y);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            x+(radius*cos(j*twicePi/triangleAmount)),
            y+(radius*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0);
    x = -120;
    glVertex2f(x,y);
    for(j=0;j<=triangleAmount;j++){
        glVertex2f(
            x+(radius*cos(j*twicePi/triangleAmount)),
            y+(radius*sin(j*twicePi/triangleAmount))
        );
    }
    glEnd();



    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_QUADS);
    glColor3ub(river1, river2, river3);
    glVertex2f(800,550);
    glVertex2f(800,-450);
    glVertex2f(-800,-450);
    glVertex2f(-800,550);
    glEnd();

    glPushMatrix();

    glTranslatef(translateRiver,0,0);
    translateRiver+=0.01;
    if(translateRiver>=800){
        translateRiver=0;
    }
    for(int i=-1600; i<=800; i+=220){
        for(int j=-400; j<=440; j+=80){
            glBegin(GL_LINES);
            glColor3ub(255,255,255);
            glVertex2f(i, j);
            glVertex2f(i+80, j);
            glEnd();

            glBegin(GL_LINES);
            glColor3ub(255,255,255);
            glVertex2f(i+110, j+40);
            glVertex2f(i+190, j+40);
            glEnd();
        }
    }

    glPopMatrix();


    //road left
    //pillar
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(-550,50);
    glVertex2f(-550,-80);
    glVertex2f(-650,-80);
    glVertex2f(-650,50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(102,102,102);
    glVertex2f(-500,50);
    glVertex2f(-700,50);
    glVertex2f(-600,-40);
    glEnd();


    //road
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(-400,240);
    glVertex2f(-400,50);
    glVertex2f(-800,50);
    glVertex2f(-800,240);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(-400,65);
    glVertex2f(-400,60);
    glVertex2f(-800,60);
    glVertex2f(-800,65);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(-400,230);
    glVertex2f(-400,225);
    glVertex2f(-800,225);
    glVertex2f(-800,230);
    glEnd();

    //dividers
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(-630,145);
    glVertex2f(-630,150);
    glVertex2f(-750,150);
    glVertex2f(-750,145);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(-450,145);
    glVertex2f(-450,150);
    glVertex2f(-570,150);
    glVertex2f(-570,145);
    glEnd();


    //rope pillar
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(-645,50);
    glVertex2f(-645,450);
    glVertex2f(-655,450);
    glVertex2f(-655,50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(-665,240);
    glVertex2f(-665,450);
    glVertex2f(-675,450);
    glVertex2f(-675,240);
    glEnd();




    //road right
    //pillar
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(550,50);
    glVertex2f(550,-80);
    glVertex2f(650,-80);
    glVertex2f(650,50);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(102,102,102);
    glVertex2f(500,50);
    glVertex2f(700,50);
    glVertex2f(600,-40);
    glEnd();

    //road
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(400,240);
    glVertex2f(400,50);
    glVertex2f(800,50);
    glVertex2f(800,240);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(400,65);
    glVertex2f(400,60);
    glVertex2f(800,60);
    glVertex2f(800,65);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(400,230);
    glVertex2f(400,225);
    glVertex2f(800,225);
    glVertex2f(800,230);
    glEnd();

    //dividers
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(630,145);
    glVertex2f(630,150);
    glVertex2f(750,150);
    glVertex2f(750,145);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(450,145);
    glVertex2f(450,150);
    glVertex2f(570,150);
    glVertex2f(570,145);
    glEnd();

    //rope pillar
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(645,50);
    glVertex2f(645,450);
    glVertex2f(655,450);
    glVertex2f(655,50);

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(665,240);
    glVertex2f(665,450);
    glVertex2f(675,450);
    glVertex2f(675,240);
    glEnd();

    glEnd();

    //bridge left
    //bridge
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(0-translateX,240+translateY);
    glVertex2f(0-translateX,50+translateY);
    glVertex2f(-400,50);
    glVertex2f(-400,240);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(0-translateX,65+translateY);
    glVertex2f(0-translateX,60+translateY);
    glVertex2f(-400,60);
    glVertex2f(-400,65);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(0-translateX,230+translateY);
    glVertex2f(0-translateX,225+translateY);
    glVertex2f(-400,225);
    glVertex2f(-400,230);
    glEnd();

    //dividers
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(-230-translateX/2,145+translateY/2.5);
    glVertex2f(-230-translateX/2,150+translateY/2.5);
    glVertex2f(-350-translateX/6,150+translateY/7);
    glVertex2f(-350-translateX/6,145+translateY/7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(-50-translateX/1.1,145+translateY/1.1);
    glVertex2f(-50-translateX/1.1,150+translateY/1.1);
    glVertex2f(-170-translateX/1.4,150+translateY/2);
    glVertex2f(-170-translateX/1.4,145+translateY/2);
    glEnd();


    //rope behind
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-675, 450);
    glVertex2f(0-translateX, 240+translateY);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-675, 430);
    glVertex2f(-50-translateX, 240+translateY/1.4);
    glEnd();


    //rope front
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-655, 440);
    glVertex2f(10-translateX/0.9, 50+translateY/1);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-655, 420);
    glVertex2f(-40-translateX, 50+translateY/1.2);
    glEnd();



    //bridge right
    //bridge
    glBegin(GL_QUADS);
    glColor3ub(102,102,102);
    glVertex2f(0+translateX,240+translateY);
    glVertex2f(0+translateX,50+translateY);
    glVertex2f(400,50);
    glVertex2f(400,240);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(0+translateX,65+translateY);
    glVertex2f(0+translateX,60+translateY);
    glVertex2f(400,60);
    glVertex2f(400,65);
    glEnd();

    //yellow stripe
    glBegin(GL_QUADS);
    glColor3ub(254,255,3);
    glVertex2f(0+translateX,230+translateY);
    glVertex2f(0+translateX,225+translateY);
    glVertex2f(400,225);
    glVertex2f(400,230);
    glEnd();

    //dividers
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(230+translateX/2,145+translateY/2.5);
    glVertex2f(230+translateX/2,150+translateY/2.5);
    glVertex2f(350+translateX/6,150+translateY/7);
    glVertex2f(350+translateX/6,145+translateY/7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(50+translateX/1.1,145+translateY/1.1);
    glVertex2f(50+translateX/1.1,150+translateY/1.1);
    glVertex2f(170+translateX/1.4,150+translateY/2);
    glVertex2f(170+translateX/1.4,145+translateY/2);
    glEnd();

    //rope behind
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(675, 450);
    glVertex2f(0+translateX, 240+translateY);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(675, 430);
    glVertex2f(50+translateX, 240+translateY/1.4);
    glEnd();

    //rope front
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(655, 440);
    glVertex2f(10+translateX/0.9, 50+translateY/1);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(655, 420);
    glVertex2f(40+translateX, 50+translateY/1.2);
    glEnd();

    //road railing

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(-800,55);
    glVertex2f(-800,50);
    glVertex2f(-400,50);
    glVertex2f(-400,55);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(800,55);
    glVertex2f(800,50);
    glVertex2f(400,50);
    glVertex2f(400,55);
    glEnd();

    drawCar();
    drawCar2();
    drawShip();
    trafficLight();
    sky();



    char text[22] = "Designed By Fardeen";
    glColor3f(0,0,0);
    glRasterPos3f(-750, -400, 0);
    for(int z=0; text[z]!='\0';z++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[z]);
    }


    if(shipMoveY>150){
        shipIsMoving=0;
    }

    if(shipMoveY>150  && (carMoveX>-750 || carMoveX<-1600)){
        isOpening=1;
        trafficState=0;
    }


    if(isOpening==0 && isClosing==0 && isOpen==0){
        carMoveX-=0.05;
    }


    //bridge opening

    if(isOpening){
        if(translateX<180){
        translateX+=0.02;
        translateY+=0.02;
        }else{
            isOpening = 0;
        }
    }else if(isClosing){

        if(translateX<=50){
            trafficState=1;
        }
        if(translateX>=0){
        translateX-=0.015;
        translateY-=0.015;
        }else{
            isClosing=0;
            trafficState=2;
        }
    }

    if(translateX>=180){
        isOpen=1;
        shipIsMoving=1;
    }

    if(shipMoveY>=200){
        isOpen=0;
        isClosing=1;
    }

    if(shipMoveY>=400){
        shipResize+=0.0001;
    }

    if(carMoveX<-1600){
        carMoveX=0;
    }

    glutPostRedisplay();
    glFlush();
}

void init (void)
{
    glOrtho(-800,800,-450,750,-1.0,1.0);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
            case 'e':
            case 'E':
                exit(0);
                break;
    }
}

void menu(int key){
    if(key==0){
        exit(0);
    }
}

int main(int a, char * *b){
    glutInit(&a, b);
    glutInitWindowSize(1200,900);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("CG Lab Final Project_CSE 068 07941");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("QUIT\t", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
