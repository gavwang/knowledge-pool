#ifndef _CSORTVECTOR_H_
#define _CSORTVECTOR_H_

namespace cth
{
	template<typename T>
	class csortvector:public NoCopy
	{
	public:  
		typedef const T* const_iterator; 
		typedef T* iterator;
		csortvector()
		{
			initData(0);
		}

		csortvector(int capa,const T& val=T())
		{
			initData(capa);
			newCapacity(capacity_);
			for (int i=0;i<size_;i++) 
				buf[i]=val; 
		}

		~csortvector()
		{
			if (buf)
			{
				delete[] buf;
				buf=NULL;
			}
			size_=capacity_=0;
		}

		int add(const T& t )
		{  
			int index=-1;
			if (size_==0)
			{  
				newCapacity(calculateCapacity()); 
				buf[size_++]=t;
				index=0;
			}else{
				int start=0;
				int end=size_-1; 
				while(start<=end)
				{
					index=(start+end)/2;
					if(buf[index]==t)
					{
						goto SORTVECTOR_INSERT;
					}
					else if(buf[index]>t)
					{
						end=index-1;
					}
					else
					{
						start=index+1;
					}
				}

				if(buf[index]<t)
				{
					index++;
				}
SORTVECTOR_INSERT:
				insert(index,t);
			} 
			return index;
		}

		void insert(int index,const T& t)
		{
			assert(index>=0 && index<=size_);
			if (size_==capacity_)
			{ 
				newCapacity(calculateCapacity());
			}
			memmove(buf+index+1,buf+index,(size_-index)*sizeof(T)); 
			buf[index]=t; 
			size_++; 
		}

		int indexOf(const T& t)
		{
			int begin=0;
			int end=size_-1;
			int index=-1;
			while (begin<=end)
			{
				index=begin+(end-begin)/2;
				if (buf[index]==t)
				{
					return index;
				}else if (buf[index]<t)
				{
					begin=index+1;
				}else{
					end=index-1;
				}
			}
			return -1;
		}

		int remove(const T& t)
		{
			int index=indexOf(t);
			if (index>=0)
			{
				memmove(buf+index ,buf+index+1,(size_-index)*sizeof(T));  
				buf[--size_]=T();
			} 
			return index;
		}

		void erase(const_iterator iter)
		{
			remove(*iter);
		}

		const_iterator begin() const
		{  
			return const_iterator(&buf[0]); 
		} 
		const_iterator end() const
		{  
			return const_iterator(&buf[size_]); 
		}
 
		const T& operator[](int index) const
		{
			assert(size_>0 && index>=0 && index<size_);
			return buf[index];
		}
 
		void clear()
		{
			if (buf)
			{
				for (int i=0;i<size_;i++)
				{
					buf[i]=T();
				}
			}
			size_=capacity_=0;
		}

		bool empty() const
		{
			return size_==0; 
		}

		int size() const
		{
			return size_;
		}

		int capacity() const
		{
			return capacity_;
		} 
	private: 
		void newCapacity(int capa)
		{ 
			assert (capa>size_) ;
			capacity_=capa;
			T* newBuf=new T[capacity_];
			if (buf)
			{
				memcpy(newBuf,buf,size_*sizeof(T) ); 
				delete [] buf;
			} 
			buf=newBuf;
		}

		inline void initData(int capa)
		{
			buf=NULL;
			size_=capacity_=capa>0?capa:0;
		}

		inline int calculateCapacity()
		{
			return capacity_*3/2+1;
		}
		int size_; 
		int capacity_ ; 
		T* buf; 
	};

	void csortvectorTest()
	{
		csortvector<int> l;
		l.add(2);
		l.add(4);
		l.add(9);
		l.add(3);
		l.add(7);
		l.add(1);
		l.add(5);
		l.add(8);
		l.add(0);
		l.add(6);
		cout<<"任意插入一组数据后，自动排序："<<endl;
		for (int i=0;i<l.size();i++)
		{
			cout<<l[i]<<" ";
		}
		cout<<endl<<endl;

		l.erase(l.begin());
		l.erase(l.end()-1);
		cout<<"删除第一个和最后一个数："<<endl; 
		for (int i=0;i<l.size();i++)
		{
			cout<<l[i]<<" ";
		} 
		cout<<endl<<endl;

		cout<<"5的下标："<<l.indexOf(5)<<endl;
		cout<<"下标为3的数："<<l[3]<<endl;
		l.remove(5);
		cout<<"删除5以后，5的下标是"<<l.indexOf(5)<<endl<<endl;

		cout<<"最后还剩："<<endl;
		for (int i=0;i<l.size();i++)
		{
			cout<<l[i]<<" ";
		} 
	}

}



#endif