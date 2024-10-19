#include "../h/Gui.h"
#include <windowsx.h>
#include <dwmapi.h>

typedef BOOL(WINAPI*destroyWindow)(HWND);
typedef HRESULT(WINAPI* dwmSetWindowAttribute)(HWND, DWORD, LPCVOID, DWORD);
typedef BOOL(WINAPI* postQuitMessage)(int);
typedef BOOL(WINAPI* setCursor)(HCURSOR);
typedef HDC(WINAPI* beginPaint)(HWND, LPPAINTSTRUCT);
typedef HBRUSH(WINAPI* createSolidBrush)(COLORREF);
typedef BOOL(WINAPI* fillRect)(HDC, const RECT*, HBRUSH);
typedef BOOL(WINAPI* deleteObject)(HGDIOBJ);
typedef BOOL(WINAPI* endPaint)(HWND, const PAINTSTRUCT*);
typedef BOOL(WINAPI* registerClassW)(const WNDCLASSW*);
typedef HWND(WINAPI* createWindowExW)(
    DWORD    dwExStyle,
    LPCWSTR  lpClassName,
    LPCWSTR  lpWindowName,
    DWORD    dwStyle,
    int      nWndX,
    int      nWndY,
    int      nWidth,
    int      nHeight,
    HWND     hWndParent,
    HMENU    hMenu,
    HINSTANCE hInstance,
    LPVOID   lpParam
    );
typedef BOOL(WINAPI* addFontResourceExW)(LPCWSTR, DWORD, PVOID);
typedef LRESULT(WINAPI* sendMessageW)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL(WINAPI* showWindow)(HWND, int);
typedef BOOL(WINAPI* updateWindow)(HWND);
typedef BOOL(WINAPI* setWindowTextW)(HWND, LPCWSTR);
typedef BOOL(WINAPI* isWindow)(HWND);
typedef LONG_PTR(WINAPI* getWindowLongW)(HWND, int);
typedef LONG_PTR(WINAPI* setWindowLongW)(HWND, int, LONG_PTR);
typedef BOOL(WINAPI* setWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X,  int Y, int cx, int cy, UINT uFlags);
typedef LRESULT(WINAPI* getMessageW)(
    LPMSG lpMsg,
    HWND hWnd,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax);
typedef BOOL(WINAPI* translateMessage)(const MSG*);
typedef LRESULT(WINAPI* dispatchMessageW)(const MSG*);
typedef BOOL(WINAPI* isWindowVisible)(HWND);
typedef BOOL(WINAPI* isIconic)(HWND);
typedef BOOL(WINAPI* getClientRect)(HWND, LPRECT);
typedef HCURSOR(WINAPI* loadCursorW)(HINSTANCE, LPCWSTR);
typedef int(WINAPI* getWindowTextLengthW)(HWND);
typedef BOOL(WINAPI* getWindowTextW)(HWND, LPWSTR, int);
typedef HMENU(WINAPI* getMenu)(HWND);
typedef HBITMAP(WINAPI* loadImageW)(HINSTANCE, LPCWSTR, UINT, int, int, UINT);
typedef HFONT(WINAPI* createFontW)( int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic,
    DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision,
    DWORD iQuality, DWORD iPitchAndFamily, LPCWSTR pszFaceName);
