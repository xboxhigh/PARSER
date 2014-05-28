#ifndef NormXML_H
#define NormXML_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <ctime>

#include "gumbo.h"
#include "json/json.h"

using namespace std;

class NormXML{
private:	
	void InitFile(string _filePath);
  
	string rawReqInfo;  
	string filePath;
	int lengthOfRawData;
	vector<string> links;
public:
	NormXML();	
	NormXML(string _filePath);	
	~NormXML()	{};
	
	int IdentifyURLEffectiveness(string _url);
	int ReadDataToString(string &_rawInfo, string _filePath);
	void WriteLinksToXML(vector<string> _url);
	void ResovleReqInfoFromXMLFile();
	void PushReqInfoInXML(int state);
	
	string SetFilePath(string _filePath)	{ filePath = _filePath;}
	vector<string> SetLinks(vector<string> _links)	{ links = _links;}
	
	vector<string> GetLinks()	{ return links;}
	string GetFilePath()	{ return filePath;}
};
#endif  // #ifndef NormJASON_H //