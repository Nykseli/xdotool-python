
#include "cmd_key.h"
#include "xdo.h"
#include "xdotool.h"


int main(int argc, char **argv)
{
     context_t context;
    context.xdo = xdo_new(":1");
    argv++, argc--;
    context.argv = argv;
    context.argc = argc;
    context.windows = NULL;
    context.nwindows = 0;
    context.have_last_mouse = False;
    context.debug = 0;

    //cmd_key(&context);
    //cmd_key(&context);

    context_execute(&context);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }
    return 0;
}
