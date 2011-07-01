#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "mstring.h"


class MString::Private{

public:
    Private(MString *m):
        m(m),
        str(0)
    {}

    ~Private()
    {
        std::cout << "freeing string data" << std::endl;
        delete[] str;
    }

    void clear()
    {
        delete[] str;
        str = 0;
    }

    MString *m;
    const char * str;

};

MString::MString(const char *str_array) :
    d(MSharedPtr<Private>(new Private(this)))
{
    d->str = new char[strlen(str_array)];
    strcpy((char*) d->str, str_array);
}

MString::MString(const MString &copy) :
    d(copy.d)
{
    d->str = copy.d->str;
}

MString::MString() :
 d(MSharedPtr<Private>(new Private(this)))
{
}

MString::~MString() {
}

void MString::print(std::ostream& os) const {
    os << d->str;
}

int MString::size() const {
    return strlen(d->str);
}

int MString::length() const {
    return strlen(d->str);
}

MString& MString::operator=(const MString& val) {
    d = val.d;
    return *this;
}

bool MString::operator==(const MString& val) {
    return MString::equals(val);
}

/**
 * 
 * @param val
 * @return 
 */
MString& MString::operator +=(const MString& val) {
    detach();

    int totalSize = strlen(d->str) + strlen(val.d->str);
    char *buffer = new char[totalSize + 1];
    strcpy(buffer, d->str);
    delete[] d->str;
    d->str = buffer;
    return *this;
}

bool MString::equals(const MString& val) const {
    if (strcmp(d->str, val.d->str) == 0) {
        return true;
    }
    return false;
}

bool MString::equalsIgnoreCase(const MString& val) const
{

    if (toLowerCase().equals(val.toLowerCase())) {
        return true;
    }
    return false;
}

MString MString::toLowerCase() const
{
    char *tmp = new char[strlen(d->str)];
    int i;
    for (i = 0; i < strlen(d->str); i++) {
        tmp[i] = tolower(d->str[i]);
    }
    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::toUpperCase() const
{
    char *tmp = new char[strlen(d->str)];
    int i;
    for (i = 0; i < strlen(d->str); i++) {
        tmp[i] = toupper(d->str[i]);
    }
    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::substring(int begin, int count)
{
    if (d->str == 0 || strlen(d->str) == 0 || strlen(d->str) < begin)
        return *this;

    char *tmp = (char*) malloc(strlen(d->str)-(begin + count));
    strncpy(tmp, d->str + begin, count);

    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::replace(const MString& str1, const MString& str2)
{
    char *ret;
    int i = 0;
    int count = 0;

    size_t newlen = strlen(str2.d->str);
    size_t oldlen = strlen(str1.d->str);

    for (i = 0; d->str[i] != '\0'; i++) {
        if (strstr(&d->str[i], str1.d->str) == &d->str[i]) {
            count++;
            i += oldlen - 1;
        }
    }

    if (!count) {
        return *this;
    }

    const int length = i + count * (newlen - oldlen);
    ret = new char[length];

    i = 0;
    int j = 0;
    for (; j < length; j++) {
        if (strstr(&d->str[j], str1.d->str) == &d->str[j]) {
            strcpy(&ret[j], str2.d->str);
            j += newlen - 1;
            i += oldlen;
            continue;
        }

        ret[j] = d->str[i];
        i++;
    }
    ret[j] = '\0';

    MString result(ret);
    delete[] ret;
    return result;
}

int MString::indexOf(const MString& val) const
{
    int i;
    for (i = 0; d->str[i] != '\0'; i++) {
        if (strstr(&d->str[i], val.d->str) == &d->str[i]) {
            return i;
        }
    }
}

bool MString::startsWith(const MString& val) const
{
    if (strncmp(d->str, val.d->str, strlen(val.d->str)) == 0) {
        return true;

    }
    return false;
}

bool MString::endsWith(const MString& val) const
{
    if (strncmp(&d->str[strlen((char*) d->str) - strlen(val.d->str)], val.d->str, strlen(val.d->str)) == 0) {
        return true;
    }
    return false;

}

bool MString::isEmpty() const
{
    if (d->str == 0 || strlen(d->str) == 0) {
        return true;
    }
    return false;
}

MString MString::concat(const MString& val)
{
    int totalSize = strlen(d->str) + strlen(val.d->str);
    char *buffer = new char[totalSize];
    strcpy(buffer, d->str);
    strcat(buffer, val.d->str);
    MString result(buffer);
    delete[] buffer;
    return result;
}

bool MString::contains(const MString& val) const
{
    int i = 0;
    int count = 0;

    size_t oldlen = strlen(val.d->str);
    for (i = 0; d->str[i] != '\0'; i++) {
        if (strstr(&d->str[i], val.d->str) == &d->str[i]) {
            count++;
            i += oldlen - 1;
        }
    }

    if (!count) {
        return false;
    }
    return true;
}

/**
 * 
 * @param os
 * @param mstr
 * @return 
 */
std::ostream& operator<<(std::ostream& os, const MString& mstr) {
    mstr.print(os);
    return os;
}

void MString::clear()
{
    detach();
    d->clear();
}

void MString::detach()
{
    std::cout << "detaching" << std::endl;

    char *data = new char[strlen(d->str)];
    strcpy(data, d->str);

    d = MSharedPtr<Private>(new Private(this));
    d->str = data;
}
