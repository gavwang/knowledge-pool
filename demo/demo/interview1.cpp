/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
https://www.onlinegdb.com/
*******************************************************************************/

#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include "algorithm.h"

using namespace std;

unsigned int string2int(const string & src) {

	unsigned long long sum = 0;

	string newStr(src);

	newStr.erase(0, src.find_first_of(' '));


	const char* curpos = src.c_str();
	while (*curpos != '\0')
	{
		assert(*curpos >= '0' && *curpos <= '9');
		sum *= 10;
		sum += *curpos - '0';
		assert(sum < UINT32_MAX);
		curpos++;
	}
	return sum;
}

string searchPrefix(const string src[], int count) {
    
    assert(src != nullptr);
    
    int arraySize = count;
    int loop = 0;
    string result = "";
    
    while(true)
    {
        char cur = src[0][loop];
        if(cur == '\0')
            break;
        bool bSeached = true;
        for(int i = 1; i < arraySize; i++)
        {
            if(src[i][loop] != cur)
            {
                bSeached = false;
                break;
            }
        }
        
        if(!bSeached)
            break;
            
        result.push_back(cur);
        loop++;
    }
    
    return result;
    
}


/*

int main()
{
	const string test[] = {"flower", "flow", "flight","flffl"};
	string prefix = searchPrefix(test ,sizeof(test)/sizeof(test[0]));
	cout << prefix << endl;

	cout<<"Hello World";

	return 0;
}

*/

/*
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

using namespace std;

char* searchPrefix(char* src[]) {
    
    assert(src != nullptr);
    
    int arraySize = sizeof(src)/sizeof(src[0]);
    int resultCap = 128;
    int prefix = 0;
    char* result = new char[resultCap];
    memset(result,0,resultCap);

    string searchedPre = "";

    
    while(true)
    {
        char cur = src[0][prefix];
        if(cur == '\0')
            break;
        bool bSeached = true;
        for(int i = 1; i < arraySize; i++)
        {
            if(src[i][prefix] != cur)
            {
                bSeached = false;
                break;
            }
        }
        
        if(!bSeached)
            break;
        
        searchedPre.push_back(cur);
        
        if(prefix==resultCap)
        {
            char* newResult = new char[resultCap+128];
            memset(newResult,0,resultCap+128);
            memcpy(newResult,result,resultCap);
            
            delete [] result;
            result = newResult;
            
            resultCap +=128;
        }
        
        result[prefix]=cur;
        prefix++;
    }
    
    result[prefix]=0;
    
    return result;

    
}


int main()
{
    char* test[] = {"flower", "flow", "flight"};
    
    char* prefix = searchPrefix(test);
    cout << prefix <<endl;
    
    delete [] prefix;
    
    cout<<"Hello World";
    
    getchar();

    return 0;
}
*/