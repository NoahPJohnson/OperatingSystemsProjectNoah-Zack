/**
 * Noah Johnson
 * Zack While
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

#include <vdiUnixCalls.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

//VDI Header
struct vdiHeader
{
    char name[64];
    unsigned int magicNumber;
    unsigned short int majorVersion;
    unsigned short int minorVersion;
    //Ignore UUID's   
};

class vdiFile
{
    int fd;
    int cursor;
    
    public:
        int vdi_open(const char*);
        void vdi_close(int);
        ssize_t vdi_read(int, void*, size_t);
        ssize_t vdi_write(int, const void*, size_t);
        off_t vdi_lseek(int, off_t, int);
        void translate();
        
};

int vdiFile::vdi_open(const char pathname*)
{
    //int fd;
    //int cursor;
    fd = open(fn, O_RDONLY);
    if (fd < 0)
    {
        return 1;
    }
    // read header
    read(fd, )    
    //read map
    
    cursor = 0;
    return 0;
}

void vdiFile::vdi_close()
{
    close(fd);
}
        
ssize_t vdi_read(int fd, void *buf, size_t count)
{
    //info = read(fd)
}        

ssize_t vdi_write(int fd, const void *buf, size_t count)
{
    //write(fd)
}

off_t vdi_lseek(int fildes, off_t offset, int whence)
{

}

void translate()
{
    int vdiPageSize;
    int pageNumber;
    int offset;
    int[] map;
    cursor / vdiPageSize = pageNumber;
    cursor % vdiPageSize = offset;
    map[pageNumber] * vdiPageSize + offset;   
}
