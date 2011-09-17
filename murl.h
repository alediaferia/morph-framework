#ifndef MURL_H
#define MURL_H

#include "mobject.h"
#include "mstring.h"
#include "mnumber.h"

class MURL : public MObject
{
    M_OBJECT(MURL)
public:
    MURL();
    ~MURL();

    MURL::MRef init();
    MURL::MRef init(MString::MRef urlString);

    MString::MRef userName() const;
    MString::MRef password() const;
    MString::MRef hostName() const;
    MString::MRef protocol() const;
    MNumber::MRef port() const;
    MString::MRef path() const;
    //MString::MRef searchPath() const;

    void setUserName(MString::MRef userName);
    void setPassword(MString::MRef password);
    void setHostName(MString::MRef hostName);
    void setProtocol(MString::MRef protocol);
    void setPort(MNumber::MRef port);
    void setPath(MString::MRef path);

    //void addSearchPair(MString::MRef key, MString::MRef value);
    //void setSearchPairSeparator(char keyValueSeparator, char searchPairSeparator);

    //bool isValid(MString::MRef part) const;
    bool isValid() const;

    mref toString() const;
    //mref copy() const;

private:
    class MURLPrivate;
    MURLPrivate *d;
};

#endif // MURL_H
