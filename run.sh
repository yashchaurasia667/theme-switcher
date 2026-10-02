#!/usr/bin/env bash

echo "running cmake --build build"
echo $(cmake --build build)

echo "running ./build/theme_switcher"
$(./build/theme_switcher)
