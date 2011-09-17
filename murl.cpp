#include "murl.h"

static const char s_unsafeChars[] = {
    ' ', '<', '>', '"', '#',
    '{', '}', '|', '\\', '^',
    '~', '[', ']', '`'
};

static const char s_reservedChars[] = {
    ';', '/', '?', ':', '@', '=', '&'
};

class MURL::MURLPrivate
{
public:
    MURLPrivate(MURL *m) : m(m)
    {}

    MURL *m;
    MString::MRef userName;
    MString::MRef password;
    MNumber::MRef port;
    MString::MRef hostName;
    MString::MRef protocol;
    MString::MRef path;

    MString::MRef encode(MString::MRef string);
    bool isUnsafe(char);
    bool isReserved(char);
};

bool MURL::MURLPrivate::isUnsafe(char c)
{
    for (int i = 0; i < sizeof(s_unsafeChars); i++) {
        if (c == s_unsafeChars[i]) {
            return true;
        }
    }

    return false;
}

bool MURL::MURLPrivate::isReserved(char c)
{
    for (int i = 0; i < sizeof(s_reservedChars); i++) {
        if (c == s_reservedChars[i]) {
            return true;
        }
    }

    return false;
}

MString::MRef MURL::MURLPrivate::encode(MString::MRef string)
{
    struct CharNode {
        CharNode *next;
        const char *value;
    };

    int totalLength = 0;
    const char *data = string->data();

    struct CharNode *head = new struct CharNode;
    head->next = 0;

    struct CharNode *current = head;
    int i = 0;
    while (i < string->length()) {

        if (i > 0) {
            current->next = new struct CharNode;
            current = current->next;
            current->next = 0;
        }

        char c = data[i];
        if (isUnsafe(c) || isReserved(c)) {
            char *encoded = new char(4); // '%' 'X' 'X' '\0' <- 4 chars
            sprintf(encoded, "%%%0X", c);
            current->value = encoded;
            totalLength += 3;
        } else {
            current->value = new char(c);
            totalLength += 1;
        }

        i++;
    }

    char *encoded = new char[totalLength+1];
    char *cursor = encoded;

    current = head;
    do {
        strcpy(cursor, current->value);
        cursor += strlen(current->value);

        struct CharNode *previous = current;
        current = current->next;

        delete previous;
    } while (current);

    encoded[totalLength] = '\0';

    MString::MRef ret = MString::alloc()->init(encoded);
    delete[] encoded;

    return ret;
}

MURL::MURL() : MObject(),
    d(new MURLPrivate(this))
{
}

MURL::~MURL()
{
    delete d;
}

void MURL::setUserName(MString::MRef userName)
{
    d->userName = userName;
}

void MURL::setPassword(MString::MRef password)
{
    d->password = password;
}

void MURL::setHostName(MString::MRef hostName)
{
    d->hostName = hostName;
}

void MURL::setProtocol(MString::MRef protocol)
{
    d->protocol = protocol;
}

void MURL::setPort(MNumber::MRef port)
{
    d->port = port;
}

void MURL::setPath(MString::MRef path)
{
    d->path = path;
}

MString::MRef MURL::userName() const
{
    return d->userName;
}

MString::MRef MURL::password() const
{
    return d->password;
}

MString::MRef MURL::hostName() const
{
    return d->hostName;
}

MString::MRef MURL::protocol() const
{
    return d->protocol;
}

MNumber::MRef MURL::port() const
{
    return d->port;
}

MString::MRef MURL::path() const
{
    return d->path;
}


bool MURL::isValid() const
{
    if (d->protocol.isNull() ||
            d->protocol->isEmpty() ||
            d->hostName.isNull() ||
            d->hostName->isEmpty() ||
            ((d->userName.isNull() || d->userName->isEmpty()) && (!d->password.isNull() && !d->password->isEmpty()))) {
        return false;
    }

    return true;
}

mref MURL::toString() const
{}
