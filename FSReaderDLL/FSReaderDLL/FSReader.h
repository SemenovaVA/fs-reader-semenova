#pragma once
#ifdef FSREADER_EXPORTS
#define FSREADER_API __declspec(dllexport)
#else
#define FSREADER_API __declspec(dllimport)
#endif

#include <wchar.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <Winioctl.h>


using std::string;


typedef struct {
	BYTE jumpCode[3];
	CHAR oemID [8];
	BYTE sectorBytesAmount[2];
	BYTE clusterSectorsAmount;
	WORD reservedSectors;
	BYTE FATTablesCopiesAmount;
	WORD fileNamesAmount32Byte;
	WORD volumeSectorsAmount16Bit;
	BYTE storageType;
	WORD FATCopySectorsAmount;
	WORD trackSectorsAmount;
	WORD headersAmount;
	DWORD hiddenSectorsAmount;
	DWORD volumeSectorsAmount32Bit;
	
} FATBootRecord;


extern "C++" FSREADER_API string GetFSName(string diskName);
extern "C++" FSREADER_API bool IsFsSupported(string sysName);
extern "C++" FSREADER_API int GetFileSystemType(string sysName);
extern "C++" FSREADER_API void PrintBootSectData(FATBootRecord _bpb);
extern "C++" FSREADER_API bool GetFsData(string diskNameFormated, FATBootRecord * _bpb);