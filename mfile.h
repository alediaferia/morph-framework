#ifndef MFILE_H
#define MFILE_H


class MFile
{

public:
    void close() const;
    void write(const char*);

private:
    MFile();
    friend class MFileManager;

private:
    int m_fd;
};

#endif // MFILE_H
