#!/bin/bash

while true; d
    sleep_time=$((RANDOM % 3 + 3))

    echo "Waiting $sleep_time seconds before the next request..."

    sleep $sleep_time
    curl -i -X GET "127.0.0.1/compute" &

    echo "HTTP GET request sent asynchronously."
doness