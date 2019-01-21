#include "xdo_cmd.h"
#include <math.h>

int cmd_mousemove_relative(context_t *context, int x, int y) {
  int ret = 0;
  //char *cmd = *context->argv;
  int polar_coordinates = 0;
  int clear_modifiers = 0;
  int opsync = 0;
  int origin_x = -1, origin_y = -1;

  charcodemap_t *active_mods = NULL;
  int active_mods_n;

  consume_args(context, optind);

  consume_args(context, 2);

  /* Quit early if we don't have to move. */
  if (x == 0 && y == 0) {
    return EXIT_SUCCESS;
  }

  //TODO: clear modification option
  if (polar_coordinates) {
    /* The original request for polar support was that '0' degrees is up
     * and that rotation was clockwise, so 0 is up, 90 right, 180 down, 270
     * left. This conversion can be done with (360 - degrees) + 90 */
    double radians = ((360 - x) + 90) * (M_PI / 180);
    double distance = y;
    x = (cos(radians) * distance);

    /* Negative sin, since screen Y coordinates are descending, where cartesian
     * is ascending */
    y = (-sin(radians) * distance);
  }

  //TODO: clear modification option
  //if (clear_modifiers) {
    xdo_get_active_modifiers(context->xdo, &active_mods, &active_mods_n);
    xdo_clear_active_modifiers(context->xdo, CURRENTWINDOW, active_mods, active_mods_n);
  //}

  if (opsync) {
    xdo_get_mouse_location(context->xdo, &origin_x, &origin_y, NULL);
  }

  ret = xdo_move_mouse_relative(context->xdo, x, y);

  if (ret) {
    fprintf(stderr, "xdo_move_mouse_relative reported an error\n");
  } else {
    if (opsync) {
      /* Wait until the mouse moves away from its current position */
      xdo_wait_for_mouse_move_from(context->xdo, origin_x, origin_y);
    }
  }

  //TODO: clear modification option
  //if (clear_modifiers) {
    xdo_set_active_modifiers(context->xdo, CURRENTWINDOW, active_mods, active_mods_n);
    free(active_mods);
  //}

  return ret;
}

