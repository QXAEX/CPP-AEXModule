//// AEXModule.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
#define AEX_DRAW_LIB_LOADED
#include "AEXModule.h" 
#include <iostream>
#include <thread>
#include <windows.h>
#include "PageHook.hpp"
#ifdef _WIN64
#define GetPage(Ptr) ((uintptr_t)Ptr & 0xFFFFFFFFFFFFF000)
#else
#define GetPage(Ptr) ((uintptr_t)Ptr & 0xFFFFF000)
#endif

int main() {
    int* addr = (int*)0x401000;
    std::cout << GetPage(addr) << " " << addr << std::endl;
    std::cin.get();
    return NULL;
}



Gui::WinGui gui;
std::wstring str = L"Hello World!";
void DrawSecondWindow1(Gui::PWinGui gui, HWND hwnd) {
    Gui::WININFO info;
    info.left = 100;
    info.top = 100;
    info.width = 200;
    info.height = 100;
    info.title = L"按钮1";
    info.event.onClick = nullptr;
    gui->Button(hwnd, info);
    gui->addWinInfo(info);
    info.left = 300;
    gui->Button(hwnd, info);
    gui->addWinInfo(info);
}
void label_click(HWND hwnd) {
    printf("芜湖,%s\n", Text::text_to_str(str).c_str());

    Gui::WINSTYLE style2;
    style2.hasMinimizeBox = true;
    style2.hasMaximizeBox = true;
    style2.hasSysMenu = true;
    style2.hasThickFrame = true;
    Gui::WININFO win2(
        L"WindowClass2",
        L"Second Window",
        500, 400, 200, 150,
        RGB(240, 240, 240),
        L"D:\\IMG\\img1.ico",
        L"D:\\Project\\C\\AEXModule\\AEXModule\\fonts\\WenQuanYi Micro Hei Mono.ttf",
        L"文泉驿等宽微米黑",
        false,
        DrawSecondWindow1
    );
    win2.style = style2;
    gui.win_create(win2);
};
void DrawFirstWindow(Gui::PWinGui gui, HWND hwnd) {
    //Gui::WININFO info;
    //info.left = 100;
    //info.top = 100;
    //info.width = 200;
    //info.height = 100;
    //info.title = L"First Window1123123123";
    //info.event.onClick = label_click;
    //gui->Label(hwnd,info,NULL);
    Gui::WININFO info;
    info.left = 100;
    info.top = 100;
    info.width = 200;
    info.height = 100;
    info.title = L"按钮1";
    info.event.onClick = label_click;
    //gui->Button(hwnd, info);
    gui->InputBox(hwnd,info,&str);
}

void DrawSecondWindow(Gui::PWinGui gui, HWND hwnd) {
    Gui::WININFO info;
    info.left = 100;
    info.top = 100;
    info.width = 200;
    info.height = 100;
    info.title = L"按钮1";
    info.event.onClick = label_click;
    gui->Button(hwnd, info);
    info.left = 300;
    gui->Button(hwnd, info);
}

int main4() {
    Gui::WINSTYLE style1;
    style1.hasMinimizeBox = true;
    style1.hasMaximizeBox = false;
    style1.hasSysMenu = true;

    Gui::WININFO win1(
        L"WindowClass1",
        L"First Window",
        400,300,100,100,
        RGB(240, 240, 0),
        L"D:\\IMG\\img1.ico",
        L"D:\\Project\\C\\AEXModule\\AEXModule\\fonts\\WenQuanYi Micro Hei Mono.ttf",
        L"文泉驿等宽微米黑",
        false,
        DrawFirstWindow
    );
    win1.style = style1;


    gui.win_create(win1);

    gui.setMainHwnd(win1.hwnd);

    gui.Main();

    return 0;
}




