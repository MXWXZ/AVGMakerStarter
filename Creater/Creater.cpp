// Creater.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Resource.h"

using namespace std;
char kTitle[60];
char kFile[MAX_PATH];
int kWidth;
int kHeight;

bool ExpandFile() {
    DWORD   dwWrite = 0;  
    HANDLE  hFile = CreateFile(kFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    HRSRC   hrsc = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE1), "EXE");
    HGLOBAL hG = LoadResource(NULL, hrsc);
    DWORD   dwSize = SizeofResource(NULL, hrsc); 
    WriteFile(hFile, hG, dwSize, &dwWrite, NULL);
    CloseHandle(hFile);

    return true;
}

bool ChangeFile() {
    ofstream fp(kFile, ios::out | ios::binary | ios::_Nocreate);
    if (!fp)
        return false;
    fp.seekp(0x19BC, ios::beg); // title
    fp.write(kTitle, strlen(kTitle) + 1);
    fp.seekp(0x646, ios::beg); // width1
    fp.write((char*)&kWidth, sizeof(int));
    fp.seekp(0x65E, ios::beg); // width2
    fp.write((char*)&kWidth, sizeof(int));
    fp.seekp(0x641, ios::beg); // height1
    fp.write((char*)&kHeight, sizeof(int));
    fp.seekp(0x659, ios::beg); // height2
    fp.write((char*)&kHeight, sizeof(int));
    return true;
}

int main() {
    cout << "#############################################" << endl;
    cout << "#  简易版橙光游戏免审核发布生成器  by MXWXZ #" << endl;
    cout << "#############################################" << endl << endl;
    cout << "请输入生成文件名（无需后缀名，将会覆盖当前目录下同名文件！）：" << endl;
    cin >> kFile;
    strcat_s(kFile, ".exe");
    getchar();  // eat /n
    cout << "请输入窗口标题（自动创建器限制<=50字符，中文算两个，如果需要超过50字符的请自行修改编译AVGMakerStarter工程）：" << endl;
    cin.getline(kTitle, 50);
    cin.clear();
    cin.sync();
    cout << "请输入工程窗口宽度：" << endl;
    cin >> kWidth;
    cout << "请输入工程窗口高度：" << endl;
    cin >> kHeight;
    cout << endl<<"请确认输入是否正确，不要指望程序自动检测:P" << endl;
    system("pause");
    cout << "正在生成文件..." << endl;
    if (!ExpandFile()) {
        cout << "生成失败！请检查权限或输入是否有误！" << endl;
        DeleteFile(kFile);
        return 0;
    }
    cout << "正在修改文件..." << endl;
    if (!ChangeFile()) {
        cout << "修改失败！请检查权限或输入是否有误！" << endl;
        DeleteFile(kFile);
        return 0;
    }

    cout << "一切正常！" << endl;
    system("pause");
    return 0;
}

