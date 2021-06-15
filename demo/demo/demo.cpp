// demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define NOMINMAX

#include "advancedcxx.h"
#include <iostream>
#include "ccbuffer.h"
#include "algorithm.h"
#include <cassert>
#include <cstring>
#include <array>
#include <limits>
#include <vector>




/*
basic function
memcpy()
memset()
*/



class NoCopybale {
public:
	inline NoCopybale() {};
private:
	NoCopybale(const NoCopybale& c) ;
	const NoCopybale& operator = (const NoCopybale&);
};

class TestCopy : NoCopybale
{
public:
	//TestCopy() {};
	//~TestCopy() {};

};

template <typename Key, typename T>
class MyMap
{
public:
	MyMap() {};
	virtual ~MyMap() {};
	
	virtual void set(Key key, T value) = 0;
	virtual const pair<int, T>* get(Key key) = 0;
	virtual void remove(Key key) = 0;

private:

};

#define BUCKETS_DEFAULT 31
template <typename T>
class MyHashMap:public MyMap<int, T>
{
public:
	MyHashMap():
		bucketSize(BUCKETS_DEFAULT),
		entrySize(0)
	{
		buckets = new Entry*[bucketSize];
		memset(buckets, 0, sizeof(Entry*)*bucketSize);
	};
	~MyHashMap() {
		for (int i = 0; i < bucketSize; i++)
		{
			Entry* header = buckets[i];
			while (header)
			{
				Entry* next = header->next;
				delete header;
				bucketSize--;
				header = next;
			}
			buckets[i] = nullptr;
		}

		delete[] buckets;

	};
	
	typedef pair<int, T>* iterator;

	class Entry
	{
	public:
		Entry() :next(nullptr) {};
		~Entry() {};
		pair<int, T> value;
		Entry* next;

	};
	typedef Entry* PEntry;

	void set(int key, T value) {
		set(make_pair(key, value));
	};

	void set(pair<int, T> e)
	{
		if (buckets[hashCode(e.first)])
		{
			Entry* entry = buckets[hashCode(e.first)];
			while ( entry)
			{
				if (entry->value.first == e.first)
				{
					entry->value.second = e.second;
					return ;
				}	
				entry = entry->next;
			}
		}

		Entry* newEentry = new Entry();
		newEentry->value = e;
		newEentry->next = buckets[hashCode(e.first)];
		buckets[hashCode(e.first)] = newEentry;
		entrySize++;

	}
	
	const pair<int,T>* get(int key) {

		if (buckets[hashCode(key)])
		{
			Entry* entry = buckets[hashCode(key)];
			while (entry)
			{
				if (entry->value.first == key)
				{
					return &(entry->value);
				}
				entry = entry->next;
			}
		}

		return nullptr;
	};
	
	void remove(int key) {
		if (buckets[hashCode(key)])
		{
			Entry* entry = buckets[hashCode(key)];
			if (entry->value.first == key)
			{
				buckets[hashCode(key)] = entry->next;
				delete entry;
				bucketSize--;
			}
			else
			{
				while (entry->next)
				{
					if (entry->next->value.first == key)
					{
						Entry* beDeleted = entry->next;
						entry->next = entry->next->next;

						delete beDeleted;
						bucketSize--;
					}

				}
			}
		}
	};
private:

	void removeBucket(int index)
	{
		Entry* header = buckets[index];
		while (header)
		{
			Entry* next = header->next;
			delete header;
			bucketSize--;
			header = next;
		}
	}

	int hashCode(int key)
	{
		return key % (bucketSize);
	}
	int hashCode(Entry* e) {
		return hashCode(e->value.first);
	};
	void capbility() {

	}
private:
	int bucketSize;
	int entrySize;
	Entry** buckets;

};


