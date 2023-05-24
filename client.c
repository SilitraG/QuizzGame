#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "tema_FIFO"
#define FIFO_NAME2 "tema2_FIFO"

int main()
{
    char s[300];
    int num, write_fifo_var, read_fifo_var;
    

    printf(".....Client is running\n\n");
    read_fifo_var = open(FIFO_NAME2, O_RDONLY);
    write_fifo_var = open(FIFO_NAME, O_WRONLY);
    
    int user_log = 0, quit_var = 0;;
	
	while(1)
	{
		
		if(!user_log)
		{
			printf(".....Choose from any commands below:\n\n");
			printf("\t<login : username>\n");
			printf("\t<quit>\n\n");
		}
		
		while ( !quit_var && !user_log && (gets(s), !feof(stdin)))
		{
		    if ((num = write(write_fifo_var, s, strlen(s))) == -1)
		        perror(".....There is an error on FIFO writing\n\n");
		    else
		    {
		        printf(".....Your command was sent to server\n\n");
		        
		        char out_string[300]="";
		        if ((num = read(read_fifo_var, out_string, 300)) == -1)
				    perror(".....There is an error on FIFO reading\n\n");
				else
				{
				    printf("%d %s\n\n", num, out_string);
				    if(!strcmp(out_string, "Logged successfully"))
				    	user_log = 1;
				    else if(!strcmp(out_string, "Your choice to quit was executed successfully"))
				    	quit_var = 1;
				    else
				    {
				    	printf(".....Choose from any commands below:\n\n");
				    	printf("\t<login : username>\n");
						printf("\t<quit>\n\n");
				    }
				}
		    }
		    while(s[0])
		    	strcpy(s, s + 1);
		}
		if(quit_var)
			return 1;
		else
		{
			printf(".....Choose from any commands below:\n\n");
			printf("\t<get-logged-users>\n");
			printf("\t<get-proc-info>\n");
			printf("\t<logout>\n\n");
		}	
			
		while (user_log && (gets(s), !feof(stdin)))
		{
				
		    if ((num = write(write_fifo_var, s, strlen(s))) == -1)
		        perror(".....There is an error on FIFO writing\n");
		    else
		    {
		        printf(".....Your command was sent to server\n\n");
		        
		        char out_string[300]="";
		        if ((num = read(read_fifo_var, out_string, 300)) == -1)
				    perror(".....There is an error on FIFO reading\n");
				else
				{
				    printf("%d %s\n\n", num, out_string);
				    if(!strcmp(out_string, "Loggedout successfully"))
				    	user_log = 0;
				    else
				    {
				    	printf(".....Choose from any commands below:\n\n");
						printf("\t<get-logged-users>\n");
						printf("\t<get-proc-info>\n");
						printf("\t<logout>\n\n");	
				    }
				}
		    }
		    while(s[0])
		    	strcpy(s, s + 1);
		}
	}	
    return 1;
}


