
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#define FIFO_NAME "tema_FIFO"
#define FIFO_NAME2 "tema2_FIFO"

#define P1_READ     0
#define P2_WRITE    1
#define P2_READ     2
#define P1_WRITE    3

int login_pipe_fork_function(char string[], char out_string[300])
{
	int fd[4];
    pid_t pid;
    
    if (pipe(fd) < 0 )
    {
    	perror("Failed to allocate first pipe");
    	exit(EXIT_FAILURE);
	}
	if (pipe(fd + 2) < 0)
	{
    	perror("Failed to allocate second pipe");
    	exit(EXIT_FAILURE);
	}
	
	if ((pid = fork()) < 0)
	{
		perror("Failed to fork process");
		return EXIT_FAILURE;
	}
	if (pid == 0)
	{
		close(fd[P1_READ]);
		close(fd[P1_WRITE]);

		pid = getpid();

		if (read(fd[P2_READ], string, 300) < 0)
		{
		    perror("Child: Failed to read data from pipe");
		    exit(EXIT_FAILURE);
		}
		else
		{
			printf(".....Your result is being processed\n");
		    strcpy(string, string + 8);
		    
		    FILE *fp;
		    char user[300];
		    int ok = 0;
		    
		    fp = fopen("username_file.txt", "r");
		    if (!fp)
		    	return EXIT_FAILURE;
		    	
		    while (fgets(user, 300, fp) != NULL)
		    {
		    	user[strlen(user)-1] = '\0';
		    	if (!strcmp(user, string))
		    		ok = 1;
		    }
		    fclose(fp);
			
			if (ok)
				strcpy(out_string, "Logged successfully");
			else
				strcpy(out_string, "Logged failed, try another user");
				
			
		    if (write(fd[P2_WRITE], out_string, strlen(out_string)) < 0)
		    {
		        perror("Child: Failed to write response value");
		        exit(EXIT_FAILURE);
		    }
		}

		close(fd[P2_READ]);
		close(fd[P2_WRITE]);

		return EXIT_SUCCESS;
	}
	close(fd[P2_READ]);
	close(fd[P2_WRITE]);

	pid = getpid();
	
	
	if (write(fd[P1_WRITE], string, strlen(string)) < 0)
	{
		perror("Parent: Failed to send value to child ");
		exit(EXIT_FAILURE);
	}


	if (read(fd[P1_READ], out_string, 300) < 0)
	{
		perror("Parent: failed to read value from pipe");
		exit(EXIT_FAILURE);
	}

	close(fd[P1_READ]);
	close(fd[P1_WRITE]);

	wait(NULL);
	
	return EXIT_SUCCESS;
}

int logout_pipe_fork_function(char string[], char out_string[300])
{
	int fd[4];
    pid_t pid;
    
    if (pipe(fd) < 0 )
    {
    	perror("Failed to allocate first pipe");
    	exit(EXIT_FAILURE);
	}
	if (pipe(fd + 2) < 0)
	{
    	perror("Failed to allocate second pipe");
    	exit(EXIT_FAILURE);
	}
	
	if ((pid = fork()) < 0)
	{
		perror("Failed to fork process");
		return EXIT_FAILURE;
	}
	if (pid == 0)
	{
		close(fd[P1_READ]);
		close(fd[P1_WRITE]);

		pid = getpid();

		if (read(fd[P2_READ], string, 300) < 0)
		{
		    perror("Child: Failed to read data from pipe");
		    exit(EXIT_FAILURE);
		}
		else
		{
		    printf(".....Your result is being processed\n");
		    
			strcpy(out_string, "Loggedout successfully");
				
			
		    if (write(fd[P2_WRITE], out_string, strlen(out_string)) < 0)
		    {
		        perror("Child: Failed to write response value");
		        exit(EXIT_FAILURE);
		    }
		}

		close(fd[P2_READ]);
		close(fd[P2_WRITE]);

		return EXIT_SUCCESS;
	}
	close(fd[P2_READ]);
	close(fd[P2_WRITE]);

	pid = getpid();
	
	
	if (write(fd[P1_WRITE], string, strlen(string)) < 0)
	{
		perror("Parent: Failed to send value to child ");
		exit(EXIT_FAILURE);
	}

	if (read(fd[P1_READ], out_string, 300) < 0)
	{
		perror("Parent: failed to read value from pipe");
		exit(EXIT_FAILURE);
	}

	close(fd[P1_READ]);
	close(fd[P1_WRITE]);

	wait(NULL);
	
	return EXIT_SUCCESS;
}

