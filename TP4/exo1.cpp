#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>
#include <array>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChild(int nodeIndex)
{
    return nodeIndex * 2 + 1;
}

int Heap::rightChild(int nodeIndex)
{
    return nodeIndex * 2 + 2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
    // use (*this)[i] or this->get(i) to get a value at index i
    int i = heapSize;
    this->set(i, value);

    while(i>0 && this->get(i) > this->get((i-1)/2)){
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i
    int i_max = nodeIndex;

    if(leftChild(nodeIndex) < heapSize && this->get(leftChild(nodeIndex)) > this->get(i_max)){
        i_max = leftChild(nodeIndex);
    }

    if(rightChild(nodeIndex) < heapSize && this->get(rightChild(nodeIndex)) > this->get(i_max)){
        i_max = rightChild(nodeIndex);
    }

    if(i_max != nodeIndex){
        swap(nodeIndex, i_max);
        heapify(heapSize, i_max);
    }
}

void Heap::buildHeap(Array& numbers)
{
    for(int i=0; i<numbers.size(); i++){
        this->insertHeapNode(i, numbers.get(i));
    }
}

void Heap::heapSort()
{
    for(int i=this->size()-1; i>=0;i--){
        swap(0, i);
        heapify(i,0);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
