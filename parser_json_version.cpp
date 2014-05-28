#include "normJSON.h"

using namespace std;

int main(int argc, char* argv[])
{	
	//	Data exchange through MongoDB and JSON, and transmitting is through stdin/stdout
	NormJSON Norm;
	if	(strcmp(argv[argc - 1], "-i") == 0)	{
		//	The first time run this parser process
		Norm.PushReqInfoInJSON(1);
	}	else	{
		//	Not the first time run this parser process
		Norm.ResovleReqInfoFromJSONFile();
	}	
}