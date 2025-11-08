#!/bin/bash
make
find_cpu_model.sh
cpu_model=$(cat cpu_model)
read -e -p "Enter a number: "
printf "$cpu_model\n$REPLY" | main
