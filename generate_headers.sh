#!/bin/bash

DIR=$(dirname $(readlink -f $0)) # Directory script is in
cd $DIR

HEADER=

function header() {
    HEADER="$1"
    echo > $HEADER
}

function write() {
    echo $@ >> $HEADER
}

function guard() {
    echo $HEADER | sed 's/\./_/g' | tr '/[a-z]' '_[A-Z]'
}

function define() {
    write "#define $@"
}

header "./include/_git_info.h"
write "#ifndef $(guard)"
write "#define $(guard)"
define GIT_BRANCH "\"$(git branch | grep -E '^\*' | cut -d' ' -f2)\""
define GIT_COMMIT "\"$(git show | head -n1 | cut -d' ' -f2)\""
write "#endif"
