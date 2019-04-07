//
// Created by LucienShui on 2019-04-07.
//

#ifndef ETCDOPERATOR_UTIL_H
#define ETCDOPERATOR_UTIL_H

#include <string>
#include <iostream>
#include <utility>

namespace seven {
    struct etcd {
    private:
        std::string container;
    public:
        explicit etcd(std::string container):container(std::move(container)) {}
        bool exec(const std::string &cmd);
        void run();
    };
}

#endif //ETCDOPERATOR_UTIL_H
