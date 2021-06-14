#pragma once
#include <iostream>
#include <string>



using namespace std;


/*
* smart pointer
*/

class House;
class Shape {
public: 
	Shape(const string& n):name(n) {};
	~Shape() {
		cout <<name << " --> Destructor" << endl;
	};

	void foo() {
		cout << "I am " << name << endl;
	}

	weak_ptr<House> house;
private:
	string  name;


};

class  House
{
public:
	House(const string& n):name(n) {};
	~House() {
		cout << name << " --> Destructor" << endl;
	};
	void foo() {
		cout << "I am " << name << endl;
	}
	shared_ptr<Shape> shape;
private:
	string name;

};
	

class Buffer {
public:
	Buffer(int s, const string& n) :
		name(n),
		data(nullptr),
		size(s)
	{
		data = new char[size];
	};
	~Buffer() {
		delete[] data;
		size = 0;
		cout << name << " --> Destructor" << endl;
	};
	void foo() {
		cout << "I am " << name << endl;
	}

	void copyData(char* b, int size)
	{

	}
	char* getData()
	{

	}
	int getSize()
	{
		return size;
	}
private:
	string name;
	char* data;
	int size;


};

void putData(shared_ptr<Buffer> b)
{
	int size = b->getSize();

	shared_ptr<Buffer> c = b;
	c.unique();

	c->getSize();
}


void sort(int arr[], int size, bool (*compare)(int x, int y))
{
	for (int i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size -1 - i; j++)
		{
			if (compare(arr[j], arr[j + 1]))
			{
				arr[j] = arr[j] ^ arr[j + 1];
				arr[j + 1] = arr[j] ^ arr[j + 1];
				arr[j] = arr[j] ^ arr[j + 1];
			}
		}
	}

}

bool com1(int x, int y)
{
	return x > y;
}
void advancedcxxTest()
{

	int bubbles[] = { 6,5,3,1,8,7,2,4,78,34,56,21,17,46,84,36 };
	sort(bubbles, sizeof(bubbles) / sizeof(bubbles[0]), com1);
	sort(bubbles, sizeof(bubbles) / sizeof(bubbles[0]), [] (int x, int y) -> bool{
		return x < y;
	});

	//lambda
	{
		int lambda = 3;
		auto func = [=]() mutable -> bool {
			lambda = 4;
			cout << "Hello" << endl;
			return false;

		};

		auto func2 = [&](int x, int y) -> bool {
			cout << "Hello:" << lambda << endl;
			lambda += 2 + 3;
			return false;
		};
		func();
		func2(2, 3);
	}

	shared_ptr<int> arr(new int[5]);
	//auto a2 = make_shared<int[1024]>();    //error
	//auto ashared = make_shared<int[5]>();   //error
	auto p = make_unique<int[]>(5);



	// weak_ptr test   
	{
		shared_ptr<Shape> child = make_shared<Shape>("child ");
		shared_ptr<House> parent = make_shared<House>("parent");
		parent->shape = child;
		child->house = parent;

		shared_ptr<House> p1arent = make_shared<House>("parent");
		shared_ptr<House> p2arent = make_shared<House>("parent");
	}

	
	unique_ptr<Shape> u = make_unique<Shape>("unique Shape");

	shared_ptr<Shape> sShape(u.release());

	weak_ptr<Shape> wShape(sShape);

	bool e = wShape.expired();
	int count = wShape.use_count();

	wShape.lock(); 
	
	sShape.reset();

	e = wShape.expired();

	auto b = wShape.lock();


	shared_ptr<Shape> p = make_shared<Shape>("Shape sp ");
	shared_ptr<House> h = make_shared<House>("House sp");

	shared_ptr<House> h2 = h;

	shared_ptr<House> bighouse(h2);

	House* orignH = new House("House Orign");
	shared_ptr<House> refH(orignH);
	//shared_ptr<House> refH2(orignH);

	refH->foo();

	if (refH.unique())
	{
		refH.reset();
	}

	shared_ptr<Buffer> buf = make_shared<Buffer>(10, "Shared Buffer");

	int size = (*buf).getSize();

	putData(buf);

	putData(buf);


	shared_ptr<int> test(new int(42));
	shared_ptr<int> test2(new int(23));
	
	test.reset(test2.get());

	if (test.unique())
	{
		//test.reset(new string(*test));
	}

	
	//delete orignH;


	//refH->foo();

   

	string a = "    this is a test";
	a.erase(0, a.find_first_of(' '));
	a.insert(1, "instert");

	char str[64];
	_itoa_s(10000,str,10);
	//a.replace()
	a.at(0);
	

}


/*********************	*********************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/*
#include <stdio.h>
#include <string>
#include <cstring>
#include <pthread.h>
#include <iostream>
using namespace std;

#define THREAD_NUM 4

void merge(int arr[], int first, int mid, int last)
{
	int* tmp = new int[last - first + 1];

	int lPos = first;
	int rPos = mid + 1;
	int curPos = 0;

	while (lPos <= mid && rPos <= last)
	{
		tmp[curPos++] = (arr[lPos] > arr[rPos]) ? arr[rPos++] : arr[lPos++];
	}

	while (lPos <= mid)
	{
		tmp[curPos++] = arr[lPos++];
	}

	while (rPos <= last)
	{
		tmp[curPos++] = arr[rPos++];
	}

	for (size_t i = 0; i < last - first + 1; i++)
	{
		arr[first + i] = tmp[i];
	}
	//memcpy(arr+ first,tmp,sizeof(int)*(last-first+1));
	delete[] tmp;
}


void mergeSort(int arr[], int first, int last)
{
	if (first >= last)
		return;

	int mid = first + (last - first) / 2;
	mergeSort(arr, first, mid);
	mergeSort(arr, mid + 1, last);
	merge(arr, first, mid, last);
}

struct  ThreadArgs
{
	int* arr;
	int size;
	int iThread;
};

void* mutipleMergeSort(void* arg)
{
	ThreadArgs* p = (ThreadArgs*)arg;

	int part = p->size / THREAD_NUM;
	if (p->iThread != THREAD_NUM - 1)
		mergeSort(p->arr, p->iThread * part, p->iThread * part + part - 1);
	else
		mergeSort(p->arr, p->iThread * part, p->size - 1);

	cout << "arr:" << p->arr << " threadID:" << p->iThread << endl;

}

int test()
{
	int sample[] = { 83, 86, 77, 15, 93, 35, 86, 92, 49, 21, 62, 27, 90, 59, 63, 26, 40, 26, 72, 36 };

	int size = sizeof(sample) / sizeof(sample[0]);
	pthread_t threads[THREAD_NUM];
	ThreadArgs args[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)
	{
		args[i].arr = sample;
		args[i].iThread = i;
		args[i].size = sizeof(sample) / sizeof(sample[0]);

		pthread_create(&threads[i], nullptr, mutipleMergeSort, (void*)&args[i]);
	}

	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threads[i], nullptr);
	}



	merge(sample, 0, (size / 2 - 1), size / 2 - 1);

	merge(sample, size / 2, size / 2 + (size - 1 - size / 2) / 2, size - 1);

	merge(sample, 0, size - 1 / 2, size - 1);


	mergeSort(sample, 0, sizeof(sample) / sizeof(sample[0]) - 1);

	//mutipleMergeSort(sample, sizeof(sample)/sizeof(sample[0]));
	printf("Hello World");

	return 0;
}

*/