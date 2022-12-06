__declspec(dllexport)int CreateMapWindow(int nCmdShow);
__declspec(dllexport)void ReceivePoints(std::vector<std::pair<int, int> >Re);
__declspec(dllexport)std::vector<std::pair<int, int> > SendPoints();
#pragma comment(lib,"map.lib")