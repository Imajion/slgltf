#!/bin/bash

#--------------------------------------------------------------------------------------------------
TEST=$1
APPNAME="slgltf"

if [ -z $TEST ]; then
    TEST="$SHDIR/${APPNAME}-test"
fi

if [ ! -f $TEST ]; then
    TEST="cmake --build ./bld --target ${APPNAME}-test"
fi

$TEST