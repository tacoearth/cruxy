#!/bin/bash
set -e
cmake --preset debug --fresh
cmake --build --preset debug
