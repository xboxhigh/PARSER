#include <fstream>

#include "json/json.h"
#include "normXML.h"


using namespace std;

int main(int argc, char* argv[])
{
	if	(argc < 2)	{
		cout << "No parameter set, please set.\n"
			<<	argv[0] << " <Data Transmit Type> <Init> <Whether Input File> [File Path]\n" ;				
		return 1;
	}	else	{
		//cout << argv[argc-1] << endl;
		NormXML XML(argv[argc-1]);
		cout << "Constructor sucess !" << endl;
		XML.ResovleReqInfoFromXMLFile();
	}
	
}