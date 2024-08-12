#include "Hwid_user.h"
#include <chrono>
#include <ctime>
#include <comdef.h>

#include <openssl/md5.h>
#include "../Utils/Json.hpp"
#include "Module/Modules/SimpleUser.h"
#include <filesystem>

#include <intrin.h>

#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
int Hwid_user::expire_time;
namespace fs = std::filesystem;
using json = nlohmann::json;
std::string Hwid_user::calculateMD5(const std::string& input){
	unsigned char digest[MD5_DIGEST_LENGTH];
	MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (unsigned char c : digest) {
		ss << std::setw(2) << static_cast<unsigned int>(c);
	}
	return ss.str();
}
#include "../Memory/GameData.h"
bool Hwid_user::fileauth(){
	std::string line;
	std::ifstream inputFile("Auth");
	if (inputFile.is_open()) {
		while (std::getline(inputFile, line));
		json params = { {"page", 1} };
		std::string result = user.queryServer("http://afdian.net/api/open/query-sponsor", user.getSignature(params));
		json jsonResponse = json::parse(result);

		if (jsonResponse["ec"] == 200) {
            int e = 1;
            for (int i = 0; i < jsonResponse["data"]["total_count"].get<int>();e++) {
                json parameter = { {"page", e} };
                std::string results = user.queryServer("http://afdian.net/api/open/query-sponsor", user.getSignature(parameter));
                json Response = json::parse(results);
                json dataList = Response["data"]["list"];
                i += Response.size();
                if (Response["ec"] == 200) {
                    for (auto& item : dataList) {
                        //LOG(INFO) << calculateMD5(item["user"]["user_id"].get<std::string>() + GetHwid() + "vqSKa4hUYNkjF3VertdCJxfb8p5nmXwB")<< item["user"]["name"].get<std::string>().c_str();
                        //Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod]用户 >> %s %s", GREEN, item["user"]["name"].get<std::string>().c_str(), item["user"]["user_id"].get<std::string>().c_str());
                        if (calculateMD5(item["user"]["user_id"].get<std::string>() + GetHwid() + "vqSKa4hUYNkjF3VertdCJxfb8p5nmXwB") == line) {
                            Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod]用户 >> %s", GREEN, item["user"]["name"].get<std::string>().c_str());
                            expire_time = item["sponsor_plans"][0]["expire_time"].get<int>();
                            return true;
                        }
                    }
                
                }
                else {
                    Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
                    return false;
                }

            }
		}
        else {
            Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
			return false;
        }
	}
	else {
		Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%shwid已生成到目录下！",RED);
		std::ofstream outputFile("Hwid.txt");
		if (outputFile.is_open()) {
			outputFile << GetHwid().c_str() << std::endl;
			outputFile.close();
		}
	}
	return false;
}
bool Hwid_user::isTime(int untime){
	json params = { {"page", 1} };
	std::string time = user.queryServer("http://afdian.net/api/open/ping", user.getSignature(params));
	json jsonResponse = json::parse(time);
	if (jsonResponse["ec"] == 200) {
		if (jsonResponse["data"]["request"]["ts"] < untime)
			return true;
		
	}
	else 
		return false;
	return false;
}

std::string Hwid_user::GetHwid(){
	return GetCpuId()+"-"+ GetVolumeSerialNumber();
}
std::string Hwid_user::GetCpuId(){
	int cpuInfo[4] = { -1 };
	char cpuId[32] = { 0 };
	__cpuid(cpuInfo, 0);
	snprintf(cpuId, sizeof(cpuId), "%X-%X-%X-%X", cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
	return std::string(cpuId);
}

std::string Hwid_user::GetBiosSerialNumber(){
    HRESULT hres;

    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        return "";
    }

    // Set general COM security levels
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    if (FAILED(hres)) {
        CoUninitialize();
        return "";
    }

    // Obtain the initial locator to WMI
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres)) {
        CoUninitialize();
        return "";
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc);

    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return "";
    }

    // Set security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE);

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "";
    }

    // Use the IWbemServices pointer to make requests of WMI
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT SerialNumber FROM Win32_BIOS"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "";
    }

    // Get the data from the query
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    std::string biosSerial = "";

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;
        hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hr)) {
            biosSerial = _bstr_t(vtProp.bstrVal);
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return biosSerial;
}
	
std::string Hwid_user::GetVolumeSerialNumber(){
	DWORD serialNumber = 0;
	if (GetVolumeInformationA("C:\\", NULL, 0, &serialNumber, NULL, NULL, NULL, 0)) {
		return std::to_string(serialNumber);
	}
}

