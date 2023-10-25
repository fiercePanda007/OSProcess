// You need to write the code in a way that the parent process terminates before the child process.
// As parent process does not exist in the sysrem the chid provcess could not print the correct PPID
//checkin
int main(){
    pid_t p;
    p=fork();
    if(p==0){
        sleep(2);
        printf("I am a child having PID %d\n",getpid());
        printf("My parent PID is %D\n",getppid());
    }

    else {
        printf("I am a parent having PID %d\n",getpid());
        printf("My child has a pid of %d\n",p);
    }

}

