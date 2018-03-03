#if defined(__APPLE__)

#include<TargetConditionals.h>

#if defined(TARGET_OS_IPHONE)
#define AZURE_TARGET_IOS 1

#elif defined(TARGET_OS_OSX)
#define AZURE_TARGET_MACOS 1

#endif // TARGET_OS_IPHONE

#elif defined(ANDROID) || defined(__ANDROID__)

#define AZURE_TARGET_ANDROID 1

#elif defined(__LINUX__)

#define AZURE_TARGET_LINUX

#endif