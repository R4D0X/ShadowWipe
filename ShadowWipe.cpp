#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <tlhelp32.h>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

void Run(const string& cmd) {
    system(cmd.c_str());
}
void DisableHiber() {
    Run("powercfg -h off");
}
void Shadows() {
    Run("vssadmin delete shadows /all /quiet");
}
void ShellBags() {
    Run("reg delete \"HKCU\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
    Run("reg delete \"HKCU\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");
}
void ClearLNKDosya() {
    string userProfile = getenv("USERPROFILE");
    Run("del /f /s /q \"" + userProfile + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\*.lnk\"");
}
void ClearUSNGnlk() {
    Run("fsutil usn deletejournal /d C:");
}

void GeriYukleme() {
    Run("vssadmin delete shadows /all /quiet");
    Run("wmic shadowcopy where \"Volume='C:\\'\" delete");
    Run("wmic shadowcopy delete");
}
void ClearFullPrefetch() {
    Run("del /f /s /q C:\\Windows\\Prefetch\\*");
    Run("del /f /q C:\\Windows\\Prefetch\\Layout.ini");
    Run("del /f /q C:\\Windows\\Prefetch\\ReadyBoot\\*");
}
void PageFWipeShutdown() {
    Run("reg add \"HKLM\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\" /v ClearPageFileAtShutdown /t REG_DWORD /d 1 /f");
}
void EventLogs() {
    Run("for /f \"tokens=*\" %i in ('wevtutil.exe el') do wevtutil.exe cl \"%i\"");
}
void FlushDNSARP() {
    Run("ipconfig /flushdns");
    Run("netsh winsock reset");
    Run("netsh int ip reset");
    Run("arp -d *");
}
void ClearTemp() {
    Run("del /f /s /q %TEMP%\\*");
    Run("del /f /s /q \"%APPDATA%\\Temp\\*\"");
    Run("del /f /s /q C:\\Windows\\Prefetch\\*");
}
void Cop() {
    Run("PowerShell.exe -Command \"Clear-RecycleBin -Force\"");
}
void ClearShell() {
    string base = getenv("APPDATA");
    string paths[] = {
        base + "\\Microsoft\\Windows\\Recent",
        base + "\\Microsoft\\Windows\\Recent\\AutomaticDestinations",
        base + "\\Microsoft\\Windows\\Recent\\CustomDestinations"
    };
    for (auto& path : paths) {
        Run("del /f /s /q \"" + path + "\\*\"");
    }
}
void Registry() {
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Internet Explorer\\TypedURLs\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\TypedPaths\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\ShellNoRoam\\MUICache\" /f");
    Run("reg delete \"HKCU\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
    Run("reg delete \"HKCU\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\" /f");
    Run("reg delete \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRU\" /f");
}
void Browser() {
    string user = getenv("USERNAME");
    string localAppData = getenv("LOCALAPPDATA");
    string appData = getenv("APPDATA");

    Run("taskkill /f /im chrome.exe");
    Run("del /f /s /q \"" + localAppData + "\\Google\\Chrome\\User Data\\Default\\History\"");
    Run("del /f /s /q \"" + localAppData + "\\Google\\Chrome\\User Data\\Default\\Cookies\"");
    Run("del /f /s /q \"" + localAppData + "\\Google\\Chrome\\User Data\\Default\\Cache\\*\"");

    Run("taskkill /f /im msedge.exe");
    Run("del /f /s /q \"" + localAppData + "\\Microsoft\\Edge\\User Data\\Default\\*\"");

    Run("taskkill /f /im firefox.exe");
    Run("del /f /s /q \"" + appData + "\\Mozilla\\Firefox\\Profiles\\*.default*\\places.sqlite\"");
    Run("del /f /s /q \"" + appData + "\\Mozilla\\Firefox\\Profiles\\*.default*\\cookies.sqlite\"");
    Run("del /f /s /q \"" + appData + "\\Mozilla\\Firefox\\Profiles\\*.default*\\cache2\\*\"");

    Run("taskkill /f /im brave.exe");
    Run("del /f /s /q \"" + localAppData + "\\BraveSoftware\\Brave-Browser\\User Data\\Default\\History\"");
    Run("del /f /s /q \"" + localAppData + "\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cookies\"");
    Run("del /f /s /q \"" + localAppData + "\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cache\\*\"");

    Run("taskkill /f /im opera.exe");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera Stable\\History\"");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera Stable\\Cookies\"");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera Stable\\Cache\\*\"");

    Run("taskkill /f /im opera.exe");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera GX Stable\\History\"");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera GX Stable\\Cookies\"");
    Run("del /f /s /q \"" + appData + "\\Opera Software\\Opera GX Stable\\Cache\\*\"");

    Run("taskkill /f /im vivaldi.exe");
    Run("del /f /s /q \"" + localAppData + "\\Vivaldi\\User Data\\Default\\History\"");
    Run("del /f /s /q \"" + localAppData + "\\Vivaldi\\User Data\\Default\\Cookies\"");
    Run("del /f /s /q \"" + localAppData + "\\Vivaldi\\User Data\\Default\\Cache\\*\"");
}

