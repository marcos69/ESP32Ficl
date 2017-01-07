#include <string.h>
#include <esp_log.h>
#include <rom/uart.h>
#include "telnet.h"
#include "testFicl.h"
#include <freertos/FreeRTOS.h>
#include <esp_system.h>
#include <stdio.h>
#include <stdlib.h>

#include "ficl.h"
extern ficlVm *vm;
extern ficlSystem *fisystem;

QueueHandle_t line_records_queue;

static char tag[] = "testFicl";



/**
 * A function used to read a line of data from the UART
 * attached serial port.
 */
#ifdef useUART
size_t readLineFromUART(char *buffer, int maxLen) {
	char *tail = buffer;
	size_t len = 0;
	while(1) {
		STATUS status = uart_rx_one_char((uint8_t*)tail);
		if (status != OK) {
			continue;
		}
		if (*tail < 32) {
			//ESP_LOGI(tag, "Got a char: nonprint - 0x%x", *cmd_tail);
		} else {
			//ESP_LOGI(tag, "Got a char: %c - 0x%x", *cmd_tail, *cmd_tail);
		}

		uart_tx_one_char(*tail);
		uart_tx_flush(0);
		if (*tail == '\r' || *tail == '\n'){
			break;
		}
		tail++;
		len++;
		if (len == maxLen) {
			break;
		}
	} // End loop for line
	return len;
} // readLineFromUART
#endif


/**
 * Read a line of text from the queue of line records and blocking if none
 * are available.  The line is copied into the passed in buffer and the
 * length of the line read is returned.  How the line is added to the queue
 * is of no importance to the caller of this function.
 */

size_t readLineQueue(char *buffer, int maxLen) {
	line_record_t line_record;
	size_t retSize;
	BaseType_t rc = xQueueReceive(line_records_queue, &line_record, portMAX_DELAY);
	if (rc == pdTRUE) {
		if (line_record.length > maxLen) {
			line_record.length = maxLen;
		}
		memcpy(buffer, line_record.data, line_record.length);
		free(line_record.data);
		retSize = line_record.length;
	} else {
		retSize = 0;
	}
	return retSize;
} // End of readLine


/**
 * A fast hack to print via telnet
 *
 */
/*
void TelnetPrintf( const char * format, ... )
{
  //char buffer[256];
  va_list args;
  va_start (args, format);
  //vsprintf (buffer,format, args);
	telnet_esp32_vprintf(format,args);
  //perror (buffer);
  va_end (args);
}
*/


/**
 * Test the ficl environment.
 */
int testFicl()
{
	int returnValue = 0;
	static char linebuffer[512];
	int len;

	ficlVm *vm;
	ficlSystem *fisystem;

	fisystem = ficlSystemCreate(NULL);
  ESP_LOGI(tag, "ficlSystemCreate OK fisystem = 0x%08x",(int) fisystem);
  ficlSystemCompileExtras(fisystem);
  ESP_LOGI(tag, "ficlSystemCompileExtras OK");
  vm = ficlSystemCreateVm(fisystem);
  ESP_LOGI(tag, "ficlSystemCreateVm OK vm = 0x%08x",(int) vm);

	returnValue = ficlVmEvaluate(vm, ".ver .( " __DATE__ " ) cr quit");

		while (returnValue != -259)
		{
			fputs(FICL_PROMPT, stdout);
			fflush(stdout);
			TelnetPrintf("TelnetOk> ");

		do {
				 //len=readLineFromUART(linebuffer, 510);
				 len=readLineQueue(linebuffer, 510);
		} while(len==0);

			linebuffer[len+1]='\n';
			linebuffer[len+2]='\0';
			fputs("\n", stdout);
			TelnetPrintf("\n");
			// ESP_LOGI(tag, "Got a line: %.*s", sizeof(linebuffer), linebuffer);
			// ESP_LOGI(tag, "vm = 0x%08x", vm);

			returnValue = ficlVmEvaluate(vm, linebuffer);
			fflush(stdout);
			len=0;
		}

	ESP_LOGI(tag, "ficlSystem Destroy");

	ficlSystemDestroy(fisystem);
	return 0;
} // End of testjs

double __ieee754_remainder(double x, double p) {
	return 0.0;
}
