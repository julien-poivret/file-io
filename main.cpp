#include <cstdlib>
#include <iostream>
#include <gnu/libc-version.h>

/*
          Basic file io under linux.  
*/

int main(int argc,char* argv[])
{
    // glibc version.
    std::cout<<"info->"<<gnu_get_libc_version()<<std::endl;

    /*
        For file io nothing better ^^ than linux/c low level syscall.
    */
    
    // File io routine -> create a file or open it.
    FILE* fd = fopen("/home/julien/sd-card/dev-study/Linux-glibc/dat.log","ab+");
   
    if(fd) {
        // if the file is open or created write or append the following data:
        char data[46]="Some random value to b writed on the sd card.";
        std::cout<<fwrite(&data,1,46,fd)<<" Bytes have been writed"<<std::endl;
    }

    // Place the file cursor at the begening.
    fseek(fd,0L, SEEK_SET);

    // Then now we are ready to read the file.
    char Buffer[46] = "";
    unsigned short count = 0;
    while(fread(&Buffer,1, 46, fd)) {
        count++;
        std::cout<<Buffer<<std::endl;
    }
    std::cout<<count*46<<" Bytes have been read"<<std::endl;

    // Set the cursor at the end of the file Technicaly it's allready there ( but for routine purpose... )
    fseek(fd,0L,SEEK_END);
    
    // Get the file size for result corelation.
    auto file_size = ftell(fd);
    std::cout<<"file size: (about) "<<(((float) file_size)/1000.0) <<" Kbytes"<<std::endl;
    
    // File descriptor stream closed.
    fclose(fd);
    return EXIT_SUCCESS;

}
