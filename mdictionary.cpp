#include "mdictionary.h"

MDictionary::MDictionary() :
    d(MSharedPtr<MDictionary>(new MDictionaryPrivate()))
{
}
