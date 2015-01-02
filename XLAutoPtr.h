#ifndef _XLAUTOPTR_H_
#define _XLAUTOPTR_H_
#include <vector>


namespace XLAutoPtr
{

template<class T>
class RefCounterObject
{
	int        m_iCount;
	T*         m_pData;

	//not to be exposed
	RefCounterObject(const RefCounterObject&);
	RefCounterObject& operator = (const RefCounterObject&);
public:
	RefCounterObject(T* data):
	m_iCount(0),
	m_pData(data)
	{
		AddRef();
	}

	~RefCounterObject()
	{
		Release();
	}

	void AddRef()
	{
		if(m_pData)
		{
			m_iCount++;
		}
	}

	int RefCount() const
	{
		return m_iCount;
	}

	void Release()
	{
		if(m_pData)
		{
			m_iCount--;
			if(m_iCount == 0)
			{
				delete m_pData;
				m_pData = 0;
			}
		}
	}

	T* GetData()  const                  {return m_pData;}
};


template<class T>
class XLSharedSmPtr
{
	typedef RefCounterObject<T>           RefCounter;
	RefCounter*                           m_pData;
public:
	XLSharedSmPtr(T* data):
	m_pData(0)
	{
		SetData(data);
	}

	XLSharedSmPtr():
	m_pData(0)
	{
	}

	void SetData(T* data)
	{
		ReleaseData();
		m_pData = new RefCounter(data);
	}

	~XLSharedSmPtr()
	{
		ReleaseData();
	}

	XLSharedSmPtr(const XLSharedSmPtr& other)
	{
		m_pData = other.m_pData;
		if(m_pData)
		{
			m_pData->AddRef();
		}
	}

	XLSharedSmPtr<T>& operator = (const XLSharedSmPtr& other)
	{
		if(this == &other)
		{
			return *this;
		}

		ReleaseData();

		m_pData = other.m_pData;

		if(m_pData)
		{
			m_pData->AddRef();
		}

		return *this;

	}

	XLSharedSmPtr<T>& operator = (T* data)
	{
		SetData(data);
		return *this;
	}

	bool operator < (const XLSharedSmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() < other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 < other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() < 0;
		}
		return false;
	}

	bool operator > (const XLSharedSmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() > other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 > other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() > 0;
		}
		return false;
	}

	bool operator <= (const XLSharedSmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() <= other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 <= other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() <= 0;
		}
		return true;
	}

	bool operator >= (const XLSharedSmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() >= other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 >= other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() >= 0;
		}
		return true;
	}

	bool operator == (const XLSharedSmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() == other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return false;
		}
		else if(m_pData)
		{
			return false;
		}
		return true;
	}

	T* operator + (int x)
	{
		return (m_pData->GetData() + x);
	}

	XLSharedSmPtr<T>& operator += (int x)
	{
		if(m_pData)
		{
			m_pData->GetData() += x;
		}
		return *this;
	}

	T* operator - (int x)
	{
		return (m_pData->GetData() - x);
	}

	XLSharedSmPtr<T>& operator -= (int x)
	{
		if(m_pData)
		{
			m_pData->GetData() -= x;
		}
		return *this;
	}

	T* GetData()                                   
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}

	T& operator*()                                
	{
		return *(m_pData->GetData());
	}

	T* operator->()                                
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}


	operator const T*() const
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}


	operator T*()	
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}

	bool operator !()  const                            
	{
		if(m_pData)
		{
			return (m_pData->GetData() == 0);
		}
		return true;
	}

	operator bool() const                           
	{
		if(m_pData)
		{
			return (m_pData->GetData() != 0);
		}
		return false;
	}

private:

	void ReleaseData()
	{
		if(m_pData)
		{
			m_pData->Release();
			if(m_pData->GetData() == 0)
			{
				delete m_pData;
			}
			m_pData = 0;
		}
	}

};


////////////////////////////////////////////////////////

template<class T>
class RefCounterArrayObject
{
	int        m_iCount;
	T*         m_pData;

	//not to be exposed
	RefCounterArrayObject(const RefCounterArrayObject&);
	RefCounterArrayObject& operator = (const RefCounterArrayObject&);
public:
	RefCounterArrayObject(T* data):
	m_iCount(0),
	m_pData(data)
	{
		AddRef();
	}

	~RefCounterArrayObject()
	{
		Release();
	}

	void AddRef()
	{
		if(m_pData)
		{
			m_iCount++;
		}
	}

	int RefCount() const
	{
		return m_iCount;
	}

	void Release()
	{
		if(m_pData)
		{
			m_iCount--;
			if(m_iCount == 0)
			{
				delete[] m_pData;
				m_pData = 0;
			}
		}
	}

	T* GetData()  const                  {return m_pData;}
};


template<class T>
class XLSharedArraySmPtr
{
	typedef RefCounterArrayObject<T>           RefCounter;
	RefCounter*                                m_pData;
public:
	XLSharedArraySmPtr(T* data):
	m_pData(0)
	{
		SetData(data);
	}

	XLSharedArraySmPtr():
	m_pData(0)
	{
	}

