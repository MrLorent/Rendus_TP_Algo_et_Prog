#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)

	// initialisation
    int firstSize = origin.size()/2, secondSize = origin.size()-firstSize;
    Array& first = w->newArray(firstSize);
    Array& second = w->newArray(secondSize);
	
	// split
    for(int i=0; i<origin.size(); i++){
        if(i<firstSize){
            first.set(i, origin.get(i));
        }else{
            second.set(i-firstSize, origin.get(i));
        }
    }

	// recursiv splitAndMerge of lowerArray and greaterArray
    if(firstSize > 1){
        splitAndMerge(first);
    }
    if(secondSize > 1){
        splitAndMerge(second);
    }

	// merge
    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result)
{
    int firstSize = first.size(), secondSize = second.size(), totalSize = result.size();
    int rangeReachedFirst = 0, rangeReachSecond = 0;

    for(int i=0; i<totalSize; i++){
        if(rangeReachedFirst == firstSize || rangeReachSecond == secondSize){
            if(rangeReachedFirst == firstSize){
                result.set(i,second.get(rangeReachSecond));
                rangeReachSecond++;
            }else{
                result.set(i,first.get(rangeReachedFirst));
                rangeReachedFirst++;
            }
        }else{
            if(first.get(rangeReachedFirst) <= second.get(rangeReachSecond)){
                result.set(i,first.get(rangeReachedFirst));
                rangeReachedFirst++;
            }else{
                result.set(i,second.get(rangeReachSecond));
                rangeReachSecond++;
            }
        }
    }
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
