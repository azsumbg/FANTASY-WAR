#include "framework.h"
#include "FANTASY WAR.h"
#include <mmsystem.h>
#include <d2d1.h>
#include <dwrite.h>
#include "helpsrv.h"
#include "ErrH.h"
#include "FCheck.h"
#include "D2BMPLOADER.h"
#include "gifresizer.h"
#include <chrono>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "helpsrv.lib")
#pragma comment(lib, "errh.lib")
#pragma comment(lib, "fcheck.lib")
#pragma comment(lib, "d2bmploader.lib")
#pragma comment(lib, "gifresizer.lib")

constexpr wchar_t bWinClassName[]{ L"TURN_STRAT" };

constexpr char tmp_file[]{ ".\\res\\data\\temp.dat" };
constexpr wchar_t Ltmp_file[]{ L".\\res\\data\\temp.dat" };
constexpr wchar_t snd_file[]{ L".\\res\\snd\\main.wav" };
constexpr wchar_t help_file[]{ L".\\res\\data\\help.dat" };
constexpr wchar_t record_file[]{ L".\\res\\data\\record.dat" };
constexpr wchar_t save_file[]{ L".\\res\\data\\save.dat" };

constexpr int mNew{ 1001 };
constexpr int mExit{ 1002 };
constexpr int mSave{ 1003 };
constexpr int mLoad{ 1004 };
constexpr int mHoF{ 1005 };

constexpr int no_record{ 2001 };
constexpr int first_record{ 2002 };
constexpr int record{ 2003 };

WNDCLASS bWinClass{};
HINSTANCE bIns{ nullptr };
HICON mainIcon{ nullptr };
HCURSOR mainCur{ nullptr };
HCURSOR outCur{ nullptr };
HMENU bBar{ nullptr };
HMENU bMain{ nullptr };
HMENU bStore{ nullptr };
HDC PaintDC{ nullptr };
PAINTSTRUCT bPaint{};
POINT cur_pos{};
HWND bHwnd{ nullptr };
MSG bMsg{};
BOOL bRet = 0;

D2D1_RECT_F b1Rect{ 0, 0, scr_width / 3 - 50.0f, 50.0f };
D2D1_RECT_F b2Rect{ scr_width / 3, 0, scr_width * 2 / 3 - 50.0f, 50.0f };
D2D1_RECT_F b3Rect{ scr_width * 2 / 3, 0, scr_width - 50.0f, 50.0f };

D2D1_RECT_F b1TxtRect{ 20.0f, 10.0f, scr_width / 3 - 50.0f, 50.0f };
D2D1_RECT_F b2TxtRect{ scr_width / 3 + 20.0f, 10.0f, scr_width * 2 / 3 - 50.0f, 50.0f };
D2D1_RECT_F b3TxtRect{ scr_width * 2 / 3 + 20.0f, 10.0f, scr_width - 50.0f, 50.0f };

ID2D1Factory* iFactory{ nullptr };
ID2D1HwndRenderTarget* Draw{ nullptr };

ID2D1RadialGradientBrush* butBckgBrush{ nullptr };
ID2D1SolidColorBrush* statBckgBrush{ nullptr };
ID2D1SolidColorBrush* txtBckgBrush{ nullptr };
ID2D1SolidColorBrush* inactBckgBrush{ nullptr };
ID2D1SolidColorBrush* hgltBckgBrush{ nullptr };

IDWriteFactory* iWriteFactory{ nullptr };
IDWriteTextFormat* nrmTxtFormat{ nullptr };
IDWriteTextFormat* midTxtFormat{ nullptr };
IDWriteTextFormat* bigTxtFormat{ nullptr };

ID2D1Bitmap* bmpGdArrow{ nullptr };
ID2D1Bitmap* bmpEvArrow{ nullptr };

