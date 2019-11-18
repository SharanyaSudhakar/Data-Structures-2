#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <fstream>
#include <string>
#include <iostream>

class BitStream {
public:
    BitStream() :  isWrite(false),file(), nbits(0), buf(0) {}
    BitStream(bool isw,std::string filename): isWrite(isw),file(),nbits(0),buf(0) {
        if (isWrite)
            file.open(filename, file.out |file.binary);
        else
            file.open(filename, file.in | file.binary);

        if (!file) {
            std::cerr << "Unable to open file";
            exit(1); // terminate with error
        }
    };

    ~BitStream() {
        flush();
        file.close();
    }
	
    void flush();
    int putBit(unsigned int bit);
    void gotoEOF();
    bool isEOF();
    int putbyte(unsigned char byte);
    void putstring(std::string str);
    unsigned char getByte();
    unsigned int getBit();
    void emptyBuffer() { buf = 0; };

private:
    bool isWrite;
    std::fstream file;
    int nbits;
    unsigned char buf;

};
#endif // !BITSTREAM_H