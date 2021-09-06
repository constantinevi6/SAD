//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include "SearchProfile.h"
#include "Product.h"
#include "download.hpp"
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    filesystem::path InputFile;
    //說明與輸入判斷
    if (argc == 2)
    {
        cout << endl;
        cout << "Sentinel Auto Downloader" << endl;
        cout << "Copyright© 2018 Constantine VI" << endl;
        cout << endl;
        cout << "Usage: " << argv[0] << " [InputFile]" << endl;
        cout << "Option:" << endl;
//        cout << "  search    Use profile.conf to search data" << endl;
//        cout << "  download  Use profile.conf to search and download data" << endl;
        cout << "  help      Plot help information" << endl;
        exit(0);
    }
    else
    {
        InputFile = filesystem::path("configuration.xml");
    }
    
    //檢查輸入檔案是否存在
    if (!filesystem::exists(InputFile))
    {
        CreateProfile(InputFile);
        cout << "Please setting the search configuration." << endl;
        exit(0);
    }
    
    //讀入Profile
    vector<Configure> *SearchConfigure = new std::vector<Configure>[SearchConfigureCount];
    vector<SearchProfile> *ProfileList = new std::vector<SearchProfile>[SearchProfileCount];
    ReadProfile(InputFile, SearchConfigure, ProfileList);
    //check_package("wget");
    Search(SearchConfigure, ProfileList);
    vector<Product> *ProductList = new vector<Product>;
    ReadXML(SearchResultFile, ProductList);
    download_wget(SearchConfigure,ProductList);
}
