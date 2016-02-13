#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <string.h>
#include <vector>
#include <string>

using namespace std;

//Rshell Class
/*
	Class is responsible for printing interface
	as well as taking input from the user. Will
	print out user and hostname name and will manage 
	the exit of the program.
*/
class RSHELL {
  protected:
	string input;
	//hostname chosen is 255 characters which is the 
	//limit for hostname length in unix.
	char hostname[255];
	char *user;
  
  public:
	//variable used in checking whether user typed in exit.
 	bool exit_r;
	RSHELL(){exit_r = false;}
	//grabs user input and stores it in a string.
	void get_input()
	{
		getline(cin, input);
		if(input == "exit")
		{
		  exit_r = true;
		}
	}
	//grabs username and hostname and prints interface to terminal
	void print()
	{
	  struct passwd *p;
	  p = getpwuid(getuid());
	  user = p->pw_name;
	  gethostname(hostname, 255);
	  cout << user << "@"<< hostname << "$";
	}
	//returns current input string
        string in(){return input;}
	//allows you to manually set input string
	void set_in(string tmp){input = tmp;}
};

