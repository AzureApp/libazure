//
//  NumberEngine.h
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#ifndef __azured__NumberEngine__
#define __azured__NumberEngine__

#include <iostream>
#include <sys/types.h>
#include <vector> 
using namespace std;
class NumberEngine
{
public:
    enum Errors
    {
       //some error enums here 
    };
    
    struct ReadData
    {
        uint address;
        int value;
    };
    
    struct LockData
    {
        uint address;
        int value;
    };

    
    NumberEngine();
    ~NumberEngine();
    vector<ReadData > readValues;
    
    int SearchNumber(int number);
    int RefineSearch(int number);
    int FloatToInt(float value);
    
    
    
    bool ResultIsEqual(uint one, uint two);
    bool ResultIsLarger(uint one, uint two);
    bool ResultIsSmaller(uint one, uint two);
    
    
};

extern NumberEngine *g_number;
#endif /* defined(__azured__NumberEngine__) */
