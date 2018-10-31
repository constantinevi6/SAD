//
//  SearchProfile.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include "SearchProfile.h"
#include <iostream>

using namespace std;

SearchProfile::SearchProfile()
{
    Keyword = "";
    Value = "";
}

void SearchProfile::set(std::string InputKeyword, std::string InputValue)
{
    Keyword=InputKeyword;
    Value=InputValue;
}

std::string SearchProfile::setTime(std::string StartTime, std::string EndTime)
{
    string TimeSyntax;
    if (StartTime.size() == 0 || EndTime.size() == 0)
    {
        TimeSyntax = "";
    }
    else
    {
        TimeSyntax = "[" + StartTime + " TO " + EndTime + "]";
    }
    return TimeSyntax;
}

void SearchProfile::setCorrd(std::string LonLat)
{
    unsigned long Break = LonLat.find(" ",0);
    unsigned long LonLatSize = LonLat.size();
    string Lon;
    string Lat;
    Lon.assign(LonLat,0,Break);
    Lat.assign(LonLat,Break + 1,LonLatSize - Break);
    if (! is_number(Lon) || ! is_number(Lat)) {
        cout << "Input Lon/Lat is invalid." << endl;
        exit(0);
    }
    Coordinates FootPrint;
    FootPrint.Lon = stod(Lon);
    FootPrint.Lat = stod(Lat);
    FootPrintList.push_back(FootPrint);
}

std::string SearchProfile::get_FootPrints()
{
    string SearchWord;
    if (FootPrintList.size() == 0)
    {
        SearchWord = "";
    }
    else if (FootPrintList.size() == 1)
    {
        SearchWord = "\\\"intersects(" + to_string(FootPrintList[0].Lat) + ", " + to_string(FootPrintList[0].Lon) + ")\\\"";
    }
    else
    {
        SearchWord = "\\\"intersects(POLYGON((";
        for (int j = 0; j < FootPrintList.size(); j++)
        {
            SearchWord = SearchWord + to_string(FootPrintList[j].Lon) + " " + to_string(FootPrintList[j].Lat) + ", ";
        }
        SearchWord = SearchWord + to_string(FootPrintList[0].Lon) + " " + to_string(FootPrintList[0].Lat)+ ")))\\\"";
    }
    return SearchWord;
}

std::string SearchProfile::SearchSyntax()
{
    string Syntax;
    Syntax = Keyword + ":" + Value;
    return Syntax;
}

void SearchProfile::print()
{
    cout << "Search Keyword = " << Keyword << endl;
    cout << "Search value = " << Value << endl;
}

bool SearchProfile::isNull()
{
    if (Keyword.size() == 0 || Value.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

