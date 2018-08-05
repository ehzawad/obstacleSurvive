#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>



#define PI 3.1416

#define MAX 15
#define MIN 5

auto timeUpdate = 100;

GLfloat top = 27.0f;
GLfloat oppoY = 0.0f;
GLfloat oppoX = 0.0f;
GLfloat oppo2Y = 0.0f;
GLfloat oppo2X = 0.0f;

GLfloat oppo3Y = 0.0f;
GLfloat oppo3X = 0.0f;
GLfloat positionx = 0.0f;

auto score = 0;


class Point {
    public:
    float x;
    float y;
    Point()
    {

    }

    Point(float X, float Y){
        this->x = X;
        this->y = Y;
    }

};




class Opponent {
    public:
        Point A;
        Point B;
        Point C;
        Point D;
        std::string name;
        Opponent()
        {

        }

         Opponent(Point& a, Point& b, Point& c, Point& d, std::string name) {
            this->A = a;
            this->B = b;
            this->C = c;
            this->D = d;
            this->name = name;
        }

        void oppocarDraw(int tx, int ty,int r,int g,int b)
        {
            glPushMatrix();
            glTranslatef(tx, ty, 0.0f);
            glColor3ub(r, g, b);
            glBegin(GL_QUADS);
            glVertex3d(A.x, A.y , 0);
            glVertex3d(B.x, B.y, 0);
            glVertex3d(C.x, C.y, 0);
            glVertex3d(D.x, D.y, 0);
            A.x = A.x + tx;
            B.x = B.x + tx;
            C.x = C.x + tx;
            D.x = D.x + tx;

            A.y = A.y + ty;
            B.y = B.y + ty;
            C.y = C.y + ty;
            D.y = D.y + ty;
            glEnd();
            glPopMatrix();

        }

        void ScoreUpdate()
        {
            if (this->C.y <= - 17) {
                score++;
            }
        }
};

class carObj {
    public:
        Point A;
        Point B;
        Point C;
        Point D;

        carObj()
        {

        }

        carObj(Point& a, Point& b, Point& c, Point& d) {
            this->A = a;
            this->B = b;
            this->C = c;
            this->D = d;
        }

        void PlayercarDraw()
        {
            glPushMatrix();
            glTranslatef(positionx, 0.0f, 0.0f);
            glColor3ub(100, 30, 240);
            glBegin(GL_QUADS);
            glVertex3d(A.x, A.y , 0);
            glVertex3d(B.x, B.y, 0);
            glVertex3d(C.x, C.y, 0);
            glVertex3d(D.x, D.y, 0);
            A.x = A.x + positionx;
            B.x = B.x + positionx;
            C.x = C.x + positionx;
            D.x = D.x + positionx;

            glEnd();
            glPopMatrix();

        }


};


carObj c;
Opponent cO;
Opponent c1;
Opponent c2;


void collisionCheck(carObj& o, Opponent& p)
{
    float yFaceToFaceCollide = abs(o.A.y - p.D.y);
    float yDownToFaceCollide = abs(o.C.y - p.D.y);
    float xLeftPlayerCollide = abs(o.A.x - p.D.x);
    // std::cout << xLeftPlayerCollide << std::endl;
    float xRightPlayerCollide = abs(o.B.x - p.C.x);
    // std::cout << xRightPlayerCollide << std::endl;

    if ((yFaceToFaceCollide <= 0 || yDownToFaceCollide <= 4) && (xLeftPlayerCollide < 3 || xRightPlayerCollide < 3)) {
        std::cout << "COLLIDED " << p.name << " " << std::endl;
    }
    else {
        /* std::cout << "NOT COLLIDED" << std::endl; */
        std::cout << timeUpdate << std::endl;

        // std::cout << score << std::endl;
    }

}



int randGen(int min, int max) {
  srand(time(NULL));
  return ((float) rand() / (float) RAND_MAX) * (max-min) + min;
}

void init()
{
    glClearColor(1, 1, 1, 0.0);
    // glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(-14, 14, -17, 17);
}

template <typename T>
void showPoint(T & c)
{
    std::cout << "p1: " << "x: " << c.A.x << " y: " << c.A.y <<  std::endl;
    std::cout << "p2: " << "x: " << c.B.x << " y: " << c.B.y <<  std::endl;
    std::cout << "p3: " << "x: " << c.C.x << " y: " << c.C.y <<  std::endl;
    std::cout << "p4: " << "x: " << c.D.x << " y: " << c.D.y <<  std::endl;
}

void timer(int value) {
    if (timeUpdate >= 20) {
        timeUpdate = timeUpdate - 0.15;
    }
    // std::cout << timeUpdate << std::endl;

    // std::cout << score << std::endl;

    glutTimerFunc(1000, timer, 0);
}

void updateOppo(int value) {
    if (oppoY <= -27) {
        oppoY = randGen(MIN, MAX);
        oppoX = randGen(-13, 2);
        oppoX++;
    }

    oppoY--;
    // std::cout << oppoY << std::endl;
    //
    //
    //

    glutPostRedisplay();
    glutTimerFunc(timeUpdate, updateOppo, 0);
}

