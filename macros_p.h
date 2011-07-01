#ifndef MACROS_P_H
#define MACROS_P_H

#define M_D_POINTER \
    class Private; \
    Private *const d;

#define M_SHARED_D_POINTER \
    class Private; \
    MSharedPtr<Private> d;

#endif // MACROS_P_H