ID2D1Bitmap* bmpField1[16]{ nullptr };
ID2D1Bitmap* bmpField2[18]{ nullptr };
ID2D1Bitmap* bmpField3[12]{ nullptr };
ID2D1Bitmap* bmpField4[20]{ nullptr };
ID2D1Bitmap* bmpField5[8]{ nullptr };

ID2D1Bitmap* bmpIntro[8]{ nullptr };
ID2D1Bitmap* bmpFireball[4]{ nullptr };

ID2D1Bitmap* bmpEvArcherL[6]{ nullptr };
ID2D1Bitmap* bmpEvArcherR[6]{ nullptr };
ID2D1Bitmap* bmpEvCoyotteL[26]{ nullptr };
ID2D1Bitmap* bmpEvCoyotteR[26]{ nullptr };
ID2D1Bitmap* bmpEvDragonL[21]{ nullptr };
ID2D1Bitmap* bmpEvDragonR[21]{ nullptr };
ID2D1Bitmap* bmpEvHydraL[12]{ nullptr };
ID2D1Bitmap* bmpEvHydraR[12]{ nullptr };
ID2D1Bitmap* bmpEvMageL[6]{ nullptr };
ID2D1Bitmap* bmpEvMageR[6]{ nullptr };
ID2D1Bitmap* bmpEvMinotaurL[7]{ nullptr };
ID2D1Bitmap* bmpEvMinotaurR[7]{ nullptr };
ID2D1Bitmap* bmpEvWarriorL[8]{ nullptr };
ID2D1Bitmap* bmpEvWarriorR[8]{ nullptr };

ID2D1Bitmap* bmpGdArcherL[42]{ nullptr };
ID2D1Bitmap* bmpGdArcherR[42]{ nullptr };
ID2D1Bitmap* bmpGdHorseL[44]{ nullptr };
ID2D1Bitmap* bmpGdHorseR[44]{ nullptr };
ID2D1Bitmap* bmpGdDragonL[7]{ nullptr };
ID2D1Bitmap* bmpGdDragonR[7]{ nullptr };
ID2D1Bitmap* bmpGdHydraL[60]{ nullptr };
ID2D1Bitmap* bmpGdHydraR[60]{ nullptr };
ID2D1Bitmap* bmpGdUnicornL[20]{ nullptr };
ID2D1Bitmap* bmpGdUnicornR[20]{ nullptr };
ID2D1Bitmap* bmpGdMinotaurL[8]{ nullptr };
ID2D1Bitmap* bmpGdMinotaurR[8]{ nullptr };
ID2D1Bitmap* bmpGdWarriorL[8]{ nullptr };
ID2D1Bitmap* bmpGdWarriorR[8]{ nullptr };

/////////////////////////////////////////////////////

wchar_t current_player[16]{ L"A KING" };

bool pause = false;
bool show_help = false;
bool sound = true;
bool in_client = true;
bool b1Hglt = false;
bool b2Hglt = false;
bool b3Hglt = false;
bool name_set = false;

int score = 0;

//////////////////////////////////////////////////////




//////////////////////////////////////////////////////

