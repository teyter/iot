#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <esp_log.h>

#include <string.h>

#include <lownet.h>
#include <serial_io.h>

#include "chat.h"

#define TAG "CHAT"

void chat_init()
{
	if (lownet_register_protocol(LOWNET_PROTOCOL_CHAT, chat_receive) != 0)
		{
			ESP_LOGE(TAG, "Error registering CHAT protocol");
		}
}

void shout_command(char* args)
{
	// ...?
}

void tell_command(char* args)
{
	if (!args)
	{
		serial_write_line("???\n");
		return;
	}
	// dest ?
	if (dest == 0)
	{
		serial_write_line("???\n");
		return;
	}
	chat_tell(args, dest);
}

void chat_receive(const lownet_frame_t* frame) {
	if (frame->destination == lownet_get_device_id()) {
		// This is a tell message, just for us!

		//  ...?
	} else {
		// This is a broadcast shout message.

		// ...?
	}
}

void chat_shout(const char* message) {
	// ...?
}

void chat_tell(const char* message, uint8_t destination) {

	printf("You: %s\n", args); // sprintf(...); serial_write_line(...)

	lownet_frame_t frame;
	frame.source = lownet_get_device_id();
	frame.destination = destination;

}
