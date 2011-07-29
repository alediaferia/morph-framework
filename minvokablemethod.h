#ifndef MINVOKABLEMETHOD_H
#define MINVOKABLEMETHOD_H

/**
 * @class MInvokableMethod
 * This is the base class for every invokable method
 * defined in an MObject or its subclasses.
 * Calling the wrong invoke method (aka the one not related
 * with the current invokable method) causes nothing to happen.
 */
class MInvokableMethod {
public:
    virtual void invoke();
    virtual void invoke(void *arg1);
    virtual void invoke(void *arg1, void* arg2);
    virtual void invoke(void *arg1, void* arg2, void* arg3);
};
#endif // MINVOKABLEMETHOD_H
