//
//  Azure.cpp
//  azure-mac-tests
//
//  Created by Callum Taylor on 23/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#include "Azure.h"



Azure* Azure::az_Instance = NULL;
GlobalSettings* Azure::azureSettings = NULL;
Azure::Azure()
{
    azureSettings = new struct GlobalSettings();
    this->GetPreferences();
}

Azure* Azure::instance()
{
    if(!az_Instance)
    {
        az_Instance = new Azure();
    }
    return az_Instance;
}

int Azure::MainLoop() //#Messy2K14
{
    pthread_t msg;
    InternalMessaging *sys = InternalMessaging::instance();
    pthread_create(&msg, NULL, &InternalMessaging::BeginMessagingSystem, NULL);

    char *ans = new char[256];
    while(true)
    {
        char **input = new char*[4];
        for(int i = 0; i < 4; i++)
        {
            input[i] = new char[32];
        }
        fflush(stdin);
        cout << kCYN << AZStub << kCLR;
        char newline = '\0';
        int count = 0;
        while (newline != '\n')
        {
            scanf("%s%c", input[count], &newline); //TODO: Check for white spaces as well as new lines (but make sure nothing follows)
            count++;
        }
        //int commands = scanf(" %s %s %s %s ", input[0], input[1], input[2], input[3]);
       /* for(int i = 0; i < count; i++)
        {
            printf("%s|", input[i]);
        }
        /*fgets(ans, 256, stdin);*/
        
        if(!strcmp(input[0], "attach") != 0)
        {
            if(count > 1)
            {
                printf("attaching to %s\n", input[1]); //TODO: check process name is valid
                if(ProcessInfo::instance()->GetProcessByName(input[1]) > 0)
                {
                    DataObject *obj = new DataObject((void*)input[1], strlen(input[0]));

                    InternalMessaging::instance()->PushMessage(m_Attach, obj);
                    goto cont;
                }
                else
                {
                    cout << kRED << "process specified was not found" << kCLR << endl;
                    goto cont;
                }
                //obj.data[0] = (void*)input[0];
                //cout << (char*)obj.data[0] << endl;
            }
            else
            {
                PrintHelp(e_attach);
               
            }
            goto cont;
        }
        if(!strcmp(input[0], "search") != 0)
        {
            if(count > 1)
            {
                printf("searching for %d\n", atoi(input[1]));
            }
            else
            {
                PrintHelp(e_search);
            }
            goto cont;
        }
        if(!strcmp(input[0], "edit") != 0 || !strcmp(input[0], "write") != 0)
        {
            if(count > 2)
            {
                printf("writing %d to 0x%lx\n", atoi(input[2]), strtol(input[1], NULL, 16));
            }
            else
            {
                PrintHelp(e_write);
            }
            
            goto cont;
        }
        if(!strcmp(input[0], "lock"))
        {
            if(count > 2)
            {
                //verify input[1]
                //add input[1] value to lock array
            }
            else
            {
                PrintHelp(e_lock);
            }
            goto cont;
        }
        if(!strcmp(input[0], "list"))
        {
            if(count == 1)
            {
                PrintHelp(e_list);
            }
            else if(!strcmp(input[1], "processes"))
            {
                //list processes
            }
            else if(!strcmp(input[1], "addresses"))
            {
                //list saved addresses (both search and lock) (remember to format if over 100)
            }
            goto cont;
        }
        if(!strcmp(input[0], "help"))
        {
            if(count == 1)
            {
                PrintHelp(e_main);
            }
            else if(!strcmp(input[1], "attach"))
            {
                PrintHelp(e_attach);
            }
            else if(!strcmp(input[1], "search"))
            {
                PrintHelp(e_search);
            }
            else if(!strcmp(input[1], "write") || !strcmp(input[1], "edit"))
            {
                PrintHelp(e_write);
            }
            else if(!strcmp(input[1], "lock"))
            {
                PrintHelp(e_lock);
            }
            else if(!strcmp(input[1], "list"))
            {
                PrintHelp(e_list);
            }
            goto cont;
        }

        if(!strcmp(input[0], "credits"))
        {
            PrintHelp(e_credits);
            goto cont;
        }

        else
        {
            PrintHelp(e_main);
        }

        goto cont;
        cont:
        {
            delete [] ans;
            delete [] input;
            continue;
        }
        
    } 
    
}

