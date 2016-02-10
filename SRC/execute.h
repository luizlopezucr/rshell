#include "command.h"


class EXECUTE: public COMMAND{

	private:
		//keeps track if commands execute properly.
		bool good_exc;

	public:
		EXECUTE():COMMAND(){good_exc=true;}
		void execute()
		{
			int size = cmd_run.size() + 1;
			char** argv = new char*[size];

			//converts vector to array
			for(unsigned i = 0; i < cmd_run.size(); ++i)	
			{
				argv[i] = cmd_run.at(i);	

			}
			//execvp requires terminating null character.							
			argv[cmd_run.size()] = '\0';

			//forks a new process for execvp
			int  pid = fork();
			if(pid < 0)
			{
				//if child process failed to create output message.
				perror("ERROR: forking child process failed\n");
				exit(1);
			}
			else if (pid == 0)
			{

				//checks if execvp failed, if it did it outputs that
				//that it had a error and changes the good_exc to false.
				if (execvp(argv[0], argv) == -1)
				{
					perror("ERROR: CMD execution failed.\n");
					good_exc = false;
					exit(1);
				}
			}
			else
			{
				if(-1 == wait(0)) perror ("There was an error with wait().");
				
			}
			delete argv;
		}
};
