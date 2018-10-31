//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/3.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include <iostream>

using namespace std;

int Search(std::vector<Configure> *ConfigureList, std::vector<SearchProfile> *ProfileList)
{
    string SearchRoot="https://scihub.copernicus.eu/dhus/search?";
    string SearchStart = "start=0";
    string SearchRows = "rows=100";
    string SearchQ = "q=*";
    string SearchAnd = " AND ";
    string DownloadPath = "Download Path";
    string Username = "Username";
    string Password = "Password";
    string OpenSearch = SearchRoot + SearchStart + "&" + SearchRows + "&" + SearchQ;
    
    vector<Configure>::iterator configure;
    for (configure = ConfigureList -> begin(); configure != ConfigureList -> end(); ++configure)
    {
        DownloadPath=configure->getValue(DownloadPath);
        Username=configure->getValue(Username);
        Password=configure->getValue(Password);
    }
    
    vector<SearchProfile>::iterator profile;
    for (profile = ProfileList -> begin(); profile != ProfileList -> end(); ++profile)
    {
        if (! profile -> isNull())
        {
            OpenSearch = OpenSearch + SearchAnd + profile -> SearchSyntax();
        }
    }
    string cmd = "wget --no-check-certificate --user=" + Username + " --password=" + Password + " --output-document=" + SearchResultFile + " \"" + OpenSearch + "\"";
    system(cmd.c_str());
    return 0;
}
