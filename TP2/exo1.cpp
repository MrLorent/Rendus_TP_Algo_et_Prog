#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){
    int tabSize = toSort.size(), positionMin;

    for(int i=0; i<tabSize; i++){

        for(int j=i; j<tabSize; j++){
            if(toSort.get(j) < toSort.get(i)){
                positionMin = j;
            }
        }

        toSort.swap(i, positionMin);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
