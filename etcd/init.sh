#!/usr/bin/env bash
if [[ ${#} != 2 ]]; then
    echo "<ID> & <DNS> is required"
    exit 0
fi
echo "ID=${1}" > .env
for ((i = 2000, j = 0; i < 10000 && j < 2; i++)) do
    if [[ $(lsof -i:${i}) == "" ]]; then
        echo "PORT_${j}=${i}" >> .env
        ((j++))
    fi
done
echo DNS=${2} >> .env
echo LOCAL_ADDR=$(python3 get_ip.py -dns=${2}) >> .env
docker-compose up

