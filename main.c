#include <cstdio>
#include <cstring>
#include <cassert>
const int maxn = 1007;
char* readline(char *str) {
    printf("root@docker:/# ");
    char *ret = fgets(str, maxn, stdin);
    str[strlen(str) - 1] = '\0';
    return ret;
}
char buf[maxn], str[maxn], cmd[maxn];
int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("docker id is required");
        return -1;
    }
    while (readline(buf)) {
        sprintf(cmd, "docker exec %s %s", argv[1], buf);
        FILE *p = popen(cmd, "r");
        if (p) {
            while (fgets(str, maxn, p)) {
                printf("%s", str);
            }
        }
        assert(pclose(p) != -1);
    }
    return 0;
}
