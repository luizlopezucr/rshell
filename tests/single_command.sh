#!/bin/bash
#below says read until my defined string
../bin/rshell << EOF
ls -a -r
mkdir somedir
ls -la
rmdir somedir
exit
EOF
exit
