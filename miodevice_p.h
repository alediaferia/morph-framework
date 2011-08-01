#ifndef MIODEVICE_P_H
#define MIODEVICE_P_H

class MIODevice::MIODevicePrivate {
public:
    MIODevicePrivate(MIODevice* m) :
        m(m),
        fd(0)
    {}

    MIODevice *m;
    int fd;
    bool seekable;
};

#endif // MIODEVICE_P_H