int quit_pipe_fork_function(char string[], char out_string[300])
{
	int fd[4];
    pid_t pid;
    
    if (pipe(fd) < 0 )
    {
    	perror("Failed to allocate first pipe");
    	exit(EXIT_FAILURE);
	}
	if (pipe(fd + 2) < 0)
	{
    	perror("Failed to allocate second pipe");
    	exit(EXIT_FAILURE);
	}
	
	if ((pid = fork()) < 0)
	{
		perror("Failed to fork process");
		return EXIT_FAILURE;
	}
	if (pid == 0)
	{
		close(fd[P1_READ]);
		close(fd[P1_WRITE]);

		pid = getpid();

		if (read(fd[P2_READ], string, 300) < 0)
		{
		    perror("Child: Failed to read data from pipe");
		    exit(EXIT_FAILURE);
		}
		else
		{
		    printf(".....Your result is being processed\n");

			strcpy(out_string, "Your choice to quit was executed successfully");
				
			
		    if (write(fd[P2_WRITE], out_string, strlen(out_string)) < 0)
		    {
		        perror("Child: Failed to write response value");
		        exit(EXIT_FAILURE);
		    }
		}

		close(fd[P2_READ]);
		close(fd[P2_WRITE]);

		return EXIT_SUCCESS;
	}
	close(fd[P2_READ]);
	close(fd[P2_WRITE]);

	pid = getpid();
	
	
	if (write(fd[P1_WRITE], string, strlen(string)) < 0)
	{
		perror("Parent: Failed to send value to child ");
		exit(EXIT_FAILURE);
	}

	if (read(fd[P1_READ], out_string, 300) < 0)
	{
		perror("Parent: failed to read value from pipe");
		exit(EXIT_FAILURE);
	}

	close(fd[P1_READ]);
	close(fd[P1_WRITE]);

	wait(NULL);
	
	return EXIT_SUCCESS;
}


int get_logged_users_socket_fork_function(char string[], char out_string[300])
{
    int fd[2];
    static const int parentsocket = 0;
    static const int childsocket = 1;
  
    pid_t pid;

    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

    if ((pid = fork()) < 0)
	{
		perror("Failed to fork process");
		return EXIT_FAILURE;
	}
	
    if (pid)
    {    
        close(fd[childsocket]);
    	
		pid = getpid();
		
		if (write(fd[parentsocket], string, strlen(string)) < 0)
		{
			perror("Parent: Failed to send value to child ");
			exit(EXIT_FAILURE);
		}

		if (read(fd[parentsocket], out_string, 300) < 0)
		{
			perror("Parent: failed to read value from pipe");
			exit(EXIT_FAILURE);
		}

		close(fd[parentsocket]);

		wait(NULL);
		
		return EXIT_SUCCESS; 
    }
    else
    {
    	
		close(fd[parentsocket]);
        
        pid = getpid();
        
        if(read(fd[childsocket], string, strlen(string) < 0))
        {
        	perror("Child: Failed to read data from pipe");
		    exit(EXIT_FAILURE);
        }
        else
        {
        	printf(".....Your result is being processed\n");
        	
        	out_string = getlogin();
			
			char hostname[300];
			gethostname(hostname, sizeof(hostname));
			
			strcat(out_string, " | ");
			strcat(out_string, hostname);
       
		    if (write(fd[childsocket], out_string, strlen(out_string)) < 0)
		    {
		        perror("Child: Failed to write response value");
		        exit(EXIT_FAILURE);
		    }
        }
        
        close(fd[childsocket]);
        
        return EXIT_SUCCESS; 
        
    }
    exit(0);
}

