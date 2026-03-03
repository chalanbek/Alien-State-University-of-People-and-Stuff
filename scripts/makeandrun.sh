#!/usr/bin/env bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

cd "$DIR/../"
cmake -B build
cmake --build build
./bin/AlienStateUniversityofPeopleandStuff