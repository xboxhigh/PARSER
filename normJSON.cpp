#include "normJSON.h"
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
////	NormJSON Class	 ////
/*-------------------------*/

// NormJSON constructor
NormJSON::NormJSON()	{
		InitStd();
}

void NormJSON::InitStd()	{
	rawReqInfo = "";
	lengthOfRawData = ReadDataToString(rawReqInfo);	//Get Request Info from stdin
	links.clear();
}

void NormJSON::LinksStorer(vector<string> _link)	{
	FILE* LinkFile;
	string fileName = currentDateTime() + "_Links";	
	LinkFile = fopen (fileName.c_str(), "w+");
	
	for (vector<string>::iterator it = _link.begin() ;it != _link.end(); ++it)	{		
		//std::cout << ' ' << *it;		
		fputs(&*it->c_str(), LinkFile);
		fputs("\n", LinkFile);
	}
	
	fclose(LinkFile);
}

void NormJSON::TempWriteBody(string _body)	{
	FILE* BODYFILE;
	
	BODYFILE = fopen ("Body.json", "w+");
	fputs(_body.c_str(), BODYFILE);
	fclose(BODYFILE);
}

int NormJSON::ReadDataToString(string &_rawInfo)	{	
	
	int len = 0;
	char buffer [1024];
	
	//	Get Request Info from stdin		
	while (len = fread(buffer, 1, 1024, stdin))	{			
		_rawInfo.append(buffer, len);
		if(feof(stdin))	{
			break;
		}
	}
	return len;
}

