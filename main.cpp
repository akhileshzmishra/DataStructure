#include "IndexTree.h"
#include <random>
#include <iostream>

using namespace std;
typedef IndexTreeSpace::CIndexTree<int> MT;
static int insertingPoint = 0;

void printMT(MT& mt)
{
	cout<<"Printing...."<<endl;
	cout<<"****************************************************"<<endl;
	int* data;
	for(int i = 0; i < mt.Size(); i++)
	{
		if(mt.Value(i, data))
		{
			cout<<i<<" : "<<*data<<endl;
		}
		else
		{
			cout<<i<<" : XX Not Found XX"<<endl;
		}
	}

	cout<<"Printing the structure"<<endl;
	mt.Print();
}

void pushbackAtMT(MT& mt, int insertSize)
{
	cout<<"Pushing "<<insertSize<<" elements"<<endl;
	for(int i = 0; i < insertSize; i++)
	{
		mt.Pushback(insertingPoint + 500000);
	}
	insertingPoint += insertSize;
	cout<<"pushed"<<endl;
}

void InsertAtMT(MT& mt, int insertSize)
{
	cout<<"Inserting "<<insertSize<<" elements"<<endl;
	for(int i = 0; i < insertSize; i++)
	{
		int x = rand()%mt.Size();
		//cout<<"Inserting at "<<x<<endl;
		mt.Insert(x, insertingPoint + 600000);
	}
	insertingPoint += insertSize;

	cout<<"Inserted"<<endl;
}

void DeleteAtMT(MT& mt, int deletesize)
{
    int xElementsToDelete = deletesize;
    cout<<"Deleting "<<xElementsToDelete<<" Elements "<<endl;

    for(int i = 0; i < xElementsToDelete; i++)
    {
    	int x = rand()%mt.Size();
    	//cout<<"Deleting at "<<x<<endl;
    	mt.Delete(x);
    }

	cout<<"Deleted"<<endl;
}


int main()
{


    int order = 4;
    int pocketSize = 4;
    MT mt(pocketSize, order);
    const int pushbackSize = 50;
    int insertSize = 60;
    int deleteSize = 50;
    mt.Pushback(50);

    for(int i = 0; i < 500; i++)
    {
    	int sizeNow = mt.Size();
    	cout<<"****************************************************"<<endl;
    	cout<<"Operation Number " <<i<<endl;
    	cout<<"****************************************************"<<endl;
    	cout<<"Size now before operation :" <<sizeNow<<endl;
    	int opType = rand()%3;
    	int value = 0;
    	switch(opType)
    	{
    	case 0:
    		value = rand()%pushbackSize;
    		pushbackAtMT(mt, value);
    		break;
    	case 1:
    		value = rand()%insertSize;
    		InsertAtMT(mt, value);
    		break;
    	case 2:
    		value = rand()%deleteSize;
    		DeleteAtMT(mt, value);
    		break;
    	default:
    		break;
    	}
    	cout<<"Size now after operation :" <<mt.Size()<<endl;
    	int change = mt.Size() - sizeNow;
    	cout<<"Change in strength "<<change<<endl;
    	if(((change == value) && (opType != 2)) || ((change == -value) && (opType == 2)))
    	{
    		cout<<"Best change BRAVOOOOOOOOOOOOOOOOOO"<<endl;
    	}
    	else
    	{
    		cout<<"Wanted to change by "<<value<<" but changed by "<<change<<endl;
    		cout<<"DISASTOR"<<endl;
    		mt.Print();
    		break;
    	}
    	cout<<"****************************************************"<<endl<<endl<<endl;

    }
    printMT(mt);
    return 0;
}




