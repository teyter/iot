#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <esp_log.h>

#include "ping.h"

#include "serial_io.h"
#include "utility.h"

#define TAG "PING"

void ping_init()
{
	if (lownet_register_protocol(LOWNET_PROTOCOL_PING, ping_receive) != 0)
		{
			ESP_LOGE(TAG, "Error registering PING protocol");
		}
}

typedef struct __attribute__((__packed__))
{
	lownet_time_t timestamp_out;
	lownet_time_t timestamp_back;
	uint8_t origin;
} ping_packet_t;

void ping_command(char* args)
{
	if (!args)
	{
		serial_write_line("A node id must be provided\n");
		return;
	}
	uint8_t dest = (uint8_t)hex_to_dec(args + 2);
	if (dest == 0)
	{
		serial_write_line("Invalid node id\n");
		return;
	}
	ping(dest);
}

void ping(uint8_t node) {
	lownet_frame_t frame;
	frame.source = lownet_get_device_id();
	frame.destination = node;
	frame.protocol = LOWNET_PROTOCOL_PING;
	frame.length = sizeof(ping_packet_t);

	ping_packet_t packet;
	packet.timestamp_out = lownet_get_time();
	packet.origin = lownet_get_device_id();

	memcpy(&frame.payload, &packet, sizeof packet);

	lownet_send(&frame);
}

// my id 0x65
// groska node 0xF0
void ping_receive(const lownet_frame_t* frame) {
	if (frame->length < sizeof(ping_packet_t)) {
		// Malformed frame.  Discard.
		return;
	}

	ping_packet_t packet;
	memcpy(&packet, &frame->payload, sizeof packet);

	if (packet.origin == lownet_get_device_id())
	{
		lownet_time_t now = lownet_get_time();
		lownet_time_t rtt = time_diff(&packet.timestamp_out, &now);

		// reply from id + rtt: + time + null
		char buffer[12 + ID_WIDTH + 6 + TIME_WIDTH + 1];
		int n = 0;
		n += sprintf(buffer + n, "Reply from ");
		n += format_id(buffer + n, frame->source);
		n += sprintf(buffer + n, " RTT: ");
		n += format_time(buffer + n, &rtt);
		serial_write_line(buffer);
	}
	else
	{
		packet.timestamp_back = lownet_get_time();

		lownet_frame_t reply;
		reply.source = lownet_get_device_id();
		reply.destination = frame->source;
		reply.protocol = LOWNET_PROTOCOL_PING;
		reply.length = frame->length;

		memcpy(&reply.payload, &frame->payload, frame->length);
		memcpy(&reply.payload, &packet, sizeof packet);

		lownet_send(&reply);
	}
}
