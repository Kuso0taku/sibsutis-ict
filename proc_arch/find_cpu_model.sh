#!/bin/bash
cat /proc/cpuinfo | awk '/model name/ {print $8}' | head -n 1 > cpu_model
