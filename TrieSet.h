#ifndef _TRIE___SET__
#define _TRIE___SET__

#include <map>
#include <vector>
#include <stack>
#include <queue>

template<class T>
class TSNodeItr;

template<class T>
class TSNode
{
	typedef TSNode<T>                            _Class;
	typedef std::map<T, _Class* >                _ChildList;
	typedef typename _ChildList::iterator        _ChildItr;
	typedef std::pair<T, _Class* >               _ChildPair;

	_ChildList                                   m_ChildList;
	T                                            m_Key;
	bool                                         m_bLeaf;
	friend class TSNodeItr<T>;

public:
	TSNode():
    m_bLeaf(false)
	{
	}


	TSNode(T key):
	m_Key(key),
    m_bLeaf(false)
	{
	}
	

	~TSNode()              {}
	T& Key()               {return m_Key;}
	bool IsLeafNode()      {return m_bLeaf;}
	int NoChildren()       {return (int) m_ChildList.size();}


	_Class* GetChild(T data)
	{
		_ChildItr itr = m_ChildList.find(data);
		if(itr != m_ChildList.end())
		{
			return itr->second;
		}
		return 0;
	}

	_Class* InsertChild(T key)
	{
		_ChildItr itr = m_ChildList.find(key);
		if(itr == m_ChildList.end())
		{
			_Class* ptr = new _Class(key) ;
			m_ChildList.insert(_ChildPair(key, ptr ));
			return ptr;
		}
		else
		{
			return itr->second;
		}
	}

	void DeleteKey(T Key)
	{
	    _ChildItr itr = m_ChildList.find(Key);
		if(itr != m_ChildList.end())
		{
			delete itr->second;
			m_ChildList.erase(itr);
		}
	}

	void SetLeafNode(bool set)
	{
		m_bLeaf = true;
	}
	void FlushData()
	{
	    m_bLeaf = false;
	}
private:
	bool IsEnd(const _ChildItr& itr)
	{
		return (itr == m_ChildList.end());
	}
	bool IsBegin(const _ChildItr& itr)
	{
		return (itr == m_ChildList.begin());
	}

};

template<class T>
class TSNodeItr
{
	typedef TSNode<T>                          _Node;
	typedef typename _Node::_ChildItr          _BaseItr;

	_Node*                                     m_pHead;
	_BaseItr                                   m_Itr;
public:
	TSNodeItr(_Node* head):
	m_pHead(head)
	{
		if(m_pHead)
		{
			m_Itr = m_pHead->m_ChildList.begin();
		}
	}
	bool IsEnd()
	{
		if(m_pHead)
		{
			return m_pHead->IsEnd(m_Itr);
		}
		return false;
	}
	bool IsBegin()
	{
		if(m_pHead)
		{
			return m_pHead->IsBegin(m_Itr);
		}
		return false;
	}
	void operator ++()
	{
		m_Itr++;
	}
	void operator ++(int)
	{
		m_Itr++;
	}
	void operator --()
	{
		m_Itr--;
	}
	void operator --(int)
	{
		m_Itr--;
	}
	_Node* Value()
	{
		return m_Itr->second;
	}


};

template<class T>
struct TSetValue
{
	T*  Array;
	int SizeArray;

	TSetValue():
	Array(0),
	SizeArray(0)
	{
	}
	TSetValue(int size):
	Array(new T[size]),
	SizeArray(size)
	{
	}
	~TSetValue()
	{
		if(Array)
		{
			delete []Array;
			Array = 0;
			SizeArray = 0;
		}
	}
	TSetValue(const TSetValue<T>& other):
	Array(0),
	SizeArray(0)
	{
		if(other.SizeArray > 0)
		{
			Array = new T[other.SizeArray];
			memcpy(Array, other.Array, sizeof(T)*other.SizeArray);
			SizeArray = other.SizeArray;
		}
	}
	TSetValue<T>& operator = (const TSetValue<T>& other)
	{
		if(this == &other)
		{
			return *this;
		}
		if(Array)
		{
			delete []Array;
			Array = 0;
			SizeArray = 0;
		}
		if(other.SizeArray > 0)
		{
			Array = new T[other.SizeArray];
			memcpy(Array, other.Array, sizeof(T)*other.SizeArray);
			SizeArray = other.SizeArray;
		}
		return *this;

	}
	T& operator [](int x)
	{
		return Array[x];
	}
};

