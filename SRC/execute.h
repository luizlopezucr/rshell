#include "command.h"
class EXECUTE: public COMMAND{

	private:
		//keeps track if commands execute properly.
		bool good_exc;
	public:
		EXECUTE():COMMAND(){good_exc=true;}
		void execute()
		{
				good_exc = true;//value indicate if command succeeded
				int fd[2];//f[0] is for reading : f[1] is for writing
				//takes an array of two integers
				//if successful the array will contain two new file
				//descriptors for the pipline
				pipe(fd);//returns 0 on success and -1 on error
				int size = cmd_run.size()+1;
				char** argv = new char*[size];
				for(unsigned i = 0; i < cmd_run.size(); i++)
				{
						argv[i] = cmd_run.at(i);
				}
				argv[cmd_run.size()] = '\0';
				//The pipeline has been established
				//thus we can fork our new child process
				//the return value of fork is dependent if the fork worked
				//if it is -1 the child process wasn't returned in the parent
				//otherwise the pid of the process is returned in the parent
				//zero returned in the child
				int  pid = fork();
				//NOTE:CTP if parent wants to receive data from the child it should
				//close fd1 and the child should close fd0
				//NOTE:PTC if the parent wants to send data from the child then 
				//it should close fd0 and the child should close fd1
				//close the end of the pipe are aren't concerned with
				if(pid < 0)
				{
						perror("ERROR: forking child process failed\n");
						exit(1);
				}
				//this is done by the child process
				else if (pid == 0)
				{
						char val[1];
						//replaces the current process with a new process
						//provides an array of pointers to null terminated strings
						//that represent the argument list available to the 
						//new program
						//takes in file name first and arguments to be executed
						//must be terminated with a null pointer
				//it only returns a value if an error has occured
				if (execvp(argv[0], argv)== -1)
				{
						//prints the error message and the interpreted value
						//of the error message erno
						val[0] = '0';
						perror("ERROR: CMD execution failed.\n");
				}
				else 
						val[0] = '1';
						//child closes the reading side of pipe
						//to send data to the parent
				close(fd[0]);
				//sends the string through the output side of pipe
				//last value is string length
				write(fd[1],val,1);
				exit(1);
				}
				//this is done by the parent process
				else
				{
						//in this case:
						//wait for the child to terminate
						//prevents the zombie state
						//in this case it is waiting for any child process with
						//the same id as the calling process
						if(-1 == wait(0)) 
						{
								perror ("There was an error with wait().");
								good_exc = false;
						}
						char buff[1];
						//to receive data from the child
						close(fd[1]);
						//size buff 1
						
						//puts the values read from child into buff
						//returns the number of bytes actually read
						read(fd[0],buff,1);
						if(buff[0] == '0')
								good_exc = false;
				}
		delete argv;
		}
};
