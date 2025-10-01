#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <esp_log.h>

#include <string.h>

#include <lownet.h>
#include <serial_io.h>
#include "utility.h"

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
	// @0xab Hello!
	if (!args)
	{
		serial_write_line("???\n");
		return;
	}

	// dest = args[2] + args[3]
	uint8_t dest = (uint8_t) hex_to_dec(strtok(args, " ") + 2);
	char* message = strtok(NULL, "\n");

	if (dest == 0)
	{
		serial_write_line("Invalid node id\n");
		return;
	}
	if (!message)
	{
		serial_write_line("Invalid message\n");
		return;
	}
	chat_tell(message, dest);
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

uint8_t is_valid(const char* message)
{
	uint8_t i = 0;
	int b = 1;
	while (message[i] != '\0')
	{
		if (!util_printable(message[i])) return 0;
		i++;
	}
	if (i > LOWNET_PAYLOAD_SIZE) return 0;
	return i;
}

void chat_tell(const char* message, uint8_t destination) {

	uint8_t length = is_valid(message);

	lownet_frame_t frame;
	frame.source = lownet_get_device_id();
	frame.destination = destination;
	frame.protocol = LOWNET_PROTOCOL_CHAT;
	frame.length = is_valid(message);
	// memcpy(&frame.payload, message length);

}
