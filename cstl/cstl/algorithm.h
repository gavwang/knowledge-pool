#ifndef _algorithm_H_
#define _algorithm_H_
#include <string>

/*
1:合并排序，将两个已经排序的数组合并成一个数组，其中一个数组能容下两个数组的所有元素;
2:合并两个单链表;
3:倒序打印一个单链表;
4:给定一个单链表的头指针和一个指定节点的指针，在O(1)时间删除该节点;
5:找到链表倒数第K个节点;
6:反转单链表;
7:通过两个栈实现一个队列;
8:二分查找;
9:快速排序;
10:获得一个int型的数中二进制中1的个数;
11:输入一个数组，实现一个函数，让所有奇数都在偶数前面;
12:判断一个字符串是否是另一个字符串的子串;
13:把一个int型数组中的数字拼成一个串，这个串代表的数字最小;
14:输入一颗二叉树，输出它的镜像（每个节点的左右子节点交换位置）;
15:输入两个链表，找到它们第一个公共节点;
*/


//合并排序，将两个已经排序的数组合并成一个数组，其中一个数组能容下两个数组的所有元素
void MergeArray(int a[],int alen,int b[],int blen)
{
	int len=alen+blen-1; 
	alen--;
	blen--;
	while (alen>=0 && blen>=0)
	{
		if (a[alen]>b[blen])
		{
			a[len--]=a[alen--];
		}else{
			a[len--]=b[blen--]; 
		}
	}

	while (alen>=0)
	{
		a[len--]=a[alen--];
	} 
	while (blen>=0)
	{
		a[len--]=b[blen--];
	} 
}

void MergeArrayTest()
{
	int a[]={2,4,6,8,10,0,0,0,0,0};
	int b[]={1,3,5,7,9};
	MergeArray(a,5,b,5);
	for (int i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		cout<<a[i]<<" ";
	}
}

//链表节点
struct NodeL 
{
	int value;
	NodeL* next;
	NodeL(int value_=0,NodeL* next_=NULL):value(value_),next(next_){}
}; 

//合并两个单链表
NodeL* MergeList(NodeL* head1,NodeL* head2)
{
	if (head1==NULL)
		return head2;
	if (head2==NULL)
		return head1;

	NodeL* head=NULL; 
	if (head1->value<head2->value)
	{
		head=head1;
		head1=head1->next;
	}else{
		head=head2;
		head2=head2->next;
	}
	NodeL* tmpNode=head;
	while (head1 && head2)
	{
		if (head1->value<head2->value)
		{
			head->next=head1;
			head1=head1->next;
		}else{
			head->next=head2;
			head2=head2->next;
		}
		head=head->next;
	}
	if (head1)
	{
		head->next=head1;
	}
	if (head2)
	{
		head->next=head2;
	} 
	return tmpNode;
}

void MergeListTest()
{
	NodeL* head1=new NodeL(1);
	NodeL* cur=head1;
	for (int i=3;i<10;i+=2)
	{
		NodeL* tmpNode=new NodeL(i);
		cur->next=tmpNode;
		cur=tmpNode;
	}
	NodeL* head2=new NodeL(2);
	cur=head2;
	for (int i=4;i<10;i+=2)
	{
		NodeL* tmpNode=new NodeL(i);
		cur->next=tmpNode;
		cur=tmpNode;
	}
	NodeL* head=MergeList(head1,head2);
	while (head)
	{
		cout<<head->value<<" ";
		head=head->next;
	}
}

//倒序打印一个单链表
void ReversePrintNode(NodeL* head)
{
	if (head)
	{
		ReversePrintNode(head->next);
		cout<<head->value<<endl;
	} 
} 
void ReversePrintNodeTest()
{
	NodeL* head=new NodeL();
	NodeL* cur=head;
	for (int i=1;i<10;i++)
	{
		NodeL* tmpNode=new NodeL(i);
		cur->next=tmpNode;
		cur=tmpNode;
	}
	ReversePrintNode(head);
}

