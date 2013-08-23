//
//  NumberEngine.cpp
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#include "Combined.h"
NumberEngine *g_number = NULL;
NumberEngine::NumberEngine()
{
    g_number = this;
}

NumberEngine::~NumberEngine()
{
    
}


int NumberEngine::SearchNumber(int number)
{
    
}


int NumberEngine::FloatToInt(float value)
{
    return *(int*)&value;
}

bool NumberEngine::ResultIsEqual(uint one, uint two)
{
    return (one == two);
}

bool NumberEngine::ResultIsLarger(uint one, uint two)
{
    return (one < two);
}

bool NumberEngine::ResultIsSmaller(uint one, uint two)
{
    return (one > two);
}