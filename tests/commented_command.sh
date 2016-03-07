#!/bin/bash
#checking before/after commander, beginning, and end, with a space and no spspace
#below says read until my defined string
../bin/rshell << EOF
#ls -a -r; echo hello || mkdir testing && echo no
ls -a && #after a (&&) echo true &&  rmdir fakename || mkdir testing; echo end
ls ||# 
ls || echo noprint#before a (&&) echo stillno; echo yes  
echo hello #nothing at the end
(( echo a ) # && echo b || echo hello)
# ((echo a && echo b) || echo c) && ((echo d || echo e) && echo f)
((echo a && echo b) || echo c) && ((echo d || echo e) && echo f)#nothing here either
exit
EOF
