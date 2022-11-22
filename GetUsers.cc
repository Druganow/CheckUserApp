#include <napi.h>
#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <string>

/// <summary>
/// Generates a string of Windows users.
/// </summary>
/// <param name="info">The object contains the arguments passed by the caller.</param>
/// <returns>A string of Windows users.</returns>
Napi::String GetUsersList(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    setlocale(LC_ALL, "Rus");
    DWORD dwlevel = 0;
    DWORD dwfilter = 0;
    USER_INFO_0* theEntries = new USER_INFO_0[20];
    DWORD dwprefmaxlen = 512;
    DWORD dwentriesread;
    DWORD dwtotalentries;
    NET_API_STATUS result;
    std::wstring resStr = L"";
    result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);
    for (int i = 0; i < dwentriesread; i++)
    {
        resStr += theEntries[i].usri0_name;
	    if (i<dwentriesread-1)
        {
	        resStr += L"@";
        }
    }
    NetApiBufferFree(theEntries);

    return Napi::String::New(env, std::u16string(resStr.begin(), resStr.end()));
}

/// <summary>
/// Initializes the module.
/// </summary>
/// <param name="env">A local copy of CallbackInfo.</param>
/// <param name="exports">Contains function names.</param>
/// <returns></returns>
Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "GetUsersList"), Napi::Function::New(env, GetUsersList));
    return exports;
};

NODE_API_MODULE(GetUsers, init);