//
//  main.cpp
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//  
//

#include <iostream>
#include "Azure.h"

int main (int argc, const char * argv[])
{
    Azure azure;
    
    const char * debug = "-d";
    if(argv[1] == debug)
    {
        azure.Debug = true;
    }
    
    //azure.Initialize
    
    //int err = azure.AzureTick
    //if(err > 0)
    //  azure.WriteLogFile("Azure Internal Error");
}

