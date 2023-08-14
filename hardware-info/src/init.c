#include <bsp/mbox/property/tags.h>
#include <rtems.h>
#include <rtems/rtems/cache.h>
#include <rtems/score/basedefs.h>
#include <stdio.h>
#include <stdlib.h>

// We need the clock and UART
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

// There's only going to be one task
#define CONFIGURE_MAXIMUM_TASKS 1

// Initialize the classic API tasks table
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#include <bsp/linker-symbols.h>

// Initialize configuration defaults
#define CONFIGURE_INIT
#include <bsp/mbox.h>
#include <bsp/mbox/property/message.h>
#include <bsp/mbox/property/tags/hardware.h>
#include <rtems/confdefs.h>

rtems_task Init(rtems_task_argument ignored) {
    mbox_property_tag_metadata tag_metadata[] = {
        HARDWARE_GET_BOARD_MAC_ADDRESS_TAG,
    };

    mbox_property_message* message = mbox_property_message_new(40);
    mbox_property_message_init(message, 40, tag_metadata,
                               RTEMS_ARRAY_SIZE(tag_metadata));

    mbox_write(PROPERTY_TAGS_ARM_TO_VC, message);
    (void)mbox_read(PROPERTY_TAGS_ARM_TO_VC);

    mbox_property_tag* clocks = (mbox_property_tag*)message->buffer;
    hardware_get_board_mac_address_tag_buffer* buf =
        (hardware_get_board_mac_address_tag_buffer*)clocks->buffer;
    for (unsigned int i = 0;
         i < RTEMS_ARRAY_SIZE(buf->response.board_mac_address); i++)
        printf("mac[%u] = %hu\n", i, buf->response.board_mac_address[i]);

    mbox_property_message_destroy(message);
    exit(0);
}