using namespace Text;
static void handleClient(Network::TCP::PCLIENT client) {
    Network::TCP::PSERVER server = reinterpret_cast<Network::TCP::PSERVER>(client->server);
    Network::TCP::SERVER_MSG_INFO info;
    info.client = client;
    while (server->started) {
        server->Recvs(&info);
        if (info.client->state == Network::TCP::_SERVER::SERVER_CLIENT_DISCONNECTION||
            info.client->state == Network::TCP::_SERVER::SERVER_DATA_RECV_FAILED ||
            info.client->state == Network::TCP::_SERVER::SERVER_DATA_SEND_FAILED
            ) {
            std::cout << "Client disconnected" << std::endl;
            server->disconnect(client);
            break;
        }
        info.file->Seek(NULL);
        std::cout << "1Received data: " << (char*)info.file->Read(info.file->Size()).data() << "file size:" << info.file->Size() << std::endl;
        
        info.file->Seek(NULL);
        info.file->Delete(info.file->Size());
        info.file->Write("Hello World!\n");
        server->Sends(&info);
        info.file->Close();
        info.file->DelFile();

        /*
        Byteset data = server->Recv(client);
        if (client->state == Network::TCP::_SERVER::SERVER_CLIENT_DISCONNECTION||
            client->state == Network::TCP::_SERVER::SERVER_DATA_RECV_FAILED ||
            client->state == Network::TCP::_SERVER::SERVER_DATA_SEND_FAILED
            ) {
            std::cout << "Client disconnected" << std::endl;
            server->disconnect(client);
            break;
        }
        std::cout << "1Received data: " << (char*)data.data() << std::endl;
        server->Send(client,"Hello World!");
        */
    }
}


