#ifndef MTYPES_H
#define MTYPES_H

#define M_DECLARE_INTERNAL_TYPE(Type, _typeId) \
    template <> \
    struct MType<Type> { \
        static unsigned int typeId() { \
            static unsigned int _type = _typeId; \
            return _type; \
        } \
    };

#endif // MTYPES_H
