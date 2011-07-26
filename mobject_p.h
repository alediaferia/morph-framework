#ifndef MOBJECT_P_H
#define MOBJECT_P_H

#define M_OBJECT_PRIVATE \
    class MRef : public MSharedPtr<MObject> \
    { \
    public: \
        MRef(MObject* object = 0) : \
            MSharedPtr<MObject>(object) \
        {} \
        MRef(const MRef& copy) : MSharedPtr<MObject>(copy) \
        {} \
        virtual ~MRef() \
        {} \
        virtual MObject* operator->() const \
        { \
            return (MObject*)MSharedPtr<MObject>::operator ->(); \
        } \
    }; \
    virtual const char* className() const { \
        static const char _className[] = "MObject"; \
        return _className; \
    } \

#endif // MOBJECT_P_H