int main3() {

    return NULL;
    //Network::TCP::Server server;
    //if (!server.start(4001)) {
    //    std::cerr << "Failed to start server" << std::endl;
    //    return 1;
    //}
    //std::cout << "Server started on port 4001" << std::endl;
    //while (true) {
    //    Network::TCP::CLIENT client = server.Listen(-1);
    //    if (client.state == Network::TCP::_SERVER::SERVER_CLIENT_CONNECTION) {
    //        std::cout << "Client connected" << std::endl;
    //        std::thread clientThread(handleClient, &client);
    //        clientThread.detach();
    //    }
    //}
    //return 0;
    //Network::TCP::Client client;
    //if (!client.Connect("127.0.0.1", 4001)) {
    //    std::cerr << "Failed to connect to server" << std::endl;
    //    return 1;
    //}
    //std::cout << "Connected to server" << std::endl;
    //Network::TCP::CLIENTS_MSG_INFO info;
    //info.file->Open(System::GetRunPath() + "\\temp\\sends_" + Text::text_random_num() + ".dat", true);
    //Byteset response;
    //do {
    //    std::string dd;
    //    std::cin >> dd;
    //    info.file->Seek(NULL);
    //    info.file->Delete(info.file->Size());
    //    info.file->Write(dd);
    //    client.Sends(&info);
    //    client.Recvs(&info);
    //    info.file->Seek(NULL);
    //    response = info.file->Read(info.file->Size());
    //    std::cout << "Received data: " << (char*)response.data() << "file size:" << response.size() << std::endl;
    //} while (response != "end");
    //info.file->Close();
    //info.file->DelFile();
    //client.disconnect();
    //std::cin.get();
    /*
        Network::TCP::Server server;
    if (!server.start(4001)) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }
    std::cout << "Server started on port 4001" << std::endl;
    while (true) {
        Network::TCP::CLIENT client = server.Listen(-1);
        if (client.state == Network::TCP::_SERVER::SERVER_CLIENT_CONNECTION) {
            std::cout << "Client connected" << std::endl;
            std::thread clientThread(handleClient, &client);
            clientThread.detach();
        }
    }
    return 0;

    Network::TCP::Client client;
    if (!client.Connect("127.0.0.1", 4001)) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }
    std::cout << "Connected to server" << std::endl;
    Byteset response;
    do {
        std::string dd;
        std::cin >> dd;
        client.Send(dd);
        response = client.Recv();
        std::cout << "Received data: " << response << std::endl;
    } while (response != "end");
    client.disconnect();
    std::cin.get();
    */
    //for (size_t i = 0; i < 1000*strlen(str); i++)
    //{
    //    data.append(str[i % strlen(str)]);
    //}
    //Network::TCP::CLIENTS_MSG_INFO info;
    //info.file->Open(System::GetRunPath() + "\\test.txt", true);
    //info.file->Write("Hello World!\n");
    //client.Sends(&info);
    //client.Recvs(&info);
    //info.file->Seek(NULL);
    //std::cout << "2Received data: " << info.file->Read(info.file->Size()) <<"file size:"<<info.file->Size() << std::endl;
    //info.file->Close();
    //info.file->DelFile();


    //Draw::DX11 dx11({NULL},"D:\\Project\\C\\AEXModule\\AEXModule\\fonts\\Poppins-SemiBold.ttf", 28);
    //std::cout << "status:" << dx11.install();
    //dx11.Main((Draw::DX11_CALL)AEXIM);

    //Memory::R3 r3;
    //SIZE_T PID = Process::ProcessGetID("PlantsVsZombies.exe");
    //r3.Open(PID);
    //size_t addr = r3.GetModuleBase("PicFace.dll") + 0x533E4;
    //Byteset data = r3.pointerChain(addr, {0x38, 0x10 ,0x178,0x4, 0x118 ,0x4 ,0x5578 });
    //std::cout << "Data size: " << data.size() << "data: " << data << std::endl;
    //printf("value:%d\n", *(int*)data.data());
    //Byteset data;
    //data = {0x1,0x12};
    //std::cout << "Data size: " << data.size() << "data: " << data << std::endl;
    //printf("data: %d\n", *(int*)data.data());
   //std::cout << Text::text_find("hello world", "world") << std::endl;//输出6
    //Byteset data;
    //data.append({ 0xFF, 0xE8, 0x30, 0x46 });//动态添加字节集
    //std::cout << "Data size: " << data.size() << "data: "<< data << std::endl;//输出字节集
    //Memory::EmbeddedCall call(GetCurrentProcessId(),0x1000);
    //Byteset data;
    //data.append({ 0x55 });//push rbp
    //data.append({ 0x48,0x8B,0xEC });//mov rbp,rsp
    ////data.append({ 0x48,0x8B,0x45,0x16 });//mov rax,[rbp+16]
    ////data.append({ 0x48,0x8B,0x7D,0x24 });//mov rdi,[rbp+24]
    ////data.append({ 0x48, 0x01, 0xF8 });//add rax,rdi
    //data.append({ 0x48, 0xB8, 0x66, 0x66, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 });
    //data.append({ 0x48, 0x8B, 0xE5 });//mov rsp,rbp
    //data.append({ 0x5D });//pop rbp
    //data.append({ 0xC3 });//ret
    //data.append({ 0xE8,0xE7, 0xFF,0xFF,0xFF });//call 0x0
    //data.append({ 0x48, 0x83, 0xC4, 0x24 });//add rsp,24
    //data.append({ 0x5D });//pop rbp
    //data.append({ 0xC3 });//ret
    //call.SetCode(data);
    //std::cout << "Call: " << call.Call<unsigned int>(0x0) << std::endl;

    //AEXStore store;
    //std::cout << "store load status:" << store.Load("C:\\Users\\QX\\Desktop\\AEXStore.txt") << std::endl;
    //bool flag = false;
    //
    //Byteset Struct = store.writeData("value1", "hello world!", flag);
    //AEX_STORE_STRUCT data;
    //data.token = store.token;
    //data.data = "hello world!";
    //data.name = "value1";
    //data.structSize = 55;
    //data.dataSize = data.data.size();
    //data.updateCount = 100;
    //data.createTime = System::GetTime(true);
    //data.updateTime = System::GetTime(true);
    //Byteset struct1 = store.restoreStruct(data);
    //data.updateCount = 101;
    //struct1.append(store.restoreStruct(data));
    //std::cout << "Struct size: " << struct1.size() << std::endl;
    //std::cout << "Struct data: " << struct1 << std::endl;
    //AEX_STORE_STRUCT data2; 
    //data2 = store.analyzeStruct(struct1,store.token,1,flag);

    //std::cout << "Struct size: " << Struct.size() << std::endl;
    //std::cout << "Struct data: " << Struct << std::endl;
    //std::cout << "store free status:" << store.Free() << std::endl;
    
    
    //std::string data = (char*)text.data();
    //std::cout << data << std::endl;
    //std::cout << text << std::endl;
    //Byteset text1 = 114514;
    //int data1 = *(int*)text1.data();
    //std::cout << data1 << std::endl;
    //std::cout << text1 << std::endl;
    //Byteset text2 = 1234567890;
    //std::cout << text2 << std::endl;
    //Byteset text3 = 12.99;
    //std::cout << text3 << std::endl;
    //Byteset text4 = 12345678901.999999999;
    //std::cout << text4 << std::endl;
    //Byteset text5 = true;
    //std::cout << text5 << std::endl;
    //File file("C:\\Users\\QX\\Desktop\\test.txt");//构造函数直接打开文件
    //std::cout << "文件是否打开: " << file.is_open << std::endl;//判断状态
    //file.Seek(0);//设置文件指针位置
    //std::cout <<"读数据:"<< file.Read(10) << std::endl;//输出空字节集
    //file.Seek(0);//设置文件指针位置
    //std::cout << "写数据:" << file.Write({ "Hello World!" }) << std::endl;//输出bool 值
    //file.Seek(0);//设置文件指针位置
    //std::cout << "读数据:" << file.Read(10) << std::endl;//输出字节集
    //file.Seek(5);//设置文件指针位置
    //std::cout << "删数据:" << file.Delete(5) << std::endl;//输出bool 值
    //file.Seek(0);//设置文件指针位置
    //std::cout << "读数据:" << file.Read(10) << std::endl;//输出字节集
    
    //SIZE_T PID = Process::ProcessGetID("test.exe");
    //Memory::R3 r3 = Memory::R3(PID);
    //printf("Addr:%p\n", r3.GetModuleBase("test.exe"));
    //int a = r3.pointerChain<int,LONG>(0x121111111113, false, { 114, 331,1123, 546567 });
    //Memory::R3HOOK r3hook;
    //r3hook.setVirtual(true);
    //std::vector<size_t>list = r3.Search({ 0xF2 , 0x0F , 0x5A , 0xE8 , 0xF3 , 0x0F , 0x11 , 0x28 , 0x48 , 0x8D , 0x65 , 0x00 , 0x5D , 0xC3 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 },nullptr, 0,-1, NULL, 1, false);
    //r3hook.Install(PID, 0x14CCBD51DDA);
    //r3hook.Capture();
    //Memory::R3HOOK_INFO64 data = r3hook.ReadData64();
   
    ////std::vector<size_t>list = r3.Search({ 0x33,0xC0,0xC3, 0x90, 0x55, 0x8B, 0xEC ,0xC7, 0x5, 0xB8, 0x6E, 0x82, 0x0, 0xA8, 0x3, 0x0, 0x0 }, {}, NULL, -1,4, 1,true);
    //Byteset data;
    //size_t mod = r3.Allocate();
    //r3.hookJump(mod, r3.GetModuleBase("worldbox.exe"),{1,2},true, true);
    //std::cout << "Allocated Memory Address: " << mod << std::endl;
    //std::cout << "Module Base Address: " << mod << std::endl;
    ////std::cout << "Reading status:" << r3.Read(mod, data, 10,true) << data << std::endl;
    ////std::cout<< "Writing status:" << r3.Write(mod, { 0x48, 0x65, 0x6C, 0x6C, 0x0, 0x0, 0x57, 0x6F, 0x72, 0x6C },  true) << std::endl;
    ////std::cout << "Reading status:" << r3.Read(mod, data, 10, true) << data << std::endl;
    //r3.Free(mod);
    //std::cout << "Memory Freed" << std::endl;
    return 0;
}
//#include "../AEXModule/AEXModule/imgui/imgui.h"
//#include "../AEXModule/AEXModule/imgui/backends/imgui_impl_dx11.h"
//#include "../AEXModule/AEXModule/imgui/backends/imgui_impl_win32.h"
//#include <d3d11.h>
//#include <tchar.h>
//#include <iostream>

