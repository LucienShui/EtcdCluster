#include <iostream>
#include "lib/util.h"

int main() {
    seven::etcd("etcd_proxy").run();
    return 0;
}