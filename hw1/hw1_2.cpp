#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){

    cout<<"Main Process ID : "<<getpid()<<"\n";

    pid_t pid;
    pid = fork();
    if(pid == 0){
        cout<<"Fork 1. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
        pid = fork();
        if(pid > 0){
            wait(NULL);
        }
        else if(pid == 0){
            cout<<"Fork 2. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
            pid = fork();
            if(pid > 0){
                wait(NULL);
            }
            else if(pid == 0){
                cout<<"Fork 3. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
            }
        }
    }
    else if(pid > 0){
        wait(NULL);
        pid = fork();
        if(pid > 0){
            wait(NULL);
            pid = fork();
	        if(pid > 0){
		        wait(NULL);
	        }
	        else if(pid == 0){
            	cout<<"Fork 6. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
	        }
        }
        else if(pid == 0){
            cout<<"Fork 4. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
        }
        pid =fork();
        if(pid > 0){
            wait(NULL);
        }
        else if(pid == 0){
            cout<<"Fork 5. I'm the child "<<getpid()<<", my parent is "<<getppid()<<".\n";
        }
    }


    return 0;
}
