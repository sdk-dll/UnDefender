#include "UnDefender.h"


int main() {
    SetConsoleTitle("UnDefender");

    std::wcout << R"(
  _    _       _____        __               _           
 | |  | |     |  __ \      / _|             | |          
 | |  | |_ __ | |  | | ___| |_ ___ _ __   __| | ___ _ __ 
 | |  | | '_ \| |  | |/ _ \  _/ _ \ '_ \ / _` |/ _ \ '__|
 | |__| | | | | |__| |  __/ ||  __/ | | | (_| |  __/ |   
  \____/|_| |_|_____/ \___|_| \___|_| |_|\__,_|\___|_|   
                                                         
                                                         
)" << std::endl;


    HKEY hKey;
    const char* subKey = "SOFTWARE\\Policies\\Microsoft\\Windows Defender";
    const char* valueName = "DisableAntiSpyware";
    DWORD data = 1;

    if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, NULL, 0, KEY_SET_VALUE | KEY_QUERY_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        DWORD dataType;
        DWORD dataSize = sizeof(data);
        DWORD existingData = 0;

        if (RegQueryValueExA(hKey, valueName, 0, &dataType, reinterpret_cast<LPBYTE>(&existingData), &dataSize) == ERROR_FILE_NOT_FOUND) {
            if (RegSetValueExA(hKey, valueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data)) == ERROR_SUCCESS) {
                std::cout << "Successfully!" << std::endl;
            }
            else {
                std::cerr << "Failed to create registry value." << std::endl;
            }
        }
        else if (dataType == REG_DWORD) {
            if (RegSetValueExA(hKey, valueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data)) == ERROR_SUCCESS) {
                std::cout << "Successfully!" << std::endl;
            }
            else {
                std::cerr << "Failed to update registry value." << std::endl;
            }
        }
        else {
            std::cerr << "Existing registry value is not of type DWORD." << std::endl;
        }

        RegCloseKey(hKey);
    }
    else {
        std::cerr << "Failed to open or create registry key." << std::endl;
    }
    system("pause");
    return 0;
}
