//
//  main.c
//  azure
//
//  Created by Callum Taylor on 26/12/2013.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//



/* to do: TIDY UP MAIN()!!!!!!
 * optimize memory usage
 * earn swag
 */

#include <iostream>
#include <mach/mach.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MemoryManager.h"
#include "ProcessInfo.h"

#define ASIZE 256
void *find( char *pat, int m, char *text, int n ) //alternate search algorithm
{
	int i,j,k,skip[ASIZE];
    if(m==0)
        return 0;
	for(k=0;k<ASIZE;k++)
        skip[k]=m;
	for(k=0;k<m-1;k++)
        skip[(int)pat[k]]=m-k-1;
	for(k=m-1;k<n;k+=skip[(int)text[k]&(ASIZE-1)])
    {
        for(j=m-1,i=k;j>=0&&text[i]==pat[j];j--)i--;
        if(j==-1)return(text+i+1);
    }
	return NULL;
}
#define kMAG  "\033[1;35m"
#define kCYN  "\033[1;36m"
#define kRED  "\033[1;31m"
#define kGRN  "\033[1;32m"
#define CLEAR() printf("\033[0m")
int old_main (int argc, const char * argv[]) //delete me at some point
{
    
    if(getuid() != 0)
    {
        printf("please run %s as root!\n", argv[0]);
        return -1;
    }
    
    ProcessInfo *p_info = ProcessInfo::instance();
    p_info->GetAllProcesses(); //move to constructor
    bool color = false;
    int proc;
    for (proc = 0; proc < p_info->processes->size(); proc++)
    {
        printf("%s%d. %s <%d>\n", color ? kMAG : kCYN, proc+1, p_info->processes->at(proc).processName, p_info->processes->at(proc).pid);
        color = !color;
        CLEAR();
    }
    printf(kGRN);
    printf("choose a process: ");
    int choice = 0;
    scanf("%d", &choice);
    int pid = p_info->processes->at(choice - 1).pid;
    task_t task;
    kern_return_t status = task_for_pid(mach_task_self(), (pid_t)pid, &task);
    //printf("%s\n", mach_error_string(status));
    if (status != KERN_SUCCESS)
    {
        printf("\ntask_for_pid failed, please tell razzile he is stupid!\n");
        return -1;
    }
    MemoryManager *mgr = MemoryManager::instance();
    //mgr->GetRegions(); //move to constructor
    
    
    printf("enter a value: ");
    int val= 0;
    scanf("%d", &val);
    mgr->BeginSearch(val, sizeof(val));
    if(mgr->searchData->addresses.size() > 10)
        printf("\n%ld results\n", mgr->searchData->addresses.size());
    else
    {
        CLEAR();
        int r = 0;
        bool c = false;
        for (uint val : mgr->searchData->addresses)
        {
            printf("%s%d. 0x%X\n",c ? kMAG : kCYN, r+1, val);
            CLEAR();
            color = !color;
            r++;
        }
        //CLEAR();
    }
    while (1)
    {
        printf("\nenter another value? <y/n> ");
        char *ans = new char(255);
        scanf("%s", ans);
        if (!strcmp(ans, "y") || !strcmp(ans, "yes"))
        {
            printf("enter another value: ");
            scanf("%d", &val);
            mgr->IterateSearch(val);
            if(mgr->searchData->addresses.size() > 100)
                printf("\n%ld results\n", mgr->searchData->addresses.size());
            else
            {
                int r = 0;
		          bool c = false;
                for (uint val : mgr->searchData->addresses)
                {
                    printf("\n%s%d. 0x%X\n",c ? kMAG : kCYN, r+1, val);
                    c = !c;
                    printf(kGRN);
                }
            }
        }
        
        else if (!strcmp(ans, "n") || !strcmp(ans, "no"))
        {
            printf("edit a value?<y/n> ");
            char *ans = new char(255);
            scanf("%s", ans);
            if (!strcmp(ans, "y") || !strcmp(ans, "yes"))
            {
                printf("please choose an address to edit: ");
                int selection = 0;
                scanf("%d", &selection);
                printf("\nenter new value for address: ");
                int value = 0;
                scanf("%d", &value);
                mgr->WriteAddress(mgr->searchData->addresses.at(selection - 1), value);
            }
            
            else if (!strcmp(ans, "n") || !strcmp(ans, "no"))
            {
                CLEAR();   
                exit(0);
            }
        
        }
        
        
    }
    
    return 0;
}

