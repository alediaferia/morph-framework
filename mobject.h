#ifndef MOBJECT_H
#define MOBJECT_H

#include "mproperty_p.h"
#include "msharedptr.h"
#include "mobject_macros.h"
#include "mobject_p.h"

class PropertyContainer;
class MInvokableMethod;

/**
 * @class MObject is the base class
 * for most of the Morph API.
 * Making a class inherit from MObject adds
 * a few features to the class.
 * Every class inheriting from MObject is enabled
 * to be used with the generic type mref
 * which makes dynamically allocated object to be
 * automatically destroyed when no more referenced
 * from anywhere. In addition to this, the specific
 * class ClassName::MRef is added automatically to the class
 * when using the M_OBJECT macro in the class definition.
 * MObject::MRef or the typedef'd mref is a special type
 * that can be used allover the framework and lets the programmer
 * avoiding to specify the specific type of the object. This
 * grants high flexibility but leaves the programmer with the responsibility
 * of making sure that the right types are there under the hood since a lot
 * is performed at runtime through type-casting.
 *
 * Usually, when making use of a class that inherits MObject, the typical
 * approach to allocate an object is as follows:
 * @code
 * MObject::MRef object = MObject::alloc()->init();
 * @endcode
 *
 * alloc() is a static method that comes for free in every MObject subclass
 * thanks to the M_OBJECT macro. The method simply allocates new memory
 * for the object itself and perform some additional tasks in order to initialize
 * the _self object.
 * The init method, instead, initializes the object with some additional tasking.
 * Usually it should be preferred to leave the default alloc() implementation and
 * perform the initialization phase inside the init method, including passing initialization
 * parameters to the object.
 * @note a special case for this is due to a C++ restriction: const member initialization
 * must be performed inside constructor: in this case a custom alloc implementation must be
 * written:
 * @code
        static MyObject::MRef alloc(int intParam)
        {
            MyObject* instance = new MyObject(intParam);
            MyObject::MRef ret(instance);
            instance->_self = ret;
            instance->_self.deref();
            return ret;
        }
 * @endcode
 *
 * The _self private member variable also comes for free in every MObject subclass
 * and represents a reference to the object itself with 0-refcount. This means
 * that it does not interfere with the MObject memory management policy.
 *
 * Memory management:
 * Memory management with MObject subclasses is refcount-based. A wrapper around
 * MObject subclasses instances pointers makes it possible to identify when an object
 * is no longer referenced in order to automatically destroy it.
 * In order for this to work, MObject::MRef or mref variables should always be preferred
 * over direct pointers use.
 */

class MObject {

public:
    class MRef : public MSharedPtr<MObject> {
        public:
            MRef(MObject* object = 0);
            MRef(const MRef &ref);
            virtual ~MRef();
            virtual MObject* operator->() const;
            virtual MObject* data() const;
            virtual bool operator==(const MObject::MRef &object) const;
            bool isNull() const;
            void deref();
        };
    M_OBJECT_PRIVATE

    MObject();
    virtual ~MObject();

    virtual bool processEvent(MObject::MRef event);
    virtual bool equals(const MObject::MRef &) const;

    MInvokableMethod* invokableByName(const char *name);

    virtual MObject::MRef toString() const;
    static MObject::MRef alloc();
    MObject::MRef init();

    virtual MObject::MRef copy() const;

protected:
    void registerInvokable(MInvokableMethod*, const char *name);

private:
    MObject::MRef _self;
    class MObjectPrivate;
    MObjectPrivate* d;
};

std::ostream& operator<<(std::ostream&, MObject::MRef);

#include "minvokablemethod.h"
#include "morph_defines.h"

#endif
