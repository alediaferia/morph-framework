/*
 *  mstring.h
 *  Untitled
 *
 *  Created by Davide Santangelo on 27/06/11.
 *
 */

#ifndef MSTRING_H
#define MSTRING_H

#include <string>
#include <iostream>
#include <ostream>

#include "mshareddataptr.h"

#include "mobject.h"

class MString : public MObject
{
    M_OBJECT(MString)
public:
    MString(const MString &);
    MString();
    ~MString();

    MString::MRef init();
    MString::MRef init(const char*);
    MString::MRef init(const char *buffer, int size);
    MString::MRef init(MString::MRef copy);

    void print( std::ostream& os ) const;
    void clear();
    int size() const;
    int length() const;

    virtual mref copy() const;

    //Operator
    //MString& operator=(MString::MRef string);
    //MString& operator+=(MString::MRef string);
    //bool operator==(MString::MRef string);

    bool equals(MString::MRef) const;
    bool equalsIgnoreCase(MString::MRef) const;
    bool isEmpty() const;
    bool startsWith(MString::MRef) const;
    bool endsWith(MString::MRef) const;
    bool contains (MString::MRef) const;
    const char *data() const;
    int indexOf(MString::MRef) const;

    MString::MRef concat(MString::MRef string);
    MString::MRef substring(int begin,int end);
    MString::MRef replace(MString::MRef source, MString::MRef destination);
    MString::MRef toLowerCase() const;
    MString::MRef toUpperCase() const;

    virtual bool equals(const MObject::MRef &) const;
    virtual MObject::MRef toString() const;

private:
    class Private;
    Private *d;
};

std::ostream& operator<<( std::ostream&, MString::MRef);


#endif
