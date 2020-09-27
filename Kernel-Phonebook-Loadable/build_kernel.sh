#!/bin/bash

shopt -s nullglob
cd linux-4.19.144
sudo make menuconfig
sudo make -j8
