#!/bin/bash

# Set the Docker image to use for all containers
IMAGE="maxv1z/httpserver"

# Define container names and CPU core assignments
SRV1="srv1"
SRV2="srv2"
SRV3="srv3"
CORE0="0"
CORE1="1"
CORE2="2"

# Define CPU usage thresholds and other parameters
BUSY_THRESHOLD=50
IDLE_THRESHOLD=10
CHECK_INTERVAL=10
CONSECUTIVE_COUNT=2
UPDATE_INTERVAL=600

# Get the CPU usage of a container
check_container_cpu() {
    local container_name=$1
    docker stats --no-stream --format "{{.CPUPerc}}" "$container_name" | tr -d '%' || echo "0"
}

# Update containers if a new image is available
update_containers() {
    echo "Checking for updates..."
    docker pull "$IMAGE"
    for container in $SRV1 $SRV2 $SRV3; do
        if docker ps | grep -q "$container"; then
            echo "Updating $container..."
            TEMP_CONTAINER="${container}_temp"
            docker run -d --name "$TEMP_CONTAINER" --cpuset-cpus="${!container^^_CORE}" "$IMAGE"
            docker stop "$container" && docker rm "$container"
            docker rename "$TEMP_CONTAINER" "$container"
        fi
    done
}

# Start SRV1 on core 0
echo "Starting $SRV1 on core $CORE0..."
docker run -d --name "$SRV1" --cpuset-cpus="$CORE0" -p 8080:80 "$IMAGE"

# Monitor containers and handle busy/idle states
while true; do
    current_time=$(date +%s)

    # Monitor SRV1
    if docker ps | grep -q "$SRV1"; then
        cpu_srv1=$(check_container_cpu "$SRV1")
        if (( $(echo "$cpu_srv1 > $BUSY_THRESHOLD" | bc -l) )); then
            ((busy_srv1++))
            if [[ $busy_srv1 -ge $CONSECUTIVE_COUNT && ! $(docker ps -q -f name=$SRV2) ]]; then
                docker run -d --name "$SRV2" --cpuset-cpus="$CORE1" "$IMAGE"
            fi
        else
            busy_srv1=0
        fi
    fi

    # Monitor SRV2
    if docker ps | grep -q "$SRV2"; then
        cpu_srv2=$(check_container_cpu "$SRV2")
        if (( $(echo "$cpu_srv2 > $BUSY_THRESHOLD" | bc -l) )); then
            ((busy_srv2++))
            if [[ $busy_srv2 -ge $CONSECUTIVE_COUNT && ! $(docker ps -q -f name=$SRV3) ]]; then
                docker run -d --name "$SRV3" --cpuset-cpus="$CORE2" "$IMAGE"
            fi
        else
            busy_srv2=0
        fi
    fi

    # Monitor SRV3 for idleness
    if docker ps | grep -q "$SRV3"; then
        cpu_srv3=$(check_container_cpu "$SRV3")
        if (( $(echo "$cpu_srv3 < $IDLE_THRESHOLD" | bc -l) )); then
            ((idle_srv3++))
            if [[ $idle_srv3 -ge $CONSECUTIVE_COUNT ]]; then
                docker stop "$SRV3" && docker rm "$SRV3"
            fi
        else
            idle_srv3=0
        fi
    fi

    # Check for updates every 10 minutes
    if (( current_time - last_update_time >= UPDATE_INTERVAL )); then
        update_containers
        last_update_time=$(date +%s)
    fi

    sleep "$CHECK_INTERVAL"
done
