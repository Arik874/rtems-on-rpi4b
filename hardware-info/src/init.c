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
#include <bsp/mbox.h>
#include <bsp/mbox/property/message.h>
#include <bsp/mbox/property/tags/hardware.h>
#include <rtems/confdefs.h>

static MBOX_PROPERTY_MESSAGE_BUFFER(buffer, 30);

rtems_task Init(rtems_task_argument ignored) {
#define TAGS(X, ...) X(HARDWARE_GET_CLOCKS_TAG, a, __VA_ARGS__)
    MBOX_PROPERTY_MESSAGE_BUFFER_INIT(mbox_buffer, TAGS, buffer);

    mbox_write(PROPERTY_TAGS_ARM_TO_VC, mbox_buffer);
    (void)mbox_read(PROPERTY_TAGS_ARM_TO_VC);

    for (unsigned int i = 0;
         i <
         RTEMS_ARRAY_SIZE(MBOX_PROPERTY_TAG_RESPONSE(mbox_buffer, a).clocks);
         i++)
        printf("%d\n", MBOX_PROPERTY_TAG_RESPONSE(mbox_buffer, a).clocks[i].id);
    exit(0);
}
