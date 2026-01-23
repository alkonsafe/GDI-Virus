// remade from the birdvirus
#include <filesystem>
#include <string>

#include <windows.h>
#include <shlobj.h>
#include <objbase.h>

#pragma comment(lib,"Shell32")
#pragma comment(lib,"Ole32")

inline std::filesystem::path get_desktop_path()
{
	wchar_t* p;
	if (S_OK != SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &p)) return "";
	std::filesystem::path result = p;
	CoTaskMemFree(p);
	return result;
}