//给定一个单链表的头指针和一个指定节点的指针，在O(1)时间删除该节点
void DeleteNode(NodeL* head,NodeL* delNode)
{
	if (!head || !delNode)
	{
		return;
	}

	if (delNode->next!=NULL)//删除中间节点
	{
		NodeL* next=delNode->next;
		delNode->next=next->next;
		delNode->value=next->value;
		delete next;
		next=NULL;
	}else if (head==delNode)//删除头结点
	{
		delete delNode;
		delNode=NULL;
		*head=NULL;
	}else//删除尾节点，考虑到delNode不在head所在的链表上的情况
	{
		NodeL* tmpNode=head;
		while (tmpNode && tmpNode->next!=delNode)
		{
			tmpNode=tmpNode->next;
		}
		if (tmpNode!=NULL)
		{
			delete delNode;
			delNode=NULL;
			tmpNode->next=NULL;
		}
	}
}

void DeleteNodeTest()
{
	int nodeCount=10;
	for (int K=0;K<nodeCount;K++)
	{
		NodeL* head=NULL;
		NodeL* cur=NULL;
		NodeL* delNode=NULL;
		for (int i=0;i<nodeCount;i++)
		{
			NodeL* tmpNode=new NodeL(i);
			if (i==0)
			{
				cur=head=tmpNode;
			}else{
				cur->next=tmpNode;
				cur=tmpNode; 
			}
			if (i==K)
			{
				delNode=tmpNode;
			} 
		}
		DeleteNode(head,delNode) ;
	} 
}

//找到链表倒数第K个节点
NodeL* FindKthToTail(NodeL* head,unsigned int k)
{
	if(head==NULL || k==0)
		return NULL;
	NodeL* tmpNode=head;
	for (int i=0;i<k;i++)
	{
		if (tmpNode!=NULL)
		{
			tmpNode=tmpNode->next;
		}else{
			return NULL;
		} 
	}
	NodeL* kNode=head;
	while (tmpNode!=NULL)
	{
		kNode=kNode->next;
		tmpNode=tmpNode->next;
	}
	return kNode;
}

void FindKthToTailTest()
{
	int nodeCount=10;
	for (int K=0;K<nodeCount;K++)
	{
		NodeL* head=NULL;
		NodeL* cur=NULL; 
		for (int i=0;i<nodeCount;i++)
		{
			NodeL* tmpNode=new NodeL(i);
			if (i==0)
			{
				cur=head=tmpNode;
			}else{
				cur->next=tmpNode;
				cur=tmpNode;  
			}
		}
		NodeL* kNode=FindKthToTail(head,K+3) ;
		if (kNode)
		{
			cout<<"倒数第 "<<K+3<<" 个节点是："<<kNode->value<<endl;
		}else{
			cout<<"倒数第 "<<K+3<<" 个节点不在链表中" <<endl;
		}
	} 
}


//反转单链表
NodeL* ReverseList(NodeL* head)
{
	if (head==NULL)
	{
		return NULL;
	}
	NodeL* reverseHead=NULL;
	NodeL* curNode=head;
	NodeL* preNode=NULL;
	while (curNode!=NULL)
	{
		NodeL* nextNode=curNode->next;
		if (nextNode==NULL)
			reverseHead=curNode;  

		curNode->next=preNode;
		preNode=curNode;
		curNode=nextNode;
	}
	return reverseHead;
}

void ReverseListTest()
{
	for (int K=0;K<=10;K++)
	{
		NodeL* head=NULL;
		NodeL* cur=NULL; 
		for (int i=0;i<K;i++)
		{
			NodeL* tmpNode=new NodeL(i);
			if (i==0)
			{
				cur=head=tmpNode;
			}else{
				cur->next=tmpNode;
				cur=tmpNode;  
			}
		}

		cur=ReverseList( head);
		while (cur)
		{
			cout<<cur->value<<" ";
			cur=cur->next;
		}
		cout<<endl;
	}
	cout<<endl;
}

