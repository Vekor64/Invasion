#include "GUI.h"

int main()
{
	try {
		// Gui.NewWindow("WindowName", Vec2(1600, 900), DrawCallBack,false );
		Gui.AttachAnotherWindow("Counter-Strike 2","", GUI::DrawCallBack);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}