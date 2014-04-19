//
//  MemoryManager.cpp
//  azure-mac-tests
//
//  Created by Callum Taylor on 03/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#include "MemoryManager.h"
MemoryManager* MemoryManager::az_mem = NULL;


MemoryManager::MemoryManager()
{
    searchData = new struct ReadData();
    lockData = new vector<struct LockData>();
}

MemoryManager* MemoryManager::instance()
{
    if(!az_mem)
    {
        az_mem = new MemoryManager();
    }
    return az_mem;
}




kern_return_t MemoryManager::GetRegions()
{
    
    kern_return_t status = KERN_SUCCESS;
    vm_address_t address = 0x0;
    while (status == KERN_SUCCESS && address <= 0xF0000000)
    {
        
        vm_size_t vmsize;
        
        vm_region_basic_info_data_t info;
        mach_msg_type_number_t info_count = VM_REGION_BASIC_INFO_COUNT;
        memory_object_name_t object;
        
        status = vm_region(currentTask, &address, &vmsize, VM_REGION_BASIC_INFO, (vm_region_info_t)&info, &info_count, &object);
        // XXX: Possibly not check for write permissions
        if((info.protection & VM_PROT_WRITE) && (info.protection & VM_PROT_READ) && (status == KERN_SUCCESS))
        {
            //printf("0x%X size: 0x%X\n", address, vmsize);
            Region temp = {static_cast<int>(address), static_cast<int>(vmsize)};
            regions.push_back(temp); // where pushed back
        }
        address+=vmsize;
        //printf("%s\n", mach_error_string(status));
    }
    return status;
}
/* ReadData(pattern, size of pattern)
 * reads memory and also finds the pattern
 * pattern finding will be dealt in a different function in the future
 */
kern_return_t MemoryManager::BeginSearch(uint bytes, size_t size)
{
    printf("searching...\n");
    this->GetRegions();
    int total = 0;
    int progressed = 0;
    
    int readsz = 0;
    int debug_actualsz = 0;
    kern_return_t status = KERN_SUCCESS;
    
    for(Region region : regions)
    {
        total += region.size;
    }
    
    for(Region region : regions)
    {
        //printf("0x%X\n", region.size);
        vm_size_t readsize = 0;
        debug_actualsz = region.size;
        //vector<uint8_t> localData;
        readsz = region.size;
        if(region.size >= 0x100000)
        {
            readsz = region.size / 4;
            if(readsz <= 0x10000)
            {
                readsz *= 2;
            }
        }
        int count = 0;
            for(int z = 0; z < region.size; z+=readsz)
            {
                uint *data = new uint[readsz];
                if(!(z >= region.size))
                    status = vm_read_overwrite(currentTask, region.start+z, readsz, (vm_address_t)data, &readsize);
                    count++;
                //readData.insert(readData.begin(), temp, temp+region.size);he
                if(status != KERN_SUCCESS)
                    break;
                int i = 0; //data
                int j = 0; //bytes
                int k = size;
                //char *byteArray = (char*)malloc(size);
                //sprintf(byteArray,"%d", bytes);
                
                do
                {
                    if(j < k)
                    {
                        if(data[i] == bytes)
                        {
                            goto found;
                            /*i++;
                             j++;*/
                        }
                        else if(data[i] != bytes)
                        {
                            i++;
                            j=0;
                        }
                    }
                    else if(j == k)
                    {
                    found:
                        //printf("%d found at 0x%lx\n",bytes, region.start + (i*sizeof(int)));
                        //addresses.push_back((region.start+i)-size);
                        searchData->addresses.push_back(region.start + (i*sizeof(int)));
                        j=0;
                        i++;
                    }
                } while(i < readsz / sizeof(uint));
                delete[] data;
                
                z = Math::Clamp<uint>(z, region.size, 0);
                //float final = addSize/total;
                progressed += z;
                //printf("\r");
                //UpdateProgress(progressed, total);
            }

        //progressed += region.size;
        //printf("\r");
        //UpdateProgress(progressed, total);

        //searchData->addresses.shrink_to_fit();
        //free(data);
        //vector<uint>().swap(data);
        //data->erase(data->begin(), data->end());
    }
    
    //data.clear();
    
    if(status != KERN_SUCCESS)
        printf("\n%s when searching memory block of size 0x%X\n", mach_error_string(status), debug_actualsz);
    printf("\r100 percent complete\n");
    return status;
}


kern_return_t MemoryManager::IterateSearch(uint newval)
{
    kern_return_t status;
    for (uint address : searchData->addresses)
    {
        uint *readval = new uint;
        vm_size_t readsize = 0;
        status = vm_read(currentTask, address, sizeof(address), (vm_address_t*)&readval, &readsize);
        if (status != KERN_SUCCESS)
        {
            printf("error %s\n", mach_error_string(status));
            break;
        }
        if(*readval == newval)
        {
            //printf("found %d at 0x%x\n", newval, address);
            searchData->addresses.erase(searchData->addresses.begin(), searchData->addresses.end());
            memcpy(searchData->data.data(), &newval, sizeof(newval));
            searchData->addresses.push_back(address);
        }
        
    }
    return status;
}

