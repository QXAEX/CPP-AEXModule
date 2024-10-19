#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "Text.h"
#include "Byteset.h"

namespace Gui {
    typedef class WinGui *PWinGui; // 前向声明
    /*
    * 窗口回调函数类型定义
    * PWinGui: 指向 WinGui 类的指针
    * HDC: 设备上下文句柄
    */
    typedef void (*WinGuiCallback)(PWinGui, HWND);
    //窗口样式结构体
    struct WINSTYLE {
        bool hasBorder;             // 窗口具有细线边框
        bool hasCaption;            // 窗口具有标题栏
        bool isChild;               // 窗口是子窗口
        bool isVisible;             // 窗口最初可见
        bool hasMinimizeBox;        // 窗口具有最小化按钮
        bool hasMaximizeBox;        // 窗口具有最大化按钮
        bool hasSysMenu;            // 窗口的标题栏上有一个窗口菜单
        bool hasThickFrame;         // 窗口具有大小调整边框
        bool hasHScroll;            // 窗口具有水平滚动条
        bool hasVScroll;            // 窗口具有垂直滚动条
        bool isDisabled;            // 窗口最初处于禁用状态
        bool hasDlgFrame;           // 窗口边框样式通常与对话框相同
        bool isGroup;               // 窗口是一组控件中的第一个控件
        bool isMaximized;           // 窗口最初是最大化的
        bool isMinimized;           // 窗口最初是最小化的
        bool isPopup;               // 窗口是弹出窗口
        bool isClipChildren;        // 在父窗口内进行绘图时，不包括子窗口
        bool isClipSiblings;        // 相对于彼此剪裁子窗口
        bool isDialog;              // 窗口是对话框
        bool hasTabStop;            // 窗口是一个控件，当用户按下 Tab 键时，该控件可以接收焦点
        bool isOverlapped;          // 窗口是重叠的窗口
        bool isTiled;               // 窗口是平铺窗口

        // 构造函数，提供默认值
        WINSTYLE()
            : hasBorder(true), hasCaption(true), isChild(false),
            isVisible(true), hasMinimizeBox(true), hasMaximizeBox(true),
            hasSysMenu(true), hasThickFrame(false), hasHScroll(false),
            hasVScroll(false), isDisabled(false), hasDlgFrame(false),
            isGroup(false), isMaximized(false), isMinimized(false),
            isPopup(false), isClipChildren(false), isClipSiblings(false),
            isDialog(false), hasTabStop(false), isOverlapped(true),
            isTiled(true) {}
    };
    // 组件操作事件结构体
    typedef struct COMPONENTEVENT {
        /**
         * 鼠标左键点击事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         */
        typedef void (*OnClick)(HWND hwnd);
        OnClick onClick = nullptr;
        /**
         * 鼠标悬停事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         * @param x: 当前鼠标的 x 坐标，表示鼠标在窗口客户区域内的位置
         * @param y: 当前鼠标的 y 坐标，表示鼠标在窗口客户区域内的位置
         */
        typedef void (*OnHover)(HWND hwnd, int x, int y);
        OnHover onHover = nullptr;
        /**
         * 鼠标离开事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         */
        typedef void (*OnMouseLeave)(HWND hwnd);
        OnMouseLeave onMouseLeave = nullptr;
        /**
         * 鼠标右键点击事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         * @param x: 当前鼠标的 x 坐标，表示鼠标在窗口客户区域内的位置
         * @param y: 当前鼠标的 y 坐标，表示鼠标在窗口客户区域内的位置
         */
        typedef void (*OnRightClick)(HWND hwnd, int x, int y);
        OnRightClick onRightClick = nullptr;
        /**
         * 鼠标双击事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         * @param x: 当前鼠标的 x 坐标，表示鼠标在窗口客户区域内的位置
         * @param y: 当前鼠标的 y 坐标，表示鼠标在窗口客户区域内的位置
         */
        typedef void (*OnDoubleClick)(HWND hwnd, int x, int y);
        OnDoubleClick onDoubleClick = nullptr;
        /**
         * 鼠标移动事件回调函数
         * @param x: 当前鼠标的 x 坐标，表示鼠标在窗口客户区域内的位置
         * @param y: 当前鼠标的 y 坐标，表示鼠标在窗口客户区域内的位置
         */
        typedef void (*OnMouseMove)(HWND hwnd, int x, int y);
        OnMouseMove onMouseMove = nullptr;
        /**
         * 键盘按下事件回调函数
         * @param key: 按下的虚拟键值
         */
        typedef void (*OnKeyDown)(HWND hwnd, unsigned char key);
        OnKeyDown onKeyDown = nullptr;
        /**
         * 键盘抬起事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         * @param key: 按下的虚拟键值
         */
        typedef void (*OnKeyUp)(HWND hwnd, unsigned char key);
        OnKeyUp onKeyUp = nullptr;
        /**
         * 焦点获得事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         */
        typedef void (*OnFocusGain)(HWND hwnd);
        OnFocusGain onFocusGain = nullptr;
        /**
         * 焦点失去事件回调函数
         * @param hwnd: 窗口句柄，表示触发事件的窗口
         */
        typedef void (*OnFocusLose)(HWND hwnd);
        OnFocusLose onFocusLose = nullptr;
    } COMPONENTEVENT, * PCOMPONENTEVENT;
    // 窗口信息结构体
    struct WININFO {
        int width;                    // 窗口宽度（必填）
        int height;                   // 窗口高度（必填）
        int left;                     // 窗口左边距（必填）
        int top;                      // 窗口顶部（必填）
        std::wstring title;           // 窗口标题（必填）
        std::wstring className;       // 窗口类名（必填）
        std::wstring* text;            // 窗口文本内容（可选，如果组件为文本框，则需要传入指针）

