
/*
*<summary>
* info
*</summary>
*/

#include "kernel.h"
int main(int argv, char** argc)
{
	kernel w;
	
	if (w.Construct(1260, 720, 1, 1, false))
	{
		w.Start();
	}

	return 0;
}