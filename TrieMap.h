#ifndef _TRIE___MAP__
#define _TRIE___MAP__

#include <map>
#include <stack>
template<class T, class D>
class TNodeItr;

template<class T, class D>
class TNode
{
	typedef std::map<T, TNode<T,D>* >           ChildList;
	typedef typename ChildList::iterator        ChildItr;
	typedef std::pair<T, TNode<T,D>* >          ChildPair;

	ChildList                                   mChildList;
	T                                           mKey;
	D*                                          mNodeValue;
	friend class TNodeItr<T, D>;

public:
	TNode():
	mNodeValue(0)
	{
	}
	TNode(T Key):
	mKey(Key),
	mNodeValue(0)
	{
	}


	~TNode()
	{
		FlushData();
	}

	D* Value()             {return mNodeValue;}
	T& Key()               {return mKey;}
	bool IsLeafNode()      {return (mNodeValue != 0);}
	int NoChildren()       {return (int) mChildList.size();}


	TNode<T,D>* GetChild(T key)
	{
		ChildItr itr = mChildList.find(key);
		if(itr != mChildList.end())
		{
			return itr->second;
		}
		return 0;
	}

	TNode<T,D>* InsertChild(T key)
	{
		ChildItr itr = mChildList.find(key);
		if(itr == mChildList.end())
		{
			TNode<T, D>* ptr = new TNode<T, D>(key);
			mChildList.insert(ChildPair(key, ptr ));
			return ptr;
		}
		else
		{
			return itr->second;
		}
	}

	void DeleteKey(T Key)
	{
	    ChildItr itr = mChildList.find(Key);
		if(itr != mChildList.end())
		{
			delete itr->second;
			mChildList.erase(itr);
		}
	}

	void SetValue(D data)
	{
		FlushData();
		mNodeValue = new D();
		*mNodeValue = data;
	}

	void FlushData()
	{
	    if(mNodeValue)
	    {
	    	delete mNodeValue;
	    	mNodeValue = 0;
	    }
	}
private:
	bool __IsEnd(const ChildItr& itr)
	{
		return (itr == mChildList.end());
	}
	bool __IsBegin(const ChildItr& itr)
	{
		return (itr == mChildList.begin());
	}

};

template<class T, class D>
class TNodeItr
{
	TNode<T, D>*                           mHead;
	typedef typename TNode<T, D>::ChildItr BaseItr;
	BaseItr                                mItr;
public:
	TNodeItr(TNode<T, D>* head):
    mHead(head)
	{
		if(mHead)
		{
			mItr = mHead->mChildList.begin();
		}
	}
	bool IsEnd()
	{
		if(mHead)
		{
			return mHead->__IsEnd(mItr);
		}
		return false;
	}
	bool IsBegin()
	{
		if(mHead)
		{
			return mHead->__IsBegin(mItr);
		}
		return false;
	}
	void operator ++()
	{
		mItr++;
	}
	void operator ++(int)
	{
		mItr++;
	}
	void operator --()
	{
		mItr--;
	}
	void operator --(int)
	{
		mItr--;
	}
	TNode<T, D>* Value()
	{
		return mItr->second;
	}
	T Key()
	{
		return mItr->first;
	}


};

template<class T, class D>
class TTrieMap
{
	TNode<T, D>   mHead;
	int           mDepth;
public:
	TTrieMap():
	mDepth(1)
	{
	}

	~TTrieMap()
	{
		__DeleteAllItems();
	}

	void Insert(T* tArray, int ArrSize, D Value)
	{
		TNode<T, D>* ref = &mHead;
		int depth = 1;
		for(int i = 0; i < ArrSize; i++)
		{
			if(ref)
			{
				ref = ref->InsertChild(tArray[i]);
				depth++;
			}
			else
			{
				break;
			}
		}
		if(ref)
		{
			ref->SetValue(Value);
		}
		if(depth > mDepth)
		{
			mDepth = depth;
		}

	}

	D* Value(T* tArray, int ArrSize)
	{
		if(ArrSize > mDepth)
		{
			return 0;
		}
		if(!tArray)
		{
			return 0;
		}
		TNode<T, D>* ref = &mHead;
		for(int i = 0; i < ArrSize; i++)
		{
			if(ref)
			{
				ref = ref->GetChild(tArray[i]);
			}
			else
			{
				return 0;
			}
		}
		if(ref)
		{
			if(ref->IsLeafNode())
			{
				return (ref->Value());
			}
		}
		return 0;
	}

	int MaxDepth()
	{
		return mDepth;
	}

	void Clear()
	{
		__DeleteAllItems();
	}

	bool Delete(T* tArray, int ArrSize)
	{
		if(ArrSize > mDepth)
		{
			return false;
		}
		if(!tArray)
		{
			return false;
		}
		TNode<T, D>* ref = &mHead;
		std::stack<TNode<T, D>* > Stack;
		for(int i = 0; i < ArrSize; i++)
		{
			if(ref)
			{
				ref = ref->GetChild(tArray[i]);
				Stack.push(ref);
			}
			else
			{
				return false;
			}
		}
		if(ref)
		{
			if(!ref->IsLeafNode())
			{
				return false;
			}
			else
			{
				ref->FlushData();
			}
			TNode<T, D>* nodeup = Stack.top();
			Stack.pop();
			T key = nodeup->Key();
			while(Stack.size() > 0)
			{
				TNode<T, D>* node = Stack.top();
				Stack.pop();
				if(node)
				{
					TNode<T, D>* child = node->GetChild(key);
					if(child)
					{
						if(child->NoChildren() == 0)
						{
							node->DeleteKey(key);
							key = node->Key();
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		return true;
	}
private:
	void __DeleteAllItems()
	{
		std::queue<TNode<T, D>* > Q;

		TNodeItr<T, D> itr(&mHead);
		while(!itr.IsEnd())
		{
			Q.push(itr.Value());
			itr++;
		}

		while(Q.size() > 0)
		{
			TNode<T, D>* node = Q.front();
			Q.pop();
			TNodeItr<T, D> itr1(node);
			while(!itr1.IsEnd())
			{
				Q.push(itr1.Value());
				itr1++;
			}

			delete node;
		}
	}

};


#endif
