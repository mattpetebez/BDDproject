#!/bin/bash

virsh nwfilter-dumpxml < /home/matt/Larry-rules.xml
virsh shutdown Larry acpi
sleep 15
virsh nwfilter-undefine Larry-rules
/home/BDDproject/RuleInserter/parser
virsh nwfilter-define /home/matt/Larry-rules.xml
virsh start Larry 

