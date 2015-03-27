//
//  Status.h
//  Azure
//
//  Created by callum taylor on 27/03/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#ifndef Azure_Status_h
#define Azure_Status_h

#include <mach/mach.h>
/* Because we need to have some originality, right? */

typedef kern_return_t AZ_STATUS;

#define AZ_SUCCESS KERN_SUCCESS
#define AZ_FAILURE KERN_FAILURE
// maybe fill out more of these?


#endif