        HWND hwnd;                    // 窗口句柄 (自动生成)
        unsigned int hMenu;                   // 控件ID (可选，默认值 -1)
        WINSTYLE style;               // 窗口样式 (可选，默认值)
        WinGuiCallback callback;       // 窗口回调函数 (可选，默认值为空)
        HINSTANCE hInstance;          // 窗口实例句柄（可选，默认值为 GetModuleHandle(NULL)）
        COLORREF color;                  //字体颜色, 默认黑色
        COLORREF bgColor;             // 窗口背景颜色（可选，默认值）
        std::wstring iconPath;        // 窗口图标路径（可选，默认值为空）
        std::wstring fontPath;        // TTF 格式字体文件路径（可选，默认值为空）
        std::wstring fontName;        // 字体名称（可选，默认值为空,在 fontPath 不为空时则为必填）
        HFONT hFont;                  // 字体句柄（可选，默认值 NULL）
        bool isMainWindow;            // 是否为主窗口（可选，默认值为 false）
        COMPONENTEVENT event;         // 组件操作事件结构体（可选，默认值为空）
        WININFO() = default;
        WININFO(
            const std::wstring& className,// 窗口类名
            const std::wstring& title,// 窗口标题
            int w, int h, int l, int topPos, // 宽度、高度、左边、顶边
            COLORREF bg = RGB(240, 240, 240), // 默认背景颜色为浅灰色
            const std::wstring& icon = L"", // 默认图标路径为空
            const std::wstring& font = L"", // 默认字体路径为空
            const std::wstring& fontName = L"", // 默认字体名称为空
            bool mainWindow = false,// 默认不是主窗口
            WinGuiCallback callback = nullptr)
            : className(className), title(title), width(w), height(h),
            left(l), top(topPos), hInstance(GetModuleHandle(NULL)), // 确保使用有效的实例句柄
            hwnd(NULL), color(RGB(0, 0, 0)), bgColor(bg),iconPath(icon), fontPath(font), fontName(fontName), 
            isMainWindow(mainWindow), callback(callback) {}
    };
    // 窗口类
    class WinGui {
    private:
        std::vector<WININFO> winList; // 窗口列表
        HWND mainHwnd;                 // 主窗口句柄
        // 窗口消息处理函数
        static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    public:
        WinGui();
        ~WinGui();
        /*
        * 获取窗口结构
        * hwnd: 窗口句柄
        * 返回值：窗口结构体
        */
        WININFO getWinInfo(HWND hwnd);
        /*
        * 获取窗口结构
        * hwnd: 窗口控件ID
        * 返回值：窗口结构体
        */
        WININFO getWinInfo(unsigned int hmenu);
        /*
        * 修改窗口结构
        * hwnd: 窗口句柄
        * info: 窗口信息结构体
        * 返回值：成功返回 true，失败返回 false
        */
        bool setWinInfo(HWND hwnd, WININFO& info);
        /*
        * 添加窗口结构
        * info: 窗口信息结构体
        * 返回值：成功返回 true，失败返回 false
        */
        bool addWinInfo(WININFO& info);
        /*
        * 设置主窗口句柄
        * hwnd: 主窗口句柄
        */
        void setMainHwnd(HWND hwnd);
        /*
        * 创建窗口
        * info: 窗口信息结构体
        * 返回值：成功返回 true，失败返回 false
        */
        bool win_create(WININFO& info);
        /*
        * 销毁窗口
        * hwnd: 窗口句柄
        * 返回值：成功返回 true，失败返回 false
        */
        bool win_destroy(HWND hwnd);
        /*
        * 显示窗口
        * hwnd: 窗口句柄
        * isShow: 是否显示窗口
        * 返回值：成功返回 true，失败返回 false
        */
        bool win_show(HWND hwnd, bool isShow);
        /*
        * 设置窗口样式
        * hwnd: 窗口句柄
        * style: 窗口样式结构体
        * 返回值：成功返回 true，失败返回 false
        */
        bool win_style(HWND hwnd, WINSTYLE& style);
        // 运行主消息循环
        void Main();
        /*
        * 添加标签
        * hwnd: 父窗口句柄
        * info: 标签信息结构体
        * align: 标签对齐方式，默认左对齐,0为左对齐，1为居中，2为右对齐
        * 返回值：成功返回标签句柄，失败返回 NULL
        */
        bool Label(HWND hwnd, WININFO& info,int align=NULL);
        /*
        * 置标签文本
        * hwnd: 标签句柄
        * text: 标签文本
        * 返回值：成功返回 true，失败返回 false
        */
        bool SetLabelText(HWND hwnd, const std::wstring& text);
        /*
        * 添加按钮
        * hwnd: 父窗口句柄
        * info: 按钮信息结构体
        * 返回值：成功返回标签句柄，失败返回 NULL
        */
        bool Button(HWND hwnd, WININFO& info);
        /*
        * 置按钮文本
        * hwnd: 按钮句柄
        * text: 按钮文本
        * 返回值：成功返回 true，失败返回 false
        */
        bool SetButtonText(HWND hwnd, const std::wstring& text);
        /*
        /* 添加文本框(最终的文本会在组件失去焦点后返回)
        /* hwnd: 父窗口句柄
        /* info: 输入框信息结构体
        /* value: 输入框数据
        /* 返回值：成功返回标签句柄，失败返回 NULL
        */
        bool InputBox(HWND hwnd, WININFO& info, std::wstring* value = nullptr);
        /*
        * 置文本框内容
        * hwnd: 文本框句柄
        * value: 文本内容
        * 返回值：成功返回 true，失败返回 false
        */
        bool SetInputBoxText(HWND hwnd, const std::wstring& value);
    };
}
