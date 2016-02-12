#include "execute.h"

int main()
{
  RSHELL interface;
  COMMAND com;
  EXECUTE shell;
	
  while(interface.exit_r == false)
  {
    interface.print();
    interface.get_input();
    if(interface.exit_r == true)break;
    else
    {
      com.set_in(interface.in());
      com.cmd_list();
	  shell.cmd_run = com.cmd_run;
	  shell.exec_main();
	  com.wipe();
    }
  }

  return 0;
}




