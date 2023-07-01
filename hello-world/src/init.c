#include <rtems.h>
#include <stdio.h>
#include <stdlib.h>

// We need the clock and UART
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

// There's only going to be one task
#define CONFIGURE_MAXIMUM_TASKS 1

// Initialize the classic API tasks table
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

// Initialize configuration defaults
#define CONFIGURE_INIT
#include <rtems/confdefs.h>

rtems_task Init(rtems_task_argument ignored) {
    printf("\nHello, world!\n");
    exit(0);
}
