#include <stdio.h>
#include <stdlib.h> //exit
#include <unistd.h> //execlp
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	int child1 = fork();
	if ( child1 == -1 )
	{
        perror("Couldn't fork.");
		exit(1);
	}
	
	if ( child1 == 0 )
	{
		//потомок
		printf( "Child: pid=%d;	group=%d;	parent=%d\n\n", getpid(), getpgrp(), getppid() );
		if ( execlp("ps", "ps", "al", 0) == -1 )
		{
		    perror( "Child couldn't exec." );
			exit(1);
        }
	}

	int child2 = fork();
	if ( child2 == -1 )
	{
        perror("Couldn't fork.");
		exit(1);
	}
	
	if ( child2 == 0 )
	{
		//потомок
		printf( "Child: pid=%d;	group=%d;	parent=%d\n\n", getpid(), getpgrp(), getppid() );
		if ( execlp("/bin/ls", "ls", "-l", 0) == -1 )
		{
		    perror( "Child couldn't exec." );
			exit(1);
        	}
	}
	
	if (child1 != 0 && child2 != 0)
	{
		//предок
		printf( "Parent: pid=%d;	group=%d;	child1=%d 	child2=%d\n", getpid(), getpgrp(), child1, child2 );
		int status;
		pid_t ret_value;

		ret_value = wait( &status );
		if ( WIFEXITED(status) )
		    printf("Parent: child %d finished with %d code.\n\n", ret_value, WEXITSTATUS(status) );
		else if ( WIFSIGNALED(status) )
		    printf( "Parent: child %d finished from signal with %d code.\n\n", ret_value, WTERMSIG(status));
		else if ( WIFSTOPPED(status) )
			printf("Parent: child %d finished from signal with %d code.\n\n", ret_value, WSTOPSIG(status));
			
		ret_value = wait( &status );
		if ( WIFEXITED(status) )
			printf("Parent: child %d finished with %d code.\n\n", ret_value, WEXITSTATUS(status) );
		else if ( WIFSIGNALED(status) )
			printf( "Parent: child %d finished from signal with %d code.\n\n", ret_value, WTERMSIG(status));
		else if ( WIFSTOPPED(status) )
			printf("Parent: child %d finished from signal with %d code.\n\n", ret_value, WSTOPSIG(status));
		return 0;
	}
}