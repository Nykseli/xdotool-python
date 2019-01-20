#include "xdo_cmd.h"
#include <string.h> /* for strcmp */

int cmd_key(context_t *context, char* cmd, char* value) {
  int ret = 0;
  int i, j;
  int c;
  charcodemap_t *active_mods = NULL;
  int active_mods_n;
  useconds_t key_delay = 12000;
  useconds_t repeat_delay = 0;
  int repeat = 1;
  const char *window_arg = NULL;
  int free_arg = 0;

  /* Options */
  int clear_modifiers = 0;

  consume_args(context, optind);

  if (context->argc == 0) {
    fprintf(stderr, "You specified the wrong number of args.\n");
    //fprintf(stderr, usage, cmd);
    return 1;
  }

  /* use %1 if there is a window stack */
  if (window_arg == NULL && context->nwindows > 0) {
    window_arg = "%1";
  }

  int (*keyfunc)(const xdo_t *, Window, const char *, useconds_t) = NULL;

  if (!strcmp(cmd, "key")) {
    keyfunc = xdo_send_keysequence_window;
  } else if (!strcmp(cmd, "keyup")) {
    keyfunc = xdo_send_keysequence_window_up;
  } else if (!strcmp(cmd, "keydown")) {
    keyfunc = xdo_send_keysequence_window_down;
  } else {
    fprintf(stderr, "Unknown command '%s'\n", cmd);
    return 1;
  }

  int max_arg = context->argc;
  window_each(context, window_arg, {
    //if (clear_modifiers) {
      xdo_get_active_modifiers(context->xdo, &active_mods, &active_mods_n);
      xdo_clear_active_modifiers(context->xdo, window, active_mods, active_mods_n);
    //}

    for (j = 0; j < repeat; j++) {
      for (i = 0; i < context->argc; i++) {
        printf("%s\n", value);
        if (is_command(value)) {
          max_arg = i;
          break;
        }
        int tmp = keyfunc(context->xdo, window, value, key_delay);
        if (tmp != 0) {
          fprintf(stderr,
                  "xdo_send_keysequence_window reported an error for string '%s'\n",
                  value);
        }
        ret += tmp;
      } /* each keysequence */

      /* Sleep if --repeat-delay given and not on the last repetition */
      if (repeat_delay > 0 && j < (repeat-1))  {
        usleep(repeat_delay);
      }
    } /* repeat */

    if (clear_modifiers) {
      xdo_set_active_modifiers(context->xdo, window, active_mods, active_mods_n);
      free(active_mods);
    }
  }); /* window_each(...) */

  if (free_arg) {
    free((char *)window_arg);
  }

  consume_args(context, max_arg);

  return ret;
}

