//
//  download.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/9/7.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "sad.h"
#include "download.hpp"
#include "Product.h"
#include <string.h>
#include <iostream>
#include <sys/io.h>
#include <filesystem>
#include <sys/stat.h>

using namespace std;

#ifdef __linux__
    using namespace std::filesystem;
#elif _WIN32
    using namespace std::experimental::filesystem::v1;
#endif


long filelength(char *f)
{
    struct stat st;
    stat(f, &st);
    return st.st_size;
}

void download_wget(vector<Configure> *ConfigureList, vector<Product> *ProductList)
{
    std::vector<Product>::iterator Product;
    for (Product = ProductList -> begin(); Product != ProductList -> end(); ++Product)
    {
        cout << "Starting download product: " << Product ->call_title() << endl;
        cout << endl;
        string DownloadPath = "Download Path";
        string Username = "Username";
        string Password = "Password";
        vector<Configure>::iterator configure;
        for (configure = ConfigureList -> begin(); configure != ConfigureList -> end(); ++configure)
        {
            DownloadPath=configure->getValue(DownloadPath);
            Username=configure->getValue(Username);
            Password=configure->getValue(Password);
        }
        string Wget = "wget";
        string WgetParmeter = " --no-check-certificate --continue";
        string WgetUsername = " --user=" + Username;
        string WgetPassword = " --password=" + Password;
        string DownloadFile = DownloadPath + "/" + Product ->call_title() + ".zip";
        cout << DownloadFile << endl;
        string WgetOutputDocument = " --output-document=" + DownloadFile;
        string WgetURL = " \"" + Product -> call_url() + "\"";
        
        struct stat buffer;
        string Database = "/Data/SAR_NAS/Sentinel1/";
        Database = Database + Product -> call_database_title();
        if (stat(Database.c_str(), &buffer) == 0) {
            cout << "File exist at Database, skip...." << endl;
        }
        else if (stat(DownloadFile.c_str(), &buffer) == 0) {
            cout << "File exist at download path, skip...." << endl;
        }
        else
        {
            string cmd = Wget + WgetParmeter + WgetUsername + WgetPassword + WgetOutputDocument + WgetURL;
		    system(cmd.c_str());
        }
    }
}

void check_package(std::string Package)
{
	cout << "Checking " << Package << "...." << endl;
    string PATHList = getenv("PATH");
    unsigned long Break;
    unsigned long PATHListSize;
    bool is_Package_exist=false;
    do {
        Break = PATHList.find(PATH_Separator,0);
        PATHListSize = PATHList.size();
        string PATH;
        PATH.assign(PATHList,0,Break);
        PATHList.assign(PATHList,Break + 1,PATHListSize - Break);
        string PackagePATH = PATH + "\\" + Package + Filename_Extension;
		string PackageName = Package + Filename_Extension;
		path pPackagePATH = PATH / PackageName;
        if (exists(pPackagePATH)) {
            is_Package_exist=true;
			cout << "Find " << Package << " in path: " << pPackagePATH << endl;
        }
    } while (!is_Package_exist && Break != std::string::npos);
    if (!is_Package_exist) {
        cout << "Package: " << Package << " not found. Please install" << Package << " and try again." << endl;
        exit(1);
    }
}

CDownloader::CDownloader(void)
{
    m_downloadCourse = 0;
    m_nConnectTimeOut = 0;
    curl_global_init (CURL_GLOBAL_ALL);
    for(int i=0; i<MAXWORK; i++)
    {
        memset(m_dowloadWork->url, 0, 512);
        memset(m_dowloadWork->filePath, 0, 256);
    }
    m_curIndex = 0;
}


CDownloader::~CDownloader(void)
{
    curl_global_cleanup();
}

bool CDownloader::IsDownloadBegin()
{
    if(m_downloadCourse == 1)
        return true;
    return false;
}

