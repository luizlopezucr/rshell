#include "execute.h"

int main()
{
  RSHELL interface;
  COMMAND com;
  EXECUTE shell;
	
  //until the user enters exit keep prompting for commands
  while(interface.exit_r == false && shell.ext() == false)
  {
    
    //prints the extra credit
    interface.print();
    //receives the line input
    interface.get_input();
    //if the input is exit it exits the loop
    
    if(interface.exit_r == true || shell.ext() == true)break;
    else
    {
      //reset input_err
      //sets the data received 
      com.set_in(interface.in());
      
      //parse
      com.cmd_list();
      
      if(!com.input_err)
      {
		//set the parsed vector to the one for execute
		shell.cmd_run = com.cmd_run;
		//execute
		unsigned init = 0;
		unsigned& ref = init;
		shell.exec_main(0, ref);
		//clear the vector
		com.wipe();
      }
      else
      {
      		  //wipe user input since it was invalid
      		  com.wipe();
      		  //reset the error
		      com.input_err = false;
	  }

    }
  }

  return 0;
}




