#ifndef MIODEVICE_P_H
#define MIODEVICE_P_H

class MIODevice::MIODevicePrivate {
public:
    MIODevicePrivate(MIODevice* m) :
        m(m)
    {}

    MIODevice *m;
    int fd;
};

#endif // MIODEVICE_P_H
