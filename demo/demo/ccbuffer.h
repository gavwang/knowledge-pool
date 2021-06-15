#pragma once
#include <string>
#include <cassert>
//#include <pthread.h>

#include <windows.h>
#include <iostream>
using namespace std;
class Fruit {
public:
	Fruit() {
		std::cout << "Fruit Construct" << endl;
	}
	virtual ~Fruit()
	{
		cout << "Fruit Destruct" << endl;
	}


	virtual string name()
	{
		cout << "My name Fruit" << endl;

		return "Fruit";
	}

};

class Apple: public Fruit
{
public:
	Apple();
	~Apple();
	string name() {
		cout << "My Name is Apple" << endl;
		return "Apple";
	}

private:

};

Apple::Apple()
{
	cout << " Apple Construct" << endl;
}

Apple::~Apple()
{
	cout << "Apple Destruct" << endl;
}

class  CCBuffer
{
public:
	 CCBuffer();
	~ CCBuffer();

	void init(unsigned int size)
	{
		if (_buffer)
		{
			delete [] _buffer;
		}

		_size = size;
		_buffer = new char[_size];
		assert(_buffer);

		reset();
	}

	int write(char* data, unsigned int length) {

		if (length > _leftSize)
			return -1;

		if (_wrpos >= _rdpos) {

			if (length <= _buffer + _size - _wrpos)
			{
				memcpy(_wrpos, data, length);
				_wrpos += length;
			}
			else
			{
				unsigned int firstPart = _buffer + _size - _wrpos;
				memcpy(_wrpos, data, firstPart);
				memcpy(_buffer, data + firstPart, length - firstPart);
				_wrpos = _buffer + length - firstPart;
			}

			_leftSize -= length;
			_unreadSize += length;

		}
		else
		{
			memcpy(_wrpos, data, length);
			_wrpos += length;
		}

		return 0;
	}

	int read(char* data, unsigned int length) {
		if (length > _unreadSize)
		{
			return -1;
		}

		if (_wrpos > _rdpos)
		{
			memcpy(data, _rdpos, length);
			_rdpos += length;
		}
		else
		{
			unsigned int firstPart = _buffer + _size - _rdpos;
			if (firstPart > length)
			{
				memcpy(data, _rdpos, firstPart);
				_rdpos = _buffer;
				char* datapos = data + firstPart;
				memcpy(datapos, _buffer, length - firstPart);
				_rdpos = _buffer + length - firstPart;
			}
			else {
				memcpy(data, _rdpos, length);
				_rdpos += length;
			}
		}

		_leftSize += length;
		_unreadSize -= length;
		return 0;
	}

	void reset()
	{
		memset(_buffer, 0, _size * sizeof(char));
		_wrpos = _rdpos = _buffer;
		_leftSize = _size;
		_unreadSize = 0;
	}

	void lock()
	{
		::EnterCriticalSection(&mutex);
		//pthread_mutex_lock(mutex2);
	}

	void unlock()
	{
		::LeaveCriticalSection(&mutex);
		//pthread_mutex_unlock(&mutex);
	}

private:
	char* _buffer;
	unsigned int _size;
	char* _wrpos;
	char* _rdpos;

	unsigned int _leftSize;
	unsigned int _unreadSize;

	CRITICAL_SECTION mutex;

	//pthread_mutex_t mutex2;


};

 CCBuffer:: CCBuffer():
	 _buffer(nullptr),
	 _size(0),
	 _wrpos(0),
	 _rdpos(0)
{
	 ::InitializeCriticalSection(&mutex);
	 //pthread_mutex_init(&mutex2);
}

 CCBuffer::~ CCBuffer()
{
	 ::DeleteCriticalSection(&mutex);
	 //pthread_mutex_destroy(&mutex);
}