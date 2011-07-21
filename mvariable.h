#ifndef MVARIABLE_H
#define MVARIABLE_H

#include <iostream>
#include <vector>
#include "mstring.h"

#include "msharedptr.h"

#include "mtype.h"
#include "mtypes.h"

#define M_DECLARE_TYPE(Type) \
    template <> \
    struct MType<Type> { \
        static unsigned int typeId() { \
            static unsigned int _type = registerType(); \
            return _type; \
        } \
    }; \

class MVariable
{
public:
    enum Type {
        Undefined,
        Bool,
        String,
        Int,
        UnsignedInt,
        Float,
        Double,
        Char,
        Custom = 1000
    };

    MVariable();
    MVariable(const MVariable &);

    MVariable(const char *);
    MVariable(int);
    MVariable(bool);
    MVariable(unsigned int);
    MVariable(unsigned long int);
    MVariable(char);
    MVariable(float);
    MVariable(const MString &);

    ~MVariable();

    bool isEmpty() const;
    bool isValid() const;

    MString toString() const;
    int toInt() const;
    bool toBool() const;

    template<typename T>
    T value() const;

    template<typename T>
    bool canConvert() const
    {
        if (d->type == MType<T>::typeId()) {
            return true;
        }
        return false;
    }

    template<typename T>
    void setValue(const T &t);

    MVariable& operator=(const MVariable &);

protected:
    template<typename T>
    bool store(void* data, unsigned int typeId);


private:
    class PrivateVariable {
    public:
        PrivateVariable(MVariable *m) :
            m(m),
            data(0),
            type(MVariable::Undefined),
            empty(true),
            valid(true)
        {}

        MVariable *m;
        void *data;
        MVariable::Type type;
        bool valid : 1;
        bool empty : 1;

        template <typename T>
        void initWithData(void *data)
        {
            if (m->store<T>(data, MType<T>::typeId())) {
                empty = false;
                valid = true;
            }

            empty = true;
            valid = false;
        }
    };

    MSharedPtr<PrivateVariable> d;

};


//// implementations

// values natively supported by the framework
M_DECLARE_INTERNAL_TYPE(char, MVariable::Char)
M_DECLARE_INTERNAL_TYPE(int, MVariable::Int)
M_DECLARE_INTERNAL_TYPE(unsigned int, MVariable::UnsignedInt)
M_DECLARE_INTERNAL_TYPE(bool, MVariable::Bool)
M_DECLARE_INTERNAL_TYPE(float, MVariable::Float)
M_DECLARE_INTERNAL_TYPE(double, MVariable::Double)
M_DECLARE_INTERNAL_TYPE(MString, MVariable::String)



template<typename T>
T MVariable::value() const
{
    if (!canConvert<T>()) {
        return T();
    }

    return T(*(T*)d->data);
}

template<typename T>
void MVariable::setValue(const T &t)
{
    if (store<T>((void*)&t, MType<T>::typeId())) {
        d->empty = false;
        d->valid = true;
        return;
    }

    d->empty = true;
    d->valid = false;
}

template<typename T>
bool MVariable::store(void* data, unsigned int typeId)
{
    delete (T*)d->data;

    d->data = new T();
    if (d->data == 0) {
        //std::cout << "unable to allocate memory" << std::endl;
        return false;
    }

    T* tmp = reinterpret_cast<T*>(d->data);
    *tmp = *((T*)data);

    d->type = (MVariable::Type)typeId;
    //std::cout << "Data type: " << d->type << std::endl;
    return true;
}


static unsigned int _m_registered_types = 1000;

static unsigned int registerType() {
    return _m_registered_types++;
}


#endif // MVARIABLE_H
