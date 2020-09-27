#!/bin/bash
insmod testmodule.ko
./test_loadable
rmmod testmodule