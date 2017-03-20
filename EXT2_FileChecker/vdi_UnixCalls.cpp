/**
Noah Johnson
Step 0, Unix System calls for vdi files

* make it a class.
* method definitions.

notes:
VDI File Structure
Header
|
map
|
disk

* google all about VDI's 
	-Image signature = magic number
	-offset block (tells you where map is) and offset data

* Step 0 works if we can decypher the disk
	-Master boot record, 55AA (magic number?)
	-byte 4 = filesystem type
	-divide by 2 ^ 20 quotient and remainder are important.

* master boot records
	-EXT 2
	[1st 1k is boot data
         2nd 1k is superblock] (both fixed size in fixed location)

* blockgroup has
	-inodes (128 bytes per inode)
	-1 block for block bitmap
	-no gaps in inodes, one big array
	-data (5 things total)
	-blockroups 0, 1, n = 3, 5, 7, or 0 ^ k have copies of superblock.

* blockgroup discriptor table 
	-only where there is a copy of the superblock, 1k, 2k

read superblock -> figure out block size

fetch block function, unsigned character, 8 bits

each entry in group descritor table, 32 bits, lots of useful information.


vdi_open()

vdi_close()

vdi_read()

vdi_write()

vdi_lseek()

translate()

*/

#include "vdiUnixCalls.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;

//VDI Header
struct vdiHeader
{
    char name[64];
    unsigned int magicNumber;
    unsigned int offsetBlocks; //how far into file the map is
    unsigned int offsetData;   //first page frame location
    unsigned int blockSize;    //page size
    unsigned int diskSize;     //total size of virtual drive
    unsigned short int majorVersion;
    unsigned short int minorVersion;
    
    //Ignore UUID's   
};

class vdiFile
{
    int fd;
    int cursor;
    vdiHeader header;
    
    
    public:
        int vdi_open(const char*);
        void vdi_close();
        ssize_t vdi_read(/*int,*/ void*, size_t);
        ssize_t vdi_write(int, const void*, size_t);
        off_t vdi_lseek(off_t, int);
        void setHeader();
        void translate();
        
};

int main()
{
    //fstream fs;
    //fs.open ("Test-fixed-1k.vdi", fstream::in);
    
    //cout << "FILE CONTENTS:  " << fs.read(); 
    //fs.close();
    char data[2560];

    vdiFile testFile;    

    testFile.vdi_open("D:/Google Drive/Dropbox/School/Junior Year/Spring/OS Project/Test-fixed-1k.vdi");
    testFile.vdi_lseek(5, SEEK_SET);
    testFile.vdi_read(data, 1920);
    testFile.vdi_close();
    cout << data << endl;
    return 0;
}

int vdiFile::vdi_open(const char *pathname)
{
    //int fd;
    //int cursor;
    fd = open(pathname, O_RDONLY);
    cout << fd << endl;
    if (fd < 0)
    {
        return 1;
    }
    // read header
    //read(fd, )    
    //read map
    
    cursor = 0;
    return 0;
}

void vdiFile::vdi_close()
{
    close(fd);
}
        
ssize_t vdiFile::vdi_read(/*const char *fn,*/ /*int fd,*/ void *buf, size_t count)
{
    //fd = file discriptor, read this.
    //*buf = buffer what is read goes here.
    //count = how far to read into file.
    //info = read(fd)
    //fd = open(*fn /*, O_RDONLY*/);
    //lseek the starting point
    read(fd, buf, count);
}        

ssize_t vdiFile::vdi_write(int fd, const void *buf, size_t count)
{
    //write(fd)
    //write(fd, *buf, count);
}

off_t vdiFile::vdi_lseek(off_t offset, int whence)
{
    lseek(fd, offset, whence);
}

void vdiFile::setHeader()
{
    header.offsetBlocks = 0;
}

void vdiFile::translate()
{
    int vdiPageSize;
    int pageNumber;
    int offset;
    //int[] map;
    //map = int[vdiPageSize];
    //cursor / vdiPageSize = pageNumber;
    //cursor % vdiPageSize = offset;
    //map[pageNumber] * vdiPageSize + offset;   
}
