//
//  download.hpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/9/7.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#ifndef download_hpp
#define download_hpp
#ifdef _WIN32
    #define PATH_Separator ";"
    #define Filename_Extension ".exe"
#else
    #define PATH_Separator ":"
    #define Filename_Extension ""
#endif

#include <stdio.h>
#include "curl/curl.h"
#include <iostream>

#define MAXWORK 200
typedef struct DownloadInfo
{
    char url[512];
    char filePath[256];
}DLIO;

typedef struct CurDownloadInfor
{
    char url[512];     //url
    char fileName[256];   //文件名稱
    long preLocalLen;     //本地已下载的大小
    double totalFileLen;   //文件大小
    double CurDownloadLen;   //每次下载的文件大小
}CURDI;

class CDownloader
{
public:
    CDownloader(void);
    ~CDownloader(void);
    int StartDownloadThread();
    double GetTotalFileLenth(const char* url);             //获取将要下载的文件长度
    long GetLocalFileLenth(const char* fileName);         //获取本地问价长度
    void GetFileNameFormUrl(char* fileName, const char* url);      //从URL中获取文件名
    void AddDownloadWork(DLIO downloadWork);
//    int SetConnectTimeOut(DWORD nConnectTimeOut);    //设置连接的超时时间
    int GetCurrentDownloadInfo(CURDI* lpCurDownloadInfor);
    bool CreateMultiDir(const char* pathName);       //是否在本地创建目录，没有就创建
    bool IsDownloadBegin();
    bool IsDownloadEnd();
protected:
    void SingleDownloadProc();
    static size_t WriteFunc(char *str, size_t size, size_t nmemb, void *stream);     //写入数据（回调函数）
    static size_t ProgressFunc(double* fileLen, double t, double d, double ultotal, double ulnow);   //下载进度
private:
    char m_filePath[512];
    char m_downloadUrl[256];
    int m_downloadCourse;   // 0 还未下载 1 正在下载 2 下载完成
    long m_curLocalFileLenth; //因为下载的时候已经计算了本地文件的大小用来设置断点，所以对于每个文件，该数字只会被设置一次；就是下载前的本地大小；
    long m_nConnectTimeOut;      //连接的超时时间
    DLIO m_dowloadWork[MAXWORK];
    CURDI m_curDownloadInfo;
    int m_curIndex;
    CURL* m_pCurl;
};

void test(std::string url);
void download_wget(std::vector<Configure> *ConfigureList, std::vector<Product> *ProductList);
void check_package(std::string Package);

#endif /* download_hpp */
