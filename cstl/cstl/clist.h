#ifndef _CLIST_H_
#define _CLIST_H_

namespace cth
{
	template<typename T>
	class literator
	{
	public: 
		literator()
		{
			t=NULL;
		}
		literator(const literator& other)
		{
			t=other.t;
		}

		literator& operator=(const literator& other)
		{
			t=other.t;
			return *this;
		}

		literator(T* t_)
		{
			t=t_;
		}

		literator& operator++()
		{
			t=t->next;
			return *this;
		}

		literator operator++(int)
		{
			literator iter=*this;
			t=t->next;
			return iter;
		}

		literator operator+(int count)
		{ 
			literator iter=*this;
			while (count-->0)
			{
				assert(t->next!=NULL);
				iter.t=iter.t->next;
			}
			return iter;
		}

		const literator operator+(int count) const
		{ 
			literator iter=*this;
			while (count-->0)
			{
				assert(t->next!=NULL);
				iter.t=iter.t->next;
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

		inline bool operator!=(const literator& other)
		{
			return t!=other.t;
		}
		inline bool operator!=(const literator& other)const
		{
			return t!=other.t;
		}

		inline bool operator==(const literator& other)
		{
			return t==other.t;
		}
		inline bool operator==(const literator& other)const
		{
			return t==other.t;
		}

		inline bool operator<(const literator& other)
		{
			return t<other.t;
		}
		inline bool operator<(const literator& other)const
		{
			return t<other.t;
		}

		inline bool operator<=(const literator& other)
		{
			return t<=other.t;
		}
		inline bool operator<=(const literator& other)const
		{
			return t<=other.t;
		}

		inline bool operator>(const literator& other)
		{
			return t>other.t;
		}
		inline bool operator>(const literator& other)const
		{
			return t>other.t;
		}

		inline bool operator>=(const literator& other)
		{
			return t>=other.t;
		} 
		inline bool operator>=(const literator& other)const
		{
			return t>=other.t;
		} 

	private: 
		T* t;
	};

	template<typename T>
	struct Node 
	{
		T data;
		Node* next;
	};

	template<typename T>
	class clist
	{
	public: 
		typedef literator<Node<T>> iterator;
		clist()
		{
			head=tail=NULL;
			size_=0;
		}
		void push_back(const T& t)
		{
			Node<T>* node=new Node<T>();
			node->data=t;
			node->next=NULL;
			if (head==NULL)
			{
				head=tail=node;
			}else{
				tail->next=node;
				tail=node;
			}
			size_++;
		}
		void push_front(const T& t)
		{
			Node<T>* node=new Node<T>();
			node->data=t;
			node->next=NULL;
			if (head==NULL)
			{
				head=tail=node;
			}else{
				node->next=head;
				head=node;
			}
			size_++;
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

		void erase_after(iterator& iter)
		{
			if (iter==end())
			{
				return;
			}
			Node<T>* t=iter->next;
			if (t!=NULL)
			{
				iter->next=t->next;
				delete t;
				size_--; 
			} 
		}
		
		void erase(iterator& iter)
		{
			if (iter==end())
			{
				return;
			}
			Node<T>* t=head;
			Node<T>* tmpNode=&*iter;
			if (head==tmpNode)
			{
				head=head->next;
				delete t;
				size_--; 
			}else 
			{
				while (t!=NULL)
				{
					if (t->next==tmpNode)
					{
						Node<T>* cur=tmpNode->next;
						t->next=cur;
						delete tmpNode;
						size_--;
						return;
					}
					t=t->next;
				}
			} 
		}
		void insert(iterator& iter,const T& item)
		{
			if (iter==end())
			{
				push_back(item);
				return;
			}
			Node<T>* t=&*iter;
			Node<T>* tmpNode=head;
			Node<T>* node=new Node<T>();
			node->data=item;
			if (head==t)
			{
				node->next=head;
				head=node;
			}else if (tail==t)
			{
				tail->next=node;
				tail=node;
			}else{ 
				while (tmpNode!=NULL && tmpNode->next!=t)
				{
					tmpNode=tmpNode->next;
				}
				if (tmpNode==NULL)
				{
					return; 
				}
				node->next=tmpNode->next;
				tmpNode->next=node;
			} 
			size_++;
		}

		T& operator[](int index)
		{
			assert(index>=0 && index<size_);
			Node<T>* t=head;
			while (index-->0)
			{
				t=t->next;		
			}
			return t->data;
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
		void pop_front()
		{
			assert(head!=NULL);
			Node<T>* tmpHead=head;
			if (head==tail)
			{
				tail=NULL;
			}
			head=tmpHead->next; 
			delete tmpHead;
			size_--;
		}

		void pop_back()
		{
			assert(tail!=NULL);
			Node<T>* tmpTail=head;
			if (head==tail)
			{
				delete tmpTail;
				head=tail=NULL;
			}else{
				while (tmpTail->next!=tail)
				{
					tmpTail=tmpTail->next;
				}
				delete tail;
				tmpTail->next =NULL;
				tail=tmpTail;
			} 
			size_--;
		}
		int size()
		{
			return size_;
		}
	 
		void clear()
		{
			if (head==NULL)
			{
				return;
			}
			Node<T>* tmpNode=head->next;
			while (tmpNode!=NULL )
			{ 
				delete head;
				head=tmpNode;
				tmpNode=tmpNode->next; 
			}
			delete head;
			head=tail=NULL;
			size_=0;
		}
		bool empty()
		{
			return size_==0;
		}
  
	private:
		Node<T>* head; 
		Node<T>* tail;
		int size_; 
	};

	void clistTest()
	{
		clist<int> list;
		for (int i=0;i<10;i++)
		{
			list.push_front(i);
		}

		for (int i=10;i<20;i++)
		{
			list.push_back(i);
		}

		for (int i=0;i<list.size();i++)
		{
			cout<<list[i]<<" ";
		}
		cout<<endl;
		list.clear();
		for (int i=0;i<10;i++)
		{
			list.push_back(i);
		}
		clist<int>::iterator iter=list.begin();
		list.insert(list.end(),111);
		iter=list.begin()+2;
		list.insert(iter,222);
		for (int i=0;i<list.size();i++)
		{
			cout<<list[i]<<" ";
		}
		cout<<endl;
		for (iter=list.begin();iter!=list.end();iter++)
		{ 
			cout<< iter->data <<" ";
		} 
		cout<<endl;
		iter=list.begin(); 
		list.erase(list.end()); 
		iter=list.begin()+3;  
		list.erase(iter); 
		iter=list.begin()+3; 
		list.erase_after(iter);
		for (iter=list.begin();iter!=list.end();iter++)
		{ 
			cout<< iter->data <<" ";
		} 
		cout<<endl;
		list.clear();
		for (int i=0;i<10;i++)
		{
			list.push_back(i);
		}
		while (list.size()>0)
		{
			cout<<list.back()<<" ";
			list.pop_back();
		}
		cout<<endl;
		list.clear();
		for (int i=0;i<10;i++)
		{
			list.push_back(i);
		}
		while (list.size()>0)
		{
			cout<<list.front()<<" ";
			list.pop_front();
		}
	}
}

#endif