typedef LRESULT(WINAPI* defWindowProcW)(HWND, UINT, WPARAM, LPARAM);
typedef void(WINAPI* screenToClient)(HWND, LPPOINT);
typedef HWND(WINAPI* windowFromPoint)(POINT);
static destroyWindow DestroyWindow_;
static dwmSetWindowAttribute DwmSetWindowAttribute_;
static postQuitMessage PostQuitMessage_;
static setCursor SetCursor_;
static beginPaint BeginPaint_;
static createSolidBrush CreateSolidBrush_;
static fillRect FillRect_;
static deleteObject DeleteObject_;
static endPaint EndPaint_;
static registerClassW RegisterClassW_;
static createWindowExW CreateWindowExW_;
static addFontResourceExW AddFontResourceExW_;
static sendMessageW SendMessageW_;
static showWindow ShowWindow_;
static updateWindow UpdateWindow_;
static setWindowTextW SetWindowTextW_;
static isWindow IsWindow_;
static getWindowLongW GetWindowLongW_;
static setWindowLongW SetWindowLongW_;
static setWindowPos SetWindowPos_;
static getMessageW GetMessageW_;
static translateMessage TranslateMessage_;
static dispatchMessageW DispatchMessageW_;
static isWindowVisible IsWindowVisible_;
static isIconic IsIconic_;
static getClientRect GetClientRect_;
static loadCursorW LoadCursorW_;
static getWindowTextLengthW GetWindowTextLengthW_;
static getWindowTextW GetWindowTextW_;
static getMenu GetMenu_;
static loadImageW LoadImageW_;
static createFontW CreateFontW_;
static defWindowProcW DefWindowProcW_;
static screenToClient ScreenToClient_;
static windowFromPoint WindowFromPoint_;
Gui::WinGui::WinGui()
{
    const HMODULE user32 = LoadLibraryA("USER32.dll");
    const HMODULE dwmapi = LoadLibraryA("dwmapi.dll");
    const HMODULE gdi32 = LoadLibraryA("GDI32.dll");
    DestroyWindow_ = (destroyWindow)GetProcAddress(user32, "DestroyWindow");
    DwmSetWindowAttribute_ = (dwmSetWindowAttribute)GetProcAddress(dwmapi, "DwmSetWindowAttribute");
    PostQuitMessage_ = (postQuitMessage)GetProcAddress(user32, "PostQuitMessage");
    SetCursor_ = (setCursor)GetProcAddress(user32, "SetCursor");
    BeginPaint_ = (beginPaint)GetProcAddress(user32, "BeginPaint");
    CreateSolidBrush_ = (createSolidBrush)GetProcAddress(gdi32, "CreateSolidBrush");
    FillRect_ = (fillRect)GetProcAddress(user32, "FillRect");
    DeleteObject_ = (deleteObject)GetProcAddress(gdi32, "DeleteObject");
    EndPaint_ = (endPaint)GetProcAddress(user32, "EndPaint");
    RegisterClassW_ = (registerClassW)GetProcAddress(user32, "RegisterClassW");
    CreateWindowExW_ = (createWindowExW)GetProcAddress(user32, "CreateWindowExW");
    AddFontResourceExW_ = (addFontResourceExW)GetProcAddress(gdi32, "AddFontResourceExW");
    SendMessageW_ = (sendMessageW)GetProcAddress(user32, "SendMessageW");
    ShowWindow_ = (showWindow)GetProcAddress(user32, "ShowWindow");
    UpdateWindow_ = (updateWindow)GetProcAddress(user32, "UpdateWindow");
    IsWindow_ = (isWindow)GetProcAddress(user32, "IsWindow");
    SetWindowTextW_ = (setWindowTextW)GetProcAddress(user32, "SetWindowTextW");
#ifdef _WIN64
    GetWindowLongW_ = (getWindowLongW)GetProcAddress(user32, "GetWindowLongPtrW");
    SetWindowLongW_ = (setWindowLongW)GetProcAddress(user32, "SetWindowLongPtrW");
#else
    GetWindowLongW_ = (getWindowLongW)GetProcAddress(user32, "GetWindowLongW");
    SetWindowLongW_ = (setWindowLongW)GetProcAddress(user32, "SetWindowLongW");
#endif
    SetWindowPos_ = (setWindowPos)GetProcAddress(user32, "SetWindowPos");
    GetMessageW_ = (getMessageW)GetProcAddress(user32, "GetMessageW");
    TranslateMessage_ = (translateMessage)GetProcAddress(user32, "TranslateMessage");
    DispatchMessageW_ = (dispatchMessageW)GetProcAddress(user32, "DispatchMessageW");
    IsWindowVisible_ = (isWindowVisible)GetProcAddress(user32, "IsWindowVisible");
    IsIconic_ = (isIconic)GetProcAddress(user32, "IsIconic");
    GetClientRect_ = (getClientRect)GetProcAddress(user32, "GetClientRect");
    LoadCursorW_ = (loadCursorW)GetProcAddress(user32, "LoadCursorW");
    GetWindowTextLengthW_ = (getWindowTextLengthW)GetProcAddress(user32, "GetWindowTextLengthW");
    GetWindowTextW_ = (getWindowTextW)GetProcAddress(user32, "GetWindowTextW");
    GetMenu_ = (getMenu)GetProcAddress(user32, "GetMenu");
    LoadImageW_   = (loadImageW)GetProcAddress(user32, "LoadImageW");
    CreateFontW_ =  (createFontW)GetProcAddress(gdi32, "CreateFontW");
    DefWindowProcW_ = (defWindowProcW)GetProcAddress(user32, "DefWindowProcW");
    ScreenToClient_ = (screenToClient)GetProcAddress(user32, "ScreenToClient");
    WindowFromPoint_ = (windowFromPoint)GetProcAddress(user32, "WindowFromPoint");
}
Gui::WinGui::~WinGui() {
    for (const auto& winInfo : winList) {
        if (winInfo.hwnd) {
            DestroyWindow_(winInfo.hwnd);
        }
    }
    winList.clear();
}