	void SetData(T* data)
	{
		ReleaseData();
		m_pData = new RefCounter(data);
	}

	~XLSharedArraySmPtr()
	{
		ReleaseData();
	}

	XLSharedArraySmPtr(const XLSharedArraySmPtr& other)
	{
		m_pData = other.m_pData;
		if(m_pData)
		{
			m_pData->AddRef();
		}
	}

	XLSharedArraySmPtr<T>& operator = (const XLSharedArraySmPtr& other)
	{
		if(this == &other)
		{
			return *this;
		}

		ReleaseData();

		m_pData = other.m_pData;

		if(m_pData)
		{
			m_pData->AddRef();
		}

		return *this;

	}

	XLSharedArraySmPtr<T>& operator = (T* data)
	{
		SetData(data);
		return *this;
	}

	bool operator < (const XLSharedArraySmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() < other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 < other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() < 0;
		}
		return false;
	}

	bool operator > (const XLSharedArraySmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() > other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 > other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() > 0;
		}
		return false;
	}

	bool operator <= (const XLSharedArraySmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() <= other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 <= other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() <= 0;
		}
		return true;
	}

	bool operator >= (const XLSharedArraySmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() >= other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return 0 >= other.m_pData->GetData();
		}
		else if(m_pData)
		{
			return m_pData->GetData() >= 0;
		}
		return true;
	}

	bool operator == (const XLSharedArraySmPtr<T>& other) const
	{
		if(m_pData && other.m_pData)
		{
			return m_pData->GetData() == other.m_pData->GetData();
		}
		else if(other.m_pData)
		{
			return false;
		}
		else if(m_pData)
		{
			return false;
		}
		return true;
	}
	
	T* operator + (int x)
	{
		return (m_pData->GetData() + x);
	}

	T* operator - (int x)
	{
		return (m_pData->GetData() - x);
	}

	T* GetData()                                   
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}

	T& operator*()                                
	{
		return *(m_pData->GetData());
	}

	T* operator->()                                
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}


	operator const T*() const
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}


	operator T*()	
	{
		if(m_pData)
		{
			return m_pData->GetData();
		}
		return 0;
	}

	bool operator !()  const                            
	{
		if(m_pData)
		{
			return (m_pData->GetData() == 0);
		}
		return true;
	}

	operator bool() const                           
	{
		if(m_pData)
		{
			return (m_pData->GetData() != 0);
		}
		return false;
	}

private:

	void ReleaseData()
	{
		if(m_pData)
		{
			m_pData->Release();
			if(m_pData->GetData() == 0)
			{
				delete m_pData;
			}
			m_pData = 0;
		}
	}

};

//////////////////////////////////////////////////////////
template<class T>
class XLSmartPtr
{
	mutable T* m_ptr;

public:
	XLSmartPtr(T* data): m_ptr(data)
	{
	}
	XLSmartPtr(const XLSmartPtr& data)
	{
		m_ptr = data.m_ptr;
		data.m_ptr = 0;
	}
	~XLSmartPtr()
	{
		if(m_ptr)
		{
			delete m_ptr;
		}
	}
	bool Viable() const
	{ 
		return (m_ptr != 0);
	}
	T* operator->()
	{
		return m_ptr;
	}
	T& operator*()
	{
		return *m_ptr;
	}
	XLSmartPtr<T>& operator = (const XLSmartPtr& other)
	{
		if(this == &other)
			return *this;
		m_ptr = other.m_ptr;
		other.m_ptr = 0;
		return *this;
	}
	bool operator !() const
	{
		return !(Viable());
	}
	operator bool() const
	{
		return Viable();
	}
	operator T*()
	{
		return m_ptr;
	}

};

template<class T>
class XLSmartArrayPtr
{
	mutable T* m_ptr;

public:
	XLSmartArrayPtr(T* data): m_ptr(data)
	{
	}
	XLSmartArrayPtr(const XLSmartArrayPtr& data):m_ptr(0)
	{
		m_ptr = data.m_ptr;
		data.m_ptr = 0;
	}
	~XLSmartArrayPtr()
	{
		Clear();
	}
	bool Viable() const
	{
		return (m_ptr != 0);
	}
	T* operator->()
	{
		return m_ptr;
	}
	operator T*()
	{
		return m_ptr;
	}
	T* operator + (int value)
	{
		return (m_ptr + value);
	}
	T* operator - (int value)
	{
		return (m_ptr - value);
	}
	T& operator*()
	{
		return *m_ptr;
	}
	XLSmartArrayPtr<T>& operator = (const XLSmartArrayPtr& other)
	{
		if(this == &other)
			return *this;

		Clear();

		m_ptr = other.m_ptr;
		other.m_ptr = 0;

		return *this;
	}
	bool operator !() const
	{
		return !(Viable());
	}
	operator bool() const
	{
		return Viable();
	}

	T* GetIntArray()
	{
		return m_ptr;
	}

	void Clear()
	{
		if(m_ptr)
		{
			delete[] m_ptr;
			m_ptr = 0;
		}
	}

};




};


#endif
