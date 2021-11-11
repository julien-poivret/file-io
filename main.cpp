#include <cstdlib>
#include <unistd.h>
#include <pwd.h>
#include <iostream>
#include <gnu/libc-version.h>
#include <sys/syscall.h>

/*
          Basic file io under linux.  
*/

int main(int argc,char* argv[])
{
    // glibc version.
    std::cout<<"info->"<<gnu_get_libc_version()<<std::endl;

    /*
        For file io nothing sim to be better ^^ than linux/c low level syscall.
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

    // Then now we are ready to read the file...
    // - the read is done by chunk of 46 bytes it's fast and ok if you know 
    //   how the file is writen,(if the file is generated (like in this case) by one of your program you can easly predict 
    //   that it can also be exactly subdivised in n chunks of 46 bytes and so look more accurately and much faster in the targeted
    //   n chunk bytes of your choice by scoping the chunk, bytes afters bytes an catch eventually some 
    //   custom escape command sequence of your own.
     
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
    
    // glibc function
    struct passwd* pass = getpwuid(getuid());
    std::cout<<pass->pw_name<<std::endl;

    // basic chmod syscall same as system("chmod 0660 ./dat.log")
    auto a = syscall(0x0f,"dat.log",0660);
    std::cout<<a<<std::endl;

    // like ... 
    system("chmod 0670 ./dat.log");

    return EXIT_SUCCESS;

}
