//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOM.hpp"
#ifndef product_h
#define product_h

#include <string>

class Product
{
private:
    std::string InstrumentShortname;
    std::string SensorOperationalMode;
    std::string InstrumentName;
    std::string SwathIdentifier;
    std::string OrbitDirection;
    std::string PolarisationMode;
    std::string ProductClass;
    std::string PlatformSerialIdentifier;
    std::string ProcessingLevel;
    std::string ProductType;
    std::string PlatformName;
    double FileSize;

    std::string Title;
    std::string UUID;
    std::string DownloadLink;
    std::string Satellite;
    std::string Mode;
    std::string Category;
    std::string Type;
    std::string Resolution;
    std::string Level;
    std::string Class;
    std::string Polarisation;
    std::string StartTime;
    std::string StopTime;
    std::string Orbit;
    std::string TakeID;
    std::string UniqueID;
    std::string Checksum;
    std::string DatabaseTitle;
public:
    Product();
    void read(xercesc::DOMNode *ProductEntry);
    void set(std::string ProductTitle);
    void get_url();
    void get_uuid(std::string uuid);
    std::string &call_title();
    std::string &call_url();
    std::string &call_database_title();
};
#endif /* product_h */
