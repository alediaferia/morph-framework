/*
 *  mstring.h
 *  Untitled
 *
 *  Created by Davide Santangelo on 27/06/11.
 *  Copyright 2011 MissingTech s.r.l. All rights reserved.
 *
 */

#ifndef MSTRING_H
#define MSTRING_H

#include <string>
#include <iostream>
#include <ostream>

#include "msharedptr.h"

#include "macros_p.h"

class MString{

public: 
    MString(const char *);
    MString(const MString &);
    MString();
    ~MString();

    void print( std::ostream& os ) const;
    void clear();
    int size() const;
    int length() const;

    //Operator
    MString& operator=(const MString&);
    MString& operator+=(const MString&);
    bool operator==(const MString&);


    bool equals(const MString&) const;
    bool equalsIgnoreCase(const MString&) const;
    bool isEmpty() const;
    bool startsWith(const MString&) const;
    bool endsWith(const MString&) const;
    bool contains (const MString&) const;
    const char *data() ;
    int indexOf(const MString&) const;

    MString concat(const MString&);
    MString substring(int begin,int end);
    MString replace(const MString&,const MString&);
    MString toLowerCase() const;
    MString toUpperCase() const;

protected:
    void detach();

private:
    M_SHARED_D_POINTER
};

std::ostream& operator<<( std::ostream&, const MString&);


#endif
