#include "audiobuffer.h"



audioBuffer::audioBuffer( int m_buff_size)
{
    m_buffer.resize(m_buff_size);
    std::cout << "Initializing audio buffer of size " << m_buff_size << std::endl;
}

int audioBuffer::bytesFree(){

    int i=0;
    while((m_wr_pos+i)% m_buffer.size() != m_rd_pos){
        i++;
    }
    if(m_wr_pos == m_rd_pos)return m_buffer.size();
    return i;

}




void audioBuffer::writeData(double *data, int length)
{
    int channelBytes = 2;
    int i=0;

    unsigned char * ptr = reinterpret_cast<unsigned char *>(m_buffer.data());

    while (length) {

            qint16 value = static_cast<qint16>(data[i] * 32767);
            i++;

            qToLittleEndian<qint16>(value, ptr+(m_wr_pos% m_buffer.size()));

            if(m_wr_pos > m_rd_pos){
                if(m_wr_pos+channelBytes >= m_buffer.size() && (m_wr_pos+channelBytes)% m_buffer.size() > m_rd_pos){
                    std::cout << "Write pointer caught  up1" << std::endl;
                    break;
                }

            }else if(m_rd_pos > m_wr_pos){
                if(m_wr_pos+channelBytes >= m_buffer.size()){
                    std::cout << "Write pointer caught  up2" << std::endl;
                    break;
                }else if(m_wr_pos+channelBytes >= m_rd_pos){
                    std::cout << "Write pointer caught  up3" << std::endl;
                    break;
                }
            }



            m_wr_pos+=channelBytes;
            if(m_wr_pos >= m_buffer.size()){
                m_wr_pos = m_wr_pos% m_buffer.size();
            }

            length -= 1;

    }
}



qint64 audioBuffer::readData(char *data, qint64 len)
{
    qint64 total = 0;

   // std::cout << "read pointer before" << m_rd_pos << std::endl;

    if(m_rd_pos > m_wr_pos){
        if(m_rd_pos+len >= m_buffer.size() && (m_rd_pos+len)% m_buffer.size() > m_wr_pos){
            std::cout << "Not enough data in generator buffer!!" << std::endl;
            return -1;
        }
    }else if(m_wr_pos > m_rd_pos){
        if(m_wr_pos+len >= m_buffer.size()){
            std::cout << "Not enough data in generator buffer!!" << std::endl;
            return -1;

        }else if(m_rd_pos+len >= m_wr_pos){
            std::cout << "Not enough data in generator buffer!!" << std::endl;
            return -1;
        }

    }else if(m_wr_pos == m_rd_pos){
        if(m_wr_pos > 0){
            m_rd_pos = m_wr_pos-1;
        }else{
            m_rd_pos=m_buffer.size()-1;
        }

        std::cout << "Not enough data in generator buffer!!" << std::endl;
        return -1;
    }
    while (len - total > 0) {
        const qint64 chunk = qMin((m_buffer.size() - m_rd_pos), len - total);
        memcpy(data + total, m_buffer.constData() + m_rd_pos, chunk);
        m_rd_pos = (m_rd_pos + chunk) % m_buffer.size();
        if(m_rd_pos > m_buffer.size()){
            m_rd_pos = m_rd_pos% m_buffer.size();
        }
        total += chunk;
    }

    return total;

}

