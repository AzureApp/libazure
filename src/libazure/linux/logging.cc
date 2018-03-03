/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : logging.h                                                           *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <android/log.h>
#include "../logging.h"

namespace azure {
 
static int az_log_level_to_android(int level) {
    switch (level) {
        case AZ_LOG_INFO: return ANDROID_LOG_INFO;
        case AZ_LOG_WARN: return ANDROID_LOG_DEBUG;
        case AZ_LOG_ERROR:
        default: return ANDROID_LOG_ERROR;
    }
}

void WriteToLog(int level, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    __android_log_print(az_log_level_to_android(level), "Azure", fmt, args);

    if (!strstr(fmt, "\n")) {
        fmt = concat(fmt, "\n");
    }
    const char *logger = "[Azure Daemon] ";
    char result[256];

    strcpy(result, logger);
    strcat(result, fmt);

    FILE *log_file = fopen(AZURE_LOG_LOC, "a+");
    
    vprintf(result, args);
    va_end(args);

    fclose(log_file);
}

}
