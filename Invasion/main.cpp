#include <iostream>
#include "Configs.hpp"
#include "Cheats.hpp"

std::string wstringToString(const std::wstring & wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

int main()
{
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

	//Get path
	wchar_t modulePath[MAX_PATH];
	if (GetModuleFileName(NULL, modulePath, MAX_PATH) == 0) {
		std::wcerr << L"[Error] Failed to get the module path." << std::endl;
		system("pause");
		exit(0);
	}
	std::wstring path(modulePath);
	std::wstring wdirectory = path.substr(0, path.find_last_of(L"\\/"));
	MenuConfig::path = wstringToString(wdirectory);

	// Load offsets
	if (!Offset::UpdateOffsets())
	{
		std::cout << "Failed to update offsets." << std::endl;
		system("pause");
		exit(0);
	}

	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
		system("pause");
		exit(0);
	}

	// Init address
	if (!gGame.InitAddress())
	{
		std::cout << "Failed to init address." << std::endl;
		system("pause");
		exit(0);
	}

	try {
		// Gui.NewWindow("WindowName", Vec2(1600, 900), DrawCallBack,false );
		Gui.AttachAnotherWindow("Counter-Strike 2","", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}