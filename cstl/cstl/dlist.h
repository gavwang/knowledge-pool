#ifndef _DLIST_H_
#define _DLIST_H_

template<typename T>
struct DNode
{ 
	T data;
	DNode* prev;
	DNode* next;
	DNode(const T& data_,DNode* prev_=NULL,DNode* next_=NULL):data(data_),prev(prev_),next(next_){}
};

template<typename T>
class diterator:public std::iterator<std::forward_iterator_tag,T>
{
public: 
	diterator()
	{
		t=NULL;
	}
	diterator(const diterator& other)
	{
		t=other.t;
	}

	diterator& operator=(const diterator& other)
	{
		t=other.t;
		return *this;
	}

	diterator(T* t_)
	{
		t=t_;
	}

	diterator& operator++()
	{
		t=t->next;
		return *this;
	}
 
	diterator operator++(int)
	{
		diterator iter=*this;
		t=t->next;
		return iter;
	}

	diterator& operator--()
	{
		t=t->prev;
		return *this;
	}

	diterator operator--(int)
	{
		diterator iter=*this;
		t=t->prev;
		return iter;
	}

	diterator operator+(int count)
	{ 
		diterator iter=*this;
		while (count-->0)
		{
			assert(t->next!=NULL);
			iter.t=iter.t->next;
		}
		return iter;
	}

	const diterator operator+(int count) const
	{ 
		diterator iter=*this;
		while (count-->0)
		{
			assert(t->next!=NULL);
			iter.t=iter.t->next;
		}
		return iter;
	}

	diterator operator-(int count)
	{ 
		diterator iter=*this;
		while (count-->0)
		{
			assert(t->prev!=NULL);
			iter.t=iter.t->prev;
		}
		return iter;
	}

	const diterator operator-(int count) const
	{ 
		diterator iter=*this;
		while (count-->0)
		{
			assert(t->prev!=NULL);
			iter.t=iter.t->prev;
		}
		return iter;
	}

	T& operator*()
	{
		return *t;
	} 
	const T& operator*() const
	{
		return *t;
	}

	T* operator->()
	{
		return t;
	}
	const T* operator->() const
	{
		return t;
	}

	inline bool operator!=(const diterator& other)
	{
		return t!=other.t;
	}
	inline bool operator!=(const diterator& other)const
	{
		return t!=other.t;
	}

	inline bool operator==(const diterator& other)
	{
		return t==other.t;
	}
	inline bool operator==(const diterator& other)const
	{
		return t==other.t;
	}

	inline bool operator<(const diterator& other)
	{
		return t<other.t;
	}
	inline bool operator<(const diterator& other)const
	{
		return t<other.t;
	}

	inline bool operator<=(const diterator& other)
	{
		return t<=other.t;
	}
	inline bool operator<=(const diterator& other)const
	{
		return t<=other.t;
	}

	inline bool operator>(const diterator& other)
	{
		return t>other.t;
	}
	inline bool operator>(const diterator& other)const
	{
		return t>other.t;
	}

	inline bool operator>=(const diterator& other)
	{
		return t>=other.t;
	} 
	inline bool operator>=(const diterator& other)const
	{
		return t>=other.t;
	} 

private: 
	T* t;
};

template<typename T>
class dlist
{
public:
	typedef diterator< DNode<T> > iterator;
	typedef const diterator< DNode<T> > const_iterator;
	dlist()
	{
		head=tail=NULL;
		size_=0;
	}
	~dlist()
	{
		clear();
	}

	void push_back(const T& t)
	{
		DNode<T>* tNode=new DNode<T>(t);
		if (head==NULL)
		{
			head=tail=tNode;
		}else{
			tail->next=tNode;
			tNode->prev=tail;
			tail=tNode;
		}
		size_++;
	}

