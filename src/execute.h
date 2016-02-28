#include "command.h"


class EXECUTE: public COMMAND{

	private:
		//keeps track if commands execute properly.
		bool good_exc;

	public:
		//default constructor
		EXECUTE():COMMAND(){good_exc=true;}
		void execute(vector<char *> tmp)
		{
		    //set size of he vector to size + 1 to account for the null character
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
			//if pid == 0 then it is the child
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
			//if pid != 0 then we are in the parent
			else
			{
				//int to store status for wait to write to
				int status;
				//wait for the child to finish and free up space to prevent zombie state
				wait(&status);	
				//checks to see if child didn't terminate normally
				//set good_exc accordingly
				good_exc = (status == 0);
			}
			//free up memory after use
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
				
				//stores the cstring in string
				cmd = cmd_run.at(i);
				//ifs to check for connectors 
				if(cmd  == ";")
				{
				    //checks to see how it should execute the commands before it
					if(fa && good_exc)execute(buff);
					if(fo && !good_exc)execute(buff);
					if(!fa && !fo)execute(buff);
					//reset the values
					fa = false;
					fo = false;
					//clear out the string we just executed
					buff.clear();
				}
				else if(cmd == "&&")
				{
					
					//if there was an || and the previous command didn't succeed then execute
					//if there was an && and the previous command worked then execute
				    //takes care of this being the first op
					if(fa && good_exc || fo && !good_exc || !fa && !fo)
					{
					  execute(buff);
					  buff.clear();
					}
				    
					//if not meant to execute then do this 
					//and set the value to false
				    else if(fa && !good_exc || fo && good_exc)
				    {
						good_exc = false;
						buff.clear();
					}
					//set the bool values of the operator we encountered
					fa = true;
				    fo = false;
				}
				else if(cmd == "||")
				{
					
					//if there was an && and the previous command succeeded
					//if there was an ||  and the previous command failed execute
					//takes care of this being the first op
					if(fo && !good_exc || fa && good_exc || !fo && !fa) 
					{
					  execute(buff);
					  buff.clear();
					}
					//if not the base case then don't execute  if there was an || and the exec succeeded
					else if(fo && good_exc || fa && !good_exc)
				    {
						//good_exc = false;
						buff.clear();
				    }
					//set the bool values of the operator we encountered
				    fo = true;
				    fa = false;
				}
				else
				{
				    //if no connectors push the string
					buff.push_back(cmd_run.at(i));
				}

			}
			//executes the last string of commands based on the last
			//logical operators
			if(fa && good_exc)execute(buff);
			if(fo && !good_exc)execute(buff);
			if(!fa && !fo)execute(buff);
			//reset value of good_exc
			good_exc = true;
		}
};
