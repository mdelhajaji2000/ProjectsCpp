#include <windows.h>
#include <iostream>
using namespace std;

int main() {
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;  // عرض الخط، اتركها صفر للحفاظ على الحجم الحالي
    fontInfo.dwFontSize.Y = 24; // ارتفاع الخط
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy(fontInfo.FaceName, L"Consolas"); // اسم الخط
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    
    cout << "Hello World !" << endl;
    system("pause>0");    
    return 0;
}
