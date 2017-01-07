# ESP32Ficl

Forth Inspired Command Line port to ESP32 with telnet support.

Uses the Espressif-IDF-sdk, FreeRTOS, libTelenet and Ficl.

Work in progress, does work, kind off...

Uncomment in ESP32Ficl/main/testFicl.c the readline UART or telnet queue.
Select the modules in Ficl.h and if softcore/softword is needed,
generate a NEW softcore.c, according to the modules.

Needs more FreeRTOS support (task creation).
Find out why float only work as double.
Playing with memory, DRAM-IRAM.
Queueing the UART, update the telnet lib...

More README, in components/libtelnet/ and components/ficl
