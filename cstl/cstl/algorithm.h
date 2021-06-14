#ifndef _algorithm_H_
#define _algorithm_H_
#include <string>

/*
1:�ϲ����򣬽������Ѿ����������ϲ���һ�����飬����һ�������������������������Ԫ��;
2:�ϲ�����������;
3:�����ӡһ��������;
4:����һ���������ͷָ���һ��ָ���ڵ��ָ�룬��O(1)ʱ��ɾ���ýڵ�;
5:�ҵ���������K���ڵ�;
6:��ת������;
7:ͨ������ջʵ��һ������;
8:���ֲ���;
9:��������;
10:���һ��int�͵����ж�������1�ĸ���;
11:����һ�����飬ʵ��һ����������������������ż��ǰ��;
12:�ж�һ���ַ����Ƿ�����һ���ַ������Ӵ�;
13:��һ��int�������е�����ƴ��һ����������������������С;
14:����һ�Ŷ�������������ľ���ÿ���ڵ�������ӽڵ㽻��λ�ã�;
15:�������������ҵ����ǵ�һ�������ڵ�;
*/


//�ϲ����򣬽������Ѿ����������ϲ���һ�����飬����һ�������������������������Ԫ��
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

//����ڵ�
struct NodeL 
{
	int value;
	NodeL* next;
	NodeL(int value_=0,NodeL* next_=NULL):value(value_),next(next_){}
}; 

//�ϲ�����������
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

//�����ӡһ��������
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

//����һ���������ͷָ���һ��ָ���ڵ��ָ�룬��O(1)ʱ��ɾ���ýڵ�
void DeleteNode(NodeL* head,NodeL* delNode)
{
	if (!head || !delNode)
	{
		return;
	}

	if (delNode->next!=NULL)//ɾ���м�ڵ�
	{
		NodeL* next=delNode->next;
		delNode->next=next->next;
		delNode->value=next->value;
		delete next;
		next=NULL;
	}else if (head==delNode)//ɾ��ͷ���
	{
		delete delNode;
		delNode=NULL;
		*head=NULL;
	}else//ɾ��β�ڵ㣬���ǵ�delNode����head���ڵ������ϵ����
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

//�ҵ���������K���ڵ�
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
			cout<<"������ "<<K+3<<" ���ڵ��ǣ�"<<kNode->value<<endl;
		}else{
			cout<<"������ "<<K+3<<" ���ڵ㲻��������" <<endl;
		}
	} 
}


//��ת������
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

//ͨ������ջʵ��һ������
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

//���ֲ���
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

//��������
//֮ǰ�и����Խ���д���ţ��붼û��д�˸�ð��,˼·�����ˣ���δ������԰ٶȰٿ�
void Qsort(int a[],int low,int high)
{
	if(low>=high)
	{
		return;
	}
	int first=low;
	int last=high;
	int key=a[first];//���ֱ�ĵ�һ����¼��Ϊ����
	while(first<last)
	{
		while(first<last && a[last]>=key )--last;
		a[first]=a[last];//���ȵ�һ��С���Ƶ��Ͷ�
		while(first<last && a[first]<=key )++first;
		a[last]=a[first];//���ȵ�һ������Ƶ��߶�
	}
	a[first]=key;//�����¼��λ
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



//���һ��int�͵����ж�������1�ĸ���
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

//����һ�����飬ʵ��һ����������������������ż��ǰ��
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

//�ж�һ���ַ����Ƿ�����һ���ַ������Ӵ�
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

//��һ��int�������е�����ƴ��һ������������������������С
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

//����һ�Ŷ�������������ľ���ÿ���ڵ�������ӽڵ㽻��λ�ã�
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
 
//�������������ҵ����ǵ�һ�������ڵ�
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
	if (longNode)//����й����ڵ㣬�ز�ΪNULL
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
    node3->next=node6;//���������ཻ�ڽڵ�node6
	
	head2->next=node4;
	node4->next=node5;
    node5->next=node6;//���������ཻ�ڽڵ�node6
	node6->next=node7;

	NodeL* node= FindFirstEqualNode(head1,head2);
	if (node)
	{
		cout<<node->value<<endl;
	}else{
		cout<<"û�й�ͬ�ڵ�"<<endl;
	}
}

#endif