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

ID2D1RadialGradientBrush* but1BckgBrush{ nullptr };
ID2D1RadialGradientBrush* but2BckgBrush{ nullptr };
ID2D1RadialGradientBrush* but3BckgBrush{ nullptr };
ID2D1SolidColorBrush* statBckgBrush{ nullptr };
ID2D1SolidColorBrush* txtBrush{ nullptr };
ID2D1SolidColorBrush* inactBrush{ nullptr };
ID2D1SolidColorBrush* hgltBrush{ nullptr };

IDWriteFactory* iWriteFactory{ nullptr };
IDWriteTextFormat* nrmTxtFormat{ nullptr };
IDWriteTextFormat* midTxtFormat{ nullptr };
IDWriteTextFormat* bigTxtFormat{ nullptr };

ID2D1Bitmap* bmpGdArrowLD{ nullptr };
ID2D1Bitmap* bmpGdArrowLU{ nullptr };
ID2D1Bitmap* bmpGdArrowRD{ nullptr };
ID2D1Bitmap* bmpGdArrowRU{ nullptr };

ID2D1Bitmap* bmpEvArrowLD{ nullptr };
ID2D1Bitmap* bmpEvArrowLU{ nullptr };
ID2D1Bitmap* bmpEvArrowRD{ nullptr };
ID2D1Bitmap* bmpEvArrowRU{ nullptr };

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
    if (!ClearHeap(&but1BckgBrush))LogError(L"Error releasing butBckgBrush !");
    if (!ClearHeap(&but2BckgBrush))LogError(L"Error releasing butBckgBrush !");
    if (!ClearHeap(&but3BckgBrush))LogError(L"Error releasing butBckgBrush !");
    if (!ClearHeap(&statBckgBrush))LogError(L"Error releasing statBckgBrush !");
    if (!ClearHeap(&txtBrush))LogError(L"Error releasing txtBckgBrush !");
    if (!ClearHeap(&inactBrush))LogError(L"Error releasing inactBckgBrush !");
    if (!ClearHeap(&hgltBrush))LogError(L"Error releasing hgltBckgBrush !");

    if (!ClearHeap(&iWriteFactory))LogError(L"Error releasing iWriteFactory !");
    if (!ClearHeap(&nrmTxtFormat))LogError(L"Error releasing nrmTxtFormat !");
    if (!ClearHeap(&midTxtFormat))LogError(L"Error releasing midTxtFormat !");
    if (!ClearHeap(&bigTxtFormat))LogError(L"Error releasing bigTxtFormat !");

    if (!ClearHeap(&bmpEvArrowLU))LogError(L"Error releasing bmpEvArrowLU !");
    if (!ClearHeap(&bmpEvArrowLD))LogError(L"Error releasing bmpEvArrowLD !");
    if (!ClearHeap(&bmpEvArrowRU))LogError(L"Error releasing bmpEvArrowRU !");
    if (!ClearHeap(&bmpEvArrowRD))LogError(L"Error releasing bmpEvArrowRD !");
    
    if (!ClearHeap(&bmpGdArrowLU))LogError(L"Error releasing bmpGdArrowLU !");
    if (!ClearHeap(&bmpGdArrowLD))LogError(L"Error releasing bmpGdArrowLD !");
    if (!ClearHeap(&bmpGdArrowRU))LogError(L"Error releasing bmpGdArrowRU !");
    if (!ClearHeap(&bmpGdArrowRD))LogError(L"Error releasing bmpGdArrowRD !");
    
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
LRESULT CALLBACK WinProc(HWND hwnd, UINT ReceivedMsg, WPARAM wParam, LPARAM lParam)
{
    switch (ReceivedMsg)
    {
    case WM_CREATE:
        if (bIns)
        {
            bBar = CreateMenu();
            bMain = CreateMenu();
            bStore = CreateMenu();

            AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bMain), L"Основно меню");
            AppendMenu(bBar, MF_POPUP, (UINT_PTR)(bStore), L"Меню за данни");

            AppendMenu(bMain, MF_STRING, mNew, L"Нова игра");
            AppendMenu(bMain, MF_SEPARATOR, NULL, NULL);
            AppendMenu(bMain, MF_STRING, mExit, L"Изход");

            AppendMenu(bStore, MF_STRING, mSave, L"Запази игра");
            AppendMenu(bStore, MF_STRING, mLoad, L"Зареди игра");
            AppendMenu(bStore, MF_SEPARATOR, NULL, NULL);
            AppendMenu(bStore, MF_STRING, mHoF, L"Зала на славата");
  
            SetMenu(hwnd, bBar);
            InitGame();
        }
        break;

    case WM_CLOSE:
        pause = true;
        if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
        if (MessageBox(hwnd, L"Ако излезеш, губиш прогреса по играта !\n\nНаистина ли излизаш ?",
            L"Изход", MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
        {
            pause = false;
            break;
        }
        GameOver();
        break;

    case WM_PAINT:
        PaintDC = BeginPaint(hwnd, &bPaint);
        FillRect(PaintDC, &bPaint.rcPaint, CreateSolidBrush(RGB(0, 0, 100)));
        EndPaint(hwnd, &bPaint);
        break;

    case WM_SETCURSOR:
        GetCursorPos(&cur_pos);
        ScreenToClient(hwnd, &cur_pos);
        if (LOWORD(lParam) == HTCLIENT)
        {
            if (!in_client)
            {
                in_client = true;
                pause = false;
            }

            if (cur_pos.y <= 50)
            {
                if (cur_pos.x >= b1Rect.left && cur_pos.x <= b1Rect.right)
                {
                    if (!b1Hglt)
                    {
                        if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
                        b1Hglt = true;
                        b2Hglt = false;
                        b3Hglt = false;
                    }
                }
                if (cur_pos.x >= b2Rect.left && cur_pos.x <= b2Rect.right)
                {
                    if (!b2Hglt)
                    {
                        if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
                        b1Hglt = false;
                        b2Hglt = true;
                        b3Hglt = false;
                    }
                }
                if (cur_pos.x >= b3Rect.left && cur_pos.x <= b3Rect.right)
                {
                    if (!b3Hglt)
                    {
                        if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
                        b1Hglt = false;
                        b2Hglt = false;
                        b3Hglt = true;
                    }
                }

                SetCursor(outCur);
                return true;
            }
            else if (b1Hglt || b2Hglt || b3Hglt)
            {
                if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
                b1Hglt = false;
                b2Hglt = false;
                b3Hglt = false;
            }

            SetCursor(mainCur);
            return true;
        }
        else
        {
            if (in_client)
            {
                in_client = false;
                pause = true;
            }

            if (b1Hglt || b2Hglt || b3Hglt)
            {
                if (sound)mciSendString(L"play .\\res\\snd\\click.wav", NULL, NULL, NULL);
                b1Hglt = false;
                b2Hglt = false;
                b3Hglt = false;
            }

            SetCursor(LoadCursor(NULL, IDC_ARROW));
            return true;
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case mNew:
            pause = true;
            if (sound)mciSendString(L"play .\\res\\snd\\exclamation.wav", NULL, NULL, NULL);
            if (MessageBox(hwnd, L"Ако рестартираш, губиш прогреса по играта !\n\nНаистина ли рестартираш ?",
                L"Рестарт", MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION) == IDNO)
            {
                pause = false;
                break;
            }
            InitGame();
            break;

        case mExit:
            SendMessage(hwnd, WM_CLOSE, NULL, NULL);
            break;


        }
        break;

    case WM_LBUTTONDOWN:
        if (HIWORD(lParam) <= 50)
        {
            if (LOWORD(lParam) >= b1Rect.left && LOWORD(lParam) <= b1Rect.right)
            {
                if (sound)mciSendString(L"play .\\res\\snd\\selelct.wav", NULL, NULL, NULL);
                pause = true;
                if (DialogBox(bIns, MAKEINTRESOURCE(IDD_PLAYER), hwnd, &DlgProc) == IDOK)name_set = true;
                pause = false;
                break;
            }
            if (LOWORD(lParam) >= b2Rect.left && LOWORD(lParam) <= b2Rect.right)
            {
                mciSendString(L"play .\\res\\snd\\selelct.wav", NULL, NULL, NULL);
                if (sound)
                {
                    sound = false;
                    PlaySound(NULL, NULL, NULL);
                    break;
                }
                else
                {
                    sound = true;
                    PlaySound(snd_file, NULL, SND_ASYNC | SND_LOOP);
                    break;
                }
            }
        }
        else
        {

        }
        break;


    default: return DefWindowProc(hwnd, ReceivedMsg, wParam, lParam);
    }



    return (LRESULT)(FALSE);
}