void BrowserR() {
    string user = getenv("USERNAME");
    string base = "C:\\Users\\" + user + "\\AppData\\Local\\";
    string roaming = "C:\\Users\\" + user + "\\AppData\\Roaming\\";

    struct Browser {
        string name;
        string path;
    };

    vector<Browser> browsers = {
        {"Chrome", base + "Google\\Chrome\\User Data\\Default\\"},
        {"Edge", base + "Microsoft\\Edge\\User Data\\Default\\"},
        {"Brave", base + "BraveSoftware\\Brave-Browser\\User Data\\Default\\"},
        {"Opera", roaming + "Opera Software\\Opera Stable\\"},
        {"OperaGX", roaming + "Opera Software\\Opera GX Stable\\"}
    };

    for (const auto& b : browsers) {
        vector<string> targets = {
            "History", "Login Data", "Web Data", "Visited Links", "Cookies",
            "Top Sites", "Local Storage", "Session Storage", "Preferences", "Favicons", "Download History"
        };
        for (const auto& file : targets) {
            string fullPath = b.path + file;
            DeleteFileA(fullPath.c_str());
        }
    }

    string profileBase = roaming + "Mozilla\\Firefox\\Profiles\\";
    for (const auto& entry : fs::directory_iterator(profileBase)) {
        if (fs::is_directory(entry.path())) {
            string profilePath = entry.path().string();
            vector<string> ffFiles = {
                "places.sqlite", "cookies.sqlite", "webappsstore.sqlite", "formhistory.sqlite",
                "logins.json", "key4.db"
            };
            for (const auto& file : ffFiles) {
                DeleteFileA((profilePath + "\\" + file).c_str());
            }
        }
    }
}

void Pano() {
    Run("del /f /s /q %LOCALAPPDATA%\\Microsoft\\Windows\\Explorer\\thumbcache_*.db");
}
void SearchGecmis() {
    Run("del /f /q \"%USERPROFILE%\\AppData\\Local\\Microsoft\\Windows\\Explorer\\SearchHistory\\*\"");
}
void TaskKill() {
    Run("taskkill /f /im chrome.exe");
    Run("taskkill /f /im firefox.exe");
    Run("taskkill /f /im msedge.exe");
    Run("taskkill /f /im brave.exe");
    Run("taskkill /f /im opera.exe");
    Run("taskkill /f /im vivaldi.exe");
}
void ClearADS(const string& filePath) {
    string ads = filePath + ":secret";
    DeleteFileA(ads.c_str());
}

// Belirli dosya için (C Diskini eklemeyin önerilmez)

// void ADSClear(const string& dirPath) {
//     for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
//         if (!fs::is_regular_file(entry.status())) continue;
//         string ads = entry.path().string() + ":secret";
//         DeleteFileA(ads.c_str());
//     }
// }

void TimeStompFile(const string& filepath, SYSTEMTIME st = {2020, 1, 0, 1, 12, 0, 0, 0}) {
    HANDLE hFile = CreateFileA(filepath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        FILETIME ft;
        SystemTimeToFileTime(&st, &ft);
        SetFileTime(hFile, &ft, &ft, &ft);
        CloseHandle(hFile);
    }
}
void Amcache() {
    Run("reg delete \"HKLM\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCompatCache\" /f");
    Run("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Amcache\" /f");
    DeleteFileA("C:\\Windows\\AppCompat\\Programs\\Amcache.hve");
}

int main() {
    
    DisableHiber();
    Shadows();
    ShellBags();
    ClearLNKDosya();
    ClearUSNGnlk();
    //ADSClear("C:\\");;
    GeriYukleme();
    ClearFullPrefetch();
    PageFWipeShutdown();
    EventLogs();
    FlushDNSARP();
    ClearTemp();
    Cop();
    ClearShell();
    Registry();
    Browser();
    BrowserR();
    Pano();
    SearchGecmis();
    TaskKill();
    ClearADS("C:\\");
    Amcache();

    return 0;
}
