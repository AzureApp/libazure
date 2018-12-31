/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : logging.h                                                          *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_LOGGING_H
#define AZURE_LOGGING_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "targets.h"

#if AZURE_TARGET_IOS
#define AZURE_LOG_LOC "/var/log/azure.log"
#elif AZURE_TARGET_MACOS
#define AZURE_LOG_LOC "/Library/Logs/Azure/azure.log"
#else
#define AZURE_LOG_LOC "./azure.log"
#endif

#define AZ_LOG_INFO 1
#define AZ_LOG_WARN 2
#define AZ_LOG_ERROR 3
#define AZ_LOG_DEBUG 4

#define AZLogE(...) azure::WriteToLog(AZ_LOG_ERROR, __VA_ARGS__)
#define AZLogW(...) azure::WriteToLog(AZ_LOG_WARN, __VA_ARGS__)
#define AZLogD(...) azure::WriteToLog(AZ_LOG_DEBUG, __VA_ARGS__)
#define AZLog(...) azure::WriteToLog(AZ_LOG_INFO, __VA_ARGS__)

namespace azure {

static const char *concat(const char *s1, const char *s2) {
  char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

/**
 * It is up to each "core" to implement this for the system(s) the core is for
 */
extern void WriteToLog(int level, const char *fmt, ...);

}  // namespace azure

#endif  // AZURE_LOGGING_H
