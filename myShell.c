#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	string command;
	cout << "\tShan system shell\n\n";

	while (command != "exit")
	{
		if (command == "ls")
			system("ls");
		else if (command == "vim")
			system("vim");
		else if (command=="date")
			system("date");
		else if (command == "help")
			cout <<"ls\tdate\thelp\texit\n"
		cout <<"ls\tdate\thelp\texit\n"
		cout <<"ls\tdate\thelp\texit\n"
	}
}