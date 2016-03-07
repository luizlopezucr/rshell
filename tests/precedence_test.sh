#!/bin/bash
#below says read until my defined string
../bin/rshell << EOF
(ls -j && echo hi) || echo bye
( [ -e /bin/ ] && echo hi) || echo bye
( [ -f /bin/ ] && echo hi) || echo bye
(()) && echo hello
(( echo hi && echo hello) || ( echo foo && echo bar )) 
((echo hi && echo hello) || ( ( echo foo && echo bar)  && echo a ))
((echo a && echo b )
((echo a && echo b) || echo c) && ((echo d || echo e) && echo hi)
((ls -j && echo foo) || echo hi) || ((echo bar || echo hello) && hello)
exit
EOF
