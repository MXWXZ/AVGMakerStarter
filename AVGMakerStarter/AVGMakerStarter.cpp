// AVGMakerStarter.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AVGMakerStarter.h"

// 一般只需要修改这三个配置然后改一下AVGMakerStarter.ico图标就可以了

const char kGameName[] = "修改此标题为游戏标题如果用自动创建器不超过五十字符";
const int kGameWidth = 961;
const int kGameHeight = 541;

// 如果不清楚不要修改下面的代码

BOOL UrlEncode(const char* v_src, char* v_buf, int v_len, BOOL v_isall) {
    if (!v_src || !v_buf || v_len <= 0)
        return FALSE;

    size_t len_ascii = strlen(v_src);
    if (len_ascii == 0) {
        v_buf[0] = 0;
        return TRUE;
    }

    char base_char = 'a';
    int len_widechar = MultiByteToWideChar(CP_ACP, 0, v_src,
                                           len_ascii, NULL, 0);
    LPWSTR str_unicode = new wchar_t[len_widechar + 1];
    MultiByteToWideChar(CP_ACP, 0, v_src, len_ascii, str_unicode,
                        len_widechar + 1);

    int len_utf8 = WideCharToMultiByte(CP_UTF8, 0, str_unicode,
                                       len_widechar, NULL, 0, NULL, NULL);
    LPSTR str_utf8 = new char[len_utf8 + 1];
    WideCharToMultiByte(CP_UTF8, 0, str_unicode, len_widechar,
                        str_utf8, len_utf8 + 1, NULL, NULL);
    str_utf8[len_utf8] = '\0';

    unsigned char c;
    int cnt = 0;
    unsigned char *psrc = (unsigned char*)str_utf8;
    unsigned char *pdest = (unsigned char*)v_buf;
    while (*psrc && cnt < v_len - 1) {
        c = *psrc;
        if (!v_isall && (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~')) {
            *pdest = c;
            ++pdest;
            ++cnt;
        } else if (!v_isall &&c == ' ') {
            *pdest = '+';
            ++pdest;
            ++cnt;
        } else {
            if (cnt + 3 > v_len - 1)
                break;
            pdest[0] = '%';
            pdest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + base_char) : ((c >> 4) + '0');
            pdest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + base_char) : ((c & 0xF) + '0');
            pdest += 3;
            cnt += 3;
        }
        ++psrc;
    }
    *pdest = '\0';
    delete[]str_unicode;
    delete[]str_utf8;
    return TRUE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow) {
    /*
    格式:
    {"OpenWindow":{"Width":"960","Height":"540",
    "Pathname":"[PATH]\interpreter\H5\bin\index.html?mark=pc",
    "Local":"True","Protocol":"file:","Slashes":"True",
    "ProjectName":"[NAME]","TitleBarStyle":"","SkipTaskbar":"False",
    "Guid":"","Uid":"0","Gindex":"0","SessionID":"","MSource":"10",
    "AlwaysOnTop":"False","OpenGame":{"ProjectWidth":960,"ProjectHeight":540,
    "MapID":1,"ProjectPath":"[GAMEPATH]",
    "FilePath":"[PATH]\interpreter\H5\UserData"}}}
    */
    char path[MAX_PATH];
    _getcwd(path, MAX_PATH);
    char pathenc[100000];
    UrlEncode(path, pathenc, 100000, true);
    char nameenc[1000];
    UrlEncode(kGameName, nameenc, 1000, true);
    char argument[100000];  // at most 32699
    sprintf_s(argument, "{\"OpenWindow\":{\"Width\":\"%d\",\"Height\":\"%d\",\"Pathname\":\"%s%%5c%%48%%35%%5c%%62%%69%%6e%%5c%%69%%6e%%64%%65%%78%%2e%%68%%74%%6d%%6c%%3f%%6d%%61%%72%%6b%%3d%%70%%63\",\"Local\":\"True\",\"Protocol\":\"file:\",\"Slashes\":\"True\",\"ProjectName\":\"%s\",\"TitleBarStyle\":\"\",\"SkipTaskbar\":\"False\",\"Guid\":\"\",\"Uid\":\"0\",\"Gindex\":\"0\",\"SessionID\":\"\",\"MSource\":\"10\",\"AlwaysOnTop\":\"False\",\"OpenGame\":{\"ProjectWidth\":%d,\"ProjectHeight\":%d,\"MapID\":1,\"ProjectPath\":\"%s%%5c%%47%%61%%6d%%65\",\"FilePath\":\"%s%%5c%%48%%35%%5c%%55%%73%%65%%72%%44%%61%%74%%61\"}}}",
              kGameWidth, kGameHeight, pathenc, nameenc, kGameWidth, kGameHeight, pathenc, pathenc);
    char argumentenc[100000];
    UrlEncode(argument, argumentenc, 100000, false);
    ShellExecute(NULL, "open", "H5\\AVG_Web_Browser.exe", argumentenc, NULL, SW_SHOWNORMAL);
    return 0;
}