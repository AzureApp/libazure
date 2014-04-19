//
//  new_main.cpp
//  azured
//
//  Created by Callum Taylor on 04/01/2014.
//
//

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Azure.h"

using namespace std;


int main(int argc, char **argv)
{
    if(getuid() != 0)
    {
        cout << "please run " << argv[0] << " as root!\n";
        return -1;
    }
    GlobalSettings *settings = Azure::azureSettings;
    Azure *az_main = Azure::instance();
    if(argc > 1)
    {
        if(strcmp(argv[1], "--help") == 0)
        {
            Azure::PrintHelp(e_main);
        }
        else if(strcmp(argv[1], "--list-processes") == 0)
        {
            settings->listOnly = true;
        }
        else if(strcmp(argv[1], "--attach") == 0)
        {
            Process temp;
            temp.processName = argv[2];
            ProcessInfo::instance()->AttachToProcess(temp);
        }
        else if(strcmp(argv[1], "--debug") == 0)
        {
            settings->debug = true;
        }
        else
        {
            Azure::PrintHelp(e_main);
        }
    }
    cout << kGRN << AZGreet << kCLR;
    
    
    
    // may be more setup required first? //
    
    int ret = az_main->MainLoop(); //shouldn't return, deal with return value
    
    return ret;
}