//通过两个栈实现一个队列
template<typename T>
class CQueue
{
public:
	void push(const T& val)
	{
		while (s2.size()>0)
		{
			s1.push(s2.top());
			s2.pop();
		}
		s1.push(val);
	}
	void pop()
	{ 
		while (s1.size()>0)
		{
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
	}

	T& front()
	{ 
		while (s1.size()>0)
		{
			s2.push(s1.top());
			s1.pop();
		}
		return s2.top();
	}
	int size()
	{
		return s1.size()+s2.size();
	}
private:
	stack<T> s1;
	stack<T> s2;
};

void CQueueTest()
{
	CQueue<int> q;
	for (int i=0;i<10;i++)
	{
		q.push(i);
	}
	while (q.size()>0)
	{
		cout<<q.front()<<" ";
		q.pop();
	}
}

//二分查找
int binarySearch(int a[],int len,int val)
{
	int start=0;
	int end=len-1;
	int index=-1;
	while (start<=end)
	{
		index=start+(end-start)/2;
		if (a[index]==val)
		{
			return index;
		}else if (a[index]<val)
		{
			start=index+1;
		}else
		{
			end=index-1;
		}
	}
	return -1;
}

void binarySearchTest()
{
	int a[]={0,1,2,3,4,5,6,7,8,9};
	int len=sizeof(a)/sizeof(a[0]);
	for (int i=0;i<len;i++)
	{
		cout<<binarySearch(a,len,i)<<" ";
	}
}

//快速排序
//之前有个面试叫我写快排，想都没想写了个冒泡,思路早忘了，这段代码来自百度百科
void Qsort(int a[],int low,int high)
{
	if(low>=high)
	{
		return;
	}
	int first=low;
	int last=high;
	int key=a[first];//用字表的第一个记录作为枢轴
	while(first<last)
	{
		while(first<last && a[last]>=key )--last;
		a[first]=a[last];//将比第一个小的移到低端
		while(first<last && a[first]<=key )++first;
		a[last]=a[first];//将比第一个大的移到高端
	}
	a[first]=key;//枢轴记录到位
	Qsort(a,low,first-1);
	Qsort(a,last+1,high);
}

void QsortTest()
{
	int a[]={1,3,5,7,9,2,4,6,8,0};
	int len=sizeof(a)/sizeof(a[0])-1;
	Qsort(a,0,len); 
	for(int i=0;i<=len;i++)
	{
		cout<<a[i]<<" ";
	} 
	cout<<endl;
} 



//获得一个int型的数中二进制中1的个数
int Find1Count(int num)
{
	if (num==0)
	{
		return 0;
	}
	int count=1;
	while (num= num & (num-1))
	{
		count++;
	}
	return count;
}

//输入一个数组，实现一个函数，让所有奇数都在偶数前面
void RecordOddEven(int A[],int len)
{
	int i=0,j=len-1;
	while (i<j)
	{
		while (i<len && A[i]%2==1) 
			i++; 

		while (j>=0 && A[j]%2==0) 
			j--; 

		if (i<j)
		{
			A[i]^=A[j]^=A[i]^=A[j]; 
		}
	}
}

void RecordOddEvenTest()
{
	int A[]={1,2,3,4,5,6,7,8,9,0,11};
	int len=sizeof(A)/sizeof(A[0]);
	RecordOddEven( A , len);
	for (int i=0;i<len;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
	for (int i=0;i<len;i++)
	{
		A[i]=2;
	}
	RecordOddEven( A , len);
	for (int i=0;i<len;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
	for (int i=0;i<len;i++)
	{
		A[i]=1;
	}
	RecordOddEven( A , len);
	for (int i=0;i<len;i++)
	{
		cout<<A[i]<<" ";
	}
}

//判断一个字符串是否是另一个字符串的子串
int substr(const char* source,const char* sub)
{
	if (source==NULL || sub==NULL)
	{
		return -1;
	}
	int souLen=strlen(source);
	int subLen=strlen(sub);
	if (souLen<subLen)
	{
		return -1;
	}

	int cmpCount=souLen-subLen;
	for (int i=0;i<=cmpCount;i++)
	{
		int j=0;
		for (;j<subLen;j++)
		{
			if (source[i+j]!=sub[j])
			{
				break;
			}
		}
		if (j==subLen)
		{
			return i ;
		}
	}
	return -1;
}

void substrTest()
{
	string a="1234567890";
	char* b="90";
	cout<<a.substr( 8,2)<<endl;

	int index=substr(a.c_str(),b);
	cout<<index<<endl;
}

//把一个int型数组中的数字拼成一个串，是这个串代表的数组最小
#define MaxLen 10 
int Compare(const void* str1,const void* str2)
{
	char cmp1[MaxLen*2+1];
	char cmp2[MaxLen*2+1];
	strcpy(cmp1,*(char**)str1);
	strcat(cmp1,*(char**)str2);

	strcpy(cmp2,*(char**)str2);
	strcat(cmp2,*(char**)str1);
	return strcmp(cmp1,cmp2);
}  
void GetLinkMin(int a[],int len)
{
	char** str=(char**)new int[len];
	for (int i=0;i<len;i++)
	{
		str[i]=new char[MaxLen+1];
		sprintf(str[i],"%d",a[i]); 
	}

	qsort(str,len,sizeof(char*),Compare);
	for (int i=0;i<len;i++)
	{
		cout<<str[i]<<" ";
		delete[] str[i] ;
	}
	delete[] str;
} 
void GetLinkMinTest()
{
	int arr[]={123,132,213,231,321,312};
	GetLinkMin(arr,sizeof(arr)/sizeof(int));
}


struct NodeT
{
	int value;
	NodeT* left;
	NodeT* right;
	NodeT(int value_=0,NodeT* left_=NULL,NodeT* right_=NULL):value(value_),left(left_),right(right_){}
};

//输入一颗二叉树，输出它的镜像（每个节点的左右子节点交换位置）
void TreeClass(NodeT* root)
{
	if( root==NULL || (root->left==NULL && root->right==NULL) ) 
		return; 
	NodeT* tmpNode=root->left;
	root->left=root->right;
	root->right=tmpNode;
	TreeClass(root->left);
	TreeClass(root->right); 
}

void PrintTree(NodeT* root)
{
	if(root)
	{
		cout<<root->value<<" ";
		PrintTree(root->left);
		PrintTree(root->right);
	} 
}

void TreeClassTest()
{
	NodeT* root=new NodeT(8);
	NodeT* n1=new NodeT(6);
	NodeT* n2=new NodeT(10);
	NodeT* n3=new NodeT(5);
	NodeT* n4=new NodeT(7);
	NodeT* n5=new NodeT(9);
	NodeT* n6=new NodeT(11);
	root->left=n1;
	root->right=n2;
	n1->left=n3;
	n1->right=n4;
	n2->left=n5;
	n2->right=n6;
	PrintTree(root);
	cout<<endl;
	TreeClass( root );
	PrintTree(root);
	cout<<endl;
}
 
//输入两个链表，找到它们第一个公共节点
int GetLinkLength(NodeL* head)
{ 
	int count=0;
	while (head)
	{
		head=head->next;
		count++;
	}
	return count;
}

NodeL* FindFirstEqualNode(NodeL* head1,NodeL* head2)
{
	if (head1==NULL || head2==NULL)
		return NULL;
	int len1=GetLinkLength(head1);
	int len2=GetLinkLength(head2);
	NodeL* longNode;
	NodeL* shortNode;
	int leftNodeCount;
	if (len1>len2)
	{
		longNode=head1;
		shortNode=head2;
		leftNodeCount=len1-len2;
	}else{
		longNode=head2;
		shortNode=head1;
		leftNodeCount=len2-len1;
	}
	for (int i=0;i<leftNodeCount;i++)
	{
		longNode=longNode->next;
	}
	while (longNode && shortNode && longNode!=shortNode)
	{
		longNode=longNode->next;
		shortNode=shortNode->next;
	}
	if (longNode)//如果有公共节点，必不为NULL
	{
		return longNode;
	}
	return NULL;  
}

void FindFirstEqualNodeTest()
{
	NodeL* head1=new NodeL(0);
	NodeL* head2=new NodeL(0);
	NodeL* node1=new NodeL(1);
	NodeL* node2=new NodeL(2);
	NodeL* node3=new NodeL(3);
	NodeL* node4=new NodeL(4);
	NodeL* node5=new NodeL(5);
	NodeL* node6=new NodeL(6);
	NodeL* node7=new NodeL(7);

	head1->next=node1;
	node1->next=node2;
	node2->next=node3;
    node3->next=node6;//两个链表相交于节点node6
	
	head2->next=node4;
	node4->next=node5;
    node5->next=node6;//两个链表相交于节点node6
	node6->next=node7;

	NodeL* node= FindFirstEqualNode(head1,head2);
	if (node)
	{
		cout<<node->value<<endl;
	}else{
		cout<<"没有共同节点"<<endl;
	}
}

#endif