#include "rshell.h"

class COMMAND:public RSHELL{
  public:
   vector<char *>cmd_run;
   COMMAND():RSHELL(){}
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
	  //while there are still commands to be read
	  for(unsigned i = 0; i < cmd_run.size(); ++i)
		{
		    //store each token string in a temp
			string tmp = cmd_run.at(i);
			//an array of connectors to check for
			string con[] = { ";","&&","||"};
		    //check the strings for these connectors
			for(unsigned j = 0; j < 3 ; ++j)
			{
				//if there is no connector for the whole length of the string
				if(tmp.find(con[j]) != string::npos && tmp != con[j])
				{
				//if it is found
					if(tmp.find(con[j]) != 0)
					{
						//deliminate at the position found for the connector
						tmp = tmp.substr(0,tmp.find(con[j]));
						//get the cstring and allocate memory for it
						//assign this shortened cstring the position we are pointing at
						cmd_run.at(i) = strdup(tmp.c_str());
						//set the iterator to point to where we need to insert
						//it is + 1 since it we split the substring in 2
						it = cmd_run.begin() + i + 1;
						//creating a temp string to store the connector
						string col = con[j];
						//inserting the connector 
						cmd_run.insert(it,strdup(col.c_str()));
					}

				}
			}

		}

   }
   
};









