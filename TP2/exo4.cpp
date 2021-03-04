#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    Array& lowerArray = w->newArray(size);
    Array& greaterArray= w->newArray(size);
    int lowerSize = 0, greaterSize = 0; // effectives sizes
    int pivot;

    if(size > 1){
        pivot = toSort.get(0);
        // split
        for(int i=1; i<size; i++){
            if(toSort.get(i) < pivot){
                lowerArray.set(lowerSize,toSort.get(i));
                lowerSize++;
            }else{
                greaterArray.set(greaterSize,toSort.get(i));
                greaterSize++;
            }
        }

        lowerArray.set(lowerSize, pivot);
        lowerSize++;

        // recursiv sort of lowerArray and greaterArray
        recursivQuickSort(lowerArray, lowerSize);
        recursivQuickSort(greaterArray, greaterSize);

        // merge
        Array& sorted = w->newArray(size);

        for(int i=0; i<lowerSize; i++){
            sorted.set(i,lowerArray.get(i));
        }

        for(int i=0; i<greaterSize; i++){
            sorted.set(lowerSize + i,greaterArray.get(i));
        }

        toSort = sorted;

        return;
    }else{
        return;
    }
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
