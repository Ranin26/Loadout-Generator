// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "queryItems.h"
void queryItems(Pool &pool) {
    //setlocale(LC_ALL, "en_US.utf8");
    size_t size = 0;
    const LPCTSTR client = L"testing123";
    const LPCWSTR domain = L"www.pathofexile.com";

    string hey = "hey";

    char* leaguesJson = NULL;
    jsonRequest(leaguesJson, client, domain, L"/api/trade/data/leagues", L"GET");

    wchar_t* url = NULL;
    getTradeUrl(leaguesJson, url);

    char* chestResJson = NULL;
    tradeQuery(chestResJson, url, pool);
    cout << "hello\n";
}

void jsonRequest(char*& oldOutBuffer, LPCTSTR client, LPCWSTR host, LPCWSTR url, LPCWSTR method, LPCWSTR additionalHeaders, DWORD headersLength, LPSTR pszData, DWORD pszLength)
{
    DWORD dwSize = 0, dwDownloaded = 0, totalDownloaded = 0; //dwBytesWritten = 0;
    HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;
    char* pszOutBuffer = NULL, *temp = NULL;
    BOOL  bResults = FALSE;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(client,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTPS_PORT, 0);

    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, method, url, NULL, 
            WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest, additionalHeaders, headersLength,
            pszData, pszLength, pszLength, 0);

    /* if (bResults)
        bResults = WinHttpWriteData(hRequest, pszData, (DWORD)strlen(pszData), &dwBytesWritten);*/

    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Keep checking for data until there is nothing left.
    if (bResults)
    {
        do
        {
            cout << "hi111\n";
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
            // Allocate space for the buffer.
            temp = pszOutBuffer;
            pszOutBuffer = new char[dwSize + 1];
            // Free the memory allocated to the buffer.
            delete[] temp;
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if(!WinHttpReadData(hRequest, (LPVOID)(pszOutBuffer), dwSize, &dwDownloaded))
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                  //  printf("%s", pszOutBuffer);
                if(dwSize > 0)
                {
                    if(totalDownloaded > 0)
                        temp = oldOutBuffer;
                    oldOutBuffer = new char[totalDownloaded + dwSize + 1];
                    ZeroMemory(oldOutBuffer, totalDownloaded + dwSize + 1);
                    if(totalDownloaded > 0)
                        strncpy_s(oldOutBuffer, totalDownloaded + dwSize + 1, temp, totalDownloaded + 1);
                    // Free the memory allocated to the buffer.
                    delete[] temp;
                    strcat_s(oldOutBuffer, totalDownloaded + dwSize + 1, pszOutBuffer);
                }
                totalDownloaded += dwDownloaded;
            }
        } while (dwSize > 0);
    }

    // Report any errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    cout << "hi112\n";
}

void getTradeUrl(char *&leaguesJson, wchar_t *&url)
{
    //1. Get document of league json
    Document doc;
    doc.Parse(leaguesJson);

    // 2. Extract the league
    Value& leagueVal = doc["result"][1]["text"];
    size_t size = leagueVal.GetStringLength() + 1;
    wchar_t* league = new wchar_t[size]; //leaguee;
    mbstowcs(league, leagueVal.GetString(), size);

    // 3. Make the url
    url = new wchar_t[18 + size];
    wcscpy(url, L"/api/trade/search/");
    wcscat(url, league);

    delete[] league;
}

void convertCurrency(string currency, float &price)
{
}

void getFetchUrl(wchar_t*& url)
{

}