	void pop_back()
	{
		if (tail!=NULL)
		{
			if (head==tail)
			{
				delete head;
				head=tail=NULL;
			}else{
				DNode<T>* tmpNode=tail;
				tail=tail->prev;
				tail->next=NULL;
				delete tmpNode;
			}
			size_--;
		}
	}

	void push_front(const T& t)
	{
		DNode<T>* tNode=new DNode<T>(t);
		if (head==NULL)
		{
			head=tail=tNode;
		}else{
			head->prev=tNode;
			tNode->next=head;
			head=tNode;
		}
		size_++;
	}

	void pop_front()
	{
		if (head!=NULL)
		{
			if (head==tail)
			{
				delete head;
				head=tail=NULL;
			}else{
				DNode<T>* tmpNode=head;
				head=head->next;
				head->prev=NULL;
				delete tmpNode;
			}
			size_--;
		}
	}

	void insert( iterator iter,const T& t)
	{
		if (iter==end())
		{
			push_back(t); 
		}else{
			DNode<T>* curItem=&*iter;
			DNode<T>* tNode=new DNode<T>(t);
			tNode->next=curItem;
			tNode->prev=curItem->prev; 
			if (curItem->prev)
			{
				curItem->prev->next=tNode;
			}
			curItem->prev=tNode;

			if (curItem==head)
			{ 
				head=tNode;
			} 
			if (curItem==tail)
			{
				tail=tNode;
			}
			size_++;
		}  
	}

	void erase(iterator iter)
	{
		if (iter==end())
		{
			return;
		}
		DNode<T>* tNode=&*iter;
		if (tNode==head)
		{
			if (head->next)
			{
				head->next->prev=NULL;
			} 
			head=head->next;
		}else if (tNode==tail)
		{
			if (tail->prev)
			{
				tail->prev->next=NULL; 
			}
			tail=tail->prev;
		}else{
			tNode->prev->next=tNode->next;
			tNode->next->prev=tNode->prev;
		}
		delete tNode;
		size_--;
	}

	void erase(iterator start,iterator last)
	{ 
		if (start==end())
		{
			return;
		}
		iterator iter = iterator(start);
		while (start!=last)
		{ 
			iter = iterator(iter->next);
			erase(start); 
			if (iter==end())
			{
				break;
			}
			start=iter;
		}
	}

	iterator begin()
	{
		assert(head!=NULL);
		return iterator(head);
	}

	iterator end()
	{
		assert(tail!=NULL);
		return iterator(tail->next);
	}

	T& front()
	{
		assert(head!=NULL);
		return head->data;
	}

	T& back()
	{
		assert(tail!=NULL);
		return tail->data;
	}

	int size()
	{
		return size_;
	}

	void clear()
	{
		if (head!=NULL)
		{
			DNode<T>* tmpNode=head->next;
			while (head!=NULL)
			{
				delete head;
				head=tmpNode;
				if (tmpNode!=NULL)
				{
					tmpNode=tmpNode->next;
				} 
			}
		}
		size_=0;
		head=tail=NULL;
	}

private:
	DNode<T>* head;
	DNode<T>* tail;
	int size_;
};

void dlistTest()
{
	dlist<int> l;
	for (int i=0;i<10;i++)
	{
		l.push_back(i);
	}
	l.insert(l.begin(),-1);
	l.insert(l.begin()+4,-1);
	l.insert(l.end(),-1);
	dlist<int>::iterator iter=l.begin(); 
	while (iter!=l.end())
	{
		cout<< iter->data<<" ";
		iter++;
	}
	cout<<endl;
	l.erase(l.begin());
	l.erase(l.begin()+3);
	l.erase(l.begin()+(l.size()-1));
	iter=l.begin();
	while (iter!=l.end())
	{
		cout<< iter->data<<" ";
		iter++;
	}
	cout<<endl;
	cout<<l.size()<<endl;
	l.erase(l.begin(),l.end());
	cout<<l.size()<<endl; 
	cout<<endl;
}

#endif