#ifndef _CQUEUE_H_
#define _CQUEUE_H_
#include "allocator.h"

namespace cth
{
	template<typename T,typename Allocator=MemoryPoolAllocator<> >
	class cqueue
	{
	public:
		cqueue(int capacity_=DefaultChunkCapacity) 
		{
			capacity=capacity_>=DefaultChunkCapacity?capacity_:DefaultChunkCapacity;
			allocator=new Allocator();
			queue_head=queue_tail=(char*)allocator->Malloc(capacity);
			queue_end=queue_head+capacity;
		}

		T* push(int count=1)
		{
			assert(count>0);
			if (queue_tail+sizeof(T)*count>queue_end)
			{
				size_t newCapacity=capacity<<1;
				size_t size=queue_tail-queue_head;
				if (newCapacity<size+sizeof(T)*count)
				{
					newCapacity=size+sizeof(T)*count;
				}
				queue_head=(char*)allocator->Realloc(queue_head,capacity,newCapacity);
				capacity=newCapacity;
				queue_tail=queue_head+size;
				queue_end=queue_head+capacity;
			}
			T* result=(T*)queue_tail;
			queue_tail+=sizeof(T)*count;
			return result;
		}
		T* front()
		{
			assert(queue_tail>queue_head);
			return (T*)queue_head; 
		}
		T* back()
		{
			assert(queue_tail>queue_head);
			return (T*)(queue_tail-sizeof(T));
		}
		void pop()
		{
			assert(queue_tail>queue_head);
			queue_head+=sizeof(T);
		}

		size_t size()
		{
			return (queue_tail-queue_head)/sizeof(T);
		}

		bool empty()
		{
			return size()==0;
		}

		~cqueue()
		{
			delete allocator;
		}
	private:
		Allocator*  allocator;
		char* queue_head;
		char* queue_tail;
		char* queue_end;
		size_t capacity;
	};

	void cqueueTest()
	{
		struct A
		{
			int x,y;
			A(int x_=0,int y_=0):x(x_),y(y_){}
		};

		cqueue<A> s;
		for (int i=0;i<10;i++)
		{
			new (s.push()) A(i,i);
		}
		cout<<"size:"<<s.size()<<endl;
		cout<<"empty:"<<s.empty()<<endl;
		while (s.size()>0)
		{
			A* i=s.front();
			s.pop();
			cout<<i->x<<" "<<i->y<<endl;
		}
		cout<<endl;  
 
	}

}
#endif