int NormJSON::ReadDataToString(string &_rawInfo, string _filePath)	{	
	
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

Json::Value NormJSON::JsonMsgParser(string &_rawInfo, char _opt)	{

	Json::Reader reader;
	Json::Value jsonInfo(Json::objectValue);

	switch(_opt)	{
	case 's':	{	//Parse simple Json infomation
				
		Json::Reader reader;
		Json::Value jsonInfo(Json::objectValue);
		jsonInfo.clear();
		
		bool parsingSuccessful = false;
		
		parsingSuccessful = reader.parse(_rawInfo, jsonInfo, true);
		
		if (!parsingSuccessful)	{		//JSON format info parse error
			fputs(reader.getFormatedErrorMessages().c_str(), stderr);
			jsonInfo.clear();
		}
		
		return jsonInfo;
	}
	break;
	case 'c':
	break;
	default:
	break;
	}
}

int NormJSON::GetRequestInfo(string &_reqInfo, char _opt)	{		

	Json::FastWriter fast_writer;
	Json::Value jobList(Json::objectValue);
	jobList.clear();
	
	switch(_opt)	{
	case 'i':	{		//Parse the "parser_id" info
		jobList = JsonMsgParser(rawReqInfo, 's');
		if (!jobList.empty())
			TransformJsonData(jobList["parser_id"], _reqInfo, 's');
	break;
	}
	case 'c':	{		//Parse the "crawler_result" info
		jobList = JsonMsgParser(rawReqInfo, 's');
		int statusCode = jobList["crawl_result"]["response"]["statusCode"].asInt();
			
		if((statusCode / 100) == 4 || (statusCode / 100) == 5)	{
			break;
		}		else	{
			if (!jobList.empty())
				TransformJsonData(jobList["crawl_result"]["body"], _reqInfo, 's');	
		}
	break;
	}
	case 'p':	{		//Parse the "prepare_info" info
		jobList = JsonMsgParser(rawReqInfo, 's');
		if (!jobList.empty())
			TransformJsonData(jobList["preparse_info"]["package_info"], _reqInfo, 'o');
	break;
	}
	default:
	break;
	}
	
	
}

int NormJSON::TransformJsonData(Json::Value _elem, string &_des, char _type)	{
	
	switch(_type)	{
	case 's':		//Input tpye is string
		_des.append(_elem.asString());
	break;
	case 'c':		//Input tpye is array
		if(_elem.size() != 0)	{		
			for(int index=0; index < _elem.size(); ++index)	{
				_des.append(_elem[index].asString());
			}
		}
		else	{
			_des.append(_elem.toStyledString());
		}
	break;
	case 'o':		//Input tpye is object
		if(_elem.size() != 0)	{		
			for(int index=0; index < _elem.size(); ++index)	{
				_des.append(_elem[index].asString());
			}
		}
		else	{
			_des.append(_elem.toStyledString());
		}
	break;
	}
	
	
	return 0;
}

void NormJSON::ResovleReqInfoFromJSONFile()	{	
	
	string parser_id = "", crawl_result_body = "", package_info = "";	

	GetRequestInfo(parser_id, 'i');			//Get Parser ID
	//cout << "Parser ID : " << parser_id << endl;	
	GetRequestInfo(crawl_result_body, 'c');		//Get Crawl Result
	//cout << "Crawl Result : " << crawl_result_body << endl;
	GetRequestInfo(package_info, 'p');		//Get Package Info		
	//cout << "Package Info : " << package_info  << endl;
	
	
	GumboOutput* output = gumbo_parse(crawl_result_body.c_str());
	search_for_links(output->root, links);
	PushReqInfoInJSON(2);
	
	//LinksStorer(links);
	
	/*
	FILE* kFile;
	kFile = fopen ("RawInfo.json", "w+");
	fputs(rawReqInfo.c_str(), kFile);
	fclose(kFile);
	
	FILE* jFile;
	jFile = fopen ("ReqInfo.json", "w+");
	fputs("Parser ID : ", jFile);
	fputs(parser_id.c_str(), jFile);
	fputs("\n", jFile);
	fputs("Crawl Result : ", jFile);
	fputs(crawl_result_body.c_str(), jFile);
	fputs("\n", jFile);
	fputs("Package Info : ", jFile);
	fputs(package_info.c_str(), jFile);
	fputs("\n", jFile);		
	fclose(jFile);
	*/
}

void NormJSON::PushReqInfoInJSON(int state)	{

	Json::FastWriter fast_writer;
	
	Json::Value emptyObj(Json::objectValue);
	Json::Value emptyArray(Json::arrayValue);
	Json::Value jobList(Json::objectValue);
	Json::Value finalJobList(Json::arrayValue);
		
	emptyObj.clear();
	jobList.clear();
	finalJobList.clear();
	emptyArray.append(Json::Value::null);
	emptyArray.clear();
	
	switch(state)	{
	case 1:	{		
		string seeds[10] = {"http://www.google.com/", "http://tw.yahoo.com/", "http://www.facebook.com/", 
						"http://docs.mongodb.org/", "http://nodejs.org/", "http://schorsch.efi.fh-nuernberg.de/",
						"http://www.iciba.com/backed", "http://docs.aws.amazon.com/", "https://plus.google.com/", 
						"http://www.bbc.co.uk/news/"};
						
		for(int i = 0; i < 10; i++)	{
			jobList["req_info"]["url"] = seeds[i];
			jobList["max_retry"] = 4;
			jobList["preparse_info"]["cmd"] = "./req";
			jobList["preparse_info"]["cmd_opts"] = emptyArray;
			jobList["preparse_info"]["env"] = emptyObj;
			jobList["preparse_info"]["package_info"] = emptyObj;
			finalJobList.append(jobList);
		}
		cout << fast_writer.write(finalJobList);
		//fputs(fast_writer.write(finalJobList), stdout);
	break;
	}
	case 2:	{
		for (vector<string>::iterator url = links.begin() ;url != links.end(); ++url)	{
			//std::cout << ' ' << *url;		
			jobList["req_info"]["url"] = *url;
			jobList["max_retry"] = 2;
			jobList["preparse_info"]["cmd"] = "./req";
			jobList["preparse_info"]["cmd_opts"] = emptyArray;
			jobList["preparse_info"]["env"] = emptyObj;
			jobList["preparse_info"]["package_info"] = emptyObj;
			finalJobList.append(jobList);
		}
		cout << fast_writer.write(finalJobList);
	}
	break;
	case 0:
	break;
	default:
		cout << "State error" << endl;
	break;
	}
}

