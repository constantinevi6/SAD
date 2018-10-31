//
//  readfile.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/2.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include <string>
#include <fstream>

using namespace std;

string *readfile(string InputFile)
{
    int LineCount = countline(string2char(InputFile));
    string *Output = new string[LineCount];
    string Line = "";
    fstream Input(InputFile, ifstream::in);
    for (int i = 0; i< LineCount; i++)
    {
        getline(Input, Line);
        Output[i] = Line;
    }
    Input.close();
    return Output;
}
