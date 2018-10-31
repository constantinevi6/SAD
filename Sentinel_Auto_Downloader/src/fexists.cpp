//
//  fexists.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <fstream>

using namespace std;

bool fexists(const std::string& filename)
{
    ifstream ifile(filename);
    return (bool)ifile;
}
