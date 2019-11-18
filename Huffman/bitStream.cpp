#ifndef BITSTEARM_CPP
#define BITSTREAM_CPP
#include "bitStream.h"
#include <fstream>
#include <string>

void BitStream::flush()
{
    if (nbits != 0)
    {
        buf = buf << (8 - nbits);
    }
    file << buf;
    buf = 0;
    nbits = 0;
}

int BitStream::putBit(unsigned int bit)
{
    buf = (buf << 1) + bit;
    nbits++;
    if (nbits == 8)
    {
        flush();
    }
    return 1;
}

void BitStream::gotoEOF()
{
    file.seekp(file.end);
}

bool BitStream::isEOF() { return file.eof(); }

int BitStream::putbyte(unsigned char byte)
{
    buf = byte;
    nbits = 8;
    flush();
    return 1;
}

void BitStream::putstring(std::string str)
{
    for (unsigned int i = 0; i < str.size(); i++)
    {
        int c = (str[i] == '0') ? 0 : 1;
        putBit(c);
    }
}

unsigned char BitStream::getByte()
{
    buf = file.get();
    nbits = 0;
    return buf;
}

unsigned int BitStream::getBit()
{
    if (nbits == 0)
    {
        buf = file.get();
        nbits = 8;
    }
    //shift and add zeros
    unsigned int bit = buf & (1 << (nbits - 1));
    bit = bit >> (nbits - 1);
    nbits--;
    return bit;
}
#endif