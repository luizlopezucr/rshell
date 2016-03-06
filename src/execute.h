#include "command.h"


class EXECUTE: public COMMAND{
    private:
		//keeps track if commands execute properly.	
		bool good_exc;
		bool close_paren;
		bool open_paren;
		bool overrider;
	public:
		//default constructor
		EXECUTE():COMMAND(){good_exc=true;close_paren = open_paren = overrider = false;}
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

		//base recursive function
		void exec_main(int start_index, int& left_off)
		{
			vector<char *> buff;
			string cmd;
			//resets the value of good_exc
			//good_exc = true;
			//keeps track of whether "&&" or "||" has been found.
			bool fa = false;
			bool fo = false;
			
			for(int i = start_index; i < cmd_run.size(); i++ )
		    {
		    	//update i if necessary
				if(left_off != 0 && i <= left_off)
						i = left_off;
				//if left off at the end break out of the loop
				if(i == cmd_run.size())
						break;
				cmd = cmd_run[i];
				//stores the cstring in string
				//if close paren execute the current stack
				if(cmd == ")")
				{
				    //executes the last string of commands based on the last
				    //logical operators
				    if(!overrider)
				    {
						if(fa && good_exc)execute(buff);
						else if(fo && !good_exc)execute(buff);
						else if(!fa && !fo)execute(buff);
						buff.clear();
				    }
				    open_paren = false;
				    close_paren = true;
					left_off = ++i;
					return;
				}
				//if open paren go down a stack level
				else if (cmd == "(")
				{
						close_paren = false;
						open_paren = true;
						//before recursing see if override needs to be set
						if((fo && good_exc) || (fa && !good_exc))
								overrider = true;
						exec_main(++i, left_off);
						//after recursing back
						if(overrider)
								overrider = false;
				}
				else
				{		
						//if overrider is not true then execute normally otherwise do not do anything at all
						if(!overrider)
						{
								//ifs to check for connectors 
								if(cmd  == ";")
								{
										//checks to see how it should execute the commands before it
										if(fa && good_exc && !close_paren)execute(buff);
										if(fo && !good_exc && !close_paren)execute(buff);
										if(!fa && !fo && !close_paren)execute(buff);
										//there was a close paren and do no work since it has already been done		
										//clear out the string we just executed
										buff.clear();
							
										//reset the values
										fa = false;
										fo = false;
										close_paren = open_paren =  false;
								}
								else if(cmd == "&&")
								{
										//if there was an || and the previous command didn't succeed then execute
										//if there was an && and the previous command worked then execute
										//takes care of this being the first op
						
										if((fa && good_exc || fo && !good_exc || !fa && !fo) && !close_paren )
										{	
												execute(buff);
												buff.clear();
										}	
				    
										//if not meant to execute then do this 
										//and set the value to false
										else if((fa && !good_exc || fo && good_exc) && !close_paren)
										{
												good_exc = false;
												buff.clear();
										}
										//close paren is true do nothing since the work has already been done
										//clear what we just executed
										buff.clear();			
										//set the bool values of the operator we encountered
										fa = true;
										fo = false;
										close_paren = open_paren = false;
								}	
								else if(cmd == "||")
								{
										//if there was an && and the previous command succeeded
										//if there was an ||  and the previous command failed execute
										//takes care of this being the first op
										if((fo && !good_exc || fa && good_exc || !fo && !fa) && !close_paren) 
										{
												execute(buff);
												buff.clear();
										}
										//if not the base case then don't execute  if there was an || and the exec succeeded
										else if((fo && good_exc || fa && !good_exc) && !close_paren)
										{	
												buff.clear();
										}
								//close paren is true do nothing since the work has already been done
								//clear out what we just executed
								buff.clear();
								//think about what to put in here
								//set the bool values of the operator we encountered
								fo = true;
								fa = false;
								close_paren = open_paren =  false;
								}
								else
								{	
										close_paren = open_paren = false;
										//if no connectors push the string
										buff.push_back(cmd_run.at(i));
								}
						}
				}
		    }
		    if(fa && good_exc)execute(buff);
		    if(fo && !good_exc)execute(buff);
		    if(!fa && !fo)execute(buff);
		    //clear out what we just executed
		    buff.clear();
			
		}
};
