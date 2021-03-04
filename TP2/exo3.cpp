#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;


void bubbleSort(Array& toSort){
    int count;
    bool untouched;

    count = 0;

    while(count<toSort.size() && !untouched){
        untouched = true;
        for(int i=0; i < toSort.size()-1; i++){
            if(toSort.get(i) > toSort.get(i+1)){
                toSort.swap(i, i+1);
                untouched = false;
            }
        }
        count++;
    }
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 100;
	w = new TestMainWindow(bubbleSort);
	w->show();

	return a.exec();
}
