#!/bin/bash

saveIFS=$IFS
IFS='=&'
parm=($QUERY_STRING)
IFS=$saveIFS

virsh shutdown Larry

#python htmlHandler.py ${parm[1]} ${parm[3]} ${parm[5]}
