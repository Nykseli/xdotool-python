#ifndef _CMD_H_
#define _CMD_H_

#include "xdo_cmd.h"

int cmd_key(context_t *context, char* cmd, char* value);
int cmd_click(context_t *context, int button);
int cmd_mousemove(context_t *context, int x, int y);
int cmd_mousemove_relative(context_t *context, int x, int y);

#endif
