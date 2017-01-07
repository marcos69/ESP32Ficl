#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ESP32Ficl

include $(IDF_PATH)/make/project.mk
CFLAGS += "-Wno-format"
CFLAGS += "-Wno-error=implicit-function-declaration"
CFLAGS += "-Wno-error=unused-value"
#CFLAGS += "-O0"
#CFLAGS += "-Wno-error=i
#CFLAGS += "-Wno-error=i
#CFLAGS += "-Wno-error=i
