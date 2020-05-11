#pragma once

#ifdef VOLUME_INFORMATION_EXPORTS
#define VOLUME_INFORMATION_API __declspec(dllexport)
#else
#define VOLUME_INFORMATION_API __declspec(dllimport)
#endif

#include <wchar.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <Winioctl.h>

using namespace std;

#pragma pack(1)
typedef struct
{
	BYTE jumpCode[3];
	BYTE oemID[8];
	WORD bytesPerSector;
	BYTE sectorPerCluster;
	WORD reservedSectors;
	BYTE always0[3];
	WORD notUsed;
	BYTE mediaDiscr;
	WORD always02;
	WORD sectorperTrack;
	WORD numOfHeaders;
	DWORD hiddenSectors;
	DWORD notUsed2;
	DWORD notused3;
	ULONGLONG totalSectors;
	ULONGLONG lcnForSMFT;
	ULONGLONG lcnForSMFTMirr;
	DWORD clusterPerFileRecordSegm;
	BYTE clusterPerIndexBuff;
	BYTE notUsed4[3];
	ULONGLONG volumeSerialNumber;
	DWORD checksum;
	BYTE bootstrap[426];
	WORD endMarker;
} NTFSBootRecord;
#pragma pack()

class FileSystem {
public:
	FileSystem(string FSdiskName) {
		diskName = FSdiskName;
	}
	virtual void printBootRecordInfo() = 0;
	virtual ~FileSystem() {}
protected:
	string diskName;
};


class NTFS : public FileSystem {
public:
	NTFS(string diskName) : FileSystem(diskName) {}

	void printBootRecordInfo() override;

private:
	NTFSBootRecord bootRecord;
};

extern "C" VOLUME_INFORMATION_API __declspec(dllexport) void getVolumeFS(string);
