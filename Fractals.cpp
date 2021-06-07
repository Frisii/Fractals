// Fractals.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <glut.h>
#include <cmath>

using namespace std;

int want;           //желанный фрактал
int n;              //кол-во приближений
int r;              //кол-во отрезков у трафарета
const int m = 16385;
double knx[m], kny[m];

//создание трафарета
void Traf(double xA, double yA, double xB, double yB, int r)
{
    knx[r] = xA;    kny[r] = yA;                                            //A
    knx[r + 1] = (2 * xA + xB) / 3;     kny[r + 1] = (2 * yA + yB) / 3;     //A1
    
    if (want == 3) //для инвентированной снежинки Коха
    {
        knx[r + 2] = (xB + xA) / 2 - (yA - yB) / (2 * sqrt(3.0));               //C_x
        kny[r + 2] = (yB + yA) / 2 - (xB - xA) / (2 * sqrt(3.0));               //C_y
    }
    else
    {
        knx[r + 2] = (xB + xA) / 2 + (yA - yB) / (2 * sqrt(3.0));               //C_x
        kny[r + 2] = (yB + yA) / 2 + (xB - xA) / (2 * sqrt(3.0));               //C_y
    }

    knx[r + 3] = (xA + 2 * xB) / 3;     kny[r + 3] = (yA + 2 * yB) / 3;     //B1
    knx[r + 4] = xB;    kny[r + 4] = yB;                                    //B
}

//построение фрактала
void Fract_krivaja_koha()
{
    Traf(-1.0, 0.0, 1.0, 0.0, 0);

    for (int j = 0; j < n; j++)
    {
        double kn1x[m], kn1y[m];
        r = pow(4.0, j + 1);
        
        for (int i = 0; i <= r; i++)
        {
            kn1x[i] = knx[i];
            kn1y[i] = kny[i];
        }

        for (int i = 0; i < r; i++)
            Traf(kn1x[i], kn1y[i], kn1x[i + 1], kn1y[i + 1], 4 * i);
    }
}

void Fract_snezhinka_koha()
{
    double Ax = -0.7, Ay = -0.4, Bx = 0.7, By = -0.4, Cx, Cy;
    Cx = (Bx + Ax) / 2 + (Ay - By) * sqrt(3.0) / 2;
    Cy = (By + Ay) / 2 + (Bx - Ax) * sqrt(3.0) / 2;
    Traf(Bx, By, Ax, Ay, 0);
    Traf(Ax, Ay, Cx, Cy, 4);
    Traf(Cx, Cy, Bx, By, 8);

    for (int j = 0; j < n; j++)
    {
        double kn1x[m], kn1y[m];   
        r = 3 * pow(4.0, j + 1);

        for (int i = 0; i <= r; i++)
        {
            kn1x[i] = knx[i];  
            kn1y[i] = kny[i];
        }

        for (int i = 0; i < r; i++)
            Traf(kn1x[i], kn1y[i], kn1x[i + 1], kn1y[i + 1], 4 * i);
    }
}

//рисование линий
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);
    glLineWidth(2.0);

    glBegin(GL_LINES);
        for (int i = 0; i < 4 * r; i++)
        {
            glVertex2d(knx[i], kny[i]);
            glVertex2d(knx[i + 1], kny[i + 1]);
        }
    glEnd();

    glFinish();
}

//no comment
int main(int argc, char **argv)
{
    cout << "1 - Krivaja Koha\n";
    cout << "2 - Snezhinka Koha\n";
    cout << "3 - Anti-Snezhinka Koha\n";
    cout << "\nVibor: ";
    cin >> want;
    cout << "\nKol-vo priblizhenij [1-5]: ";
    cin >> n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 800);

    //рисование
    switch (want)
    {
        case 1: glutCreateWindow("Кривая Коха");     
                glClearColor(0.0, 0.5, 1.0, 1.0);
                Fract_krivaja_koha();
                break;
        case 2: glutCreateWindow("Снежинка Коха");
                glClearColor(0.0, 0.5, 1.0, 1.0);
                Fract_snezhinka_koha();
                break;
        case 3: glutCreateWindow("Инвентированная снежинка Коха");
                glClearColor(0.0, 0.5, 1.0, 1.0);
                Fract_snezhinka_koha();
                break;
        default:
            break;
    }
    glutDisplayFunc(Draw);
    //

    glutMainLoop();
}