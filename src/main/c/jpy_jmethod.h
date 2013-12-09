#ifndef JPY_JMETHOD_H
#define JPY_JMETHOD_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Python object representing a Java method. It's type is 'JMethod'.
 */
typedef struct
{
    PyObject_HEAD

    // Method name.
    PyObject* name;
    // Method parameter count.
    int paramCount;
    // Method parameter types. Will be NULL, if parameter_count == 0.
    JPy_ParamDescriptor* paramDescriptors;
    // Method return type. Will be NULL for constructors.
    JPy_ReturnDescriptor* returnDescriptor;
    // Method is static?
    jboolean isStatic;
    // Method ID retrieved from JNI.
    jmethodID mid;
}
JPy_JMethod;

/**
 * The Python 'JMethod' type singleton.
 */
extern PyTypeObject JMethod_Type;

/**
 * Python object representing an overloaded Java method. It's type is 'JOverloadedMethod'.
 */
typedef struct
{
    PyObject_HEAD

    // The containing type.
    JPy_JType* type;
    // Method name.
    PyObject* name;
    // List of method overloads (a PyList with items of type JPy_JMethod).
    PyObject* methodList;
}
JPy_JOverloadedMethod;

/**
 * The Python 'JOverloadedMethod' type singleton.
 */
extern PyTypeObject JOverloadedMethod_Type;

JPy_JMethod*           JOverloadedMethod_FindMethod(JPy_JOverloadedMethod* overloadedMethod, PyObject* argTuple);
JPy_JMethod*           JOverloadedMethod_FindStaticMethod(JPy_JOverloadedMethod* overloadedMethod, PyObject* argTuple);
JPy_JOverloadedMethod* JOverloadedMethod_New(JPy_JType* type, PyObject* name, JPy_JMethod* method);
int                    JOverloadedMethod_AddMethod(JPy_JOverloadedMethod* overloadedMethod, JPy_JMethod* method);

JPy_JMethod* JMethod_New(PyObject* name,
                         int paramCount,
                         JPy_ParamDescriptor* paramDescriptors,
                         JPy_ReturnDescriptor* returnDescriptor,
                         jboolean isStatic,
                         jmethodID mid);

int JMethod_ConvertToJavaValues(JPy_JMethod* jMethod, int argCount, PyObject* argTuple, jvalue* jArgs);

int JMethod_CreateJArgs(JPy_JMethod* jMethod, PyObject* argTuple, jvalue** jArgs);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* !JPY_JMETHOD_H */