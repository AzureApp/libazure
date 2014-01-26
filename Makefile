GO_EASY_ON_ME = 1
include theos/makefiles/common.mk

TOOL_NAME = azure
azure_FILES = main.cpp MemoryManager.cpp Azure.cpp ProcessInfo.cpp
azure_CFLAGS += -Wc++11-extensions
azure_CODESIGN_FLAGS = -Sent.plist
include $(THEOS_MAKE_PATH)/tool.mk