template<class T>
struct TSStackNode
{
	typedef TSNode<T>           _Node;

	_Node*                      Node;
	int                         Level;
	TSStackNode():
	Node(0),
	Level(0)
	{
	}
	TSStackNode(_Node* node, int level):
	Node(node),
	Level(level)
	{
	}
};

template<class T>
class TTrieSet
{
	typedef TSNode<T>           _Node;
	typedef TSNodeItr<T>        _NodeItr;
	typedef TSetValue<T>        _NodeSetVal;
	typedef TSStackNode<T>      _StackNode;

	_Node                       m_Head;
	int                         m_iDepth;
public:
	TTrieSet():
	m_iDepth(1)
	{
	}
	~TTrieSet()
	{
		DeleteAllItems();
	}
	void Insert(T* tArray, int ArrSize)
	{
		_Node*  ptr  = &m_Head;
		int depth = 1;
		for(int i = 0; i < ArrSize; i++)
		{
			if(ptr)
			{
				ptr = ((ptr)->InsertChild(tArray[i]));
				depth++;
			}
			else
			{
				break;
			}
		}
		if(ptr)
		{
			(ptr)->SetLeafNode(true);
		}
		if(depth > m_iDepth)
		{
			m_iDepth = depth;
		}

	}

	bool Value(T* tArray, int ArrSize)
	{
		if(ArrSize > m_iDepth)
		{
			return 0;
		}
		if(!tArray)
		{
			return 0;
		}

		_Node*  ptr  = &m_Head;
		_Node*& ref = ptr;
		for(int i = 0; i < ArrSize; i++)
		{
			if(ref)
			{
				ref = ref->GetChild(tArray[i]);
			}
		}
		if(ref)
		{
			if(ref->IsLeafNode())
			{
				return ref->IsLeafNode();
			}
		}
		return false;
	}
	int MaxDepth()
	{
		return m_iDepth;
	}
	bool Delete(T* tArray, int ArrSize)
	{
		if(ArrSize > m_iDepth)
		{
			return false;
		}
		if(!tArray)
		{
			return false;
		}
		_Node* ref = &m_Head;
		std::stack<_Node* > Stack;
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
			_Node* nodeup = Stack.top();
			Stack.pop();
			T key = nodeup->Key();
			while(Stack.size() > 0)
			{
				_Node* node = Stack.top();
				Stack.pop();
				if(node)
				{
					_Node* child = node->GetChild(key);
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
	std::vector<_NodeSetVal > GetAllMatches(T* tArray, int ArrSize)
	{
		std::vector<_NodeSetVal> result;
		if(ArrSize > m_iDepth)
		{
			return result;
		}
		if(!tArray)
		{
			return result;
		}
		if(m_iDepth > 0)
		{
			_NodeSetVal newVal(m_iDepth);

			memcpy(newVal.Array, tArray, ArrSize);
			TSNode<T>* ref = &m_Head;
			for(int i = 0; i < ArrSize; i++)
			{
				if(ref)
				{
					ref = ref->GetChild(tArray[i]);
				}
				else
				{
					return result;
				}
			}
			if(ref)
			{
				std::stack<_StackNode > Stack;
				Stack.push(_StackNode(ref, 0));
				int pos = ArrSize - 1;
				while(Stack.size() > 0)
				{
					_StackNode node = Stack.top();
					Stack.pop();
					if((node.Node->IsLeafNode()) || (node.Node->NoChildren() == 0))	
					{
						newVal[pos + node.Level] = node.Node->Key();
						newVal[pos + node.Level + 1] = 0;
						result.push_back(newVal);
					}
					else
					{
						newVal[pos + node.Level] = node.Node->Key();
						_NodeItr itr(node.Node);
						while(!itr.IsEnd())
						{
							Stack.push(_StackNode(itr.Value(), node.Level + 1));
							itr++;
						}
					}


				}

			}
			return result;

		}
		return result;
	}



private:
	void DeleteAllItems()
	{
		std::queue<_Node* > Q;

		_NodeItr itr(&m_Head);
		while(!itr.IsEnd())
		{
			Q.push(itr.Value());
			itr++;
		}

		while(Q.size() > 0)
		{
			_Node* node = Q.front();
			Q.pop();
			_NodeItr itr1(node);
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