void CreateResources()
{
    int result{ 0 };
    CheckFile(Ltmp_file, &result);

    if (result == FILE_EXIST)ErrExit(eStarted);
    else
    {
        std::wofstream start(tmp_file);
        start << L"Game started at: " << std::chrono::system_clock::now();
        start.close();
    }

    int win_x = GetSystemMetrics(SM_CXSCREEN) / 2 - (int)(scr_width / 2);
    int win_y = 10;

    if (GetSystemMetrics(SM_CXSCREEN) < win_x + (int)(scr_width) || GetSystemMetrics(SM_CYSCREEN) < win_y + (int)(scr_height))
        ErrExit(eScreen);
    
    mainIcon = (HICON)(LoadImage(NULL, L".\\res\\main.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE));
    if (!mainIcon)ErrExit(eIcon);

    mainCur = LoadCursorFromFile(L".\\res\\main.ani");
    outCur = LoadCursorFromFile(L".\\res\\out.ani");
    if (!mainCur || !outCur)ErrExit(eCursor);

    bWinClass.lpszClassName = bWinClassName;
    bWinClass.hInstance = bIns;
    bWinClass.lpfnWndProc = &WinProc;
    bWinClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 100));
    bWinClass.hIcon = mainIcon;
    bWinClass.hCursor = mainCur;
    bWinClass.style = CS_DROPSHADOW;

    if (!RegisterClass(&bWinClass))ErrExit(eClass);

    bHwnd = CreateWindow(bWinClassName, L"ФАНТАСТИЧНА БИТКА", WS_CAPTION | WS_SYSMENU, win_x, win_y, (int)(scr_width),
        (int)(scr_height), NULL, NULL, bIns, NULL);
    if (!bHwnd)ErrExit(eWindow);
    else
    {
        ShowWindow(bHwnd, SW_SHOWDEFAULT);

        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &iFactory);
        if (hr != S_OK)
        {
            LogError(L"Error creating iFactory !");
            ErrExit(eD2D);
        }

        if (iFactory)
        {
            hr = iFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(bHwnd,
                D2D1::SizeU((UINT32)(scr_width), (UINT32)(scr_height))), &Draw);
            if (hr != S_OK)
            {
                LogError(L"Error creating D2D1 HwndRenderTarget !");
                ErrExit(eD2D);
            }

            if (Draw)
            {
                D2D1_GRADIENT_STOP stops[2]{};
                ID2D1GradientStopCollection* Coll{ nullptr };

                stops[0].position = 0;
                stops[0].color = D2D1::ColorF(D2D1::ColorF::DarkOrange);
                stops[1].position = 1.0;
                stops[1].color = D2D1::ColorF(D2D1::ColorF::SaddleBrown);

                Draw->CreateGradientStopCollection(stops, 2, &Coll);

                if (hr != S_OK)
                {
                    LogError(L"Error creating D2D1 GradientStopsCollection !");
                    ErrExit(eD2D);
                }

                if (Coll)
                {
                    hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b1Rect.right
                        - b1Rect.left) / 2, 25.0f), D2D1::Point2F(0, 0), (b1Rect.right - b1Rect.left) / 2, 25.0f),
                        Coll, &but1BckgBrush);
                    hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b2Rect.right
                        - b2Rect.left) / 2, 25.0f), D2D1::Point2F(0, 0), (b2Rect.right - b2Rect.left) / 2, 25.0f),
                        Coll, &but2BckgBrush);
                    hr = Draw->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F((b3Rect.right
                        - b3Rect.left) / 2, 25.0f), D2D1::Point2F(0, 0), (b3Rect.right - b3Rect.left) / 2, 25.0f),
                        Coll, &but3BckgBrush);
                    if (hr != S_OK)
                    {
                        LogError(L"Error creating D2D1 Buttons backgrounds !");
                        ErrExit(eD2D);
                    }

                    ClearHeap(&Coll);
                }

                hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkCyan), &statBckgBrush);
                hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::ForestGreen), &txtBrush);
                hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::IndianRed), &hgltBrush);
                hr = Draw->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &inactBrush);

                if (hr != S_OK)
                {
                    LogError(L"Error creating D2D1 text and status brushes !");
                    ErrExit(eD2D);
                }

                bmpGdArrowLU = Load(L".\\res\\img\\good\\arrow\\l\\up.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpGdArrowLU !");
                    ErrExit(eD2D);
                }
                bmpGdArrowRU = Load(L".\\res\\img\\good\\arrow\\r\\up.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpGdArrowRU !");
                    ErrExit(eD2D);
                }
                bmpGdArrowLD = Load(L".\\res\\img\\good\\arrow\\l\\down.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpGdArrowDL !");
                    ErrExit(eD2D);
                }
                bmpGdArrowRD = Load(L".\\res\\img\\good\\arrow\\r\\down.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpGdArrowRD !");
                    ErrExit(eD2D);
                }

                bmpEvArrowLU = Load(L".\\res\\img\\evil\\arrow\\l\\up.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpEvArrowLU !");
                    ErrExit(eD2D);
                }
                bmpEvArrowRU = Load(L".\\res\\img\\evil\\arrow\\r\\up.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpEvArrowRU !");
                    ErrExit(eD2D);
                }
                bmpEvArrowLD = Load(L".\\res\\img\\evil\\arrow\\l\\down.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpEvArrowDL !");
                    ErrExit(eD2D);
                }
                bmpEvArrowRD = Load(L".\\res\\img\\evil\\arrow\\r\\down.png", Draw);
                if (hr != S_OK)
                {
                    LogError(L"Error loading bmpEvArrowRD !");
                    ErrExit(eD2D);
                }

                for (int i = 0; i < 16; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\field1\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpField1[i] = Load(name, Draw);
                    if (!bmpField1[i])
                    {
                        LogError(L"Error loading bmpField1 !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 18; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\field2\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpField2[i] = Load(name, Draw);
                    if (!bmpField2[i])
                    {
                        LogError(L"Error loading bmpField2 !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 12; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\field3\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpField3[i] = Load(name, Draw);
                    if (!bmpField3[i])
                    {
                        LogError(L"Error loading bmpField3 !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 20; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\field4\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpField4[i] = Load(name, Draw);
                    if (!bmpField4[i])
                    {
                        LogError(L"Error loading bmpField4 !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\field5\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpField5[i] = Load(name, Draw);
                    if (!bmpField5[i])
                    {
                        LogError(L"Error loading bmpField5 !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\intro\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");
                   
                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpIntro[i] = Load(name, Draw);
                    if (!bmpIntro[i])
                    {
                        LogError(L"Error loading bmpIntro !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 4; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\assets\\fireball\\";
                    wchar_t add[5] = L"\0";

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpFireball[i] = Load(name, Draw);
                    if (!bmpFireball[i])
                    {
                        LogError(L"Error loading bmpFireball !");
                        ErrExit(eD2D);
                    }
                }

                // EVILS ****************************

                for (int i = 0; i < 6; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\archer\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");
                    
                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvArcherL[i] = Load(name, Draw);
                    if (!bmpEvArcherL[i])
                    {
                        LogError(L"Error loading bmpEvArcherL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 6; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\archer\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvArcherR[i] = Load(name, Draw);
                    if (!bmpEvArcherR[i])
                    {
                        LogError(L"Error loading bmpEvArcherR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 26; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\coyotte\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvCoyotteL[i] = Load(name, Draw);
                    if (!bmpEvCoyotteL[i])
                    {
                        LogError(L"Error loading bmpEvCoyotteL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 26; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\coyotte\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvCoyotteR[i] = Load(name, Draw);
                    if (!bmpEvCoyotteR[i])
                    {
                        LogError(L"Error loading bmpEvCoyotteR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 21; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\dragon\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvDragonL[i] = Load(name, Draw);
                    if (!bmpEvDragonL[i])
                    {
                        LogError(L"Error loading bmpEvDragonL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 21; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\dragon\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvDragonR[i] = Load(name, Draw);
                    if (!bmpEvDragonR[i])
                    {
                        LogError(L"Error loading bmpEvDragonR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 12; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\hydra\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvHydraL[i] = Load(name, Draw);
                    if (!bmpEvHydraL[i])
                    {
                        LogError(L"Error loading bmpEvHydraL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 12; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\hydra\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvHydraR[i] = Load(name, Draw);
                    if (!bmpEvHydraR[i])
                    {
                        LogError(L"Error loading bmpEvHydraR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 6; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\mage\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");
                    
                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvMageL[i] = Load(name, Draw);
                    if (!bmpEvMageL[i])
                    {
                        LogError(L"Error loading bmpEvMageL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 6; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\mage\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvMageR[i] = Load(name, Draw);
                    if (!bmpEvMageR[i])
                    {
                        LogError(L"Error loading bmpEvMageR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 7; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\minotaur\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvMinotaurL[i] = Load(name, Draw);
                    if (!bmpEvMinotaurL[i])
                    {
                        LogError(L"Error loading bmpEvMinotaurL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 7; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\minotaur\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvMinotaurR[i] = Load(name, Draw);
                    if (!bmpEvMinotaurR[i])
                    {
                        LogError(L"Error loading bmpEvMinotaurR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 8; ++i)                {
                    wchar_t name[200] = L".\\res\\img\\evil\\warrior\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvWarriorL[i] = Load(name, Draw);
                    if (!bmpEvWarriorL[i])
                    {
                        LogError(L"Error loading bmpEvWarriorL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 8; ++i) 
                {
                    wchar_t name[200] = L".\\res\\img\\evil\\warrior\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpEvWarriorR[i] = Load(name, Draw);
                    if (!bmpEvWarriorR[i])
                    {
                        LogError(L"Error loading bmpEvWarriorR !");
                        ErrExit(eD2D);
                    }
                }

                /////////////////////////////////////

                for (int i = 0; i < 42; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\archer\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdArcherL[i] = Load(name, Draw);
                    if (!bmpGdArcherL[i])
                    {
                        LogError(L"Error loading bmpGdArcherL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 42; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\archer\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdArcherR[i] = Load(name, Draw);
                    if (!bmpGdArcherR[i])
                    {
                        LogError(L"Error loading bmpGdArcherR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 44; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\horse\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdHorseL[i] = Load(name, Draw);
                    if (!bmpGdHorseL[i])
                    {
                        LogError(L"Error loading bmpGdHorseL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 44; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\horse\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdHorseR[i] = Load(name, Draw);
                    if (!bmpGdHorseR[i])
                    {
                        LogError(L"Error loading bmpGdHorseR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 7; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\dragon\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");
                    
                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdDragonL[i] = Load(name, Draw);
                    if (!bmpGdDragonL[i])
                    {
                        LogError(L"Error loading bmpGdDragonL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 7; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\dragon\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdDragonR[i] = Load(name, Draw);
                    if (!bmpGdDragonR[i])
                    {
                        LogError(L"Error loading bmpGdDragonR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 60; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\hydra\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdHydraL[i] = Load(name, Draw);
                    if (!bmpGdHydraL[i])
                    {
                        LogError(L"Error loading bmpGdHydraL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 60; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\hydra\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdHydraR[i] = Load(name, Draw);
                    if (!bmpGdHydraR[i])
                    {
                        LogError(L"Error loading bmpGdHydraR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 20; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\unicorn\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdUnicornL[i] = Load(name, Draw);
                    if (!bmpGdUnicornL[i])
                    {
                        LogError(L"Error loading bmpGdUnicornL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 20; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\unicorn\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"00");
                    else wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdUnicornR[i] = Load(name, Draw);
                    if (!bmpGdUnicornR[i])
                    {
                        LogError(L"Error loading bmpGdUnicornR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\minotaur\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdMinotaurL[i] = Load(name, Draw);
                    if (!bmpGdMinotaurL[i])
                    {
                        LogError(L"Error loading bmpGdMinotaurL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\minotaur\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdMinotaurR[i] = Load(name, Draw);
                    if (!bmpGdMinotaurR[i])
                    {
                        LogError(L"Error loading bmpGdMinotaurR !");
                        ErrExit(eD2D);
                    }
                }

                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\warrior\\l\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdWarriorL[i] = Load(name, Draw);
                    if (!bmpGdWarriorL[i])
                    {
                        LogError(L"Error loading bmpGdWarriorL !");
                        ErrExit(eD2D);
                    }
                }
                for (int i = 0; i < 8; ++i)
                {
                    wchar_t name[200] = L".\\res\\img\\good\\warrior\\r\\";
                    wchar_t add[5] = L"\0";

                    if (i < 10)wcscat_s(name, L"0");

                    wsprintf(add, L"%d", i);
                    wcscat_s(name, add);
                    wcscat_s(name, L".png");

                    bmpGdWarriorR[i] = Load(name, Draw);
                    if (!bmpGdWarriorR[i])
                    {
                        LogError(L"Error loading bmpGdWarriorR !");
                        ErrExit(eD2D);
                    }
                }
            }
        }

        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&iWriteFactory));

        if (hr != S_OK)
        {
            LogError(L"Error creating iWriteFactory !");
            ErrExit(eD2D);
        }
        
        if (iWriteFactory)
        {
            hr = iWriteFactory->CreateTextFormat(L"SEGOE PRINT", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK, DWRITE_FONT_STYLE_OBLIQUE,
                DWRITE_FONT_STRETCH_NORMAL, 16.0f, L"", &nrmTxtFormat);
            hr = iWriteFactory->CreateTextFormat(L"SEGOE PRINT", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK, DWRITE_FONT_STYLE_OBLIQUE,
                DWRITE_FONT_STRETCH_NORMAL, 28.0f, L"", &midTxtFormat);
            hr = iWriteFactory->CreateTextFormat(L"SEGOE PRINT", NULL, DWRITE_FONT_WEIGHT_EXTRA_BLACK, DWRITE_FONT_STYLE_OBLIQUE,
                DWRITE_FONT_STRETCH_NORMAL, 72.0f, L"", &bigTxtFormat);
        
            if (hr != S_OK)
            {
                LogError(L"Error creating D2D1 text formats !");
                ErrExit(eD2D);
            }
        }
    }










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