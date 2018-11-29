//
//  ReadConfigure.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include "SearchProfile.h"
#include <iostream>

using namespace std;

int ReadProfile(string InputFile, std::vector<Configure> *ConfigureList, std::vector<SearchProfile> *ProfileList)
{
    string SearchKeyword[SearchProfileCount] = {"platformname","","filename","footprint","producttype","sensoroperationalmode","orbitdirection","","","polarisationmode","swathidentifier","cloudcoverpercentage","collection"};
    string *ProfileArr = readfile(InputFile);
    string ConfigureKeyword[SearchConfigureCount] = {"Download Path","Username","Password"};
    int LineDelayCount = LineDelay;
    int LineNumber = 0;
    //讀取程式參數
    for (int i = 0; i < SearchConfigureCount; i++)
    {
        Configure configure;
        LineNumber = (i * 3) + LineDelayCount;
        configure.set(ConfigureKeyword[i], ProfileArr[LineNumber]);
        ConfigureList -> push_back(configure);
    }
    LineDelayCount = LineNumber + 3;
    //讀取搜尋參數
    for (int i = 0; i < SearchProfileCount; i++)
    {
        SearchProfile Profile;
        LineNumber = (i * 3) + LineDelayCount;
        if(SearchKeyword[i] == "")
        {
            SearchKeyword[i] = ProfileArr[LineNumber];
            LineDelayCount = LineDelayCount + 3;
            LineNumber = (i * 3) + LineDelayCount;
        }
        if(SearchKeyword[i] == "beginposition" || SearchKeyword[i] == "endposition" || SearchKeyword[i] == "ingestiondate")
        {
            string StartTime = ProfileArr[LineNumber];
            LineDelayCount = LineDelayCount + 3;
            LineNumber = (i * 3) + LineDelayCount;
            string EndTime = ProfileArr[LineNumber];
            Profile.set(SearchKeyword[i], Profile.setTime(StartTime, EndTime));
        }
        else if(SearchKeyword[i] == "footprint")
        {
            while (ProfileArr[LineNumber] != "")
            {
                Profile.setCorrd(ProfileArr[LineNumber]);
                LineDelayCount++;
                LineNumber = (i * 3) + LineDelayCount;
            }
            LineDelayCount = LineDelayCount - 1;
            Profile.set(SearchKeyword[i], Profile.get_FootPrints());
        }
        else
        {
            Profile.set(SearchKeyword[i], ProfileArr[LineNumber]);
        }
        ProfileList -> push_back(Profile);
    }
    return 0;
}