void tradeQuery(char *&ResJson, wchar_t *&url, Pool& pool)
{
    wchar_t** keys = NULL;
    LPSTR helmetQuery, glovesQuery, chestQuery, bootsQuery, ring1Query, ring2Query, beltQuery, amuletQuery;
    string qstr;

    searchQuery query;
    query.readRequirements();

    //cout << queryJson("chest", query.chestQuery).c_str() << endl;
    qstr = queryJson("chest", query.chestQuery);
    chestQuery = (LPSTR)qstr.c_str();
    cout << "here" << endl;
    cout << chestQuery << endl;

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, chestQuery, (DWORD)strlen(chestQuery));
    processQueryKeys(keys, ResJson, pool, "chest");

    //q.str(string());
   // q.clear();

    qstr = queryJson("helmet", query.helmetQuery);
    helmetQuery = (LPSTR)qstr.c_str();
    cout << "hur" << endl;
    cout << helmetQuery << endl;

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, helmetQuery, (DWORD)strlen(helmetQuery));
    processQueryKeys(keys, ResJson, pool, "helmet");

    qstr = queryJson("gloves", query.glovesQuery);
    glovesQuery = (LPSTR)qstr.c_str();

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, glovesQuery, (DWORD)strlen(glovesQuery));
    processQueryKeys(keys, ResJson, pool, "gloves");

    qstr = queryJson("boots", query.bootsQuery);
    bootsQuery = (LPSTR)qstr.c_str();

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, bootsQuery, (DWORD)strlen(bootsQuery));
    processQueryKeys(keys, ResJson, pool, "boots");

    qstr = queryJson("belt", query.beltQuery);
    beltQuery = (LPSTR)qstr.c_str();

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, beltQuery, (DWORD)strlen(beltQuery));
    processQueryKeys(keys, ResJson, pool, "belt");

    qstr = queryJson("ring1", query.ring1Query);
    ring1Query = (LPSTR)qstr.c_str();

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, ring1Query, (DWORD)strlen(ring1Query));
    processQueryKeys(keys, ResJson, pool, "ring1");

    qstr = queryJson("ring2", query.ring2Query);
    ring2Query = (LPSTR)qstr.c_str();

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, ring2Query, (DWORD)strlen(ring2Query));
    processQueryKeys(keys, ResJson, pool, "ring2");

    qstr = queryJson("amulet", query.amuletQuery);
    amuletQuery = (LPSTR)qstr.c_str();
    
    cout << "amulet query" << amuletQuery << endl;

    jsonRequest(ResJson, L"testing123", L"www.pathofexile.com", url, L"POST", L"Content-Type: application/json\n", -1, amuletQuery, (DWORD)strlen(amuletQuery));
    processQueryKeys(keys, ResJson, pool, "amulet");
}

