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
			string con[] = { ";","&&","||"};

			for(unsigned j = 0; j < 3 ; ++j)
			{

				if(tmp.find(con[j]) != string::npos && tmp != con[j])
				{
					if(tmp.find(con[j]) != 0)
					{
						tmp = tmp.substr(0,tmp.find(con[j]));
						cmd_run.at(i) = strdup(tmp.c_str());
						it = cmd_run.begin() + i + 1;
						string col = con[j];
						cmd_run.insert(it,strdup(col.c_str()));
					}

				}
			}

		}

   }
   
};









