#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#define MSG_BUFFER_LENGTH 128

#define MSG_BUFFER_LENGTH 128

void serial_write_line(const char* string);
void serial_write_prompt();

int serial_read_line(char* buffer);
#endif
