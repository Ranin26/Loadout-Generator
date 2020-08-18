#ifndef QUERYITEMS_H
#define QUERYITEMS_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <windows.h> //include order matters
#include <winhttp.h>
//#include <tchar.h>
#include <objbase.h>
#include <comutil.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream> 
#include <fstream>
#include "loadout.h"
//#include <string>

#pragma comment(lib, "Winhttp")

using namespace std;
using namespace rapidjson;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

const int MAX_RESULTS = 6;
const int WAIT_TIME = 6;

class Query
{
public:
	void setMinArmor(int min);
	void setMinHP(int min);
	void setMinElecRes(int min);
	void setMinFireRes(int min);
	void setMinColdRes(int min);
	void setMinChaosRes(int min);
	void setMinEleRes(int min);
	void setMinTotalRes(int min);
	void setMaxPrice(float max);
	int getMinArmor();
	int getMinHP();
	int getMinElecRes();
	int getMinFireRes();
	int getMinColdRes();
	int getMinChaosRes();
	int getMinEleRes();
	int getMinTotalRes();
	float getMaxPrice();
private:
	int minArmor;
	int minHP;
	int minElecRes;
	int minFireRes;
	int minColdRes;
	int minChaosRes;
	int minEleRes;
	int minTotalRes;
	float maxPrice;
};

class searchQuery
{
public:
	Query helmetQuery;
	Query glovesQuery;
	Query bootsQuery;
	Query chestQuery;
	Query amuletQuery;
	Query ring1Query;
	Query ring2Query;
	Query beltQuery;
	void readRequirements();
private:
};

void queryItems(Pool &pool);
void jsonRequest(char*& oldOutBuffer, LPCTSTR client, LPCWSTR host, LPCWSTR url, LPCWSTR method, LPCWSTR additionalHeaders = WINHTTP_NO_ADDITIONAL_HEADERS, DWORD headersLength = 0, LPSTR pszData = WINHTTP_NO_REQUEST_DATA, DWORD pszLength = 0);
void convertCurrency(string currency, float& price);
void getTradeUrl(char*& leaguesJson, wchar_t*& url);
void getFetchUrl(wchar_t*& url);
string queryJson(string type, Query &query);
void tradeQuery(char*& ResJson, wchar_t*& url, Pool& pool);
void processQueryKeys(wchar_t**& keys, char*& ResJson, Pool& pool, string type);
void processTradeResults(wchar_t**& keys, const char* id, int j, Pool& pool, string type);
#endif
