#include "execute.h"

int main()
{
  RSHELL interface;
  COMMAND com;
  EXECUTE shell;
	
  //until the user enters exit keep prompting for commands
  while(interface.exit_r == false)
  {
    //prints the extra credit
    interface.print();
    //receives the line input
    interface.get_input();
    //if the input is exit it exits the loop
    if(interface.exit_r == true)break;
    else
    {
      //sets the data received 
      com.set_in(interface.in());
      //parse
      com.cmd_list();
      //set the parsed vector to the one for execute
	  shell.cmd_run = com.cmd_run;
	  //execute
	  shell.exec_main();
	  //clear the vector
	  com.wipe();
    }
  }

  return 0;
}