void processTradeResults(wchar_t **&keys, const char* id, int j, Pool& pool, string type)
{
    char* resultsJson;
    size_t size = strlen(id) + 1;
    wchar_t *temp = new wchar_t[size],
            *url = NULL;
    mbstowcs(temp, id, size);
    SizeType i;
    int c = 0, k, hp, armor, fRes, cRes, eRes, chRes;
    string ID;
    float cost;
    int l = 0;
    for (c = 0; c <= j; c++)
    {
        cout << "hi3\n";
        if (c > 0 && c % 2 == 0)
            sleep_for(seconds(WAIT_TIME));
        Document doc;
        cout << "\n===========================================================================\n" << "\n";
        url = new wchar_t[17 + wcslen(keys[c]) + size + 7 + 317];
        wcscpy(url, L"/api/trade/fetch/");
        wcscat(url, keys[c]);
        wcscat(url, L"?query=");
        wcscat(url, temp);
        wcscat(url, L"&pseudos[]=pseudo.pseudo_total_elemental_resistance&pseudos[]=pseudo.pseudo_total_life&pseudos[]=pseudo.pseudo_total_cold_resistance&pseudos[]=pseudo.pseudo_total_fire_resistance&pseudos[]=pseudo.pseudo_total_lightning_resistance&pseudos[]=pseudo.pseudo_total_chaos_resistance&pseudos[]=pseudo.pseudo_total_resistance");
        wcout << "\n" << c << " Url: " << url << endl;
        jsonRequest(resultsJson, L"testing123", L"www.pathofexile.com", url, L"GET");
        doc.Parse(resultsJson);
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        cout << buffer.GetString() << "\n";
        for (k = 0; k < MAX_RESULTS && k < doc["result"].Size(); k++)
        {
            cout << "hi4\n";
            hp = 0;
            cost = 0;
            armor = 0;
            fRes = 0;
            cRes = 0;
            eRes = 0;
            chRes = 0;
            ID = doc["result"][k]["id"].GetString();
            if (!doc["result"][k]["listing"]["price"].IsNull())
            {
                Value& price = doc["result"][k]["listing"]["price"]["amount"];
                cost = price.GetFloat();
                if (doc["result"][k]["listing"]["price"]["currency"].GetString() != "chaos")
                    convertCurrency(doc["result"][k]["listing"]["price"]["currency"].GetString(), cost);
            }
            Value& name = doc["result"][k]["item"]["name"];
            if (doc["result"][k]["item"].HasMember("properties"))//[0]["values"][0][0];//if == armour
            {
                Value& propertiesArr = doc["result"][k]["item"]["properties"];
                for (i = 0; i < propertiesArr.Size(); i++)
                {
                    cout << "hi5\n";
                    string str = propertiesArr[i]["name"].GetString();
                    if (str == "Armour")
                    {
                        stringstream armVal(propertiesArr[i]["values"][0][0].GetString());
                        armVal >> armor;
                        break;
                    }
                }
            }
            //assert(doc3["result"][k]["item"].HasMember("explicitMods"));
            //Value& exModsArr = doc3["result"][k]["item"]["explicitMods"];
            assert(doc["result"][k]["item"].HasMember("pseudoMods"));
            if (doc["result"][k]["item"].HasMember("pseudoMods"))
            {
                Value& psModsArr = doc["result"][k]["item"]["pseudoMods"];
                // +81 total maximum Life", "(pseudo) +77% total Elemental Resistance"] }
                assert(psModsArr.IsArray());
                assert(!psModsArr.Empty());
                for (i = 0; i < psModsArr.Size(); i++)
                {
                    cout << "hi6\n";
                    string mod = psModsArr[i].GetString();
                    if (!hp && mod.find("total maximum Life", 10) < mod.capacity())
                    {
                        stringstream geek(mod.substr(10, 3));
                        geek >> hp;
                        continue;
                    }
                    else if (!fRes && mod.find("total to Fire Resistance", 10) < mod.capacity())
                    {
                        stringstream geek(mod.substr(10, 2));
                        geek >> fRes;
                        continue;
                    }
                    else if (!cRes && mod.find("total to Cold Resistance", 10) < mod.capacity())
                    {
                        stringstream geek(mod.substr(10, 2));
                        geek >> cRes;
                        continue;
                    }
                    else if (!eRes && mod.find("total to Lightning Resistance", 10) < mod.capacity())
                    {
                        stringstream geek(mod.substr(10, 2));
                        geek >> eRes;
                        continue;
                    }
                    else if (!chRes && mod.find("total to Chaos Resistance", 10) < mod.capacity())
                    {
                        stringstream geek(mod.substr(10, 2));
                        geek >> chRes;
                        continue;
                    }
                }
            }
            cout << "hi 6.1" << "\n";
            if (type == "chest") {
                Armor tempChest;
                tempChest.setName(name.GetString());
                tempChest.setId(ID);
                tempChest.setHp(hp);
                tempChest.setArmor(armor);
                tempChest.seteRes(eRes);
                tempChest.setcRes(cRes);
                tempChest.setfRes(fRes);
                tempChest.setchRes(chRes);
                tempChest.setCost(cost);
                tempChest.calcRating();
                pool.addItem<Armor>(pool, type, l, tempChest);
            } else if (type == "gloves") {
                Armor tempGloves;
                tempGloves.setName(name.GetString());
                tempGloves.setId(ID);
                tempGloves.setHp(hp);
                tempGloves.setArmor(armor);
                tempGloves.seteRes(eRes);
                tempGloves.setcRes(cRes);
                tempGloves.setfRes(fRes);
                tempGloves.setchRes(chRes);
                tempGloves.setCost(cost);
                tempGloves.calcRating();
                pool.addItem<Armor>(pool, type, l, tempGloves);
            } else if (type == "boots") {
                Armor tempBoots;
                tempBoots.setName(name.GetString());
                tempBoots.setId(ID);
                tempBoots.setHp(hp);
                tempBoots.setArmor(armor);
                tempBoots.seteRes(eRes);
                tempBoots.setcRes(cRes);
                tempBoots.setfRes(fRes);
                tempBoots.setchRes(chRes);
                tempBoots.setCost(cost);
                tempBoots.calcRating();
                pool.addItem<Armor>(pool, type, l, tempBoots);
            } else if (type == "helmet") {
                Armor tempHelmet;
                tempHelmet.setName(name.GetString());
                tempHelmet.setId(ID);
                tempHelmet.setHp(hp);
                tempHelmet.setArmor(armor);
                tempHelmet.seteRes(eRes);
                tempHelmet.setcRes(cRes);
                tempHelmet.setfRes(fRes);
                tempHelmet.setchRes(chRes);
                tempHelmet.setCost(cost);
                tempHelmet.calcRating();
                pool.addItem<Armor>(pool, type, l, tempHelmet);
            } else if (type == "amulet") {
                Jewlry tempAmulet;
                tempAmulet.setName(name.GetString());
                tempAmulet.setId(ID);
                tempAmulet.setHp(hp);
                tempAmulet.setArmor(armor);
                tempAmulet.seteRes(eRes);
                tempAmulet.setcRes(cRes);
                tempAmulet.setfRes(fRes);
                tempAmulet.setchRes(chRes);
                tempAmulet.setCost(cost);
                tempAmulet.calcRating();
                pool.addItem<Jewlry>(pool, type, l, tempAmulet);
            } else if (type == "ring1") {
                Jewlry tempRing1;
                tempRing1.setName(name.GetString());
                tempRing1.setId(ID);
                tempRing1.setHp(hp);
                tempRing1.setArmor(armor);
                tempRing1.seteRes(eRes);
                tempRing1.setcRes(cRes);
                tempRing1.setfRes(fRes);
                tempRing1.setchRes(chRes);
                tempRing1.setCost(cost);
                tempRing1.calcRating();
                pool.addItem<Jewlry>(pool, type, l, tempRing1);
            } else if (type == "ring2") {
                Jewlry tempRing2;
                tempRing2.setName(name.GetString());
                tempRing2.setId(ID);
                tempRing2.setHp(hp);
                tempRing2.setArmor(armor);
                tempRing2.seteRes(eRes);
                tempRing2.setcRes(cRes);
                tempRing2.setfRes(fRes);
                tempRing2.setchRes(chRes);
                tempRing2.setCost(cost);
                tempRing2.calcRating();
                pool.addItem<Jewlry>(pool, type, l, tempRing2);
            } else if (type == "belt") {
                cout << "hi belt" << "\n";
                Jewlry tempBelt;
                tempBelt.setName(name.GetString());
                tempBelt.setId(ID);
                tempBelt.setHp(hp);
                tempBelt.setArmor(armor);
                tempBelt.seteRes(eRes);
                tempBelt.setcRes(cRes);
                tempBelt.setfRes(fRes);
                tempBelt.setchRes(chRes);
                tempBelt.setCost(cost);
                tempBelt.calcRating();
                cout << "hi pre POOL" << "\n";
                pool.addItem<Jewlry>(pool, type, l, tempBelt);
                cout << "hi post POOL" << "\n";
            }
            cout << "hi 6.2" << "\n";
            cout << "Name :" << name.GetString() << "\n";
            cout << "Id :" << ID << "\n";
            cout << "Cost :" << cost << "\n";
            cout << "HP :" << hp << "\n";
            cout << "Armour :" << armor << "\n";
            cout << "Fire Res :" << fRes << "\n";
            cout << "Cold Res :" << cRes << "\n";
            cout << "Elec Res :" << eRes << "\n";
            cout << "Chaos Res :" << chRes << "\n\n";
            //Value& hp = doc3["result"][j]["item"]["explicitMods"][i];
            if (l < MAX - 1)
                l++;
        }
        delete[] resultsJson;
        //write3.~Writer();
        //buff3.~StringBuffer();
        doc.SetObject();
    }
    delete[] temp;


    // 2. Modify it by DOM.
   // Value& s = doc["result"][1]["text"];
  //  league = (wchar_t)s.GetString();
    // 3. Stringify the DOM

    // Output json

    delete[] url;
    for (c = 0; c < j; c++)
    {
        cout << "hi7\n";
        delete[] keys[c];
    }
    delete[] keys;
}

