//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <fstream>
#include <string>

using namespace std;

int countline(const char *InputFile)
{
    int i = 0;
    string Line = "";
    fstream Input(InputFile, ifstream::in);
    while (getline(Input, Line))
    {
        i++;
    }
    Input.close();
    return i;
}
