//
//  System.hpp
//  ASPS
//
//  Created by Constantine VI on 2020/12/24.
//  Copyright © 2020 CSRSR. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <thread>
#include <filesystem>
#include <complex>

#ifdef _WIN32

#define sleep(sec) Sleep(sec * 1000)
#define popen(command, mode) _popen(command, mode)
#define pclose(stream) _pclose(stream)

#elif __APPLE__
#include <unistd.h>
#define sleep(sec) usleep(sec * 1000000)

#elif __linux__
#include <unistd.h>
#define sleep(sec) usleep(sec * 1000000)

#endif

// 獲取系統記憶體容量(byte)
unsigned long long getTotalSystemMemory();

// 獲取可用記憶體容量(byte)
unsigned long long getFreeMemory();

// 拷貝檔案, copyfile(來源檔案, 目標位置)
int copyFile(std::filesystem::path FromPath, std::filesystem::path ToPath);

// 建立目錄, createDirectory(目錄路徑)
int createDirectory(std::filesystem::path pathDirectory);

// 獲取檔案或目錄大小(byte)
std::uintmax_t FileSize(std::filesystem::path filePath);

// Byteswap
short shortswap(short Input);
int longswap(int Input);
float floatswap(float Input);
double doubleswap(double Input);
std::complex<short> cshortswap(std::complex<short> Input);
std::complex<float> cfloatswap(std::complex<float> Input);

// 系統微處理器數量
const unsigned int uiNCPU = std::thread::hardware_concurrency();

// 系統記憶體容量(MB)
const unsigned long long ullRAM = getTotalSystemMemory() / 1024 / 1024;

// 保留記憶體容量(MB)
const unsigned long long MemoryPreserve = 2 * 1024;

#endif
