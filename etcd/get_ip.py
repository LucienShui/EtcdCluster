#!/usr/bin/env python3
import socket
from sys import argv


def get_host_ip(DNS):
    """
    get host ip address

    :return host ip:
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect((DNS, 80))
        ip = s.getsockname()[0]
    finally:
        s.close()

    return ip


def main():
    if argv.__len__() == 3 and argv[1] == '-dns':
        return get_host_ip(argv[2])
    elif argv.__len__() == 2 and '=' in argv[1]:
        return get_host_ip(argv[1].split('=')[1])
    else:
        return "-dns <your dns> or -dns=<your dns>"


if __name__ == '__main__':
    print(main())



