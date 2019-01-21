#include <python3.5m/Python.h>

#include "cmd.h"
#include "xdo.h"

static PyObject* movemouse(PyObject *self, PyObject *args, PyObject *kwargs){
    // Mouse position coordinates
    int x;
    int y;

    if(!PyArg_ParseTuple(args, "ii", &x, &y))
        Py_RETURN_FALSE;

    context_t context;
    context.xdo = xdo_new(NULL);
    context.argc = 3;
    context.windows = NULL;
    context.nwindows = 0;
    context.have_last_mouse = False;
    context.debug = 0;

    cmd_mousemove(&context, x, y);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }

    Py_RETURN_TRUE;
}
static PyObject* movemouse_relative(PyObject *self, PyObject *args, PyObject *kwargs){
    int x; // move on x axis
    int y; // move on y axis

    if(!PyArg_ParseTuple(args, "ii", &x, &y))
        Py_RETURN_FALSE;

    context_t context;
    context.xdo = xdo_new(NULL);
    context.argc = 3;
    context.windows = NULL;
    context.nwindows = 0;
    context.have_last_mouse = False;
    context.debug = 0;

    cmd_mousemove_relative(&context, x, y);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }

    Py_RETURN_TRUE;
}

static PyObject* mouseclick(PyObject *self, PyObject *args, PyObject *kwargs){
    int button; // 1, left click, 2 right click, 3 middle button

    if(!PyArg_ParseTuple(args, "i", &button))
        Py_RETURN_FALSE;

    context_t context;
    context.xdo = xdo_new(NULL);
    context.argc = 2;
    context.windows = NULL;
    context.nwindows = 0;
    context.have_last_mouse = False;
    context.debug = 0;

    int vall = cmd_click(&context, button);
    //cmd_key(&context);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }

    Py_RETURN_TRUE;
}

/**
 * @brief emulate single keyboard input.
 *
 * @param self reference to python object. UNUSED
 * @param args first arg: key - xdotool command (key, keydown, keyup). second arg - input value
 * @param kwargs currently unused. TODO: set options heres
 * @return PyObject* True if successfull, False if not
 */
static PyObject *keyboardinput(PyObject *self, PyObject *args, PyObject *kwargs){

    // value is the char in unicode format
    char* key = NULL;
    char* value = NULL;

    // options
    int clearModifications = 0;


    // option namelist. NOT USED
    static char* kwlist[] ={
        "key", //first is the required value
        "clearModifications", // boolean, test if we want to clear shift, ctrl modifications etc
        NULL
    };

    // if(!PyArg_ParseTupleAndKeywords(args, kwargs, "ss|p", kwlist, &key, &value, &clearModifications))
    //     return NULL;

    if(!PyArg_ParseTuple(args, "ss", &key, &value))
        Py_RETURN_FALSE;


    if(!key || !value) Py_RETURN_FALSE;
    context_t context;
    context.xdo = xdo_new(NULL);
//    printf("%s\n", key);

    //context.argv[0] = key;
    //context.argv[1] = value;
    context.argc = 2;
    context.windows = NULL;
    context.nwindows = 0;
    context.have_last_mouse = False;
    context.debug = 0;

    int vall = cmd_key(&context, key, value);
    //cmd_key(&context);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }

    //return Py_BuildValue("s s", key, value);
   Py_RETURN_TRUE;
}

static char xdotool_docs[] =
    "Testing this doc!\n";

static PyMethodDef xdotool_funcs[] = {
    {"keyboardinput", (PyCFunction) keyboardinput, METH_VARARGS | METH_KEYWORDS, xdotool_docs},
    {"mouseclick", (PyCFunction) mouseclick, METH_VARARGS | METH_KEYWORDS, xdotool_docs},
    {"movemouse", (PyCFunction) movemouse, METH_VARARGS | METH_KEYWORDS, xdotool_docs},
    {"movemouse_relative", (PyCFunction) movemouse_relative, METH_VARARGS | METH_KEYWORDS, xdotool_docs},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Combinations =
{
    PyModuleDef_HEAD_INIT,
    "_xdotool", /* name of module */
    xdotool_docs, /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    xdotool_funcs
};

void PyInit__xdotool(void) {
    PyModule_Create(&Combinations);
}
