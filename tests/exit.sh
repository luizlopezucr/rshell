#!/bin/bash
#checking to see if it it executes after exiting each time
#exiting at beginning/middle/end
#below says read until my defined string
../bin/rshell << EOF

ls || echo noprint&&echo stillno; echo yes  
ls -a -r; echo hello ||mkdir testing && echo no
exit

EOF
../bin/rshell << STOP
ls -a && echo true &&  rmdir fakename|| mkdir testing; echo end
exit
STOP
../bin/rshell << ENDME
ls -r ; rmdir testing
echo hello || echo nothing
echo ENDING && echo NOW
exit
ENDME
