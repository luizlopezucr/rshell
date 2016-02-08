#include "rshell.h"

class COMMAND:public RSHELL{
  private:
   vector<char *>cmd_run;
  
  public:
   COMMAND():RSHELL(){}
   void cmd_list()
   {
	  //Removes any comments from input and 
	  //removes spaces in input and converts
	  //to vector.
      string comment = "#";
      size_t com = input.find(comment);
      if(com != string::npos)
      {
		input = input.substr(0, com);
      }
	  char *tok = strtok(const_cast<char*>(input.c_str())," ");
	  while(tok != NULL)
	  {
		cmd_run.push_back(tok);
		tok = strtok(NULL, " ");
	  }
   }
};









