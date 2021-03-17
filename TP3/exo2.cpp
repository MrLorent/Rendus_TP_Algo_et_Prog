#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;


void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
    indexMin = indexMax = -1;
    int start = 0, end = array.size(), mid;

    while(start < end && indexMin == -1){
        if(end-start == 1 && array.get(end) == toSearch){
            indexMin = end;
        }else{
            mid = (start+end)/2;

            if(toSearch < array.get(mid)){
                end = mid;
            }else{
                if(toSearch > array.get(mid)){
                    start = mid + 1;
                }else{
                    end = mid;
                }
            }
        }
    }

    start = 0, end = array.size();

    while(start < end && indexMax == -1){
        if(end-start == 1 && array.get(start) == toSearch){
            indexMax = start;
        }else{
            mid = (start+end)/2;

            if(toSearch < array.get(mid)){
                end = mid;
            }else{
                if(toSearch > array.get(mid)){
                    start = mid + 1;
                }else{
                    start = mid;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