template<typename T>concept HasRelease = requires(T var)
{
    var.Release();
};
template<HasRelease U> bool ClearHeap(U** var)
{
    if ((*var))
    {
        (*var)->Release();
        (*var) = nullptr;
        return true;
    }

    return false;
}
void LogError(LPCWSTR what)
{
    std::wofstream err(L".\\res\\data\\error.log", std::ios::app);
    err << what << L" Time stamp: " << std::chrono::system_clock::now();
    err.close();
}
void ClearResources()
{
    if (!ClearHeap(&iFactory))LogError(L"Error releasing iFactory !");
    if (!ClearHeap(&Draw))LogError(L"Error releasing Draw !");
    if (!ClearHeap(&butBckgBrush))LogError(L"Error releasing butBckgBrush !");
    if (!ClearHeap(&statBckgBrush))LogError(L"Error releasing statBckgBrush !");
    if (!ClearHeap(&txtBckgBrush))LogError(L"Error releasing txtBckgBrush !");
    if (!ClearHeap(&inactBckgBrush))LogError(L"Error releasing inactBckgBrush !");
    if (!ClearHeap(&hgltBckgBrush))LogError(L"Error releasing hgltBckgBrush !");

    if (!ClearHeap(&iWriteFactory))LogError(L"Error releasing iWriteFactory !");
    if (!ClearHeap(&nrmTxtFormat))LogError(L"Error releasing nrmTxtFormat !");
    if (!ClearHeap(&midTxtFormat))LogError(L"Error releasing midTxtFormat !");
    if (!ClearHeap(&bigTxtFormat))LogError(L"Error releasing bigTxtFormat !");

    if (!ClearHeap(&bmpEvArrow))LogError(L"Error releasing bmpEvArrow !");
    if (!ClearHeap(&bmpGdArrow))LogError(L"Error releasing bmpGdArrow !");
    for (int i = 0; i < 16; ++i)if (!ClearHeap(&bmpField1[i]))LogError(L"Error releasing bmpField1 !");
    for (int i = 0; i < 18; ++i)if (!ClearHeap(&bmpField2[i]))LogError(L"Error releasing bmpField2 !");
    for (int i = 0; i < 12; ++i)if (!ClearHeap(&bmpField3[i]))LogError(L"Error releasing bmpField3 !");
    for (int i = 0; i < 20; ++i)if (!ClearHeap(&bmpField4[i]))LogError(L"Error releasing bmpField4 !");
    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpField5[i]))LogError(L"Error releasing bmpField5 !");
    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpIntro[i]))LogError(L"Error releasing bmpIntro !");
    for (int i = 0; i < 4; ++i)if (!ClearHeap(&bmpFireball[i]))LogError(L"Error releasing bmpFireBall !");

    for (int i = 0; i < 6; ++i)if (!ClearHeap(&bmpEvArcherL[i]))LogError(L"Error releasing bmpEvArcherL !");
    for (int i = 0; i < 6; ++i)if (!ClearHeap(&bmpEvArcherR[i]))LogError(L"Error releasing bmpEvArcherR !");

    for (int i = 0; i < 26; ++i)if (!ClearHeap(&bmpEvCoyotteL[i]))LogError(L"Error releasing bmpEvCoyotteL !");
    for (int i = 0; i < 26; ++i)if (!ClearHeap(&bmpEvCoyotteR[i]))LogError(L"Error releasing bmpEvCoyotteR !");

    for (int i = 0; i < 21; ++i)if (!ClearHeap(&bmpEvDragonL[i]))LogError(L"Error releasing bmpEvDragonL !");
    for (int i = 0; i < 21; ++i)if (!ClearHeap(&bmpEvDragonR[i]))LogError(L"Error releasing bmpEvDragonR !");

    for (int i = 0; i < 60; ++i)if (!ClearHeap(&bmpEvHydraL[i]))LogError(L"Error releasing bmpEvHydraL !");
    for (int i = 0; i < 60; ++i)if (!ClearHeap(&bmpEvHydraR[i]))LogError(L"Error releasing bmpEvHydraR !");

    for (int i = 0; i < 6; ++i)if (!ClearHeap(&bmpEvMageL[i]))LogError(L"Error releasing bmpEvMageL !");
    for (int i = 0; i < 6; ++i)if (!ClearHeap(&bmpEvMageR[i]))LogError(L"Error releasing bmpEvMageR !");

    for (int i = 0; i < 7; ++i)if (!ClearHeap(&bmpEvMinotaurL[i]))LogError(L"Error releasing bmpEvMinotaurL !");
    for (int i = 0; i < 7; ++i)if (!ClearHeap(&bmpEvMinotaurR[i]))LogError(L"Error releasing bmpEvMinotaurR !");

    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpEvWarriorL[i]))LogError(L"Error releasing bmpEvWarriorL !");
    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpEvWarriorR[i]))LogError(L"Error releasing bmpEvWarriorR !");


    for (int i = 0; i < 42; ++i)if (!ClearHeap(&bmpGdArcherL[i]))LogError(L"Error releasing bmpGdArcherL !");
    for (int i = 0; i < 42; ++i)if (!ClearHeap(&bmpGdArcherR[i]))LogError(L"Error releasing bmpGdArcherR !");

    for (int i = 0; i < 44; ++i)if (!ClearHeap(&bmpGdHorseL[i]))LogError(L"Error releasing bmpGdHorseL !");
    for (int i = 0; i < 44; ++i)if (!ClearHeap(&bmpGdHorseR[i]))LogError(L"Error releasing bmpGdHorseR !");

    for (int i = 0; i < 7; ++i)if (!ClearHeap(&bmpGdDragonL[i]))LogError(L"Error releasing bmpGdDragonL !");
    for (int i = 0; i < 7; ++i)if (!ClearHeap(&bmpGdDragonR[i]))LogError(L"Error releasing bmpGdDragonR !");

    for (int i = 0; i < 60; ++i)if (!ClearHeap(&bmpGdHydraL[i]))LogError(L"Error releasing bmpGdHydraL !");
    for (int i = 0; i < 60; ++i)if (!ClearHeap(&bmpGdHydraR[i]))LogError(L"Error releasing bmpGdHydraR !");

    for (int i = 0; i < 20; ++i)if (!ClearHeap(&bmpGdUnicornL[i]))LogError(L"Error releasing bmpGdUnicornL !");
    for (int i = 0; i < 20; ++i)if (!ClearHeap(&bmpGdUnicornR[i]))LogError(L"Error releasing bmpGdUnicornR !");

    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpGdMinotaurL[i]))LogError(L"Error releasing bmpGdMinotaurL !");
    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpGdMinotaurR[i]))LogError(L"Error releasing bmpGdMinotaurR !");

    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpGdWarriorL[i]))LogError(L"Error releasing bmpGdWarriorL !");
    for (int i = 0; i < 8; ++i)if (!ClearHeap(&bmpGdWarriorR[i]))LogError(L"Error releasing bmpGdWarriorR !");
}
void ErrExit(int what)
{
    MessageBeep(MB_ICONERROR);

    MessageBox(NULL, ErrHandle(what), L"Критична грешка !", MB_OK | MB_APPLMODAL | MB_ICONERROR);

    std::remove(tmp_file);
    ClearResources();
    exit(1);
}

