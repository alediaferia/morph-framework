#ifndef MDICTIONARY_H
#define MDICTIONARY_H

#include "msharedptr.h"

template<typename K, typename V>
class MDictionary
{
public:
    MDictionary();
    MDictionary(const MDictionary &);
    ~MDictionary();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    V value(const K& key) const;

private:
    class MDictionaryPrivate;
    MSharedPtr<MDictionaryPrivate> d;
};

#endif // MDICTIONARY_H
