//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#ifndef product_h
#define product_h

#include <string>

class Product
{
private:
    std::string Title;
    std::string UUID;
    std::string DownloadLink;
    std::string Satellite;
    std::string Mode;
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
    void set(std::string ProductTitle);
    void get_url();
    void get_uuid(std::string uuid);
    std::string &call_title();
    std::string &call_url();
    std::string &call_database_title();
};
#endif /* product_h */