void update2Oppo(int value) {
    if (oppo2Y <= -33) {
        oppo2Y = randGen(MIN, MAX);
        oppo2X = randGen(-7, 2);

        oppo2X++;
    }

    oppo2Y--;
    // std::cout << oppoY << std::endl;
    glutPostRedisplay();
    glutTimerFunc(timeUpdate, update2Oppo, 0);
}

void update3Oppo(int value) {
    if (oppo3Y <= -39) {
        oppo3Y = randGen(MIN, MAX);
        oppo3X = randGen(0, 2);
        oppo3X++;
    }

    oppo3Y--;
    // std::cout << oppoY << std::endl;
    glutPostRedisplay();
    glutTimerFunc(timeUpdate, update3Oppo, 0);
}


void update(int value) {

    if ( top <= 13 ) {
        top = 27.0f;
    }
        top--;

    // std::cout << top << std::endl;


    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}


void middleBar()
{
    glPushMatrix();
    glColor3ub(0, 30, 20);
    glBegin(GL_LINES);
    glVertex3d(0, top + 12, 0);
    glVertex3d(0, top - 2, 0);
    glBegin(GL_LINES);
    glVertex3d(0, top, 0);
    glVertex3d(0, top - 10, 0);


    // glEnd();
    glColor3ub(0, 30, 20);
    glBegin(GL_LINES);
    glVertex3d(0, top - 10 -2, 0);
    glVertex3d(0, top -10 - 10 -2, 0);
    // glEnd();
    glColor3ub(0, 30, 20);
    glBegin(GL_LINES);
    glVertex3d(0, top - 24, 0);
    glVertex3d(0, top - 24 -10, 0);
    glEnd();
    glPopMatrix();

}

void road()
{
    glPushMatrix();

    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(-8, +17, 0);
    glVertex3d(-8, -17, 0);
    glEnd();
    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(+8, +17, 0);
    glVertex3d(+8, -17, 0);
    glEnd();
    glPopMatrix();


}

void processSpecialKeys (int key, int mx, int my) {
    switch(key){
    case GLUT_KEY_LEFT :
        if (positionx >= -3) {
            positionx-=1.0;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT :
        if (positionx <= +8) {
            positionx+=1.0;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN :
        if (timeUpdate <= 200) {
            timeUpdate++;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP :
        timeUpdate--;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


void car()
{
    Point p1 =  Point(-4, -11);
    Point p2 =  Point(-1, -11);
    Point p3 =  Point(-1, -16);
    Point p4 =  Point(-4, -16);
    c = carObj(p1, p2, p3, p4);
    c.PlayercarDraw();
    // showPoint(c);
}


void carOppo()
{
    Point p1 =  Point(-4+7, -11+22);
    Point p2 =  Point(-1+7, -11+22);
    Point p3 =  Point(-1+7, -16+22);
    Point p4 =  Point(-4+7, -16+22);
    cO = Opponent(p1, p2, p3, p4, "car1");
    cO.oppocarDraw(oppoX, oppoY, 122, 143, 222);
    cO.ScoreUpdate();
    // showPoint(cO);
}

void car2Oppo()
{
    Point p1 =  Point(-4+7-5, -11+22+4);
    Point p2 =  Point(-1+7-5, -11+22+4);
    Point p3 =  Point(-1+7-5, -16+22+4);
    Point p4 =  Point(-4+7-5, -16+22+4);
    c1 = Opponent(p1, p2, p3, p4, "car2");
    c1.oppocarDraw(oppo2X, oppo2Y, 200, 155, 240);
    c1.ScoreUpdate();
    // showPoint(c1);

}

void car3Oppo()
{
    Point p1 =  Point(-4+7-5, -11+22+4);
    Point p2 =  Point(-1+7-5, -11+22+4);
    Point p3 =  Point(-1+7-5, -16+22+4);
    Point p4 =  Point(-4+7-5, -16+22+4);
    c2 = Opponent(p1, p2, p3, p4, "car3");
    c2.oppocarDraw(oppo3X, oppo3Y, 133, 299, 155);
    c2.ScoreUpdate();
    // showPoint(c2);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    road();
    glPopMatrix();

    glPushMatrix();
    car();
    glPopMatrix();
    glPushMatrix();
    carOppo();
    glPopMatrix();

    glPushMatrix();
    car2Oppo();
    glPopMatrix();

    // car3
    glPushMatrix();
    car3Oppo();
    glPopMatrix();

    middleBar();


    collisionCheck(c, cO);
    collisionCheck(c, c1);
    collisionCheck(c, c2);

    glutSwapBuffers();
    // glutPostRedisplay();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(2*280, 2*340);
    glutCreateWindow("Batman");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(100, updateOppo, 0);
    glutTimerFunc(100, update2Oppo, 0);
    glutTimerFunc(100, update3Oppo, 0);
    glutSpecialFunc(processSpecialKeys);
    glutMainLoop();
    return 0;
}
