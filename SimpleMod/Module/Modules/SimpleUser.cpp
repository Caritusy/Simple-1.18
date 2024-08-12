//#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "libcrypto_static.lib")
//#pragma comment(lib, "libcrypto_static.lib")
//#pragma comment(lib, "libssl_static.lib")
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>

#include "SimpleUser.h"
#include <openssl/md5.h>
#include "../../../Memory/GameData.h"
#include <filesystem>

#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")

using boost::asio::ip::tcp;

std::string calculateMD5(const std::string& input) {
	unsigned char digest[MD5_DIGEST_LENGTH];
	MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), digest);
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (unsigned char c : digest) {
		ss << std::setw(2) << static_cast<unsigned int>(c);
	}
	return ss.str();
}
SimpleUser::SimpleUser() {
}
void SimpleUser::SimpleUserinit(std::string userid, std::string Token) {
	ID = userid;
	token = Token;
}
std::string SimpleUser::getSignature(const json& params) {
    std::string params_str = params.dump();
    std::string signature = "爱发电Token" + std::string("params") + params_str + "ts" + std::to_string(std::time(nullptr)) + "user_id" + "76c659c0b43b11eea14352540025c377";
    json request_json = {
        {"user_id", "爱发电USERID"},
        {"params", params_str},
        {"ts", std::time(nullptr)},
        {"sign", calculateMD5(signature)}
    };
    return request_json.dump();
}
void SimpleUser::DownloadFile(const std::string& url, const std::string& local_path) {
    std::size_t last_slash_pos = local_path.find_last_of("\\/");
    std::string directory = local_path.substr(0, last_slash_pos);
    if (std::filesystem::exists(local_path))
        return;

    std::filesystem::create_directories(directory);  // Ensure directories are created

    HRESULT hr = URLDownloadToFile(
        NULL,
        url.c_str(),
        local_path.c_str(),
        0,
        NULL);

    if (SUCCEEDED(hr)) {
        LOG(INFO) << "Downloaded: " << local_path << std::endl;
    }
    else {
        LOG(INFO) << "Failed to download file. Error: " << hr << std::endl;
    }
}

SimpleUser::~SimpleUser() {
}

std::string SimpleUser::makeHttpsRequest(std::string url, const char* parameter, ...) {
	va_list arg;
	va_start(arg, parameter);

	auto lengthNeeded = _vscprintf(parameter, arg) + 1;
	if (lengthNeeded >= 300) {
		LOG(DEBUG) << "A message that was" << lengthNeeded << "characters long could not be fitted into the buffer";
		return "";}
	char message[300];
	vsprintf_s(message, 300, parameter, arg);
	va_end(arg);
	std::string msg(message);
	std::string respond;
	try {queryServer(url, msg);}
	catch (std::exception& e) {
		LOG(INFO) << "Exception: " << e.what();
		return "";
	}	
	return respond;
}

std::string SimpleUser::queryServer(const std::string& api, const std::string& additionalParams) {
    std::string protocol, host, path;
    std::size_t protocol_pos = api.find("://");
    if (protocol_pos != std::string::npos) {
        protocol = api.substr(0, protocol_pos);
        std::size_t host_pos = api.find('/', protocol_pos + 3);
        if (host_pos != std::string::npos) {
            host = api.substr(protocol_pos + 3, host_pos - protocol_pos - 3);
            path = api.substr(host_pos);
        }
        else {
            host = api.substr(protocol_pos + 3);
            path = "/";
        }
    }
    else {
        throw std::invalid_argument("Invalid API URL");
    }

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host, protocol == "https" ? "443" : "80");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    std::string request;
    if (!additionalParams.empty()) {
        request = "POST " + path + " HTTP/1.1\r\n"
            "Host: " + host + "\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(additionalParams.length()) + "\r\n"
            "Connection: close\r\n\r\n" + additionalParams;
    }
    else {
        request = "GET " + path + " HTTP/1.1\r\n"
            "Host: " + host + "\r\n"
            "Connection: close\r\n\r\n";
    }
    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf response;
    boost::system::error_code error;
    boost::asio::read(socket, response, boost::asio::transfer_all(), error);

    std::istream response_stream(&response);
    std::string response_data((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());

    socket.shutdown(tcp::socket::shutdown_both, error);
    socket.close();

    // Find the end of the headers
    std::size_t header_end = response_data.find("\r\n\r\n");
    if (header_end != std::string::npos) {
        response_data = response_data.substr(header_end + 4);
    }

    // Remove chunked transfer encoding
    std::stringstream body;
    std::string::size_type pos = 0;
    while (true) {
        std::size_t chunk_size_end = response_data.find("\r\n", pos);
        if (chunk_size_end == std::string::npos) {
            std::cerr << "Error: Chunk size delimiter not found" << std::endl;
            break;
        }
        std::string chunk_size_str = response_data.substr(pos, chunk_size_end - pos);
        std::size_t chunk_size;
        try {
            chunk_size = std::stoul(chunk_size_str, nullptr, 16);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid chunk size: " << chunk_size_str << std::endl;
            break;
        }
        if (chunk_size == 0) {
            break;
        }
        pos = chunk_size_end + 2;
        if (pos + chunk_size > response_data.size()) {
            std::cerr << "Error: Chunk size exceeds remaining data size" << std::endl;
            break;
        }
        body.write(response_data.data() + pos, chunk_size);
        pos += chunk_size + 2; // Skip the chunk data and the trailing \r\n
    }

    return body.str();
}

bool SimpleUser::pingServer() {
	std::string result = queryServer("https://afdian.net/api/open/ping");
	json jsonResponse = json::parse(result);
	if (jsonResponse["ec"] == 200) {
		return true;
	}
	LOG(DEBUG) << "响应: " << jsonResponse["ec"];
	return false;
}

std::vector<std::string> SimpleUser::getOrders(unsigned __int32 page) {
	std::string result = queryServer("query-order", "$page [1]");
	json jsonResponse = json::parse(result);
	if (jsonResponse["ec"] == 200) {
		json dataList = jsonResponse["data"]["list"];
		std::vector<std::string> customOrderIds;
		for (auto& item : dataList) {
			customOrderIds.emplace_back("UserName:" + jsonResponse["custom_order_id"]);
			customOrderIds.emplace_back(u8"订单号:" + jsonResponse["out_trade_no"]);
			customOrderIds.emplace_back(u8"用户ID:" + jsonResponse["user_id"]);
			customOrderIds.emplace_back(u8"赞助月份:" + jsonResponse["month"]);
			customOrderIds.emplace_back(u8"交易状态:" + jsonResponse["status"]);
			customOrderIds.emplace_back(u8"留言:" + jsonResponse["remark "]);
		}
		return customOrderIds;
	}
	return jsonResponse["ec"];
}
