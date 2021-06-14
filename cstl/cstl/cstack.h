#ifndef _CSTACK_H_
#define _CSTACK_H_ 

#include "allocator.h"

namespace cth
{
	template<typename T,typename Allocator=MemoryPoolAllocator<> >
	class cstack
	{
	public:
		cstack(int capacity_=DefaultChunkCapacity) 
		{
			capacity=capacity_>=DefaultChunkCapacity?capacity_:DefaultChunkCapacity;
			allocator=new Allocator();
			stack_=stack_top_=(char*)allocator->Malloc(capacity);
			stack_end_=stack_+capacity;
		}

		T* push(int count=1)
		{
			assert(count>0);
			if (stack_top_+sizeof(T)*count>stack_end_)
			{
				size_t newCapacity=capacity<<1;
				size_t size=stack_top_-stack_;
				if (newCapacity<size+sizeof(T)*count)
				{
					newCapacity=size+sizeof(T)*count;
				}
				stack_=(char*)allocator->Realloc(stack_,capacity,newCapacity);
				capacity=newCapacity;
				stack_top_=stack_+size;
				stack_end_=stack_+capacity;
			}
			T* result=(T*)stack_top_;
			stack_top_+=sizeof(T)*count;
			return result;
		}

		T* top()
		{
			assert(stack_top_>stack_);
			return (T*)(stack_top_-sizeof(T));
		}
		T* back()
		{
			return (T*)stack_;
		}
		void pop()
		{
			assert(stack_top_>stack_);
			stack_top_-=sizeof(T);
		}

		size_t size()
		{
			return (stack_top_-stack_)/sizeof(T);
		}

		bool empty()
		{
			return size()==0;
		}
		~cstack()
		{
			delete allocator;
		}
	private:
		Allocator*  allocator;
		char* stack_;
		char* stack_top_;
		char* stack_end_;
		size_t capacity;
	};

 
	void cstackTest()
	{
		struct A
		{
			int x,y;
			A(int x_=0,int y_=0):x(x_),y(y_){}
		};

		cstack<A> q;
		for (int i=0;i<10;i++)
		{
			new (q.push()) A(i,i);
		}
		cout<<"size:"<<q.size()<<endl;
		cout<<"top:["<<q.top()->x<<","<<q.top()->y<<"]"<<endl;
		cout<<"back:["<<q.back()->x<<","<<q.back()->y<<"]"<<endl;
		while (q.size()>0)
		{
			A* i=q.top();
			q.pop();
			cout<<i->x<<" "<<i->y<<endl;
		}

	}
}
#endif