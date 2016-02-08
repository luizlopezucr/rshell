
#include "command.h"

int main()
{
  RSHELL interface;
  COMMAND com;
	
  while(interface.exit_r == false)
  {
    interface.print();
    interface.get_input();
    if(interface.exit_r == true)break;
    else
    {
      com.set_in(interface.in());
      com.cmd_list();
    }
  }

  return 0;
}




