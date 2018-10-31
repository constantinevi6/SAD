//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/3.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <string>

bool is_number(const std::string &Inputstring)
{
    try
    {
        std::stod(Inputstring);
    }
    catch(...)
    {
        return false;
    }
    return true;
}
