/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : logging.h                                                           *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_LOGGING_H
#define AZURE_LOGGING_H

#include <syslog.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "targets.h"

#if AZURE_TARGET_IOS
#define AZURE_LOG_LOC "/var/log/azure.log"
#elif AZURE_TARGET_MACOS
#define AZURE_LOG_LOC "/Library/Logs/Azure/azure.log"
#else
#define AZURE_LOG_LOC "."
#endif

#define AZ_LOG_INFO 1
#define AZ_LOG_WARN 2
#define  AZ_LOG_ERROR 3

#define AZLogE(...) azure::WriteToLog(LOG_ERR, __VA_ARGS__)
#define AZLogW(...) azure::WriteToLog(LOG_WARNING, __VA_ARGS__)
#define AZLog(...) azure::WriteToLog(LOG_INFO, __VA_ARGS__)

namespace azure {

static const char* concat(const char *s1, const char *s2) {
    char *result = (char*)malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

extern void WriteToLog(int level, const char *fmt, ...);

}

#endif //AZURE_LOGGING_H