void swapInt(int& a, int& b)
{
	//a = a + b;
	//b = a - b;
	//a = a - b;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}
void bubbleSort(int a[], int size)
{
	for (size_t i = 0; i < size-1; i++)
	{
		for(int j = 0 ; j < size - i - 1; j++)
		if (a[j] > a[j + 1])
		{
			swapInt(a[j], a[j + 1]);
		}

	}

}


void mergeArray(int a[], int sizeA, int b[], int sizeB)
{
	int len = sizeA + sizeB;

	int curPos = len - 1;

	int aPos = sizeA - 1;
	int bPos = sizeB - 1;

	while (aPos >= 0 && bPos >= 0)
	{
		a[curPos--] = a[aPos] > b[bPos] ? a[aPos--] : b[bPos--];
	}

	while (aPos >= 0)
	{
		a[curPos--] = a[aPos--];
	}

	while (bPos >= 0)
	{
		a[curPos--] = b[bPos--];
	}
}


void merge(int arr[], int first,int mid, int last)
{
	//int mid = first + (last - first) / 2;
	int* tmpArr = new int[last - first + 1];
	
	int curIndex = 0;
	int lpos = first;
	int rpos = mid + 1;
	while (lpos <= mid  && rpos <= last)
	{
		if (arr[lpos] <= arr[rpos])
		{
			tmpArr[curIndex++] = arr[lpos++];
		}
		else
		{
			tmpArr[curIndex++] = arr[rpos++];
		}
	}
	while (lpos <= mid)
	{
		tmpArr[curIndex++] = arr[lpos++];
	}

	while (rpos <= last)
	{
		tmpArr[curIndex++] = arr[rpos++];
	}

	for (size_t i = 0; i < last-first + 1; i++)
	{
		arr[first + i] = tmpArr[i];
	}
}

/*
left: pos
ritht pos of array
*/
void sort_recursive(int a[], int first, int last)
{
	if (first >= last)
		return;
	int mid = first + (last - first) / 2;
	sort_recursive(a, first, mid);
	sort_recursive(a, mid + 1, last);
	merge(a, first,mid, last);
}


void mergeSort(int a[], int size) {

	sort_recursive(a, 0, size - 1);
}


void loopMergeSort(int a[], int len) {
	int* arr = a;
	int* tmp = new int[len];

	int step = 1;
	int start = 0;
	for ( step = 1; step < len; step += step)
	{
		for (start = 0; start < len; start += step*2)
		{
			int low = start;
			int mid = min(start + step, len);
			int high = min(start + 2 * step, len);
			int curPos = start;
			int start1 = low;
			int end1 = mid;
			int start2 = mid;
			int end2 = high;

			while (start1 < mid && start2 < end2 )
			{
				tmp[curPos++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
			}

			while (start1 < end1)
			{
				tmp[curPos++] = arr[start1++];
			}
			while (start2 < end2)
			{
				tmp[curPos++] = arr[start2++];
			}

		}

		int* tmpPtr = arr;
		arr = tmp;
		tmp = tmpPtr;
	}

	if (arr != a)
	{
		for (int i = 0; i < len; i++)
		{
			tmp[i] = arr[i];
		}

		tmp = arr;
	}

	delete[] tmp;
}


bool lbs_less(int x, int y)
{
	return x > y;
}
bool less_10(int x)
{
	return x<10;
}
struct  test
{
	bool operator ()(int& left, int& right) {
		return left > right;
	}

};


unsigned int uintMax()
{
	return numeric_limits<unsigned int>::max();
}

unsigned int string2int5(const string& src)
{
	string newSrc(src);
	newSrc.erase(0, src.find_first_not_of(' '));

	const char* pSrc = newSrc.c_str();
	unsigned int sum = 0;
	char tConvert;
	while (*pSrc)
	{
		assert(*pSrc >= '0' && *pSrc <= '9');
		int curNumber = *pSrc - '0';
		if (sum > uintMax() / 10 || 
			(sum == uintMax() / 10 && curNumber > uintMax() % 10))
		{
			return uintMax();
		}

		sum = sum * 10 + curNumber;

		pSrc++;
	}
	return sum;
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


int main()
{ 
	NoCopybale n;
	TestCopy t;
	std::cout << "Hello World!\n" << endl;
	std::cout << string2int5("3456778843")<<endl;
	std::cout << string2int5("4294967296") << endl;
	std::cout << string2int5("5294967296") << endl;

	vector<int> v = { 1,2,3,5 };
	
	//advancedcxxTest();

	int a[] = { 1,7,5,9,0,0,0,0 };
	int b[] = { 2,6,3,8 };
	mergeArray(a, 4, b, 4);

	//int bubbles [] = { 6,5,3,1,8,7,2,4,78,34,56,21,17,46,84,36 };

	//bubbleSort(bubbles, sizeof(bubbles)/sizeof(bubbles[0]));

	//int sample[] = { 6,5,3,1,8,7,2,4,78,34,56,56,21,17,46,84,36 };

	int sample[] = { 83, 86, 77, 15, 93, 35, 86, 92, 49, 21, 62, 27, 90, 59, 63, 26, 40, 26, 72, 36 };
	//loopMergeSort(sample, sizeof(sample) / sizeof(sample[0]));
	mergeSort(sample, sizeof(sample) / sizeof(sample[0]));

	std::array<int, 10> arr = { 1,3,5,2,68,45,24,45,34,67 };

	std::sort(arr.begin(), arr.end(), test());
	//std::sort(arr.begin(), arr.end(), );

	string number("13454589");
	cout << "string2int: " << number << "-->" << string2int(number) << endl;


	Fruit* f = new Apple();
	f->name();
	f->Fruit::name();
	delete f;


	MyHashMap<string> map;// = new MyHashMap<string>();

	map.set(1, "1");
	map.set(5, "5");
	map.set(65534, "65534");
	map.set(1000, "1000");
	map.set(32, "32");

	map.set(800, "800");

	const pair<int, string>* p = map.get(1);
	p = map.get(4);
	p = map.get(65534);
	p = map.get(1000);
	p = map.get(800);


	map.remove(4);
	map.remove(1);
	map.remove(65534);

	p = map.get(4);
	p = map.get(65534);
	p = map.get(1000);
	p = map.get(800);


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