//// 全局变量
//ID3D11Device* g_pd3dDevice = nullptr;
//ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
//IDXGISwapChain* g_pSwapChain = nullptr;
//ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
//
//// 函数声明
//bool CreateDeviceD3D(HWND hWnd);
//void CleanupDeviceD3D();
//void CreateRenderTarget();
//void CleanupRenderTarget();
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//int main() {
//    // 创建窗口
//    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
//    ::RegisterClassExW(&wc);
//    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);
//
//    // 初始化Direct3D
//    if (!CreateDeviceD3D(hwnd)) {
//        CleanupDeviceD3D();
//        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
//        return 1;
//    }
//
//    // 显示窗口
//    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
//    ::UpdateWindow(hwnd);
//
//    // 初始化Dear ImGui
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = (ImGuiIO&)ImGui::GetIO();
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 启用键盘控制
//
//    // 设置样式
//    ImGui::StyleColorsDark();
//
//    // 初始化后端
//    ImGui_ImplWin32_Init(hwnd);
//    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
//
//    // 主循环
//    bool done = false;
//    while (!done) {
//        // 处理窗口消息
//        MSG msg;
//        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
//            ::TranslateMessage(&msg);
//            ::DispatchMessage(&msg);
//            if (msg.message == WM_QUIT)
//                done = true;
//        }
//        if (done)
//            break;
//
//        // 开始新帧
//        ImGui_ImplDX11_NewFrame();
//        ImGui_ImplWin32_NewFrame();
//        ImGui::NewFrame();
//
//        // 创建你的GUI
//        ImGui::Begin("Hello, world!");
//        ImGui::Text("This is some useful text.");
//        ImGui::End();
//
//        // 渲染
//        ImGui::Render();
//        ImDrawData* drawData = (ImDrawData*)ImGui::GetDrawData();
//        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
//        // 将 ImVec4 转换为 FLOAT 数组
//        FLOAT clearColor[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
//        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);
//        ImGui_ImplDX11_RenderDrawData(drawData);
//
//        g_pSwapChain->Present(1, 0); // 垂直同步
//    }
//
//    // 清理
//    ImGui_ImplDX11_Shutdown();
//    ImGui_ImplWin32_Shutdown();
//    ImGui::DestroyContext();
//
//    CleanupDeviceD3D();
//    ::DestroyWindow(hwnd);
//    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
//
//    return 0;
//}
//
//// 辅助函数
//bool CreateDeviceD3D(HWND hWnd) {
//    // 设置交换链
//    DXGI_SWAP_CHAIN_DESC sd;
//    ZeroMemory(&sd, sizeof(sd));
//    sd.BufferCount = 2;
//    sd.BufferDesc.Width = 0;
//    sd.BufferDesc.Height = 0;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    sd.OutputWindow = hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = TRUE;
//    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//    UINT createDeviceFlags = 0;
//    D3D_FEATURE_LEVEL featureLevel;
//    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
//    if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
//        return false;
//
//    CreateRenderTarget();
//    return true;
//}
//
//void CleanupDeviceD3D() {
//    CleanupRenderTarget();
//    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
//    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
//    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
//}
//
//void CreateRenderTarget() {
//    ID3D11Texture2D* pBackBuffer;
//    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
//    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
//    pBackBuffer->Release();
//}
//
//void CleanupRenderTarget() {
//    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
//}
//
//// Win32消息处理函数
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
//        return true;
//
//    switch (msg) {
//    case WM_SIZE:
//        if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED) {
//            CleanupRenderTarget();
//            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
//            CreateRenderTarget();
//        }
//        return 0;
//    case WM_SYSCOMMAND:
//        if ((wParam & 0xfff0) == SC_KEYMENU) // 禁用ALT应用程序菜单
//            return 0;
//        break;
//    case WM_DESTROY:
//        ::PostQuitMessage(0);
//        return 0;
//    }
//    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
//}

//// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
//// 调试程序: F5 或调试 >“开始调试”菜单
//
//// 入门使用技巧: 
////   1. 使用解决方案资源管理器窗口添加/管理文件
////   2. 使用团队资源管理器窗口连接到源代码管理
////   3. 使用输出窗口查看生成输出和其他消息
////   4. 使用错误列表窗口查看错误
////   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
////   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
