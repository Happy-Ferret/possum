#!/bin/bash

TEST_DISPLAY=:1

VERBOSE=false

if [ "$1" == "-v" ]; then
    VERBOSE=true
fi

function run() {
    sleep 1
    echo "Starting $1..."
    if $VERBOSE; then
        DISPLAY="$TEST_DISPLAY" $@
    else
        DISPLAY="$TEST_DISPLAY" $@ &>/dev/null
    fi
}

echo "Starting X server..."
if $VERBOSE; then
    X $TEST_DISPLAY &
else
    X $TEST_DISPLAY &>/dev/null &
fi
X_PID=$!

run ./possum &
run xterm

echo "Killing X server..."
kill $X_PID

echo

