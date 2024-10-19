#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "Text.h"
#include "Byteset.h"

namespace Gui {
    typedef class WinGui *PWinGui; // ǰ������
    /*
    * ���ڻص��������Ͷ���
    * PWinGui: ָ�� WinGui ���ָ��
    * HDC: �豸�����ľ��
    */
    typedef void (*WinGuiCallback)(PWinGui, HWND);
    //������ʽ�ṹ��
    struct WINSTYLE {
        bool hasBorder;             // ���ھ���ϸ�߱߿�
        bool hasCaption;            // ���ھ��б�����
        bool isChild;               // �������Ӵ���
        bool isVisible;             // ��������ɼ�
        bool hasMinimizeBox;        // ���ھ�����С����ť
        bool hasMaximizeBox;        // ���ھ�����󻯰�ť
        bool hasSysMenu;            // ���ڵı���������һ�����ڲ˵�
        bool hasThickFrame;         // ���ھ��д�С�����߿�
        bool hasHScroll;            // ���ھ���ˮƽ������
        bool hasVScroll;            // ���ھ��д�ֱ������
        bool isDisabled;            // ����������ڽ���״̬
        bool hasDlgFrame;           // ���ڱ߿���ʽͨ����Ի�����ͬ
        bool isGroup;               // ������һ��ؼ��еĵ�һ���ؼ�
        bool isMaximized;           // �����������󻯵�
        bool isMinimized;           // �����������С����
        bool isPopup;               // �����ǵ�������
        bool isClipChildren;        // �ڸ������ڽ��л�ͼʱ���������Ӵ���
        bool isClipSiblings;        // ����ڱ˴˼����Ӵ���
        bool isDialog;              // �����ǶԻ���
        bool hasTabStop;            // ������һ���ؼ������û����� Tab ��ʱ���ÿؼ����Խ��ս���
        bool isOverlapped;          // �������ص��Ĵ���
        bool isTiled;               // ������ƽ�̴���

        // ���캯�����ṩĬ��ֵ
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
    // ��������¼��ṹ��
    typedef struct COMPONENTEVENT {
        /**
         * ����������¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         */
        typedef void (*OnClick)(HWND hwnd);
        OnClick onClick = nullptr;
        /**
         * �����ͣ�¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         * @param x: ��ǰ���� x ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         * @param y: ��ǰ���� y ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         */
        typedef void (*OnHover)(HWND hwnd, int x, int y);
        OnHover onHover = nullptr;
        /**
         * ����뿪�¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         */
        typedef void (*OnMouseLeave)(HWND hwnd);
        OnMouseLeave onMouseLeave = nullptr;
        /**
         * ����Ҽ�����¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         * @param x: ��ǰ���� x ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         * @param y: ��ǰ���� y ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         */
        typedef void (*OnRightClick)(HWND hwnd, int x, int y);
        OnRightClick onRightClick = nullptr;
        /**
         * ���˫���¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         * @param x: ��ǰ���� x ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         * @param y: ��ǰ���� y ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         */
        typedef void (*OnDoubleClick)(HWND hwnd, int x, int y);
        OnDoubleClick onDoubleClick = nullptr;
        /**
         * ����ƶ��¼��ص�����
         * @param x: ��ǰ���� x ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         * @param y: ��ǰ���� y ���꣬��ʾ����ڴ��ڿͻ������ڵ�λ��
         */
        typedef void (*OnMouseMove)(HWND hwnd, int x, int y);
        OnMouseMove onMouseMove = nullptr;
        /**
         * ���̰����¼��ص�����
         * @param key: ���µ������ֵ
         */
        typedef void (*OnKeyDown)(HWND hwnd, unsigned char key);
        OnKeyDown onKeyDown = nullptr;
        /**
         * ����̧���¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         * @param key: ���µ������ֵ
         */
        typedef void (*OnKeyUp)(HWND hwnd, unsigned char key);
        OnKeyUp onKeyUp = nullptr;
        /**
         * �������¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         */
        typedef void (*OnFocusGain)(HWND hwnd);
        OnFocusGain onFocusGain = nullptr;
        /**
         * ����ʧȥ�¼��ص�����
         * @param hwnd: ���ھ������ʾ�����¼��Ĵ���
         */
        typedef void (*OnFocusLose)(HWND hwnd);
        OnFocusLose onFocusLose = nullptr;
    } COMPONENTEVENT, * PCOMPONENTEVENT;
    // ������Ϣ�ṹ��
    struct WININFO {
        int width;                    // ���ڿ�ȣ����
        int height;                   // ���ڸ߶ȣ����
        int left;                     // ������߾ࣨ���
        int top;                      // ���ڶ��������
        std::wstring title;           // ���ڱ��⣨���
        std::wstring className;       // �������������
        std::wstring* text;            // �����ı����ݣ���ѡ��������Ϊ�ı�������Ҫ����ָ�룩

