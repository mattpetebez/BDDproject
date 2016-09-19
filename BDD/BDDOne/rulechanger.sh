#!/bin/bash

virsh dumpxml Larry-rules.xml /home/matt
virsh shutdown Larry acpi
sleep 7
virsh nwfilter-undefine Larry-rules
/home/matt/BDDproject/RuleInserter/a.out
virsh nwfilter-define /home/matt/Larry-rules.xml
virsh start Larry 

