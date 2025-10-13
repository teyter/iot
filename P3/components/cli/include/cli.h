#ifndef CLI_H
#define CLI_H

#include <stddef.h>

/*
  A command consists of a name, a description, and a function which
  accepts a char* ARGS.  The value of ARGS and its interpretation is
  function defined.
 */

typedef void (*command_fun_t)(char* args);
typedef struct
{
	char* name;
	char* description;
	command_fun_t fun;
} command_t;

// Usage: find_command(COMMAND, COMMANDS, N)
// Pre:   COMMAND is the name of a command in COMMANDS.
//        COMMANDS is an array of command_t objects.
//        N is the length of COMMANDS.
// Value: A pointer to the function that corresponds to the command COMMAND.
command_fun_t find_command (const char* command, const command_t* commands, size_t n);

// DEFINITION: A node id is a string of the form 0xXX where XX is a
// valid hexadecimal number.

// Usage: id_command(NULL)
// Pre:   None, this command takes no arguments.
// Post:  The id of the node has been written to the serial port.
void id_command(char* args);

// Usage: date_command(NULL)
// Pre:   None, this command takes no arguments.
// Post:  The network time has been written to the serial port.
void date_command(char* args);

#endif
