#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "signal.h"

//in user handler change the value of registers which are stored in trapframe
void cont_handler(int signal){
  __asm__ ("movl $0x0,%eax\n\t");
  __asm__ ("movl $0x43,%ebx\n\t");
  __asm__ ("movl $0x76,%ecx\n\t");
}

void tstp_handler(int signal){
  __asm__ ("movl $0x25,%eax\n\t");
  __asm__ ("movl $0x87,%ebx\n\t");
  __asm__ ("movl $0x06,%ecx\n\t");
}


int main(){
  int i = 0;
  int pid = fork();

  //child process
  if(pid == 0) {
    signal(SIGCONT, cont_handler);
    signal(SIGTSTP, tstp_handler);
    register uint eax asm ("%eax");
    register uint ebx asm ("%ebx");
    register uint ecx asm ("%ecx");
    __asm__ ("movl $0x21,%eax\n\t");
    __asm__ ("movl $0x10,%ebx\n\t");
    __asm__ ("movl $0x03,%ecx\n\t");
    uint saved_eax = eax;
    uint saved_ebx = ebx;
    uint saved_ecx = ecx;
    for(i = 0; i < 600; i++){
      //printf (1, "eax %d ebx %d ecx %d\n", eax, ebx, ecx);
      saved_eax = eax;
      saved_ebx = ebx;
      saved_ecx = ecx;
      if (saved_eax != 33 || saved_ebx != 16 || saved_ecx != 3){
        break;
      } 
      else{ 
	sleep(1);
	continue;
      }
    }
    if (i == 600){
      printf (1, "test passed\n");
    }
    else{
      printf (1, "test failed\n");
    }
  } 

  //parent process
  else
  {
    sleep(200);
    sendkill(pid, SIGCONT);

    //for (i = 0; i < 10; i++){
    //  sleep(40);
    //  sendkill(pid, SIGCONT);
    //}
      //sleep(10);
      //sendkill(pid, SIGTSTP);
    //}
    //sendkill(pid, SIGKILL);
      //sleep(80);
      //sendkill(pid, SIGCONT);
      //sleep(80);
      //sendkill(pid, SIGCONT);
    //}
    wait();
  }
    // int ret = 0;

    // int pid = fork();

    // if(pid == 0) {
    //     ret = pause();
    //     if (-1 == ret)
    //         printf(1,"Process exited\n");
    //     } 
    // else
    // {
    //     printf(1,"Parent\n");

    //     sendkill(pid, SIGTERM);
    //     wait();
    // }
   
    
  exit();
}
