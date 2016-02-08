#include <iostream>
#include "rshell.h"

using namespace std;



int main()
{
  RSHELL interface;
	
  while(interface.exit_r == false)
  {
    interface.print();
    interface.get_input();
  }

  return 0;
}




