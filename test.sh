#!/bin/bash

set -e

if [ $# -ne 1 ];then
    echo "`basename $0` <dir>"
    exit 1
fi

dir=$1
echo "test: $(cd $dir && pwd)"
cd $dir
make test -f ../Makefile

succ=0
fail=0
for input in *.in; do
    output=${input/.in/.out}

    result=`./test < $input`
    expect=`cat $output`

    if [ "$result" != "$expect" ]; then
        echo "fail on: $input"
        echo "------------------------------"
        cat $input
        echo "------------------------------"
        echo "expect:"
        echo "$expect"
        echo "------------------------------"
        echo "result:"
        echo "$result"
        echo "------------------------------"
        echo

        fail=$((fail+1))
    else
        echo "Success on: $input"
        succ=$((succ+1))
    fi
done

echo "succ: $succ, fail: $fail"
if [ $fail == 0 ];then
    echo "All test done successfully!"
else
    echo "Some test fail!"
fi