void GameOver()
{
    PlaySound(NULL, NULL, NULL);



    bMsg.message = WM_QUIT;
    bMsg.wParam = 0;
}
void InitGame()
{
    wcscpy_s(current_player, L"A KING");
    name_set = false;
    score = 0;





}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
    switch (ReceivedMsg)
    {
    case WM_INITDIALOG:
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)(mainIcon));
        return true;

    case WM_CLOSE:
        EndDialog(hwnd, IDCANCEL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;

        case IDOK:
            if (GetDlgItemText(hwnd, IDC_NAME, current_player, 16) < 1)
            {
                name_set = false;
                wcscpy_s(current_player, L"A KING");
                if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
                MessageBox(bHwnd, L"Ха, ха, ха, забрави си името !\n\nЗабраватор !", L"Кой бях аз ?",
                    MB_OK | MB_APPLMODAL | MB_ICONEXCLAMATION);
                EndDialog(hwnd, IDCANCEL);
                break;
            }
            EndDialog(hwnd, IDOK);
            break;
        }
        break;
    }

    return (INT_PTR)(FALSE);
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    bIns = hInstance;
    if (!bIns)
    {
        LogError(L"Error obtaining Windows hInstance !");
        ErrExit(eClass);
    }











    ClearResources();
    std::remove(tmp_file);

    return (int) bMsg.wParam;
}