void Azure::PrintHelp(HelpTopics topic)
{
    switch(topic)
    {
        case e_main:
        default:
            //the amount of messyness here is too damn high
            cout << kGRN << "Azure help:\n" \
            << "type " << kRED << "help " << kYEL << "[command]" << kCLR << " for specific command help" << endl \
            << "Commands " << endl << endl << kBLU << "blue = command " << kRED << "red = required " << kYEL << "yellow = optional " << endl << endl \
            << kBLU << "attach " << kRED << "[process name]" << kCLR << endl \
            << kBLU << "search " << kRED << "[search value] " << kYEL << "-a|i|f|s|x" << kCLR << endl \
            << kBLU << "write " << kRED << "[address] " << "[value] " << kYEL <<  "-a|i|f|s|x" << kCLR << endl \
            << kBLU << "lock " << kRED << "[address] " << "[value] " << kYEL << "-a|i|f|s|x" << kCLR << endl \
            //list
            << kBLU << "credits " << kCLR << endl << endl;
            break;

        case e_attach:
            cout \
            << kBLU << "attach " << kRED << "[process name]" << kCLR << endl \
            << kCYN << "Attaches azure to the specified process. This is required before you can search for values." << kCLR << endl;
            break;

        case e_search:
            cout \
            << kBLU << "search " << kRED << "[search value] " << kYEL << "-a|i|f|s|x" << kCLR << endl \
            << kCYN << "Searches the attached process for the specified value. You can also specify the type of value to search with any of the above flags." << endl \
            << "-a for any (default), -i for integer, -f for float, -s for string, -x for byte array." << endl \
            << "currently, fuzzy search is not supported but will be soon!" << kCLR << endl;
            break;

        case e_lock:
            cout \
            << kBLU << "lock " << kRED << "[address] [value] " << kYEL << "-a|i|f|s|x" kCLR << endl \ 
            << kCYN << "The value at the address specified is locked to the supplied value. You can specify data type with any of the above flags." << endl \
            << "-a for any (default), -i for integer, -f for float, -s for string, -x for byte array." << kCLR << endl;
            break;

        case e_credits:
            cout \
            << kCYN << "Azure (0.5)" << endl << "Created by Razzile" << endl << "Special thanks to Brave Heart, Alcatraz and all the iOSCheaters crew, everybody on the #theos irc, and saurik himself for dealing with constant questions!" \
            << endl << "Visit " << kYEL << "http://ioscheaters.com " << kCYN "for much more!" << kCLR << endl;
            break;
    }
}


void Azure::WriteToLog(const char *fmt, ...)
{
    va_list arg;
    /* Check if the message should be logged */
    if (!azureSettings || azureSettings->debug != true)
    {
        return;
    }
    FILE *log_file = fopen("/var/mobile/Azure/log.txt", "w+");
    /* Write the error message */
    va_start(arg, fmt);
    vfprintf(log_file, fmt, arg);
    va_end(arg);
    fclose(log_file);
    return;
}

