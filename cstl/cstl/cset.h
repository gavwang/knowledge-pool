#ifndef _CSET_H_
#define _CSET_H_
namespace cth
{ 
	template<typename T>
	struct treeNode 
	{
		T data;
		treeNode *left;
		treeNode *right;
		treeNode(const T& data_,treeNode* left_=NULL,treeNode* right_=NULL):data(data_),left(left_),right(right_){}
	} ;

	template<typename T>
	class cset:public NoCopy
	{
		public:

		private:

	};

	void csetTest()
	{
		set<int> s ;
		s.insert(3);
		s.insert(2);
		s.insert(2);
		s.insert(1);
		 
		set<int>::iterator it=s.begin();
		while (it!=s.end())
		{
			cout<<*it++<<" ";
		}
		cout<<endl<<endl;  
		it=s.find(2) ;
		cout<<*it<<endl;
	}
}
#endif