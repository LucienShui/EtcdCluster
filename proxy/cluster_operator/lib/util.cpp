//
// Created by LucienShui on 2019-04-07.
//

#include "util.h"

bool seven::etcd::exec(const std::string &cmd) {
#ifdef DEBUG
    FILE *system_out = popen(cmd.c_str(), "r");
#else
    FILE *system_out = popen(("docker exec " + container + " etcdctl " + cmd).c_str(), "r");
#endif

    if (system_out) {
        std::string out;
        int buf;
        while (~(buf = fgetc(system_out))) out.push_back(char(buf));
        std::cout << out << std::flush;
        return true;
    }
    return false;
}

void seven::etcd::run() {
    std::string buf;
    std::cout << "Cluster Operator 0.0.1\n"
                 "Type \"help\" for more information" << std::endl;
    while (std::cout << ">>> " << std::flush,
            std::getline(std::cin, buf) && buf != "exit") this->exec(buf);
}
