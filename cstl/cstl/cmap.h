#ifndef _CMAP_H_
#define _CMAP_H_
#include "csortvector.h"
namespace cth
{
	template<typename Key,typename Value>
	struct pair 
	{
		typedef Key first_type;
		typedef Value second_type; 
		pair(){}
		pair(const Key& key,const Value& val):first(key),second(val){}
		pair(const pair& other):first(other.first),second(other.second){}
		Key first;
		Value second;
	};


	template<typename Key,typename Value>
	class cmap:public NoCopy
	{
	public:
		typedef pair<Key,Value>* iterator;
		typedef const pair<Key,Value>* const_iterator;
		cmap(){}
		int insert(const pair<Key,Value>& item)
		{
			iterator iter=find(item.first);
			if (iter!=end())
			{
				return iter-begin();
			}
			int index=Keys.add(item.first);
			if (index>=0)
			{
				index=Values.insert(Values.begin() + index,item);
			}
			return index;
		}

		int insert(const Key& key,const Value& val)
		{
			pair<Key,Value> item;
			item.first=key;
			item.second=val;
			return insert(item);
		}

		Value& operator[](const Key& key)
		{
			int index=Keys.indexOf(key);
			if (index<0)
			{
				index=insert(key,Value());
			}
			return Values[index].second;
		}

		iterator begin()
		{
			return iterator(&*Values.begin());
		}

		iterator end()
		{
			return iterator(&*Values.end());
		}

		iterator find(const Key& key)
		{
			int index=Keys.indexOf(key);
			if (index<0)
			{
				return end(); 
			}else
			{
				return iterator(&Values[index]); 
			} 
		}

		void erase(const Key& key)
		{ 
			int index=Keys.remove(key) ; 
			if (index>=0)
			{
				cvector<pair<Key,Value>>::iterator iter=Values.begin()+index;
				Values.erase(iter);
			} 
		}

		void erase(const_iterator iter)
		{ 
			int index=Keys.remove(iter->first) ; 
			if (index>=0)
			{
				cvector<pair<Key,Value>>::iterator iter=Values.begin()+index;
				Values.erase(iter);
			} 
		}

		int size()
		{
			return Keys.size();
		}

		bool empty()
		{
			return Keys.size()==0;
		}

		void clear()
		{
			Keys.clear();
			Values.clear();
		}

	private:
		csortvector<Key> Keys;
		cvector<pair<Key,Value>> Values; 
	};

	void cmapTest()
	{
		cmap<int,int> m;
		for (int i=0;i<10;i++)
		{
			m[i]=i;
		} 
		m.insert(cth::pair<int,int>(5,5)); 
		m.insert(cth::pair<int,int>(50,50)); 
		m.erase(m.begin());
		m.erase(8);
		cmap<int,int>::iterator iter=m.begin();
		while (iter!=m.end())
		{
			cout<<iter->first<<" "<<iter->second<<endl;
			iter++;
		}
		cout<<m[5]<<endl; 
		iter= m.find(6);
		if (iter!=m.end())
		{
			cout<<iter->first<<" "<<iter->second<<endl;
		}
		cout<<m.size()<<endl;
		m.clear();
		cout<<m.size()<<endl;
	}
}
#endif