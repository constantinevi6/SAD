//
//  System.cpp
//  Automatic SAR Processing System
//
//  Created by Constantine VI on 2020/07/22.
//  Copyright © 2018 CSRSR. All rights reserved.
//

#include "System.hpp"
#include <iostream>
#include <sys/stat.h>
#ifdef _WIN32
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif

unsigned long long getTotalSystemMemory()
{
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
#else
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
#endif
}

unsigned long long getFreeMemory()
{
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullAvailPhys;
#else
    struct rusage usage;
    if(0 == getrusage(RUSAGE_SELF, &usage))
        return getTotalSystemMemory() - (usage.ru_maxrss * 1024);
    else
        return 0;
#endif
}

std::uintmax_t FileSize(std::filesystem::path filePath)
{
    std::uintmax_t TotalSize = 0;
    if (std::filesystem::is_directory(filePath))
    {
        std::filesystem::directory_iterator list(filePath);
        for (auto& it : list)
        {
            TotalSize = TotalSize + FileSize(it);
        }
    }
    else
    {
        TotalSize = std::filesystem::file_size(filePath);
    }
    return TotalSize;
}

int copyFile(std::filesystem::path FromPath, std::filesystem::path ToPath)
{
    if (!std::filesystem::exists(FromPath)) {
        throw "Error: Source doesn't exists.";
        return 1;
    }
    createDirectory(ToPath);
    std::filesystem::space_info DiskSpace = std::filesystem::space(ToPath);
    std::uintmax_t FileSpace = FileSize(FromPath);

    while (DiskSpace.available < FileSpace)
    {
        std::cout << "Insufficient disk space, waiting 30s for free space to cpoy " << FromPath.string() << std::endl;
        sleep(30);
        DiskSpace = std::filesystem::space(ToPath);
    }
    std::cout << "Cpoy " << FromPath.string() << " to " << ToPath.string() << std::endl;
#ifdef _WIN32
    if (std::filesystem::is_directory(FromPath))
    {
        std::filesystem::path NameDir = FromPath.filename();
        ToPath = ToPath / NameDir;
        createDirectory(ToPath);
        std::filesystem::copy(FromPath, ToPath, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    }
    else
    {
        std::filesystem::copy(FromPath, ToPath, std::filesystem::copy_options::overwrite_existing);
    }
#else
    std::string CMD = "cp -r " + FromPath.string() + " " + ToPath.string();
    system(CMD.c_str());
#endif
    return 0;
}

int createDirectory(std::filesystem::path pathDirectory)
{
    if (!std::filesystem::is_directory(pathDirectory.parent_path()))
    {
        createDirectory(pathDirectory.parent_path());
    }
    if (!std::filesystem::is_directory(pathDirectory))
    {
        std::filesystem::create_directory(pathDirectory);
    }
    return 0;
}

short shortswap(short Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    short Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[1];
    OutputByte[1] = InputByte[0];
    return Output;
}

int longswap(int Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    int Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[3];
    OutputByte[1] = InputByte[2];
    OutputByte[2] = InputByte[1];
    OutputByte[3] = InputByte[0];
    return Output;
}

float floatswap(float Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    float Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[3];
    OutputByte[1] = InputByte[2];
    OutputByte[2] = InputByte[1];
    OutputByte[3] = InputByte[0];
    return Output;
}

double doubleswap(double Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    double Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[7];
    OutputByte[1] = InputByte[6];
    OutputByte[2] = InputByte[5];
    OutputByte[3] = InputByte[4];
    OutputByte[4] = InputByte[3];
    OutputByte[5] = InputByte[2];
    OutputByte[6] = InputByte[1];
    OutputByte[7] = InputByte[0];
    return Output;
}

std::complex<short> cshortswap(std::complex<short> Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    std::complex<short> Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[1];
    OutputByte[1] = InputByte[0];
    OutputByte[2] = InputByte[3];
    OutputByte[3] = InputByte[2];
    return Output;
}

std::complex<float> cfloatswap(std::complex<float> Input)
{
    char* InputByte = reinterpret_cast<char*>(&Input);
    std::complex<float> Output;
    char* OutputByte = reinterpret_cast<char*>(&Output);
    OutputByte[0] = InputByte[3];
    OutputByte[1] = InputByte[2];
    OutputByte[2] = InputByte[1];
    OutputByte[3] = InputByte[0];
    OutputByte[4] = InputByte[7];
    OutputByte[5] = InputByte[6];
    OutputByte[6] = InputByte[5];
    OutputByte[7] = InputByte[4];
    return Output;
}
