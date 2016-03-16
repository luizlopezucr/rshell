#include <iostream>
#include <sys/stat.h>

using namespace std;


bool test_funct(string dir, string flag)
{
	//variable we return
	bool test_r = false;

	/*when calling stat it will store additional info
	**on file or Directory*/
	struct stat f_stats;

	if(flag == "-e")
	{
		//returns true if file or directory is exist
		test_r = ( stat(dir.c_str(), &f_stats) == 0);
	}
	 	
	
	if(flag == "-d")
	{
		//returns true if file or directory is exist
		test_r = ( stat(dir.c_str(), &f_stats) == 0);

		/*after we verify file or directory exist,
		**check if it is a directory*/
		if(test_r)
		{
			if(S_ISDIR(f_stats.st_mode))test_r = true;
			else test_r = false;
		}
	}

	if(flag == "-f")
	{	
		//returns true if file or directory is exist
		test_r = ( stat(dir.c_str(), &f_stats) == 0);

		/*after we verify file or directory exist,
		**check if it is a regular file*/
		if(test_r)
		{
			if(S_IFREG & f_stats.st_mode)test_r = true;
			else test_r = false;
		}
	}
	//Output to Terminal if True or false.
	if(test_r == true)cout << "(True)" << endl;
	else cout << "(False)" << endl;

	return test_r;
}

