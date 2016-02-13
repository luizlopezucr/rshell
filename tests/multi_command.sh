#!/bin/bash
#testing different combinations of connectors
#checking if parsed correctly with connector at the beginning/end of a 
#command and no spaces
#below says read until my defined string
../bin/rshell << EOF

ls -a -r; echo hello ||mkdir testing && echo no
ls -a && echo true &&  rmdir fakename|| mkdir testing; echo end
ls || echo noprint&&echo stillno; echo yes  

EOF
exit
