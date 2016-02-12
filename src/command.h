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
	  vector<char *>::iterator it;
	  for(unsigned i = 0; i < cmd_run.size(); ++i)
		{
			string tmp = cmd_run.at(i);
			if(tmp.find(";") != string::npos && tmp != ";")
			{
				if(tmp.at(tmp.size()-1) == ';')
				{
					tmp = tmp.substr(0,tmp.size()-1);
					cmd_run.at(i) = strdup(tmp.c_str());
					it = cmd_run.begin() + i + 1;
					string col = ";";
					cmd_run.insert(it,strdup(col.c_str()));
				}

			}

			if(tmp.find("&&") != string::npos && tmp != "&&")
			{
				if(tmp.at(tmp.size()-1) == ';')
				{
					tmp = tmp.substr(0,tmp.size()-1);
					cmd_run.at(i) = strdup(tmp.c_str());
					it = cmd_run.begin() + i + 1;
					string col = "&&";
					cmd_run.insert(it,strdup(col.c_str()));
				}

			}

			if(tmp.find("||") != string::npos && tmp != "||")
			{
				if(tmp.at(tmp.size()-1) == ';')
				{
					tmp = tmp.substr(0,tmp.size()-1);
					cmd_run.at(i) = strdup(tmp.c_str());
					it = cmd_run.begin() + i + 1;
					string col = "&&";
					cmd_run.insert(it,strdup(col.c_str()));
				}

			}

		}

   }
   
};









