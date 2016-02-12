#include "command.h"


class EXECUTE: public COMMAND{

	private:
		//keeps track if commands execute properly.
		bool good_exc;

	public:
		EXECUTE():COMMAND(){good_exc=true;}
		void execute(vector<char *> tmp)
		{
			int size = tmp.size() + 1;
			char** argv = new char*[size];

			//converts vector to array
			for(unsigned i = 0; i < tmp.size(); ++i)	
			{
				argv[i] = tmp.at(i);	

			}
			//execvp requires terminating null character.							
			argv[tmp.size()] = '\0';

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

		void exec_main()
		{
			vector<char *> buff;
			string cmd;

			//keeps track of whether "&&" or "||" has been found.
			bool fa = false;
			bool fo = false;


			for(unsigned i = 0; i < cmd_run.size(); ++i)
			{
				cmd = cmd_run.at(i);
				if(cmd  == ";")
				{
					if(fa && good_exc)execute(buff);
					if(fo && !good_exc)execute(buff);
					if(!fa && !fo)execute(buff);
					fa = false;
					fo = false;
					buff.clear();
				}
				else if(cmd == "&&")
				{
					if(!fa)
					{
					  execute(buff);
					  buff.clear();
					  fa = true;
					  fo = false;
					}
					if(fa && good_exc)
					{
					  execute(buff);
					  buff.clear();
					}  
				}
				else if(cmd == "||")
				{
					if(!fo)
					{
					  execute(buff);
					  buff.clear();
					  fo = true;
					  fa = false;
					}
					if(fo && !good_exc)
					{
					  execute(buff);
					  buff.clear();
					}  
				}
				else
				{	
					buff.push_back(cmd_run.at(i));
				}

			}
			if(fa && good_exc)execute(buff);
			if(fo && !good_exc)execute(buff);
			if(!fa && !fo)execute(buff);
		}
};