LRESULT CALLBACK Gui::WinGui::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_NCCREATE: {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        WinGui* gui = reinterpret_cast<WinGui*>(pCreate->lpCreateParams);
        SetWindowLongW_(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(gui));
        return TRUE;
    }
    case WM_DESTROY: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        if (gui && hwnd == gui->mainHwnd) {
            PostQuitMessage_(0);
        }
        return 0;
    }
    case WM_SETCURSOR: {
        if (LOWORD(lParam) == HTCLIENT) {
            SetCursor_(LoadCursorW_(NULL, IDC_ARROW));
            return TRUE;
        }
        break;
    }
    case WM_PAINT: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint_(hwnd, &ps);
        HBRUSH brush = CreateSolidBrush_(gui->getWinInfo(hwnd).bgColor);
        FillRect_(hdc, &ps.rcPaint, brush);
        DeleteObject_(brush);
        EndPaint_(hwnd, &ps);
        break;
    }
    case WM_COMMAND: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (HIWORD(wParam) == EN_CHANGE) {
            int length = GetWindowTextLengthW_(info.hwnd);
            if (length > 0) {
                std::wstring buffer(length, L'\0');
                GetWindowTextW_(info.hwnd, &buffer[0], length + 1);
                info.text->assign(buffer);
            }
            else {
                info.text->clear();
            }
        }else if (info.event.onClick) {
            info.event.onClick(hwnd);
        }
        break;
    }
    case WM_RBUTTONDOWN: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onRightClick) {
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            HWND hClickedChild = WindowFromPoint_(pt);
            ScreenToClient_(hwnd, &pt);
            info.event.onRightClick(hwnd, pt.x, pt.y);
        }
        break;
    }
    case WM_LBUTTONDBLCLK: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onDoubleClick) {
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            HWND hClickedChild = WindowFromPoint_(pt);
            ScreenToClient_(hwnd, &pt);
            info.event.onDoubleClick(hwnd, pt.x, pt.y);
        }
        break;
    }
    case WM_MOUSEHOVER: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onHover) {
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            HWND hClickedChild = WindowFromPoint_(pt);
            ScreenToClient_(hwnd, &pt);
            info.event.onHover(hwnd, pt.x, pt.y);
        }
        break;
    }
    case WM_MOUSELEAVE: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onMouseLeave) {
            info.event.onMouseLeave(hwnd);
        }
        break;
    }
    case WM_MOUSEMOVE: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onMouseMove) {
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            HWND hClickedChild = WindowFromPoint_(pt);
            ScreenToClient_(hwnd, &pt);
            info.event.onMouseMove(hwnd, pt.x, pt.y);
        }
        break;
    }
    case WM_KEYDOWN: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onKeyDown) {
            info.event.onKeyDown(hwnd, (unsigned char)wParam);
        }
        break;
    }
    case WM_KEYUP: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onKeyUp) {
            info.event.onKeyUp(hwnd, (unsigned char)wParam);
        }
        break;
    }
    case WM_ACTIVATE: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onFocusGain) {
            info.event.onFocusGain(hwnd);
        }
        break;
    }
    case WM_KILLFOCUS: {
        WinGui* gui = reinterpret_cast<WinGui*>(GetWindowLongW_(hwnd, GWLP_USERDATA));
        Gui::WININFO info = gui->getWinInfo(LOWORD(wParam));
        if (info.event.onFocusLose) {
            info.event.onFocusLose(hwnd);
        }
        break;
    }
    }
    return DefWindowProcW_(hwnd, msg, wParam, lParam);
}

