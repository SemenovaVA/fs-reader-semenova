#include <tchar.h>
#include <iostream>
#include <windows.h>
#include <Winioctl.h>
#include <wchar.h>
#include <algorithm>
#include <Libloaderapi.h>


using namespace std;

typedef void (*VolumeFSReader)(string);

VolumeFSReader getFSReader()
{
	HINSTANCE hDLL = LoadLibrary(_T("VolumeInformation"));

	if (hDLL == NULL) {
		throw "Error. Couldn't load VolumeInformation library...\n";
	}

	return (VolumeFSReader)GetProcAddress((HMODULE)hDLL, "getVolumeFS");
}



int main()
{
	VolumeFSReader getVolumeFS = getFSReader();

	if (!getVolumeFS) {

		cout << GetLastError() << endl;

		return EXIT_FAILURE;
	}

	string diskName;

	while (1)
	{
		cout << "Please specify volume name (\"C\", \"D\", etc.)." << endl;

		diskName = cin.get();

		if (diskName.length() == 1)
		{
			break;
		}
	}

	try
	{
		getVolumeFS(diskName.c_str());
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	
	cout << "Press Enter to exit";
	cin.get();
	cin.get();

	return 0;
}
