#ifndef MOBJECT_P_H
#define MOBJECT_P_H

#define M_OBJECT_PRIVATE \
    virtual const char* className() const { \
        static const char _className[] = "MObject"; \
        return _className; \
    }

#endif // MOBJECT_P_H
