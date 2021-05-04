/*
 * ExrLoader.h
 *
 *  Created on: Sep 19, 2017
 *      Author: alban
 */

#ifndef SRC_EXRLOADER_H_
#define SRC_EXRLOADER_H_

#include <OpenEXR/ImfIO.h>
#include <OpenEXR/ImfInt64.h>

#include <cstring>

class MyStream : public Imf::IStream {
    public:
        MyStream (void* buff, int size, const char fileName[])
            : Imf::IStream(fileName)
            , _buff((char*)buff)
            , _pos(0)
            , _size(size)
        {

        }

        //-----------
        // Destructor
        //-----------

        virtual ~MyStream () {

        }

        //------------------------------------------------------
        // Read from the stream:
        //
        // read(c,n) reads n bytes from the stream, and stores
        // them in array c.  If the stream contains less than n
        // bytes, or if an I/O error occurs, read(c,n) throws
        // an exception.  If read(c,n) reads the last byte from
        // the file it returns false, otherwise it returns true.
        //------------------------------------------------------

        virtual bool read (char c[/*n*/], int n) {
            if (n + _pos > _size) {
                throw std::exception();
            } else {
                memcpy((void*)c, &_buff[_pos], n);
                _pos += n;
                if (_pos == _size) {
                    return false;
                }
            }
            return true;
        }


        //--------------------------------------------------------
        // Get the current reading position, in bytes from the
        // beginning of the file.  If the next call to read() will
        // read the first byte in the file, tellg() returns 0.
        //--------------------------------------------------------

        virtual Imf::Int64   tellg () {
            return _pos;
        }


        //-------------------------------------------
        // Set the current reading position.
        // After calling seekg(i), tellg() returns i.
        //-------------------------------------------

        virtual void    seekg (Imf::Int64 pos) {
            _pos = pos;
        }


      private:
        char* _buff;
        Imf::Int64 _pos;
        Imf::Int64 _size;
};

extern "C" unsigned char* load_exr(void* buffer, int size, const char *filename,
                            int *width, int *height);


#endif /* SRC_EXRLOADER_H_ */