Gui::WININFO Gui::WinGui::getWinInfo(HWND hwnd) {
    for (auto& winInfo : winList) {
        if (winInfo.hwnd == hwnd) {
            return winInfo;
        }
    }
    return WININFO();
}

Gui::WININFO Gui::WinGui::getWinInfo(unsigned int hmenu) {
    for (auto& winInfo : winList) {
        unsigned int menuId = ((unsigned int)GetMenu_(winInfo.hwnd));
        if (menuId == hmenu) {
            return winInfo;
        }
    }
    return WININFO();
}

bool Gui::WinGui::setWinInfo(HWND hwnd, WININFO& info) {
    for (auto& winInfo : winList) {
        if (winInfo.hwnd == hwnd) {
            winInfo = info;
            return true;
        }
    }
    return false;
}

bool Gui::WinGui::addWinInfo(WININFO& info) {
    for (auto& winInfo : winList) {
        if (winInfo.hwnd == info.hwnd) {
            return false;
        }
    }
    winList.push_back(info);
    return true;
}

void Gui::WinGui::setMainHwnd(HWND hwnd) {
    mainHwnd = hwnd;
    for (auto& winInfo : winList) {
        if (winInfo.hwnd == hwnd) {
            winInfo.isMainWindow = true;
            break;
        }
    }
}

