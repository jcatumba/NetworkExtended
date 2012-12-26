#include <Python.h>
#include <stdio.h>

void main(int argc, char** argv)
{
    PyObject* main_module, * main_dict, * expression;

    //We execute a simple command in the Python interpreter...
    Py_Initialize();
    PyRun_SimpleString("print(\"Hello\\nWorld\")");

    //Reference to the main module
    main_module = PyImport_AddModule("__main__");
    //Main's dictionary and its copy
    main_dict = PyModule_GetDict(main_module);
    if (PyDict_Check(main_dict)){
        printf("Its a Dict!\n");
    } else {
        printf("Its not a Dict!\n");
    }
    //Evaluation of functions
    expression = PyDict_GetItemString(main_dict, "print");
    PyObject_CallFunction(expression, "s", "Hello again\n");
    Py_Finalize();
}
