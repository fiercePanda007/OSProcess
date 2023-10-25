#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>


int main(){
    pid_t q;
    printf("before fork\n");
    q=fork();
    if(q=0){
        printf("I am a child having id %d", getpid());
        printf("My parents id is %d\n",getppid());
    }
    else {
        wait(NULL);
        printf("My childs id is %d",getpid());
        printf("I am parent having id %d\n",getpid());
    }

    printf("Common\n");
}