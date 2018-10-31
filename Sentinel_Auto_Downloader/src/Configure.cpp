//
//  Configure.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/3.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include <iostream>
#include <string>

using namespace std;

Configure::Configure()
{
    Keyword = "";
    Value = "";
}

void Configure::set(string ConfigureKeyword, string InputValue)
{
    Keyword = ConfigureKeyword;
    if (InputValue.size() == 0)
    {
        cout << "Please enter " + Keyword + ":" << endl;
        cin >> Value;
    }
    else
    {
        Value = InputValue;
    }
}
string Configure::getValue(std::string InputKeyword)
{
    if (Keyword.compare(InputKeyword) == 0)
    {
        return Value;
    }
    else
    {
        return InputKeyword;
    }
}