        HWND hwnd;                    // ���ھ�� (�Զ�����)
        unsigned int hMenu;                   // �ؼ�ID (��ѡ��Ĭ��ֵ -1)
        WINSTYLE style;               // ������ʽ (��ѡ��Ĭ��ֵ)
        WinGuiCallback callback;       // ���ڻص����� (��ѡ��Ĭ��ֵΪ��)
        HINSTANCE hInstance;          // ����ʵ���������ѡ��Ĭ��ֵΪ GetModuleHandle(NULL)��
        COLORREF color;                  //������ɫ, Ĭ�Ϻ�ɫ
        COLORREF bgColor;             // ���ڱ�����ɫ����ѡ��Ĭ��ֵ��
        std::wstring iconPath;        // ����ͼ��·������ѡ��Ĭ��ֵΪ�գ�
        std::wstring fontPath;        // TTF ��ʽ�����ļ�·������ѡ��Ĭ��ֵΪ�գ�
        std::wstring fontName;        // �������ƣ���ѡ��Ĭ��ֵΪ��,�� fontPath ��Ϊ��ʱ��Ϊ���
        HFONT hFont;                  // ����������ѡ��Ĭ��ֵ NULL��
        bool isMainWindow;            // �Ƿ�Ϊ�����ڣ���ѡ��Ĭ��ֵΪ false��
        COMPONENTEVENT event;         // ��������¼��ṹ�壨��ѡ��Ĭ��ֵΪ�գ�
        WININFO() = default;
        WININFO(
            const std::wstring& className,// ��������
            const std::wstring& title,// ���ڱ���
            int w, int h, int l, int topPos, // ��ȡ��߶ȡ���ߡ�����
            COLORREF bg = RGB(240, 240, 240), // Ĭ�ϱ�����ɫΪǳ��ɫ
            const std::wstring& icon = L"", // Ĭ��ͼ��·��Ϊ��
            const std::wstring& font = L"", // Ĭ������·��Ϊ��
            const std::wstring& fontName = L"", // Ĭ����������Ϊ��
            bool mainWindow = false,// Ĭ�ϲ���������
            WinGuiCallback callback = nullptr)
            : className(className), title(title), width(w), height(h),
            left(l), top(topPos), hInstance(GetModuleHandle(NULL)), // ȷ��ʹ����Ч��ʵ�����
            hwnd(NULL), color(RGB(0, 0, 0)), bgColor(bg),iconPath(icon), fontPath(font), fontName(fontName), 
            isMainWindow(mainWindow), callback(callback) {}
    };
    // ������
    class WinGui {
    private:
        std::vector<WININFO> winList; // �����б�
        HWND mainHwnd;                 // �����ھ��
        // ������Ϣ������
        static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    public:
        WinGui();
        ~WinGui();
        /*
        * ��ȡ���ڽṹ
        * hwnd: ���ھ��
        * ����ֵ�����ڽṹ��
        */
        WININFO getWinInfo(HWND hwnd);
        /*
        * ��ȡ���ڽṹ
        * hwnd: ���ڿؼ�ID
        * ����ֵ�����ڽṹ��
        */
        WININFO getWinInfo(unsigned int hmenu);
        /*
        * �޸Ĵ��ڽṹ
        * hwnd: ���ھ��
        * info: ������Ϣ�ṹ��
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool setWinInfo(HWND hwnd, WININFO& info);
        /*
        * ��Ӵ��ڽṹ
        * info: ������Ϣ�ṹ��
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool addWinInfo(WININFO& info);
        /*
        * ���������ھ��
        * hwnd: �����ھ��
        */
        void setMainHwnd(HWND hwnd);
        /*
        * ��������
        * info: ������Ϣ�ṹ��
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool win_create(WININFO& info);
        /*
        * ���ٴ���
        * hwnd: ���ھ��
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool win_destroy(HWND hwnd);
        /*
        * ��ʾ����
        * hwnd: ���ھ��
        * isShow: �Ƿ���ʾ����
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool win_show(HWND hwnd, bool isShow);
        /*
        * ���ô�����ʽ
        * hwnd: ���ھ��
        * style: ������ʽ�ṹ��
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool win_style(HWND hwnd, WINSTYLE& style);
        // ��������Ϣѭ��
        void Main();
        /*
        * ��ӱ�ǩ
        * hwnd: �����ھ��
        * info: ��ǩ��Ϣ�ṹ��
        * align: ��ǩ���뷽ʽ��Ĭ�������,0Ϊ����룬1Ϊ���У�2Ϊ�Ҷ���
        * ����ֵ���ɹ����ر�ǩ�����ʧ�ܷ��� NULL
        */
        bool Label(HWND hwnd, WININFO& info,int align=NULL);
        /*
        * �ñ�ǩ�ı�
        * hwnd: ��ǩ���
        * text: ��ǩ�ı�
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool SetLabelText(HWND hwnd, const std::wstring& text);
        /*
        * ��Ӱ�ť
        * hwnd: �����ھ��
        * info: ��ť��Ϣ�ṹ��
        * ����ֵ���ɹ����ر�ǩ�����ʧ�ܷ��� NULL
        */
        bool Button(HWND hwnd, WININFO& info);
        /*
        * �ð�ť�ı�
        * hwnd: ��ť���
        * text: ��ť�ı�
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool SetButtonText(HWND hwnd, const std::wstring& text);
        /*
        /* ����ı���(���յ��ı��������ʧȥ����󷵻�)
        /* hwnd: �����ھ��
        /* info: �������Ϣ�ṹ��
        /* value: ���������
        /* ����ֵ���ɹ����ر�ǩ�����ʧ�ܷ��� NULL
        */
        bool InputBox(HWND hwnd, WININFO& info, std::wstring* value = nullptr);
        /*
        * ���ı�������
        * hwnd: �ı�����
        * value: �ı�����
        * ����ֵ���ɹ����� true��ʧ�ܷ��� false
        */
        bool SetInputBoxText(HWND hwnd, const std::wstring& value);
    };
}
