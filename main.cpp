#include <cstdlib>
#include <iostream>
#include <gnu/libc-version.h>

int main(int argc,char* argv[])
{

    // glibc version.
    std::cout<<"info->"<<gnu_get_libc_version()<<std::endl;

    // For file io nothing better than low level syscall.

    // File io routine -> create a file.
    FILE* fd = fopen("/home/julien/sd-card/dev-study/Linux-glibc/dat.log","ab+");
    if(fd) {
        // if the file is open or created write or append the following data:
        char data[46]="Some random value to b writed on the sd card.";
        std::cout<<fwrite(&data,1,46,fd)<<" Bytes have been writed"<<std::endl;
    }

    // Place the file cursor at the begening.
    fseek(fd,0L, SEEK_SET);

    // Then now read the file.
    char Buffer[46] = "";
    unsigned short count = 0;
    while(fread(&Buffer,1, 46, fd)) {
        count++;
        std::cout<<Buffer<<std::endl;
    }
    std::cout<<count*46<<" Bytes have been read"<<std::endl;

    // Cursor at the end Technicaly it allready there but for routine purpose...
    fseek(fd,0L,SEEK_END);
    // get the file size for result corelation.
    auto file_size = ftell(fd);
    std::cout<<"file size: (about) "<<(((float) file_size)/1000.0) <<" Kbytes"<<std::endl;
    fclose(fd);
    return EXIT_SUCCESS;

}
