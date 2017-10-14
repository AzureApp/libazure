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
#include <TargetConditionals.h>

#if TARGET_OS_IOS
#define AZ_LOG_LOC "/var/log/azure.log"
#elif TARGET_OS_OSX
#define AZ_LOG_LOC "/Library/Logs/Azure/azure.log"
#else
#define AZ_LOG_LOC "."
#endif

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

static void WriteToLog(int level, const char *fmt, ...) {
    if (fmt == nullptr) return;

    openlog("azure", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);

    va_list args;
    va_start(args, fmt);

    vsyslog(level, fmt, args);

    va_end(args);
    closelog();

    if (!strstr(fmt, "\n")) {
        fmt = concat(fmt, "\n");
    }
    const char *logger = "[Azure Daemon] ";
    char result[256];

    strcpy(result, logger);
    strcat(result, fmt);

    va_list arg;
    FILE *log_file = fopen(AZ_LOG_LOC, "a+");

    va_start(arg, fmt);
    vprintf(result, arg);
    va_end(arg);

    fclose(log_file);
}

}

#endif //AZURE_LOGGING_H
