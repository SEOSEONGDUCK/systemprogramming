#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256 
static char receive[BUFFER_LENGTH];
int main(){
  int ret, fd;
  char stringToSend[BUFFER_LENGTH];
  
  fd = open("device",O_RDWR);
  
  if(fd<0){
    perror("Failed to open the device...");
    return errno;
   }
  
  printf("Type in a short string to send to the kernel mode:\n");
  scanf("%s",stringToSend);

  printf("Writing message to the device [%s].\n",stringTosend);

  ret = write(fd,stringToSend,BUFFER_LENGTH);

  if (ret <0) {
     perror("Failed to write the message to the device.");
     return errno;
  }

  printf("Reading from the device...\n");

  ret = read(fd,receive,BUFFER_LENGTH);

  if(ret<0) {

     perror("Failed to read the message from the device.");
     return errno;
  }

  printf("The received message is [%s]\n", receive);
  printf("End of the program \n");
  return 0;

}


