#ifndef NormJSON_H
#define NormJSON_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <ctime>

#include "gumbo.h"
#include "json/json.h"

using namespace std;

class NormJSON	{
private:
	void InitStd();
	int TransformJsonData(Json::Value _elem, string &_des, char _type);
	int GetRequestInfo(string &_reqInfo, char _opt);
  
	Json::Value JsonMsgParser(string &_rawInfo, char _opt);
	string rawReqInfo;
	int lengthOfRawData;
	vector<string> links;
public:
	NormJSON();
	~NormJSON()	{};
  
	void ResovleReqInfoFromJSONFile();
	void PushReqInfoInJSON(int state);
	void TempWriteBody(string _body);
	void LinksStorer(vector<string> _link);
	int ReadDataToString(string &_rawInfo);
	int ReadDataToString(string &_rawInfo, string _filePath);
	
	/*
	string SetRawInfo(string _rawReqInfo)	{ rawReqInfo = _rawReqInfo;}
	int SetLengthOfRawData(int _lengthOfRawData)	{ lengthOfRawData = _lengthOfRawData;}
	string GetRawInfo()	{ return rawReqInfo;}
	int GetLengthOfRawData()	{ return lengthOfRawData;}
	*/
};
#endif  // ifndef NormJSON_H //
  
  