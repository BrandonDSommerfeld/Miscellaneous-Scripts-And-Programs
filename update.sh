#!/bin/bash
#Small script to be automatically run at reboot
#to ensure that all packages are up to date
#Needs to be given +sx permissions to be run

sudo apt update
echo "y\n" | sudo apt upgrade
