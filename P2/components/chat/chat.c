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
	if (!args)
	{
		serial_write_line("Shout command needs arguement\n");
		return;
	}
	chat_shout(args);
}

void tell_command(char* args)
{
	// @0xab Hello!
	if (!args)
	{
		serial_write_line("Tell command needs arguement\n");
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

	char msg[frame->length + 1];
	memcpy(msg, &frame->payload, frame->length);
	msg[frame->length] = '\0';

	char buffer[4 + 9 + frame->length + 16 + 4 + 1 + 1];
	int n = 0;
	n += format_id(buffer + n, frame->source);
	if (frame->destination == lownet_get_device_id()) {
		// This is a tell message, just for us!
		n += sprintf(buffer + n, " %s: ", "says");
	} else {
		// This is a broadcast shout message.
		n += sprintf(buffer + n, " %s: ", "shouts");

	}
	n += sprintf(buffer + n, "%s", msg);
	serial_write_line(buffer);
}

void chat_shout(const char* message) {
	chat_tell(message, LOWNET_BROADCAST_ADDRESS);
}

uint8_t is_valid(const char* message)
{
	uint8_t i = 0;
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
	frame.length = length;
	memcpy(&frame.payload, message, length);
	frame.payload[length] = '\0';
	lownet_send(&frame);
}