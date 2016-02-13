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

   }
};









