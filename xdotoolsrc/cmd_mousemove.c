#include "xdo_cmd.h"
#include <math.h>
#include <string.h>

struct mousemove {
  Window window;
  int clear_modifiers;
  int opsync;
  int polar_coordinates;
  int x;
  int y;
  int screen;
  useconds_t delay;
  int step;
};

static int _mousemove(context_t *context, struct mousemove *mousemove);

int cmd_mousemove(context_t *context, int x, int y) {
  int ret = 0;
  char *cmd = *context->argv;
  char *window_arg = NULL;

  struct mousemove mousemove;
  mousemove.clear_modifiers = 0;
  mousemove.polar_coordinates = 0;
  mousemove.opsync = 0;
  mousemove.screen = 0;
  mousemove.x = 0;
  mousemove.y = 0;
  mousemove.step = 0;


  consume_args(context, optind);

  //TODO: restore functionality (commented out part)
  /* if (context->argc < 1 \
      || (strcmp(context->argv[0], "restore") && context->argc < 2)) {
    fprintf(stderr, usage, cmd);
    fprintf(stderr, "You specified the wrong number of args (expected 2 coordinates or 'restore').\n");
    return 1;
  }

  if (!strcmp(context->argv[0], "restore")) {
    if (!context->have_last_mouse) {
      fprintf(stderr, "Have no previous mouse position. Cannot restore.\n");
      return EXIT_FAILURE;
    }

    mousemove.x = context->last_mouse_x;
    mousemove.y = context->last_mouse_y;
    mousemove.screen = context->last_mouse_screen;
    consume_args(context, 1);
  } else {
    mousemove.x = atoi(context->argv[0]);
    mousemove.y = atoi(context->argv[1]);
    consume_args(context, 2);
  }

  mousemove.x = atoi(context->argv[0]);
  mousemove.y = atoi(context->argv[1]);
  */
  mousemove.x = x;
  mousemove.y = y;
  consume_args(context, 2);

  window_each(context, window_arg, {
    mousemove.window = window;
    ret = _mousemove(context, &mousemove);
    if (ret != XDO_SUCCESS) {
      return ret;
    }
  }); /* window_each(...) */

  return ret;
}

static int _mousemove(context_t *context, struct mousemove *mousemove) {
  int ret;
  charcodemap_t *active_mods = NULL;
  int active_mods_n;

  int x = mousemove->x;
  int y = mousemove->y;
  int screen = mousemove->screen;
  Window window = mousemove->window;

  /* Save the mouse position if the window is CURRENTWINDOW */
  if (window == CURRENTWINDOW) {
    context->have_last_mouse = True;
    xdo_get_mouse_location(context->xdo, &(context->last_mouse_x),
                      &(context->last_mouse_y), &(context->last_mouse_screen));
  }

  if (mousemove->polar_coordinates) {
    /* x becomes angle (degrees), y becomes distance.
     * XXX: Origin should be center (of window or screen)
     */
    int origin_x, origin_y;
    if (mousemove->window != CURRENTWINDOW) {
      int win_x, win_y;
      unsigned int win_w, win_h;
      xdo_get_window_location(context->xdo, window, &win_x, &win_y, NULL);
      xdo_get_window_size(context->xdo, window, &win_w, &win_h);
      origin_x = win_x + (win_w / 2);
      origin_y = win_y + (win_h / 2);
    } else { /* no window selected, move relative to screen */
      Screen *s = ScreenOfDisplay(context->xdo->xdpy, screen);
      origin_x = s->width / 2;
      origin_y = s->height / 2;
    }

    /* The original request for polar support was that '0' degrees is up
     * and that rotation was clockwise, so 0 is up, 90 right, 180 down, 270
     * left. This conversion can be done with (360 - degrees) + 90 */
    //double radians = (x * M_PI / 180);
    double radians = ((360 - x) + 90) * M_PI / 180;
    double distance = y;
    x = origin_x + (cos(radians) * distance);

    /* Negative sin, since screen Y coordinates are descending, where cartesian
     * is ascending */
    y = origin_y + (-sin(radians) * distance);
  }

  int mx, my, mscreen;
  xdo_get_mouse_location(context->xdo, &mx, &my, &mscreen);


  if (mousemove->clear_modifiers) {
    xdo_get_active_modifiers(context->xdo, &active_mods, &active_mods_n);
    xdo_clear_active_modifiers(context->xdo, window, active_mods, active_mods_n);
  }

  if (mousemove->step == 0) {
    if (window != CURRENTWINDOW && !mousemove->polar_coordinates) {
      ret = xdo_move_mouse_relative_to_window(context->xdo, window, x, y);
    } else {
      ret = xdo_move_mouse(context->xdo, x, y, screen);
    }
  } else {
    if (mx == x && my == y && mscreen == screen) {
      /* Nothing to move. Quit now. */
      return 0;
    }

    fprintf(stderr, "--step support not yet implemented\n");

    if (window > 0) {
      ret = xdo_move_mouse_relative_to_window(context->xdo, window, x, y);
    } else {
      ret = xdo_move_mouse(context->xdo, x, y, screen);
    }
  }

  if (ret) {
    fprintf(stderr, "xdo_move_mouse reported an error\n");
  } else {
    if (mousemove->opsync) {
      /* Wait until the mouse moves away from its current position */
      xdo_wait_for_mouse_move_from(context->xdo, mx, my);
    }
  }

  if (mousemove->clear_modifiers) {
    xdo_set_active_modifiers(context->xdo, window, active_mods, active_mods_n);
    free(active_mods);
  }

  return 0;
} /* int mousemove ... */
