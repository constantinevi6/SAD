//
//  Product.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/5.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "Product.h"
#include "sad.h"

using namespace std;

Product::Product()
{
    Title = "";
    Satellite = "";
    Mode = "";
    Type = "";
    Resolution = "";
    Level = "";
    Class = "";
    Polarisation = "";
    StartTime = "";
    StopTime = "";
    Orbit = "";
    TakeID = "";
    UniqueID = "";
    DatabaseTitle = "";
    UUID = "";
}
void Product::set(std::string ProductTitle)
{
    Title = ProductTitle;
    Satellite.assign(Title,0,3);
    Mode.assign(Title,4,2);
    Type.assign(Title,7,3);
    Resolution.assign(Title,10,1);
    Level.assign(Title,12,1);
    Class.assign(Title,13,1);
    Polarisation.assign(Title,14,2);
    StartTime.assign(Title,17,15);
    StopTime.assign(Title,33,15);
    Orbit.assign(Title,49,6);
    TakeID.assign(Title,56,6);
    UniqueID.assign(Title,63,4);
}

void Product::get_url()
{
    DownloadLink = (string)OpenDataHub + "('" + UUID + "')" + "/" + URLSlash + "$value";
}

void Product::get_uuid(std::string uuid)
{
    UUID = uuid;
}

std::string &Product::call_title()
{
    return Title;
}

std::string &Product::call_url()
{
    return DownloadLink;
}

std::string &Product::call_database_title()
{
    std::string UnderLine = "_";
    DatabaseTitle = Satellite + UnderLine + Mode + UnderLine + Type + Resolution + UnderLine + Level + Class + Polarisation + UnderLine + StartTime + UnderLine + UniqueID;
    return DatabaseTitle;
}
