#include "pch.h"
#include <string>
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <Winioctl.h>
#include "FSReader.h"


void PrintBootSectData(FATBootRecord _bpb)
{
	printf("FAT Disk Information: \n");
	printf("===========================\n");
	printf("OEM Name: %s\n", _bpb.oemID);
	printf("Cluster sectors amount: %d\n", _bpb.clusterSectorsAmount);
	printf("Reserved sectors amount: %d\n", _bpb.reservedSectors);
	printf("Amount of FAT table copies for the volume: %d\n", _bpb.FATTablesCopiesAmount);
	printf("Amount of 32-byte files and catalogs name (FAT12/16 only): %d\n", _bpb.fileNamesAmount32Byte);
	printf("Volume sectors amount 16-bit (FAT12/16 only): %d\n", _bpb.volumeSectorsAmount16Bit);
	printf("Storage type: %d\n", _bpb.storageType);
	printf("Amount of sectors in each FAT copy (FAT12/16 only): %d\n", _bpb.FATCopySectorsAmount);
	printf("Amount of sectors in a track: %d\n", _bpb.trackSectorsAmount);
	printf("Amount of headers: %d\n", _bpb.headersAmount);
	printf("Hidden sectors amount: %d\n", _bpb.hiddenSectorsAmount);
	printf("Volume sectors amount 32-bit: %d\n", _bpb.volumeSectorsAmount32Bit);
	
}

int GetFileSystemType(std::string sysName)
{

	if (sysName.find("FAT") != std::string::npos)
	{
		return 1;
	}

	return -1;
}

std::string GetFSName(std::string diskName)
{
	DWORD FileSF;
	DWORD VSNumber;
	DWORD MCLength;
	char SysBuffer[MAX_PATH];
	char NameBuffer[MAX_PATH];
	std::string forVolumeInf = diskName + ":\\";

	if (
		GetVolumeInformationA(
			forVolumeInf.c_str(),
			NameBuffer,
			sizeof(NameBuffer),
			&VSNumber,
			&MCLength,
			&FileSF,
			SysBuffer,
			sizeof(SysBuffer)
		)
		)
	{
		std::cout << "Detected file system is " << SysBuffer << std::endl << std::endl;
		std::string SysName = SysBuffer;

		return SysName;
	}

	return std::string("");
}

bool IsFsSupported(std::string sysName)
{
	if (sysName.find("FAT") == std::string::npos)
	{
		return false;
	}

	return true;
}

bool GetFsData(std::string diskNameFormated, FATBootRecord* _bpb)
{
	DWORD dwBytesRead(0);
	BYTE bBootSector[512];
	memset(bBootSector, 0, 512);
	HANDLE hDisk = CreateFileA(
		diskNameFormated.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hDisk == INVALID_HANDLE_VALUE)
	{
		wprintf(L"CreateFile() failed! You'll rrobably need to run the app as administrator\n");
		wprintf(L" %u \n", GetLastError());

		if (CloseHandle(hDisk) != 0)
		{
			wprintf(L"hVolume handle was closed successfully!\n");

		}
		else
		{
			wprintf(L"Failed to close hVolume handle!\n");
		}

		return false;
	}

	if (!ReadFile(hDisk, bBootSector, 512, &dwBytesRead, NULL))
	{
		printf("Error in reading the disk\n");
		CloseHandle(hDisk);

		return false;
	}

	CloseHandle(hDisk);

	*_bpb = *reinterpret_cast<FATBootRecord*>(bBootSector);

	return true;
}