void processQueryKeys(wchar_t **&keys, char*& ResJson, Pool& pool, string type)
{
    cout << "hi26\n";
    wchar_t* temp = NULL;
    Document d;
    d.Parse(ResJson);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    cout << buffer.GetString() << "\n";
    Value& keysArr = d["result"];
    Value& id = d["id"];
    assert(keysArr.IsArray());
    assert(!keysArr.Empty());
    cout << "hi224\n";
    if (keysArr.Size() < 1)
    {
        cout << "No results for " << type << ". Try again.\n";
        exit(1);
    }
    size_t size = keysArr[0].GetStringLength() + 1;
    cout << "hi224.1\n";
    wchar_t ** temp2;
    keys = new wchar_t* [1];
    cout << "hi224.2\n";
    int j = 0, c;
    keys[0] = new wchar_t[size + 1];//1 for comma
    cout << "hi224.3\n";
    mbstowcs(keys[0], keysArr[0].GetString(), size);
    cout << "hi224.4\n";
    for (SizeType i = 1; i < keysArr.Size(); i++) // Uses SizeType instead of size_t
    {
        cout << "hi1\n";
        if (i % MAX_RESULTS == 0)
        {
            temp2 = keys;
            keys = new wchar_t* [++j + 1];
            for (c = 0; c < j; c++)
            {
                cout << "hi2\n";
                keys[c] = temp2[c];
            }
            delete[] temp2;
            keys[j] = NULL;
        }
        else {
            //cout << "Key: " << s.GetString() << endl;
            wcscat(keys[j], L",");
        }
        temp = keys[j];
        size = keysArr[i].GetStringLength() + 1;
        if (keys[j])
            keys[j] = new wchar_t[wcslen(keys[j]) + size + 1];//1 for comma
        else
        {
            keys[j] = new wchar_t[size + 1];//1 for comma
            wcscpy(keys[j], L"\0");
        }
        if (temp)
        {
            wcscpy(keys[j], temp);
            delete[] temp;
        }
        temp = new wchar_t[size];
        mbstowcs(temp, keysArr[i].GetString(), size);
        wcscat(keys[j], temp);
        delete[] temp;
    }
    // 3. Stringify the DOM
    //StringBuffer buffer;
    //Writer<StringBuffer> writer(buffer);
    //d.Accept(writer);
    //wcout << keys << "\n"; 
    // Output json
    //cout << buffer.GetString() << "\n";
    cout << "hi8\n";
    processTradeResults(keys, id.GetString(), j, pool, type);
    cout << "hi9\n";
}

