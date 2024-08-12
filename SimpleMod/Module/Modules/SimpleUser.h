#pragma once
#include "../../../Utils/easylogging++.h"
#include "../../../Utils/Json.hpp"
using json = nlohmann::json;
class SimpleUser {
public:
	std::string time;
	std::string params;
	std::string token;
	std::string ID;
	std::string sign;
	std::string api_url;
	 
	SimpleUser();
	~SimpleUser();
public:
	std::string getSignature(const json& params);
	void DownloadFile(const std::string& api, const std::string& folder="downloaded_files\\");
	std::string makeHttpsRequest(std::string url, const char* parameter,...);
	std::string queryServer(const std::string& api, const std::string& additionalParams="");
	void SimpleUserinit(std::string userid, std::string token);
	bool pingServer();
	std::vector<std::string> getOrders(unsigned __int32 page = 1);
}; 
static SimpleUser user;
