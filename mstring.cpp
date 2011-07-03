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

const char* MString::data() {
    char *tmp = new char[strlen(d->str)];
    int i;
    for (i = 0; i < strlen(d->str); i++) {
        tmp[i] = (d->str[i]);
    }

    return tmp;
}

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

/**
  Returns the length of this string
  @returns the length of the sequence of characters represented by this object.
  */
int MString::length() const {
    return strlen(d->str);
}

/**
  Assigns other to this string and returns a reference to this string.
  */
MString& MString::operator=(const MString& val) {
    d = val.d;
    return *this;
}

/**
 Returns true if string other is equal to this string; otherwise returns false.
  */
bool MString::operator==(const MString& val) {
    return MString::equals(val);
}

/**
 * Appends the string other onto the end of this string and returns a reference to this string.
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
/**
    Compares this string to the specified object.
    The result is true if and only if the argument is not null and is a String object
    that represents the same sequence of characters as this object.
    @param val anObject - the object to compare this String against.
    @return true if the String are equal; false otherwise.
*/
bool MString::equals(const MString& val) const {
    if (strcmp(d->str, val.d->str) == 0) {
        return true;
    }
    return false;
}
/**
    Compares this String to another String, ignoring case considerations.
    @param val the String to compare this String against.
    @return true if the argument is not null and the Strings are equal, ignoring case; false otherwise.
*/
bool MString::equalsIgnoreCase(const MString& val) const
{
    if (toLowerCase().equals(val.toLowerCase())) {
        return true;
    }
    return false;
}

/**
  Converts all of the characters in this String to lower case using the rules of the default locale.
  @return the String, converted to lowercase.
  */
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

/**
  Converts all of the characters in this String to upper case using the rules of the default locale.
  @return the String, converted to uppercase.
  */
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

/**
  Returns a new string that is a substring of this string.
  The substring begins at the specified beginIndex and extends to the character at index endIndex - 1.
  Thus the length of the substring is endIndex-beginIndex.
  @param begin the beginning index, inclusive.
  @param end the ending index, exclusive.
  @return the specified substring.
  */
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

/**
  Returns a new string resulting from replacing all occurrences of oldChar in this string with newChar.
  @param str1 the old character.
  @param str2 the new character.
  @returns a string derived from this string by replacing every occurrence of oldChar with newChar.
  */
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

/**
  Returns the index within this string of the first occurrence of the specified character.
  @param val a string to found
  @returns the index of the first occurrence of the character in the character sequence represented by this object, or -1 if the character does not occur.
  */
int MString::indexOf(const MString& val) const
{
    int i;
    for (i = 0; d->str[i] != '\0'; i++) {
        if (strstr(&d->str[i], val.d->str) == &d->str[i]) {
            return i;
        }
    }

    return -1;
}

/**
  Tests if this string starts with the specified prefix.
  @param val string to analyze
  @returns true if the character sequence represented by the argument is a prefix of the character sequence represented by this string; false otherwise.
*/
bool MString::startsWith(const MString& val) const
{
    if (strncmp(d->str, val.d->str, strlen(val.d->str)) == 0) {
        return true;

    }
    return false;
}
/**
  Tests if this string ends with the specified suffix.
  @param val string to analyze
  @returns true true if the character sequence represented by the argument is a suffix of the character sequence represented by this object; false otherwise.
*/
bool MString::endsWith(const MString& val) const
{
    if (strncmp(&d->str[strlen((char*) d->str) - strlen(val.d->str)], val.d->str, strlen(val.d->str)) == 0) {
        return true;
    }
    return false;

}
/**
  Returns true if, and only if, length() is 0.
  @returns true if length() is 0, otherwise false
*/
bool MString::isEmpty() const
{
    if (d->str == 0 || strlen(d->str) == 0) {
        return true;
    }
    return false;
}

/**
  Concatenates the specified string to the end of this string.
  @param val he String that is concatenated to the end of this String.
  @returns a string that represents the concatenation of this string.
  */
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

/**
  Returns true if and only if this string contains the specified sequence of char values.

  @param the sequence to search for
  @returns true if this string contains s, false otherwise
*/
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
