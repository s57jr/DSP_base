#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QObject>
#include <iostream>
#include <qendian.h>


//implement more sophisticated handling (full, empty flags, r/w pointers,...). add mutex?

class audioBuffer : public QObject
{
    Q_OBJECT

public:

    audioBuffer(int m_buff_size);

    qint64 readData(char *data, qint64 maxlen);

    void writeData(double *data, int length);
    int bytesFree();

private:
    qint64 m_rd_pos = 0;
    qint64 m_wr_pos = 0;

    QByteArray m_buffer;

};

#endif // AUDIOBUFFER_H
