#include "IndexTree.h"
#include "TrieMap.h"
#include <random>
#include <iostream>
#include <string.h>

using namespace std;
typedef IndexTreeSpace::CIndexTree<int> MT;
static int insertingPoint = 0;

void printMT(MT& mt)
{
	cout<<"Printing...."<<endl;
	cout<<"****************************************************"<<endl;
	int* data;
	int x = 0;
	for(int i = 0; i < mt.Size(); i++)
	{
		if(mt.Value(i, data))
		{
			cout<<" [ "<<i<<" ] = "<<*data<<" , ";
		}
		else
		{
			cout<<" [ "<<i<<" ] = NF , ";
		}
		x++;
		if(x == 6)
		{
			x = 0;
			cout<<endl;
		}
	}

	cout<<endl<<"Printing the structure"<<endl;
	mt.Print();
}

void pushbackAtMT(MT& mt, int insertSize)
{
	cout<<"Pushing "<<insertSize<<" elements"<<endl;
	for(int i = 0; i < insertSize; i++)
	{
		mt.Pushback(insertingPoint + 50000000);
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
		mt.Insert(x, insertingPoint + 60000000);
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


int TestIndexTree()
{


    int order =32;
    int pocketSize = 16;
    MT mt(pocketSize, order);
    const int pushbackSize = 50;
    int insertSize = 60;
    int deleteSize = 50;
    mt.Pushback(50);

    for(int i = 0; i < 24000; i++)
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
    	cout<<"Change in size "<<change<<endl;
    	if(((change == value) && (opType != 2)) || ((change == -value) && (opType == 2)))
    	{
    		cout<<"Best change BRAVOOOOOOOOOOOOOOOOOO"<<endl;
    	}
    	else
    	{
    		cout<<"Wanted to change by "<<value<<" but changed by "<<change<<endl;
    		cout<<"DISASTOR"<<endl;
    		break;
    	}
    	cout<<"****************************************************"<<endl<<endl<<endl;

    }
    printMT(mt);
    return 0;
}


void TestTrieMap()
{
	TTrieMap<char, int> tM;
	char Name[][30] =
	{
			"Akhilesh Mishra",
			"Abhishek Mishra",
			"Abhishek PAndey",
			"Preeti",
			"Ankita",
			"Akhilesh Tiwari",
			"Anuj kumar",
			"Poonam Khatri",
			"Pooja Majumdar",
			"Pooja Manya",
			"Abhinayak Guha",
			"Akhnipushkar bhaskar",
			"Aklaya Tunkshar",
			"Olivia vishtra",
			"Olka polka",
			"Prakriti pandey",
			"Proosanna das",
			"Pradeep tikka",
			"Praneeti pandey",
			"Akhtawar shoota",
			"Akhsindya vidharbha",
			"Akhhinda kumar",
			"Akkdimma majumdar",
			"Akhilya khanna",
			"Ponty Chaddha",
			"Ponnu Sami",
			"Piyush prakar"

	};

	int nameNum = 27;
	cout<<"****************************************************"<<endl;
	cout<<"Insertion"<<endl<<endl;
	cout<<"****************************************************"<<endl;
	for(int i = 0; i < nameNum; i++)
	{
		tM.Insert(Name[i], strlen(Name[i]), i);
		cout<<Name[i]<<" "<<i<<endl;
	}
	cout<<"****************************************************"<<endl<<endl<<endl;
	cout<<"Recanting"<<endl;
	cout<<"****************************************************"<<endl;
	int* myVal = 0;
	for(int i = 0; i < nameNum; i++)
	{
		myVal = tM.Value(Name[i], (int)strlen(Name[i]));
		if(myVal)
		{
			cout<<Name[i]<<" "<<*myVal<<endl;
		}
		else
		{
			cout<<Name[i]<<" ===>> NOT_________FOUND"<<endl;
		}
	}
	cout<<"****************************************************"<<endl<<endl<<endl;

}

int main()
{
	//TestIndexTree();
	TestTrieMap();
	return 0;
}

