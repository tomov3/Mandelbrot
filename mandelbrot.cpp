#include <GLUT/glut.h>

#define MANDEL 1

//計算開始位置
#define P_X -2.0
#define P_Y -1.5

//計算範囲
#define RANGE 3.0

//ピクセル
#define P 10000

//発散条件
#define Z 3.5

//収束回数
#define N 30

//倍率
float z = 1.0;

//位置
float point_x = 0.0;
float point_y = 0.0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); //背景色で塗る
    glColor3d( 1.0, 0.0, 0.0 );   // 描画色を赤で指定(赤成分,緑成分,青成分)

    glPushMatrix();
    glScalef(z, z, 1.0);
    glTranslatef(point_x, point_y, 1.0);
    glCallList(MANDEL); 
    glPopMatrix();
    glutSwapBuffers();
}

void myinit()
{

    double STEP = RANGE / P;
    double zr, zi, tmpr, tmpi, cr, ci;
    int n;

    glNewList(MANDEL, GL_COMPILE);
    glPointSize( 0.01 );           // 点の大きさ指定(画素単位)

    glBegin(GL_POINTS);           // 表示対象(点群)作成

    for (int i=0; i<P; i++) {
        for (int j=0; j<P; j++) {
            n = 0;
            zr = zi = 0; 

            cr = P_X + (STEP*j);
            ci = P_Y + (STEP*i);

            do {
                tmpr = (zr*zr) - (zi*zi) + cr;
                tmpi = (zr*zi*2.0) + ci;

                zr = tmpr;
                zi = tmpi;
            } while (((zr*zr)+(zi*zi)) < Z*Z && (++n < N));

            if (n >= N) { 
                //集合に含まれる
                glColor3d(0.0, 0.0, 0.0);
                glVertex2d(cr, ci);
            } else {
                //集合に含まれない
                switch (n%10) {
                    case 0:
                        glColor3d(0.0, 0.0, 0.0);
                        break;
                    case 1:
                        glColor3d(0.0, 0.1, 0.1);
                        break;
                    case 2:
                        glColor3d(0.0, 0.2, 0.2);
                        break;
                    case 3:
                        glColor3d(0.0, 0.3, 0.3);
                        break;
                    case 4:
                        glColor3d(0.0, 0.4, 0.4);
                        break;
                    case 5:
                        glColor3d(0.0, 0.5, 0.5);
                        break;
                    case 6:
                        glColor3d(0.0, 0.6, 0.6);
                        break;
                    case 7:
                        glColor3d(0.0, 0.7, 0.7);
                        break;
                    case 8:
                        glColor3d(0.0, 0.8, 0.8);
                        break;
                    case 9:
                        glColor3d(0.0, 0.9, 0.9);
                        break;
                    default:
                        glColor3d(0.8, 0.8, 0.8);	  
                        break;
                }
                glVertex2d(cr, ci);
            }
        }
    }
    glEnd();
    glEndList();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case ' ':
            z += 0.1;
            break;
        default: break;
    }
    glutPostRedisplay();
}

void special_key(int key, int x, int y) 
{
    switch(key){
        case GLUT_KEY_LEFT: 
            point_x += 0.1;
            break;
        case GLUT_KEY_UP:
            point_y -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            point_x -= 0.1;
            break;
        case GLUT_KEY_DOWN:
            point_y += 0.1;
            break;

        default: break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);  // 表示領域をウィンドウ全体に指定
    glLoadIdentity(); 
    glOrtho(-(float)w/480.,(float)w/480.,-(float)h/480.,(float)h/480., -1.0, 1.0);
}

void init(void)
{
    glClearColor( 1.0f,1.0f,1.0f,1.0f );
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1000, 800);

    glutCreateWindow("mandelbrot");

    myinit();
    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_key);

    init();

    glutMainLoop();

    return 0;
}