bool CDownloader::IsDownloadEnd()
{
    if(m_downloadCourse == 2)
        return true;
    return false;
}

bool CDownloader::CreateMultiDir(const char* pathName)
{
    if(pathName == NULL) return false;
    char filePath[256] = {0};
    strcpy(filePath, pathName);
    int i = 0, pathLen = strlen(pathName);
    string curPath;
    char curFilePath[256] = {0};
    if(filePath[pathLen - 1] != '\\')    //最后一个非0字符不是‘\\’则加上
    {
        filePath[pathLen] = '\\';
    }
    while(filePath[i] != '\0')
    {
        if(filePath[i] == ':')
        {
            i+=2;
            continue;
        }
        if(filePath[i] == '\\')
        {
            memcpy(curFilePath, filePath, i);
            curFilePath[i] = '\0';
            curPath = curFilePath;
//            if(FindFirstFile(curPath, &swf) == INVALID_HANDLE_VALUE) //目录不存在就创建
//            {
//                if(!CreateDirectory(curPath, NULL))
//                {
//                    return false;
//                }
//            }
        }
        i++;
    }
    return true;
}

void CDownloader::AddDownloadWork(DLIO downloadWork)
{
    char filePath[256] = {0};
    char mUrl[512] = {0};
    strcpy(mUrl, downloadWork.url);
    strcpy(filePath, downloadWork.filePath);
    int i = strlen(filePath) -1;
    bool isPath = true;
    while(filePath[i] != '\\')
    {
        if(filePath[i] == '.' && filePath[i+1] != '\0')
        {
            isPath = false;
        }
        i--;
    }
    if(isPath)
    {
        if(!CreateMultiDir(filePath))
            return;
        char fileName[256] = {0};
        GetFileNameFormUrl(fileName,mUrl);
        if(filePath[strlen(filePath)-1] != '\\')
        {
            strcat(filePath, "\\");
        }
        strcat(filePath, fileName);
    }
    else
    {
        char realPath[256] = {0};
        for(int k=0; k<i; k++)
        {
            realPath[k] = filePath[k];
        }
        realPath[i] = '\\';
        if(!CreateMultiDir(realPath))
            return;
    }
    strcpy(m_dowloadWork[m_curIndex].url, mUrl);
    strcpy(m_dowloadWork[m_curIndex].filePath, filePath);
    m_curIndex++;
}

void CDownloader::GetFileNameFormUrl(char* fileName, const char* url)
{
    int urlLen = strlen(url);
    char mUrl[512] = {0};
    char fName[256] = {0};
    strcpy(mUrl, url);
    int cutIndex = 0;
    int i = urlLen - 1, j = 0;
    while(mUrl[--i] != '/');
    i++;
    while(mUrl[i] != '\0' && mUrl[i] != '?' &&mUrl[i] != '&')
    {
        fName[j++] = mUrl[i++];
    }
    fName[j] = '\0';
    strcpy(fileName, fName);
    return ;
}

long CDownloader::GetLocalFileLenth(const char* fileName)
{
    if(m_downloadCourse == 0)        //文件已经开始下载的时候，取到的是下载前本地文件的大小；
        return m_curLocalFileLenth;
    char strTemp[256] = {0};
    strcpy(strTemp,fileName);
    FILE* fp = fopen(strTemp, "rb");
    if(fp != NULL)
    {
//        m_curLocalFileLenth = filelength(fileno(fp));
        fclose(fp);
        return m_curLocalFileLenth;
    }
    return 0;
}

