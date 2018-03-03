/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : logging.h                                                           *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <syslog.h>
#include "../logging.h"

namespace azure {

static int az_log_level_to_syslog(int level) {
    switch (level) {
        case AZ_LOG_INFO: return LOG_INFO;
        case AZ_LOG_WARN: return LOG_WARNING;
        case AZ_LOG_ERROR: 
        default: return LOG_ERR;
    }
}

static void WriteToLog(int level, const char *fmt, ...) {
    if (fmt == nullptr) return;

    openlog("azure", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);

    va_list args;
    va_start(args, fmt);

    vsyslog(az_log_level_to_syslog(level), fmt, args);

    closelog();

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
    
} // namespace azure