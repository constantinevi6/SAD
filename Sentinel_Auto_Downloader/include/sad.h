//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#ifndef sad_h
#define sad_h

#include <string>
#include "SearchProfile.h"
#include "Product.h"

#define OpenDataHub "https://scihub.copernicus.eu/dhus/odata/v1/Products"
#define ApiHub "https://scihub.copernicus.eu/apihub/odata/v1/Products"

class Configure
{
private:
    std::string Keyword;
    std::string Value;
public:
    Configure();
    void set(std::string ConfigureKeyword, std::string InputValue);
    std::string getValue(std::string InputKeyword);
    bool isNull();
};

char *string2char(std::string Inputstring);
std::string *readfile(std::string InputFile);
bool fexists(const std::string& filename);
int countline(const char *InputFile);
bool is_number(const std::string &Inputstring);

int CreateProfile(std::string Profile);
int ReadProfile(std::string InputFile, std::vector<Configure> *InputConfigure, std::vector<SearchProfile> *ProfileList);
int Search(std::vector<Configure> *ConfigureList, std::vector<SearchProfile> *ProfileList);
int ReadXML(char* InputXML, std::vector<Product> *ProductList);
#endif /* sad_h */