void Query::setMinArmor(int min)
{
    minArmor = min;
}

void Query::setMinHP(int min)
{
    minHP = min;
}

void Query::setMinElecRes(int min)
{
    minElecRes = min;
}

void Query::setMinFireRes(int min)
{
    minFireRes = min;
}

void Query::setMinColdRes(int min)
{
    minColdRes = min;
}

void Query::setMinChaosRes(int min)
{
    minChaosRes = min;
}

void Query::setMinEleRes(int min)
{
    minEleRes = min;
}

void Query::setMinTotalRes(int min)
{
    minTotalRes = min;
}

void Query::setMaxPrice(float max)
{
    maxPrice = max;
}

int Query::getMinArmor()
{
    return minArmor;
}

int Query::getMinHP()
{
    return minHP;
}

int Query::getMinElecRes()
{
    return minElecRes;
}

int Query::getMinFireRes()
{
    return minFireRes;
}

int Query::getMinColdRes()
{
    return minColdRes;
}

int Query::getMinChaosRes()
{
    return minChaosRes;
}

int Query::getMinEleRes()
{ 
    return minEleRes;
}

int Query::getMinTotalRes()
{
    return minTotalRes;
}

float Query::getMaxPrice()
{
    return maxPrice;
}

void searchQuery::readRequirements()
{
    int minHP, minArmor, minElecRes, minFireRes, minColdRes, minChaosRes, minEleRes, minTotalRes;
    float maxPrice;
    ifstream fin;
    fin.open("query.txt");

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    helmetQuery.setMinHP(minHP);
    helmetQuery.setMinArmor(minArmor);
    helmetQuery.setMinElecRes(minElecRes);
    helmetQuery.setMinFireRes(minFireRes);
    helmetQuery.setMinColdRes(minColdRes);
    helmetQuery.setMinChaosRes(minChaosRes);
    helmetQuery.setMinEleRes(minEleRes);
    helmetQuery.setMinTotalRes(minTotalRes);
    helmetQuery.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    chestQuery.setMinHP(minHP);
    chestQuery.setMinArmor(minArmor);
    chestQuery.setMinElecRes(minElecRes);
    chestQuery.setMinFireRes(minFireRes);
    chestQuery.setMinColdRes(minColdRes);
    chestQuery.setMinChaosRes(minChaosRes);
    chestQuery.setMinEleRes(minEleRes);
    chestQuery.setMinTotalRes(minTotalRes);
    chestQuery.setMaxPrice(maxPrice);

    cout << minHP << endl << minArmor << endl << minElecRes << endl << minFireRes << endl << minColdRes << endl << minChaosRes << endl << minEleRes << endl << minTotalRes << endl << maxPrice;
    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    glovesQuery.setMinHP(minHP);
    glovesQuery.setMinArmor(minArmor);
    glovesQuery.setMinElecRes(minElecRes);
    glovesQuery.setMinFireRes(minFireRes);
    glovesQuery.setMinColdRes(minColdRes);
    glovesQuery.setMinChaosRes(minChaosRes);
    glovesQuery.setMinEleRes(minEleRes);
    glovesQuery.setMinTotalRes(minTotalRes);
    glovesQuery.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    bootsQuery.setMinHP(minHP);
    bootsQuery.setMinArmor(minArmor);
    bootsQuery.setMinElecRes(minElecRes);
    bootsQuery.setMinFireRes(minFireRes);
    bootsQuery.setMinColdRes(minColdRes);
    bootsQuery.setMinChaosRes(minChaosRes);
    bootsQuery.setMinEleRes(minEleRes);
    bootsQuery.setMinTotalRes(minTotalRes);
    bootsQuery.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    amuletQuery.setMinHP(minHP);
    amuletQuery.setMinArmor(minArmor);
    amuletQuery.setMinElecRes(minElecRes);
    amuletQuery.setMinFireRes(minFireRes);
    amuletQuery.setMinColdRes(minColdRes);
    amuletQuery.setMinChaosRes(minChaosRes);
    amuletQuery.setMinEleRes(minEleRes);
    amuletQuery.setMinTotalRes(minTotalRes);
    amuletQuery.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    ring1Query.setMinHP(minHP);
    ring1Query.setMinArmor(minArmor);
    ring1Query.setMinElecRes(minElecRes);
    ring1Query.setMinFireRes(minFireRes);
    ring1Query.setMinColdRes(minColdRes);
    ring1Query.setMinChaosRes(minChaosRes);
    ring1Query.setMinEleRes(minEleRes);
    ring1Query.setMinTotalRes(minTotalRes);
    ring1Query.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    ring2Query.setMinHP(minHP);
    ring2Query.setMinArmor(minArmor);
    ring2Query.setMinElecRes(minElecRes);
    ring2Query.setMinFireRes(minFireRes);
    ring2Query.setMinColdRes(minColdRes);
    ring2Query.setMinChaosRes(minChaosRes);
    ring2Query.setMinEleRes(minEleRes);
    ring2Query.setMinTotalRes(minTotalRes);
    ring2Query.setMaxPrice(maxPrice);

    fin >> minHP >> minArmor >> minElecRes >> minFireRes >> minColdRes >> minChaosRes >> minEleRes >> minTotalRes >> maxPrice;

    beltQuery.setMinHP(minHP);
    beltQuery.setMinArmor(minArmor);
    beltQuery.setMinElecRes(minElecRes);
    beltQuery.setMinFireRes(minFireRes);
    beltQuery.setMinColdRes(minColdRes);
    beltQuery.setMinChaosRes(minChaosRes);
    beltQuery.setMinEleRes(minEleRes);
    beltQuery.setMinTotalRes(minTotalRes);
    beltQuery.setMaxPrice(maxPrice);

    fin.close();
}

