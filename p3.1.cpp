#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
 
int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        exit(0);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        exit(0);
    }
    
    if(connect(ret, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout<<"Error : Connect Failed \n";
        exit(0);
    }
    
    while(true)
    {
        char buf[128];
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        std::cout<<"Daytime: "<<buf<<std::endl;
    }
 
    close(fd);
 
    return 0;
}
