#include <iostream>
#include <string>
#include <cstring>  // or include string.h
#include <cassert>
#include <vector>

using namespace std;
/**
 *  function to convert string including '0 - 9' to int 
 * 
 */

int string2int (char* src)
{
    if(!src)
        return -1;

    int len = strlen(src);

    char* pos = src + len;

    int loop = 1;
    int sum = 0;
    while ( --pos >= src)
    {
        assert(*pos >= '0' && *pos <= '9');
        sum += (*pos - '0')*loop;
        loop *= 10;
    }
    cout << "sum: "<< sum << endl;
    return sum;
}

int max_int_char_size()
{
    long long max = INT32_MAX;
    if (sizeof(int) == 8)
    {
        max = INT64_MAX;
    }

    int size = 0;
    while (max > 0)
    {
        size++;
        max = max/10;
    }

    return size;
}


int string2int2 (char* src)
{
    assert(src != nullptr);
    
    int number = 0;
    int sign = 1;
    if(*src == '-')
    {
        sign = -1;
        src++;
    }else if (*src == '+')
    {
        src++;
    }

    while (*src)
    {
        assert (*src > '0' && *src <'9');
        if(number < INT32_MAX/10 || (number == INT32_MAX/10 && (*src - '0') <= (INT32_MAX%10)))
        {
            number = number * 10 + (*src - '0');
        }else  {
            assert(0);
        } 
        src++;
    }

    number *= sign;

    return  number;
    
}
