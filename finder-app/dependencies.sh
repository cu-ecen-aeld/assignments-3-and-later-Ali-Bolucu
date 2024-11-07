#!/bin/bash
# Dependency installation script for kernel build.
# Author: Siddhant Jajoo.


sudo apt-get install -y libssl-dev
sudo apt-get install -y u-boot-tools
sudo apt-get install -y qemu

sudo apt-get install -y flex
sudo apt-get install -y libelf-dev
sudo apt-get install -y libudev-dev
sudo apt-get install -y libpci-dev
sudo apt-get install -y libiberty-dev
sudo apt-get install -y libncurses-dev 
sudo apt-get install -y bison
sudo apt-get install -y openssl
sudo apt-get install -y dkms
sudo apt-get install -y autoconf


sudo apt update
sudo apt install qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils virt-manager
sudo adduser $USER libvirt
sudo adduser $USER kvm

