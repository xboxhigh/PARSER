#include "normXML.h"
/*-------------------------*/
////  Static Functions   ////
/*-------------------------*/

static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

static void search_for_links(GumboNode* node, vector<string> &_links) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  //cout << node->v.element.tag;
  if (node->v.element.tag == GUMBO_TAG_A &&
     (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    //std::cout << href->value << std::endl;
	_links.push_back(href->value);
	
  }
  GumboVector* children = &node->v.element.children;
  for (int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]), _links);
  }
}


/*-------------------------*/
////	NormXML Class	 ////
/*-------------------------*/

// NormXML constructor
NormXML::NormXML(string _filePath)	{
	cout << filePath << endl;
		InitFile(_filePath);
}

void NormXML::InitFile(string _filePath)	{

	rawReqInfo = "";  
	filePath = _filePath;
	lengthOfRawData = 0;
	links.clear();
}

int NormXML::ReadDataToString(string &_rawInfo, string _filePath)	{	
	
	int len = 0;
	char buffer [1024];
	FILE* fileStr;	
	
	//	Get Request Info from file		
	fileStr = fopen(_filePath.c_str(), "rb");
	
	if	(fileStr == NULL)	{	
		string _buff = "No such file path. [" + _filePath + "]\n";
		
		fputs(_buff.c_str(), stderr);
		return 1;
	}
		
	while (len = fread(buffer, 1, 1024, fileStr))	{			
		_rawInfo.append(buffer, len);
		if(feof(fileStr))	{
			break;
		}
	}
	fclose(fileStr);
	
	return len;
}

void NormXML::ResovleReqInfoFromXMLFile()	{
	string crawl_result_body = "";
	ReadDataToString(crawl_result_body, filePath);
	
	cout << crawl_result_body;
	
	GumboOutput* output = gumbo_parse(crawl_result_body.c_str());
	search_for_links(output->root, links);
	PushReqInfoInXML(2);
}

int NormXML::IdentifyURLEffectiveness(string _url)	{

	cout << "II" << endl;
	char extract[6];
	
	if	(_url.length() < 4)	{
		//cout << "URL length is too short\n";
		return 1;
	}
	
	memcpy(extract, _url.c_str(), 5);
	memcpy(&extract[5], "\0", 1);
	
	if	(strncmp(extract, "http", 4) == 0 || strncmp(extract, "https", 5) == 0)	{
		//cout << "URL type is right\n";
		return 0;
	}
	
	return 1;
}

void NormXML::WriteLinksToXML(vector<string> _url)	{
	
}

void NormXML::PushReqInfoInXML(int state)	{

	switch (state)	{
	case 1:	{		
	break;
	}
	case 2:	{
		for (vector<string>::iterator url = links.begin() ;url != links.end(); ++url)	{
			cout << *url << endl;
		}
	break;
	}
	default:	{
	
	}
	break;
	}
	
}

