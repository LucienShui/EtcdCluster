#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "../../cpp-socket/lib/socket.h"
#include "../../cpp-socket/lib/socket.cpp"
using cpp_socket::error;
std::pair<std::string, std::string> split(const std::string &str) {
    size_t pos = str.find('=');
    if (pos == std::string::npos) {
        error("wront config file");
    }
    return {str.substr(0, pos), str.substr(pos + 1, str.length() - pos - 1)};
}
std::map<std::string, std::string> value;
std::vector<std::string> required =
        {"ID",  // etcd identity
         "DNS",  // dns server's ip
         "WEB_ADDR",  // srv's domain
         "PORT_0",
         "PORT_1",
         "ETCD_TOKEN",  // cluster's token
         "STATE",  // cluster's state
         "LOCAL_IP",  // this node's ip
         "CLUSTER_ADDR"};  // cluster's address, url allowed

int main() {
    for (const auto &each : required) value[each] = "";
    {
        std::ifstream file;
        file.open("config.txt", std::ios::in);
        std::string line; while (std::getline(file, line)) {
            auto pair = split(line);
            value[pair.first] = std::move(pair.second);
        }
        for (const auto &each : required) if (value[each].empty() && each[0] != 'C') error("wrong config file");
    }

    bool flag = true;

    // send to proxy node
    if (value["STATE"] == "existing") {
        if (value["CLUSTER_ADDR"].empty()) {
            error("STATE or CLUSTER_ADDR wrong");
        }
        flag &= cpp_socket::client(value["CLUSTER_ADDR"].c_str(), 4399).send((
                "member add etcd" + value["ID"] +
                " http://etcd" + value["ID"] + "." + value["WEB_ADDR"] + ":" +
                value["PORT_1"]).c_str());
    }

    // send to dns server
    flag &= cpp_socket::client(value["DNS"].c_str(), 4399).send(
            ("etcd" + value["ID"] + " " + value["LOCAL_IP"]).c_str());

    if (flag) {
        std::ofstream file;
        file.open(".env", std::ios::out | std::ios::trunc);
        for (const auto &each : value) {
            file << each.first << '=' << each.second << std::endl;
        }
    }
    return 0;
}