double CDownloader::GetTotalFileLenth(const char* url)
{
    char mUrl[512] = {0};
    strcpy(mUrl, url);
    double downloadFileLenth = 0;
    CURL* pCurl = curl_easy_init();
    curl_easy_setopt(pCurl, CURLOPT_URL, mUrl);
    curl_easy_setopt(pCurl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(pCurl, CURLOPT_NOBODY, 1L);
    if(curl_easy_perform(pCurl) == CURLE_OK)
    {
        curl_easy_getinfo(pCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloadFileLenth);
    }
    else
    {
        downloadFileLenth = -1;
    }
    curl_easy_cleanup(pCurl);
    return downloadFileLenth;
}


size_t CDownloader::WriteFunc(char *str, size_t size, size_t nmemb, void *stream)
{
    return fwrite(str, size, nmemb, (FILE*)stream);
}

size_t CDownloader::ProgressFunc(
    double* pFileLen,
    double t,// 下载时总大小
    double d, // 已经下载大小
    double ultotal, // 上传是总大小
    double ulnow)   // 已经上传大小
{
    if(t == 0) return 0;
    *pFileLen = d;
    return 0;
}

//int CDownloader::StartDownloadThread()
//{
//    if(m_downloadCourse == -1||m_downloadCourse == 1)
//    {
//        HANDLE downloadThread = CreateThread(NULL, 0, SingleDownloadProc, this, 0, NULL);
//        CloseHandle(downloadThread);
//        return 0;
//    }
//    return -1;
//}
//
void CDownloader::SingleDownloadProc()
{
    CDownloader* pDownload;
    int curDLIndex = 0;
    CURL* pCurl = curl_easy_init();
    while(curDLIndex <= pDownload->m_curIndex)
    {
        char fileName[256] = {0};
        char url[512] = {0};
        strcpy(fileName, pDownload->m_dowloadWork[curDLIndex].filePath);
        strcpy(url, pDownload->m_dowloadWork[curDLIndex].url);
        strcpy(pDownload->m_curDownloadInfo.url, url);
        strcpy(pDownload->m_curDownloadInfo.fileName, fileName);
        long localFileLen = pDownload->GetLocalFileLenth(fileName);
        pDownload->m_curLocalFileLenth = localFileLen;
        pDownload->m_curDownloadInfo.preLocalLen = pDownload->m_curLocalFileLenth;
        double totalFileLen = pDownload->m_curDownloadInfo.totalFileLen = pDownload->GetTotalFileLenth(url);
        if(localFileLen >= (long)totalFileLen)        //如果需要下载文件的大小大于等于本地文件的大小，直接下载下一个文件
        {
            curDLIndex++;
            pDownload->m_downloadCourse = -1;
            continue;
        }
        FILE* fp = fopen(fileName,"ab+");
        if(fp == NULL) //文件打开错误，进行下一个文件的下载
        {
            pDownload->m_downloadCourse = -1;
            continue;
        }
        curl_easy_setopt(pCurl, CURLOPT_URL, url);
        curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, pDownload->m_nConnectTimeOut);
        curl_easy_setopt(pCurl, CURLOPT_HEADER, 0L);
        curl_easy_setopt(pCurl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(pCurl, CURLOPT_RESUME_FROM, localFileLen);

        curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, WriteFunc);
        curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, fp);

        curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, ProgressFunc);
        curl_easy_setopt(pCurl, CURLOPT_PROGRESSDATA, &(pDownload->m_curDownloadInfo.CurDownloadLen));

        pDownload->m_downloadCourse = 0;
        if(!curl_easy_perform(pCurl))
        {
            curDLIndex++;
            pDownload->m_downloadCourse = -1;
        }
        fclose(fp);
    }
    curl_easy_cleanup(pCurl);
    pDownload->m_downloadCourse = 1;
}

int CDownloader::GetCurrentDownloadInfo(CURDI* lpCurDownloadInfor)
{
    *lpCurDownloadInfor = m_curDownloadInfo;
    return 0;
}

//int CDownloader::SetConnectTimeOut(DWORD nConnectTimeOut)
//{
//    if(m_downloadCourse == 0) return -1;
//    else
//        m_nConnectTimeOut = nConnectTimeOut;
//    return 0;
//}

void test(string url)
{
    CURL * curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);

}