kern_return_t MemoryManager::WriteAddress(uint addr, uint data)
{
    kern_return_t status = vm_write(currentTask, addr, (vm_address_t)&data, sizeof(data));
    if(status != KERN_SUCCESS)
    {
        //log error
    }
    return status;
}

kern_return_t MemoryManager::Search(SearchObject* obj)
{
    memcpy(searchData->data.data(), obj->data(), obj->_dataCnt); //lel
    if(searchData->addresses.size() == 0)
    {
        int regCnt = 0;
        int readsz = 0;
        kern_return_t status = KERN_SUCCESS;
        
        for (Region region : regions)
        {
            if(region.size >= 0x100000)
            {
                readsz = region.size / 4;
                if(readsz <= 0x10000)
                {
                    readsz *= 2;
                }
            }
            while (regCnt < readsz)
            {
                char *readData = new char[readsz];
                char *patternData = (char*)obj->data();
                
                status = vm_read_overwrite(this->currentTask, region.start, readsz, (unsigned)readData, NULL);
                if(status != KERN_SUCCESS)
                {
                    AZLog("Memory Manager: read error: ");
                    AZLog(mach_error_string(status));
                    AZLog("\n");
                }
                
                int i = 0; //data
                int j = 0; //bytes
                int k = obj->_dataCnt;
                do
                {
                    if(j < k)
                    {
                        if(patternData[i] == readData[i])
                        {
                            
                            i++;
                            j++;
                        }
                        else if(patternData[i] != readData[i])
                        {
                            i++;
                            j=0;
                        }
                    }
                    else if(j == k)
                    {
                        //printf("%d found at 0x%lx\n",bytes, region.start + (i*sizeof(int)));
                        //addresses.push_back((region.start+i)-size);
                        searchData->addresses.push_back(region.start + i); //verify this works, if not looka t memcmp
                        
                        j=0;
                        i++;
                    }
                } while(i < readsz);
                
                 //debug
                
                if((region.size - 0x1000) < 0)
                    readsz += region.size - readsz;
                else
                    readsz += 0x1000;
                
                delete readData;
            }
        }
        return status;
    }
    else
    {
        vector<vm_address_t> localAddresses;
        kern_return_t status = KERN_SUCCESS;
        for(int i = 0; i <= searchData->addresses.size(); i++) // <= or < ?
        {
            vm_address_t addr = searchData->addresses[i];
            void* newData = malloc(obj->_dataCnt);

            status = vm_read_overwrite(this->currentTask, addr, obj->_dataCnt, (unsigned)newData, NULL);
            if(status != KERN_SUCCESS)
            {
                AZLog("Read error: could not read saved address (%s)\n", mach_error_string(status));
            }

            if(memcmp(obj->data(), newData, obj->_dataCnt) == 0)
            {
                localAddresses.push_back(addr);
            }
        }
        searchData->addresses.erase(searchData->addresses.begin(), searchData->addresses.end());
        searchData->addresses = localAddresses;

        return status;
    }
}
kern_return_t MemoryManager::WriteData(WriteObject* obj)
{
    //if(always write)
    //XXX: Finish me off
    kern_return_t status;
    vm_prot_t protection;
    vm_size_t vmsize;
    
    vm_region_basic_info_data_t info;
    mach_msg_type_number_t info_count = VM_REGION_BASIC_INFO_COUNT;
    memory_object_name_t object;
    
    status = vm_region(currentTask, &obj->_address, &vmsize, VM_REGION_BASIC_INFO, (vm_region_info_t)&info, &info_count, &object);
    if(status != KERN_SUCCESS)
    {
        AZLog("Memory Manager: region error: %s\n", mach_error_string(status));
    }

    protection = info.protection;
    if(!(info.protection & VM_PROT_WRITE))
    {
        status = vm_protect(this->currentTask, obj->_address, obj->_dataCnt, false, VM_PROT_ALL);
    }
    status = vm_write(this->currentTask, obj->_address, (vm_address_t)obj->data(), obj->_dataCnt);
    if(status != KERN_SUCCESS)
    {
        AZLog("Memory Manager: write error: %s\n", mach_error_string(status));
    }

    status = vm_protect(this->currentTask, obj->_address, obj->_dataCnt, false, protection);
    return status;
}

void MemoryManager::Lock(WriteObject *obj)
{
    LockData tmp = {obj->data(), obj->_dataCnt, static_cast<int>(obj->_address)};
    lockData->push_back(tmp);
}





