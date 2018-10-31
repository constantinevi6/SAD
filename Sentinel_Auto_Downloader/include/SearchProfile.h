//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#ifndef SearchProfile_h
#define SearchProfile_h

#include <string>
#include <vector>

#define SearchResultFile "Search_Result.xml"
#define SearchConfigureCount 3
#define SearchProfileCount 13
#define LineDelay 4

typedef struct Coordinates
{
    double Lon;
    double Lat;
}Coordinates;

class SearchProfile
{
private:
    std::string Keyword;
    std::string Value;
    std::vector<Coordinates> FootPrintList;
public:
    SearchProfile();
    void set(std::string Keyword, std::string InputValue);
    void setCorrd(std::string LonLat);
    void print();
    std::string setTime(std::string StartTime, std::string EndTime);
    std::string SearchSyntax();
    std::string get_FootPrints();
    int sizeCorrd();
    bool isNull();
};

#endif /* SearchProfile_h */
