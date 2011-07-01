#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "mstring.h"


using namespace std;

MString::MString(const char *str_array) :
m_str(0) {
    this->m_str = new char[strlen(str_array)];
    strcpy((char*) this->m_str, str_array);
}

MString::MString(const MString &copy) :
m_str(0) {
    this->m_str = copy.m_str;
}

MString::MString() : m_str(0) {
}

MString::~MString() {

    delete[] m_str;
}

int main(int argc, char * const argv[]) {

    MString a = ("ciao sono davide");


    return 0;
}

void MString::print(std::ostream& os) const {
    os << this->m_str;
}

int MString::size() const {
    return strlen(this->m_str);
}

int MString::length() const {
    return strlen(this->m_str);
}

MString& MString::operator=(const MString& val) {
    this->m_str = val.m_str;
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
    int totalSize = strlen(m_str) + strlen(val.m_str);
    char *buffer = new char[totalSize + 1];
    strcpy(buffer, m_str);
    delete[] m_str;
    m_str = buffer;
    return *this;
}

bool MString::equals(const MString& val) {
    if (strcmp(this->m_str, val.m_str) == 0) {
        return true;
    }
    return false;
}

bool MString::equalsIgnoreCase(const MString& val) {

    MString str1(m_str);
    MString str2(val.m_str);

    if (str1.toLowerCase().equals(str2.toLowerCase())) {
        return true;
    }
    return false;
}

MString MString::toLowerCase() {
    char *tmp = new char[strlen(m_str)];
    int i;
    for (i = 0; i < strlen(m_str); i++) {
        tmp[i] = tolower(m_str[i]);
    }
    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::toUpperCase() {
    char *tmp = new char[strlen(m_str)];
    int i;
    for (i = 0; i < strlen(m_str); i++) {
        tmp[i] = toupper(m_str[i]);
    }
    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::substring(int begin, int count) {
    if (m_str == 0 || strlen(m_str) == 0 || strlen(m_str) < begin)
        return *this;

    char *tmp = (char*) malloc(strlen(m_str)-(begin + count));
    strncpy(tmp, m_str + begin, count);

    MString result(tmp);

    delete[] tmp;
    return result;
}

MString MString::replace(const MString& str1, const MString& str2) {

    char *ret;
    int i = 0;
    int count = 0;

    size_t newlen = strlen(str2.m_str);
    size_t oldlen = strlen(str1.m_str);

    for (i = 0; m_str[i] != '\0'; i++) {
        if (strstr(&m_str[i], str1.m_str) == &m_str[i]) {
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
        if (strstr(&m_str[j], str1.m_str) == &m_str[j]) {
            strcpy(&ret[j], str2.m_str);
            j += newlen - 1;
            i += oldlen;
            continue;
        }

        ret[j] = m_str[i];
        i++;
    }
    ret[j] = '\0';

    MString result(ret);
    delete[] ret;
    return result;
}

int MString::indexOf(const MString& val) const {
    int i;
    for (i = 0; m_str[i] != '\0'; i++) {
        if (strstr(&m_str[i], val.m_str) == &m_str[i]) {
            return i;
        }
    }
}

bool MString::startsWith(const MString& val) const {
    if (strncmp(m_str, val.m_str, strlen(val.m_str)) == 0) {
        return true;

    }
    return false;
}

bool MString::endsWith(const MString& val) const {
    if (strncmp(&m_str[strlen((char*) m_str) - strlen(val.m_str)], val.m_str, strlen(val.m_str)) == 0) {
        return true;
    }
    return false;

}

bool MString::isEmpty() const {
    if (m_str == 0 || strlen(m_str) == 0) {
        return true;
    }
    return false;
}

MString MString::concat(const MString& val) {
    int totalSize = strlen(m_str) + strlen(val.m_str);
    char *buffer = new char[totalSize];
    strcpy(buffer, m_str);
    strcat(buffer, val.m_str);
    MString result(buffer);
    delete[] buffer;
    return result;
}

bool MString::contains(const MString& val) const {
    int i = 0;
    int count = 0;

    size_t oldlen = strlen(val.m_str);
    for (i = 0; m_str[i] != '\0'; i++) {
        if (strstr(&m_str[i], val.m_str) == &m_str[i]) {
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

void MString::clear() {
    m_str = 0;
}
