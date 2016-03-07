#include "rshell.h"
#include "errno.h"
class COMMAND:public RSHELL{
  public:
   vector<char *>cmd_run;
   bool input_err;
   COMMAND():RSHELL(){input_err= false;}
   //reset the vector
   void wipe()
   {
	cmd_run.clear();
   }
   void cmd_list()
   {
	  //Removes any comments from input and 
	  //removes spaces in input and converts
	  //to vector.
      string comment = "#";
      
      size_t com = input.find(comment);
      //searches the whole string for the comment
      //if it finds a position
      if(com != string::npos)
      {
      	//then only take the string before it
		input = input.substr(0, com);
      }
		//stores tokens deliminated by spaces
	  char *tok = strtok(const_cast<char*>(input.c_str())," ");
	  //while there are tokens
	  while(tok != NULL)
	  {
		//push back the token
		cmd_run.push_back(tok);
		//go to next token
		tok = strtok(NULL, " ");
	  }
	  //declaring an iterator to keep track of position in vector
	  vector<char *>::iterator it;
	 

      string con[] = { ";","&&","||", "(", ")"};
	  //while there are still commands to be read
	  for(unsigned i = 0; i < cmd_run.size(); ++i)
		{
		    //store each token string in a temp
			string tmp = cmd_run.at(i);
			//an array of connectors to check for
			bool con_found = false;
		    //check the strings for these connectors
			for(unsigned j = 0; j < 5 ; ++j)
			{	
				int pos = tmp.find(con[j]);
				//if there is a connector for the whole length of the string
				if(pos != string::npos && tmp != con[j] && !con_found)
				{		
						con_found = true;
						//store the connector in the current position	
						cmd_run.at(i) = strdup(con[j].c_str());
						//if there is more after connector
						if(pos + con[j].size() < tmp.size() )
						{
								//insert after the connector
								it = cmd_run.begin() + i + 1;
								cmd_run.insert(it, strdup((tmp.substr(pos + con[j].size(), tmp.size())).c_str()));
						}
						//if there is something before the connector
						if(pos > 0)
						{
								//insert before the connector
								it = cmd_run.begin() + i;
								cmd_run.insert(it, strdup(((tmp.substr(0, pos)).c_str())));
						}
				}
				
			}
			
		}
		 //variable to keep track of parentheses matching
		int depth = 0;
		for(unsigned i = 0; i < cmd_run.size(); i++)
		{
				//checks for mismatched parentheses
				string temp = cmd_run[i];
				if(temp == "(" || temp  == ")")
				{
						temp  == "(" ? depth++ : depth--;
				}
		}
		//if mismatched then output an error and set the bool variable accordingly
			
		if(depth != 0)
		{
				//set bool accordingly
				input_err = true;
				//set error to invalid argument
				errno = EINVAL ;
				//output string error to stderr
				perror("ERROR: MISSING PARENTHESES");
		}
   }
};









