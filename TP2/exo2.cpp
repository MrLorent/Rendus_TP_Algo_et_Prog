#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());

    sorted[0] = toSort[0];
    int count;
    bool inserted;

    for(int i=1; i<toSort.size(); i++){
        count = 0;
        inserted = false;
        while(count < sorted.size()-1 && !inserted){
            if(sorted.get(count) > toSort.get(i)){
                sorted.insert(count, toSort.get(i));
                inserted = true;
            }
            count++;
        }

        if(!inserted){
            sorted.insert(i, toSort.get(i));
        }
    }
	
	toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
