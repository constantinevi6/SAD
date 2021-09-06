//
//  txtfile.hpp
//  ASPS
//
//  Created by Constantine VI on 2021/8/24.
//  Copyright © 2021 CSRSR. All rights reserved.
//

#ifndef txtfile_h
#define txtfile_h

#include <vector>
#include <string>
#include <filesystem>

class txtFile
{
private:
    std::filesystem::path pathFile;
    std::vector<std::string> TXTContent;
public:
    txtFile();
    txtFile(std::filesystem::path InputFilePath);
    ~txtFile();

    // 讀取文字檔內容
    int read();

    // 寫入文字檔
    int write();

    // 寫入文字檔至新的位置
    int write(std::filesystem::path pathOutputFile);

    // 於檔案末端加入文字
    int append(std::string Inputstr);

    // 於檔案末端加入一行文字
    int appendLine(std::string Inputstr);

    // 加入一行文字至指定的行數之後
    int appendLine(std::string Inputstr, int NoLine);

    // 印出檔案內容
    int print();

    // 印出指定行數之內容
    std::string getLine(int NoLine);

    // 印出包含關鍵字之內容
    std::string getLine(std::string InputKeyword);

    // 取得文字檔內容
    std::vector<std::string> getTXTContent();
};

#endif /* txtfile_h */
