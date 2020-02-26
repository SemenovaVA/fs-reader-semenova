#include <wchar.h>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <Winioctl.h>
#include "FSReader.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string diskName;

	cout << "Enter volume name (for example \"C\", \"D\" etc.): ";

	diskName = cin.get();
	string fsName = GetFSName(diskName);
	string formattedDiskName = "\\\\.\\" + diskName + ":";

	

	if (GetFileSystemType(fsName) == 1) {
		FATBootRecord _bpb;

		if (GetFsData(formattedDiskName, &_bpb))
		{
			PrintBootSectData(_bpb);
		}
	}

	cout << "Press Enter to exit";

	cin.get();
	cin.get();

	exit(0);
}

