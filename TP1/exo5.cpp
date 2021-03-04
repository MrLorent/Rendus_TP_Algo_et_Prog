#include "tp1.h"
#include <QApplication>
#include <time.h>

void complexeCarre(Point * complexe);

int isMandelbrot(Point z, int n, Point point){
    if(n >= 0){
        complexeCarre(&z);
        z.x += point.x;
        z.y += point.y;

        if(sqrt(pow(z.x,2) + pow(z.y,2)) > 2){
            return 1;
        }else{
            return isMandelbrot(z,n-1,point);
        }
    }else{
        return 0;
    }
}

void complexeCarre(Point * complexe){
    complexe->x = pow(complexe->x, 2) - pow(complexe->y, 2);
    complexe->y = 2*complexe->x*complexe->y;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



