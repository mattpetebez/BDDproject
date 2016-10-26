#!/bin/bash

virsh shutdown $1
sleep 20
virsh start $1
