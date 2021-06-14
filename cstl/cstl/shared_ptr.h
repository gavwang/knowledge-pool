#pragma once 

//简单实现的引用计数智能指针  

template<typename T>
class shared_count
{
public:
	shared_count(T* t=NULL):str(t),refCount(1){}
	~shared_count()
	{
		if (str) 
		{
			delete str; 
		}
	}
	void addref()
	{
		assert(InterlockedExchangeAdd(&refCount,0));
		InterlockedIncrement(&refCount);
	}
	int getref()
	{
		return InterlockedExchangeAdd(&refCount,0);
	} 
	void release()
	{
		assert(InterlockedExchangeAdd(&refCount,0));
		if(InterlockedDecrement(&refCount)==0)
		{
			delete this;
		}
	}

	T* str;
private:
	shared_count(const shared_count&);
	shared_count& operator=(const shared_count&);
	volatile long refCount;
};


template< typename T > 
class shared_ptr
{
public:
	typedef shared_ptr<T> this_type;

	shared_ptr(T* t)
	{ 
		str=t;
		scnt=new shared_count<T>(t);
	}

	shared_ptr(const shared_ptr& other)
	{ 
		str=other.str;
		scnt=other.scnt;
		if (scnt)
		{ 
			scnt->addref();
		}
	}

	shared_ptr& operator=(const shared_ptr& other)
	{
		if (this!=&other)
		{
			if (scnt)
			{
				scnt->release();
			}
			str=other.str;
			scnt=other.scnt;
			if (scnt)
			{ 
				scnt->addref();
			}
		}
		return *this;
	}

	~shared_ptr()
	{
		if (scnt)
		{
			scnt->release();
		}
	}

	LONG useCount()
	{
		return scnt ? scnt->getref() : 0;
	}

	T* get() const
	{
		return str;
	}

	T* operator->() const
	{
		assert(str!=NULL);
		return str;
	}

	T& operator*() const
	{
		assert(str!=NULL);
		return *str;
	}

	void reset()
	{
		this_type().swap(*this);
	}
 
	void swap( shared_ptr & other )
	{
		std::swap(str,other.str);
		std::swap(scnt,other.scnt);
	}
private:
	T* str;
	shared_count<T>* scnt;
};

template<typename T>
bool inline operator==(const shared_ptr<T>& p1,const shared_ptr<T>& p2)
{
	return p1.get()==p2.get();
}

template<typename T>
bool inline operator!=(const shared_ptr<T>& p1,const shared_ptr<T>& p2)
{
	return p1.get()!=p2.get();
}

template<typename T>
bool inline operator<(const shared_ptr<T>& p1,const shared_ptr<T>& p2)
{
	return p1.get()<p2.get();
}

 