string queryJson(string type, Query& query)
{
    string category;
    if (type == "helmet") {
        category = "armour.helmet";
    } else if (type == "gloves") {
        category = "armour.gloves";
    } else if (type == "boots") {
        category = "armour.boots";
    } else if (type == "chest") {
        category = "armour.chest";
    } else if (type == "amulet") {
        category = "accessory.amulet";
    } else if (type == "belt") {
        category = "accessory.belt";
    } else if (type == "ring1") {
        category = "accessory.ring";
    } else if (type == "ring2") {
        category = "accessory.ring";
    }

    stringstream q;
    string qstr;
    q << "{"
            "\"query\":{"
                "\"status\":{"
                    "\"option\": \"online\""
                "},"
                "\"filters\":{"
                    "\"type_filters\":{"
                        "\"filters\":{"
                            "\"category\":{"
                                "\"option\":\"" << category <<"\""
                            "}"
                        "},"
                        "\"disabled\" : false"
                    "},"
                    "\"armour_filters\" :{"
                        "\"filters\":{"
                            "\"ar\":{"
                                "\"min\":" << query.getMinArmor() <<
                                ",\"max\" : null"
                            "}"
                        "},"
                        "\"disabled\" : false"
                    "}"
                "},"
                "\"stats\" : [{ "
                    "\"filters\" : [{"
                        "\"id\":\"pseudo.pseudo_total_elemental_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" : {"
                            "\"min\":" << query.getMinEleRes() <<
                        "}"
                    "},"
                    "{"
                        "\"id\":\"pseudo.pseudo_total_life\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinHP() <<
                        "}"
                    "},"
                    "{"
                        "\"id\":\"pseudo.pseudo_total_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinTotalRes() <<
                         "}"
                    "}],"
                    "\"disabled\" : false,"
                    "\"type\": \"and\""
                "},"
                "{"
                    "\"filters\" : [{"
                        "\"id\":\"pseudo.pseudo_total_cold_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinColdRes() <<
                        "}"
                    "},"
                    "{"
                        "\"id\":\"pseudo.pseudo_total_fire_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinFireRes() <<
                         "}"
                    "},"
                    "{"
                        "\"id\":\"pseudo.pseudo_total_lightning_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinElecRes() <<
                        "}"
                    "},"
                    "{"
                        "\"id\":\"pseudo.pseudo_total_chaos_resistance\","
                        "\"disabled\" : false,"
                        "\"value\" :{"
                            "\"min\":" << query.getMinChaosRes() <<
                        "}"
                    "}],"
                    "\"type\": \"count\","
                    "\"value\": {"
                        "\"min\":1"
                    "}"
                "}]"
            "},"
            "\"sort\": {"
                "\"price\": \"asc\""
            "}"
        "}";

    qstr = q.str();
    //cout << (LPSTR)qstr.c_str() << endl;
    return qstr.c_str();
}