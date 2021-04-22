#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int depth;
pid_t left;                                 //left child of node
pid_t right;                                //right child of node
int i=1;                                    //position of node
int status;                                  //exit status of processes

void half(){
    depth--;
    if(depth==0)                             //leaves dont fork
        return;
    left = fork();                           //left process is created
    if(left!=0){                             //parent process
        fprintf(stderr,"[%d]pid %d  created child pid %d\n",i,getpid(),left);
    }
    if (left == 0){                         //left child
        i=2*i;                              //indexes are determined like array implementation of binary tree
        fprintf(stderr,"[%d]pid %d ppid %d\n",i,getpid(),getppid());
        half();                             //left child tries create it's children
        exit(i);                            //left child exits with it's position as a argument
    }
    else{                                   //parent continues
        right = fork();                     //parent creates left child
        if(right!=0){                       //parent executes
            fprintf(stderr,"[%d]pid %d created child pid %d\n",i,getpid(),right);
        }
        if(right == 0){                     //right child exucutes
            i=2*i+1;                        //indexes are determined like array implementation of binary tree
            fprintf(stderr,"[%d]pid %d ppid %d\n",i,getpid(),getppid());
            half();                         //right child tries create it's children
            exit(i);                        //right child exits with it's position as a argument
        }
    }
    sleep(1);
    if(left!=0){
        waitpid(left,&status,0);     //parent waits left child
        fprintf(stderr,"[%d] left child %d of %d exited status: %d\n",i,left,getpid(),status/256);
    }
    if(right!=0){
        waitpid(right,&status,0);    //parent waits right child
        fprintf(stderr,"[%d] right child %d of %d exited status: %d\n",i,right,getpid(),status/256);
    }
}
int main(int argc,char* argv[]) {
    fprintf(stderr,"[%d]pid %d ppid %d\n",i,getpid(),getppid());    //depth 0
    depth = atoi(argv[1]);                                            //argument to integer
    half();                                                                //recursive function which creates processes depending on depth
}