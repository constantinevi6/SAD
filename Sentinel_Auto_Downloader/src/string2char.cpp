//
//  string2char.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <string>

char *string2char(std::string Inputstring)
{
    char *output = new char[((sizeof Inputstring) * __CHAR_BIT__) + 2];
    strcpy(output, Inputstring.c_str());
    return output;
}
