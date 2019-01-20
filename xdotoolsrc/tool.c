#include <python3.5m/Python.h>

#include "cmd_key.h"
#include "xdo.h"


static PyObject *hellotool(PyObject *self, PyObject *args, PyObject *kwargs){

    // Key is the char in unicode format
    char* key = NULL;
    char* value = NULL;

    // options
    int clearModifications = 0;


    // option namelsit
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
    printf("%d\n", vall);
    //cmd_key(&context);

    xdo_free(context.xdo);
    if (context.windows != NULL) {
       free(context.windows);
    }

    //return Py_BuildValue("s s", key, value);
   Py_RETURN_TRUE;
}

static char hellotool_docs[] =
    "Testing this doc!\n";

static PyMethodDef hellotool_funcs[] = {
    {"hellotool", (PyCFunction) hellotool, METH_VARARGS | METH_KEYWORDS, hellotool_docs},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Combinations =
{
    PyModuleDef_HEAD_INIT,
    "xdotool_py", /* name of module */
    "usage: control Xorg\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    hellotool_funcs
};

void PyInit_xdotool_py(void) {
    PyModule_Create(&Combinations);
}
