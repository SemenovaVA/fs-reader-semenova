#include <string>
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <Winioctl.h>
#include "pch.h"
#include "VolumeInformation.h"

void getVolumeFS(string diskName) {
	char NameBuffer[MAX_PATH];
	char SysBuffer[MAX_PATH];

	DWORD FileSF;
	DWORD VSNumber;
	DWORD MCLength;

	string forVolumeInf = diskName + ":\\";


	if (GetVolumeInformationA(forVolumeInf.c_str(), NameBuffer, sizeof(NameBuffer),
		&VSNumber, &MCLength, &FileSF, SysBuffer, sizeof(SysBuffer)))
	{
		cout << "File system is " << SysBuffer << endl << endl;
		string systemName = SysBuffer;

		if (systemName.find("NTFS") != string::npos)
		{
			FileSystem* fileSystem = new NTFS(diskName.c_str());

			fileSystem->printBootRecordInfo();
		}
		else
		{
			throw "File system is not supported.";
		}
	}
	else throw "Unexpected error. Cannot get information about your system. Please, contact the developer.";

}
