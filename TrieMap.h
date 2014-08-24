#ifndef _TRIE___MAP__
#define _TRIE___MAP__

#include <map>
#include <stack>
template<class T, class D>
class TNodeItr;

template<class T, class D>
class TNode
{
	typedef TNode<T, D>                         _Class;
	typedef std::map<T, _Class* >               _ChildList;
	typedef typename _ChildList::iterator       _ChildItr;
	typedef std::pair<T, _Class* >              _ChildPair;


	_ChildList                                  m_ChildList;
	T                                           m_Key;
	D*                                          m_pNodeValue;
	friend class TNodeItr<T, D>;

public:
	TNode():
	m_pNodeValue(0)
	{
	}
	TNode(T Key):
	m_Key(Key),
	m_pNodeValue(0)
	{
	}


	~TNode()
	{
		FlushData();
	}

	D* Value()             {return m_pNodeValue;}
	T& Key()               {return m_Key;}
	bool IsLeafNode()      {return (m_pNodeValue != 0);}
	int NoChildren()       {return (int) m_ChildList.size();}


	_Class* GetChild(T key)
	{
		_ChildItr itr = m_ChildList.find(key);
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
			TNode<T, D>* ptr = new TNode<T, D>(key);
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

	void SetValue(D data)
	{
		FlushData();
		m_pNodeValue = new D();
		*m_pNodeValue = data;
	}

	void FlushData()
	{
	    if(m_pNodeValue)
	    {
	    	delete m_pNodeValue;
	    	m_pNodeValue = 0;
	    }
	}
private:
	bool __IsEnd(const _ChildItr& itr)
	{
		return (itr == m_ChildList.end());
	}
	bool __IsBegin(const _ChildItr& itr)
	{
		return (itr == m_ChildList.begin());
	}

};

template<class T, class D>
class TNodeItr
{
	typedef TNode<T, D>                      _Node;
	typedef typename _Node::_ChildItr        _BaseItr;

	_Node*                                   m_pHead;
	_BaseItr                                 m_Itr;
public:
	TNodeItr(_Node* head):
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
			return m_pHead->__IsEnd(m_Itr);
		}
		return false;
	}
	bool IsBegin()
	{
		if(m_pHead)
		{
			return m_pHead->__IsBegin(m_Itr);
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
	T Key()
	{
		return m_Itr->first;
	}


};

template<class T, class D>
class TTrieMap
{
	typedef TNode<T, D>            _Node;
	typedef TNodeItr<T, D>         _NodeItr;

	_Node                          m_Head;
	int                            m_iDepth;
public:
	TTrieMap():
	m_iDepth(1)
	{
	}

	~TTrieMap()
	{
		__DeleteAllItems();
	}

	void Insert(T* tArray, int ArrSize, D Value)
	{
		_Node* ref = &m_Head;
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
		if(depth > m_iDepth)
		{
			m_iDepth = depth;
		}

	}

	D* Value(T* tArray, int ArrSize)
	{
		if(ArrSize > m_iDepth)
		{
			return 0;
		}
		if(!tArray)
		{
			return 0;
		}
		_Node* ref = &m_Head;
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
		return m_iDepth;
	}

	void Clear()
	{
		__DeleteAllItems();
		m_iDepth = 1;
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
			else
			{
				ref->FlushData();
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
private:
	void __DeleteAllItems()
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