void Azure::GetPreferences()
{
    xmlDoc *doc = NULL;
    char* settings_locations[3] = {
        "/var/mobile/Library/Azure/settings.xml", "/Applications/Azure.app/settings.xml", "/usr/bin/settings.xml"
    };
    xmlInitParser();
    for(int i = 0; i < 3; i++)
    {
   
        if(access(settings_locations[i],F_OK) != -1)
        {
            doc = xmlParseFile(settings_locations[i]);
        }

    }
    if(doc == NULL)
    {
        *azureSettings = {0x0, 0xF0000000, 0x10000, false, false, false, false};
        xmlCleanupParser();
        return;
    }
    xmlNode *cur_node = xmlDocGetRootElement(doc);
    for (; cur_node != NULL; cur_node = cur_node->next)
    {
    	
        if (cur_node->type == XML_ELEMENT_NODE)
        {
            
        	if(xmlStrstr(cur_node->name, (const xmlChar *)"debug") != 0)
        	{
        		if(xmlStrstr(xmlNodeListGetString(cur_node->doc, cur_node->xmlChildrenNode, 1), (const xmlChar *)"true") == 0)
        		{
        			azureSettings->debug = true;
        		}
        		else
        		{
        			azureSettings->debug = false;
        		}
                
        	}
        	else if(xmlStrstr(cur_node->name, (const xmlChar *)"filewrite") != 0)
        	{
        		if(xmlStrstr(xmlNodeListGetString(cur_node->doc, cur_node->xmlChildrenNode, 1), (const xmlChar *)"true") == 0)
        		{
        			azureSettings->fileWrite = true;
        		}
        		else
        		{
        			azureSettings->fileWrite = false;
        		}
        		
        	}
            if(xmlStrstr(cur_node->name, (const xmlChar *)"list") != 0)
            {
                if(xmlStrstr(xmlNodeListGetString(cur_node->doc, cur_node->xmlChildrenNode, 1), (const xmlChar *)"true") == 0)
                {
                    azureSettings->listOnly = true;
                }
                else
                {
                    azureSettings->listOnly = false;
                }
                
            }
            if(xmlStrstr(cur_node->name, (const xmlChar *)"system-apps") != 0)
            {
                if(xmlStrstr(xmlNodeListGetString(cur_node->doc, cur_node->xmlChildrenNode, 1), (const xmlChar *)"true") == 0)
                {
                    azureSettings->systemApps = true;
                }
                else
                {
                    azureSettings->systemApps = false;
                }
                
            }
        	else if(xmlStrstr(cur_node->name, (const xmlChar *)"scandata") != 0)
        	{
        		for(xmlNode *next_node = cur_node->children; next_node != NULL; next_node = next_node->next)
        		{
        			if(xmlStrstr(next_node->name, (const xmlChar *)"start") != 0)
        			{
        				azureSettings->start_addr = strtol(reinterpret_cast<const char*>(xmlNodeListGetString(next_node->doc, next_node->xmlChildrenNode, 1)), 0, 16);
        			}
        			else if(xmlStrstr(next_node->name, (const xmlChar *)"end") != 0)
        			{
        				azureSettings->end_addr = strtol(reinterpret_cast<const char*>(xmlNodeListGetString(next_node->doc, next_node->xmlChildrenNode, 1)), 0, 16);
        			}
        			else if(xmlStrstr(next_node->name, (const xmlChar *)"chunksize") != 0)
        			{
        				azureSettings->chunk_size = strtol(reinterpret_cast<const char*>(xmlNodeListGetString(next_node->doc, next_node->xmlChildrenNode, 1)), 0, 16);
        			}
        		}
        	}
        }
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

/* TO DO: Tidy this up */
int Azure::SetPreferences(GlobalSettings prefs)
{
    if(prefs.start_addr > -1)
    {
        this->azureSettings->start_addr = prefs.start_addr;
    }
    if(prefs.end_addr > -1)
    {
        this->azureSettings->end_addr = prefs.end_addr;
    }
    if(prefs.chunk_size > 0)
    {
        this->azureSettings->chunk_size = prefs.chunk_size;
    }
    this->azureSettings->debug = prefs.debug;
    this->azureSettings->fileWrite = prefs.fileWrite;
    this->azureSettings->listOnly = prefs.listOnly;

    return 0;
        
}


Azure::~Azure()
{
    delete azureSettings;
}

