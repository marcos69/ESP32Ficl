#include "ficl.h"
#include <malloc.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <heap_alloc_caps.h>
#include <rom/uart.h>
#include <esp_log.h>


void *ficlMalloc(size_t size)
{
    //return pvPortMallocCaps( size, MALLOC_CAP_EXEC | MALLOC_CAP_8BIT | MALLOC_CAP_32BIT );

    return malloc(size);
}

void *ficlRealloc(void *p, size_t size)
{
    return realloc(p, size);
}

void ficlFree(void *p)
{
      free(p);
}

void TelnetPrintf ( const char * format, ... )
{
  va_list args;
  va_start (args, format);
  telnet_esp32_vprintf(format,args);
  va_end (args);
}

void  ficlCallbackDefaultTextOut(ficlCallback *callback, char *message)
{
    FICL_IGNORE(callback);
    if (message != NULL){
        fputs(message, stdout);
        TelnetPrintf(message);
      }
    else {
        uart_tx_flush(0);
        fflush(stdout);
        }
    return;
}


/* not supported under strict ANSI C */
int ficlFileStatus(char *filename, int *status)
{
    *status = -1;
    return -1;
}


/* gotta do it the hard way under strict ANSI C */
long ficlFileSize(ficlFile *ff)
{
    long currentOffset;
    long size;

    if (ff == NULL)
        return -1;
/*
    currentOffset = ftell(ff->f);
    fseek(ff->f, 0, SEEK_END);
    size = ftell(ff->f);
    fseek(ff->f, currentOffset, SEEK_SET);
*/
    return size;
}



void ficlSystemCompilePlatform(ficlSystem *system)
{
    return;
}
