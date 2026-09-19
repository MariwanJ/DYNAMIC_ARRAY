#!/bin/bash

set -e

premake5 gmake

if [ "$1" = "test" ]; then
    make config=debug tests
    ./bin/tests/tests
else
    make config=debug prj1
    ./bin/prj1/prj1
fi