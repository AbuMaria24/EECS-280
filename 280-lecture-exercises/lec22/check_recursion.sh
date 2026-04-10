#!/bin/bash

grep -q -e "for[^a-z]" -e "while" $1 || exit 0
echo "Found a for or while loop in $1"
exit 1