bool Gui::WinGui::win_create(WININFO& info) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = MsgProc;
    wc.hInstance = info.hInstance;
    wc.lpszClassName = info.className.c_str();

    if (!RegisterClassW_(&wc)) {
        return false;
    }

    info.hwnd = CreateWindowExW_(
        0, // 可以添加扩展样式，如果不需要可以设为0
        info.className.c_str(), nullptr,
        WS_OVERLAPPEDWINDOW,
        info.left, info.top, info.width, info.height,
        NULL,
        NULL,
        info.hInstance,
        this
    );

    if (!info.fontPath.empty()) {
        AddFontResourceExW_(info.fontPath.c_str(), FR_PRIVATE, NULL);
        info.hFont = CreateFontW_(
            -12,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_QUALITY,
            info.fontName.c_str()
        );
        SendMessageW_(info.hwnd, WM_SETFONT, (WPARAM)info.hFont, TRUE);
    }
    if (!info.iconPath.empty()) {
        HICON hIcon = (HICON)LoadImageW_(NULL, info.iconPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
        if (hIcon) {
            SendMessageW_(info.hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            SendMessageW_(info.hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        }
    }
    winList.push_back(info);
    if (!win_style(info.hwnd, info.style)) {
        DestroyWindow_(info.hwnd);
        return false;
    }
    if (info.hwnd) {
        if(info.callback != nullptr) info.callback(this, info.hwnd);
        BOOL value = TRUE;
        HRESULT hr = DwmSetWindowAttribute_(info.hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
        this->win_show(info.hwnd, true);
        SetWindowTextW_(info.hwnd, info.title.c_str());
        return true;
    }
    return false;
}

bool Gui::WinGui::win_destroy(HWND hwnd) {
    if (IsWindow_(hwnd)) {
        DestroyWindow_(hwnd);
        winList.erase(std::remove_if(winList.begin(), winList.end(),
            [hwnd](const WININFO& info) { return info.hwnd == hwnd; }), winList.end());
        return true;
    }
    return false;
}

bool Gui::WinGui::win_show(HWND hwnd, bool isShow) {
    if (IsWindow_(hwnd)) {
        ShowWindow_(hwnd, isShow ? SW_SHOW : SW_HIDE);
        UpdateWindow_(hwnd);
        return true;
    }
    return false;
}

bool Gui::WinGui::win_style(HWND hwnd, WINSTYLE& style) {
    if (!IsWindow_(hwnd)) {
        return false;
    }
    DWORD newStyle = GetWindowLongW_(hwnd, GWL_STYLE);
    newStyle &= ~WS_SYSMENU;
    newStyle &= ~WS_MINIMIZEBOX;
    newStyle &= ~WS_MAXIMIZEBOX;
    if (style.hasBorder) {
        newStyle |= WS_BORDER;
    }
    else {
        newStyle &= ~WS_BORDER;
    }
    if (style.hasCaption) {
        newStyle |= WS_CAPTION;
    }
    else {
        newStyle &= ~WS_CAPTION;
    }
    if (style.isChild) {
        newStyle |= WS_CHILD;
    }
    else {
        newStyle |= WS_OVERLAPPED;
    }
    if (style.hasMinimizeBox) {
        newStyle |= WS_MINIMIZEBOX;
    }
    else {
        newStyle &= ~WS_MINIMIZEBOX;
    }
    if (style.hasMaximizeBox) {
        newStyle |= WS_MAXIMIZEBOX;
    }
    else {
        newStyle &= ~WS_MAXIMIZEBOX;
    }
    if (style.hasSysMenu) {
        newStyle |= WS_SYSMENU;
    }
    else {
        newStyle &= ~WS_SYSMENU;
    }
    if (style.hasThickFrame) {
        newStyle |= WS_THICKFRAME;
    }
    else {
        newStyle &= ~WS_THICKFRAME;
    }
    if (style.hasHScroll) {
        newStyle |= WS_HSCROLL;
    }
    else {
        newStyle &= ~WS_HSCROLL;
    }
    if (style.hasVScroll) {
        newStyle |= WS_VSCROLL;
    }
    else {
        newStyle &= ~WS_VSCROLL;
    }
    SetWindowLongW_(hwnd, GWL_STYLE, newStyle);
    SetWindowPos_(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    return true;
}

void Gui::WinGui::Main() {
    MSG msg;
    while (GetMessageW_(&msg, NULL, 0, 0)) {
        TranslateMessage_(&msg);
        DispatchMessageW_(&msg);
        for (size_t i = 0; i < winList.size(); ++i) {
            if (IsWindow_(winList[i].hwnd)) {
                bool isVisible = IsWindowVisible_(winList[i].hwnd);
                bool isIconic = IsIconic_(winList[i].hwnd);
                RECT rect;
                GetClientRect_(winList[i].hwnd, &rect);
                int newWidth = rect.right - rect.left;
                int newHeight = rect.bottom - rect.top;
                bool sizeChanged = (newWidth != winList[i].width || newHeight != winList[i].height);
                if (sizeChanged || (isVisible != winList[i].isMainWindow) || isIconic) {
                    winList[i].isMainWindow = isVisible;
                    winList[i].width = newWidth;
                    winList[i].height = newHeight;
                }
            }
        }
    }
}

bool Gui::WinGui::Label(HWND hwnd, WININFO& info, int align) {
    DWORD style = WS_CHILD | WS_VISIBLE;
    if (align == 1) {
        style |= SS_CENTER;
    }
    else if (align == 2) {
        style |= SS_RIGHT;
    }
    else {
        style |= SS_LEFT;
    }
    do {
        std::string id = Text::text_random_num(4);
        info.hMenu = std::stoi(id);
    } while (this->getWinInfo(info.hMenu).hwnd != NULL);
    info.className = L"STATIC";
    info.hwnd = CreateWindowExW_(
        NULL,
        info.className.c_str(), info.title.c_str(),
        style, info.left, info.top, info.width, info.height, hwnd,
        (HMENU)info.hMenu,
        (HINSTANCE)GetWindowLongW_(hwnd, GWLP_HINSTANCE),
        NULL
    );
    SendMessageW_(info.hwnd, WM_SETFONT, (WPARAM)this->getWinInfo(hwnd).hFont, TRUE);
    if (info.hwnd != NULL) this->addWinInfo(info);
    return info.hwnd != NULL;
}

bool Gui::WinGui::SetLabelText(HWND hwnd, const std::wstring& text)
{
    WININFO info = this->getWinInfo(hwnd);
    if (info.hwnd != NULL) {
        info.title = text;
        SetWindowTextW_(info.hwnd, text.c_str());
        this->setWinInfo(hwnd, info);
    }
    return info.hwnd != NULL;
}

bool Gui::WinGui::Button(HWND hwnd, WININFO& info) {
    do {
        std::string id = Text::text_random_num(4);
        info.hMenu = std::stoi(id);
    } while (this->getWinInfo(info.hMenu).hwnd != NULL);

    info.className = L"BUTTON";
#ifdef _WIN64
    info.hwnd = CreateWindowExW_(
        NULL,
        info.className.c_str(), info.title.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
        info.left,
        info.top,
        info.width,
        info.height,
        hwnd,
        (HMENU)info.hMenu,
        (HINSTANCE)GetWindowLongW_(hwnd, GWLP_HINSTANCE),
        NULL
    );
#else
    info.hwnd = CreateWindowExW_(
        NULL,
        info.className.c_str(), info.title.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
        info.left,
        info.top,
        info.width,
        info.height,
        hwnd,
        (HMENU)info.hMenu,
        (HINSTANCE)GetWindowLongW_(hwnd, GWL_HINSTANCE),
        NULL
    );
#endif
    SendMessageW_(info.hwnd, WM_SETFONT, (WPARAM)this->getWinInfo(hwnd).hFont, TRUE);
    if(info.hwnd != NULL) this->addWinInfo(info);
    return info.hwnd != NULL;
}

bool Gui::WinGui::SetButtonText(HWND hwnd, const std::wstring& text)
{
    WININFO info = this->getWinInfo(hwnd);
    if (info.hwnd != NULL) {
        info.title = text;
        SetWindowTextW_(info.hwnd, text.c_str());
        this->setWinInfo(hwnd, info);
    }
    return info.hwnd != NULL;
}

bool Gui::WinGui::InputBox(HWND hwnd, WININFO& info, std::wstring* value)
{
    if (value == nullptr) {
        return false;
    }
    do {
        std::string id = Text::text_random_num(4);
        info.hMenu = std::stoi(id);
    } while (this->getWinInfo(info.hMenu).hwnd != NULL);
    info.className = L"EDIT";
    info.hwnd = CreateWindowExW_(
        NULL,
        info.className.c_str(), nullptr,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        info.left, info.top, info.width, info.height,
        hwnd,
        (HMENU)info.hMenu,
        (HINSTANCE)GetWindowLongW_(hwnd, GWLP_HINSTANCE),
        NULL
    );
    SendMessageW_(info.hwnd, WM_SETFONT, (WPARAM)this->getWinInfo(hwnd).hFont, TRUE);
    if (info.hwnd != NULL) {
        info.text = value;
        this->addWinInfo(info);
        this->SetInputBoxText(info.hwnd, *info.text);
        return true;
    }
    return false;
}

bool Gui::WinGui::SetInputBoxText(HWND hwnd, const std::wstring& value)
{
    WININFO info = this->getWinInfo(hwnd);
    std::wstring text = value;
    if (info.hwnd != NULL) {
        info.text->clear();
        info.text->append(text);
        SetWindowTextW_(info.hwnd, info.text->c_str());
        this->setWinInfo(hwnd, info);
    }
    return info.hwnd != NULL;
}

