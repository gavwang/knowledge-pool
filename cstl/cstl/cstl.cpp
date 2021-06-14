#include "stdafx.h" 
#include "nocopy.h"
#include "cvector.h"
#include "clist.h"
#include "csortvector.h"
#include "cmap.h"
#include "cset.h"
#include "cheap.h" 
#include "algorithm.h"
#include "shared_ptr.h"
#include "dlist.h"
#include "cstack.h"
#include "cqueue.h"
 
using namespace cth;


  
int _tmain(int argc, _TCHAR* argv[])
{
	{ 
		for (int i=0;i<10000;i++)
		{
			cqueueTest();
			cstackTest();
		} 
	}
	system("pause");
	return 0;
}

