//
//  new_main.cpp
//  azured
//
//  Created by Callum Taylor on 04/01/2014.
//
//

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Azure.h"

using namespace std;
using namespace azure;

int main(int argc, char **argv)
{
    GlobalSettings settings = {-1, -1, -1, false, false, false};
    if(argc > 1)
        if(!strcmp(argv[1], "--help"))
        {
            //PrintHelp
        }
        else if(!strcmp(argv[1], "--list-processes"))
        {
            settings.listOnly = true;
        }
        else if(!strcmp(argv[1], "--attach"))
        {
            //attach to argv[2]
        }
        else if(!strcmp(argv[1], "--debug"))
        {
            settings.debug = true;
        }
        else
        {
            //print help
        }
    cout << kBLU << AZGreet << kCLR;
    Azure *az_main = Azure::GetInstance();
    az_main->SetPreferences(settings);
    // may be more setup required first? //
    int ret = az_main->MainLoop();
    //shouldn't return, deal with return value
    
    return 0;
}