int get_proc_info_socket_fork_function(char string[], char out_string[300])
{
    int fd[2];
    static const int parentsocket = 0;
    static const int childsocket = 1;
  
    pid_t pid;

    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

    if ((pid = fork()) < 0)
	{
		perror("Failed to fork process");
		return EXIT_FAILURE;
	}
	
    if (pid)
    {    
        close(fd[childsocket]);
    	
		pid = getpid();
		
		if (write(fd[parentsocket], string, strlen(string)) < 0)
		{
			perror("Parent: Failed to send value to child ");
			exit(EXIT_FAILURE);
		}

		if (read(fd[parentsocket], out_string, 300) < 0)
		{
			perror("Parent: failed to read value from pipe");
			exit(EXIT_FAILURE);
		}
		

		close(fd[parentsocket]);

		wait(NULL);
		
		return EXIT_SUCCESS; 
    }
    else
    {
    	
		close(fd[parentsocket]);
        
        pid = getpid();
        
        if(read(fd[childsocket], string, strlen(string) < 0))
        {
        	perror("Child: Failed to read data from pipe");
		    exit(EXIT_FAILURE);
        }
        else
        {
        	printf(".....Your result is being processed\n");
        	
        	FILE *fp;
        	char path[30], pid_num[10], line[300];
        	
        	strcpy(pid_num, string + 16);
        	
        	strcpy(path,"/proc/");
		    strcat(path, pid_num);
        	strcat(path,"/status");
        	
        	
        	fp = fopen(path, "r");
        	if (!fp)
		    	return EXIT_FAILURE;
		    	
		    while (fgets(line, 300, fp) != NULL)
		    {
		    	if (strstr(line, "Name"))
				{
					strcat(out_string, line);
				}
				else if (strstr(line, "State"))
				{
					strcat(out_string, line);
				}
				else if (strstr(line, "PPid"))
				{
					strcat(out_string, line);
				}
				else if (strstr(line, "Uid"))
				{
					strcat(out_string, line);
				}
				else if(strstr(line, "VmSize"))
				{
					strcat(out_string, line);
				}
		    }
		    fclose(fp);
       
		    if (write(fd[childsocket], out_string, strlen(out_string)) < 0)
		    {
		        perror("Child: Failed to write response value");
		        exit(EXIT_FAILURE);
		    }
        }
        
        close(fd[childsocket]);
        
        return EXIT_SUCCESS; 
        
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    int num, read_fifo_var, write_fifo_var;
  
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    

    printf(".....Server is running\n\n");
    mknod(FIFO_NAME2, S_IFIFO | 0666, 0);
    write_fifo_var = open(FIFO_NAME2, O_WRONLY);
    read_fifo_var = open(FIFO_NAME, O_RDONLY);
    

    do
    {   
    	char s[300] = "";
        if ((num = read(read_fifo_var, s, 300)) == -1)
            perror(".....There is an error on FIFO reading\n");
        else
        {
        	printf(".....Your command was received by server\n");
        	char out_string[300]="";
        	if (strstr(s,"login : "))
        	{
        		login_pipe_fork_function(s, out_string);
        	}
        	else if(!strcmp(s, "logout"))
        	{
        		logout_pipe_fork_function(s, out_string);
        	}
        	else if(!strcmp(s, "quit"))
        	{
        		quit_pipe_fork_function(s, out_string);
        	}
        	else if(!strcmp(s, "get-logged-users"))
        	{
        		get_logged_users_socket_fork_function(s, out_string);
        	}
        	else if(strstr(s, "get-proc-info : "))
        	{
        		get_proc_info_socket_fork_function(s, out_string);
        	}
        	else
        	{
        		strcpy(out_string,"Please try to write a valid command");
        	}

            
            if ((num = write(write_fifo_var, out_string, strlen(out_string))) == -1)
		        perror(".....There is an error on FIFO writing\n");
		    else
		    {
		        printf(".....Your result was sent to client\n\n");
		        if(!strcmp(out_string, "Your choice to quit was executed successfully"))
		        {
		        	printf(".....Server stopped\n\n");
		        	return 1;
		        }
		    }
        }
    }while (num > 0);
}


