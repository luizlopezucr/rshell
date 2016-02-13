#!/bin/bash
#checking before/after commander, beginning, and end, with a space and no spspace
#below says read until my defined string
../bin/rshell << EOF

#ls -a -r; echo hello || mkdir testing && echo no
ls -a && #after a (&&) echo true &&  rmdir fakename || mkdir testing; echo end
ls ||# 
ls || echo noprint#before a (&&) echo stillno; echo yes  
echo hello #nothing at the end
exit
EOF
