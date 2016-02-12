#!/bin/sh
#
# install script for chantilly libraries , raspi 2B+ version
# v1.01, dev
#
# SUDO exec needed
#
UPD_WEB=http://chantilly.sideme-electronique.com/download/bin/
UPD_B2_HEADER=CHANTILLY_B2.h
UPD_B2_LIB=libchantilly_b2.a
UPD_B2_SHARED=libchantilly_b2.so
# generates the same script as the B+ version install. script is common to the two version , arguments --bp or --b2 sets the compilation lib to be used
UPD_B2_GCC_CONFIG_SCRIPT=chantilly
#
UPD_TARGET_LIB=/usr/local/lib
UPD_TARGET_INC=/usr/local/include
UPD_TARGET_CONFIG=/usr/local/bin
#
echo "Checking for updates :\n"
echo "----------------------\n"
echo "(A)\tHeader file(s) :"
wget "${UPD_WEB}${UPD_B2_HEADER}"
echo "(B)\tStatic library (.a) :"
wget "${UPD_WEB}${UPD_B2_LIB}"
echo "(B)\tShared library (.so) :"
wget "${UPD_WEB}${UPD_B2_SHARED}"
echo "(C)\tGCC configuration script :"
wget "${UPD_WEB}${UPD_B2_GCC_CONFIG_SCRIPT}"
#
# checks files 
#
header=0
static_lib=0
config_script=0
if [ -f "${UPD_B2_HEADER}" ];then	echo "\t${UPD_B2_HEADER}:OK";else echo "${UPD_B2_HEADER} **ERROR**";fi
if [ -f "${UPD_B2_LIB}" ];then	echo "\t${UPD_B2_LIB}:OK";else echo "${UPD_B2_LIB} **ERROR**";fi
if [ -f "${UPD_B2_SHARED}" ];then	echo "\t${UPD_B2_SHARED}:OK";else echo "${UPD_B2_SHARED} **ERROR**";fi
if [ -f "${UPD_B2_GCC_CONFIG_SCRIPT}" ];then	echo "\t${UPD_B2_GCC_CONFIG_SCRIPT}:OK";else echo "${UPD_B2_GCC_CONFIG_SCRIPT} **ERROR**";fi
#
# rename target's files .old
#
cp ${UPD_TARGET_CONFIG}/${UPD_B2_GCC_CONFIG_SCRIPT} ${UPD_TARGET_CONFIG}/${UPD_B2_GCC_CONFIG_SCRIPT}.old
cp ${UPD_TARGET_LIB}/${UPD_B2_LIB} ${UPD_TARGET_LIB}/${UPD_B2_LIB}.old
cp ${UPD_TARGET_LIB}/${UPD_B2_SHARED} ${UPD_TARGET_LIB}/${UPD_B2_SHARED}.old
cp ${UPD_TARGET_INC}/${UPD_B2_HEADER} ${UPD_TARGET_INC}/${UPD_B2_HEADER}.old
#
# copy new files
#
mv ${UPD_B2_GCC_CONFIG_SCRIPT} ${UPD_TARGET_CONFIG}/
mv ${UPD_B2_LIB} ${UPD_TARGET_LIB}/
mv ${UPD_B2_SHARED} ${UPD_TARGET_LIB}/
mv ${UPD_B2_HEADER} ${UPD_TARGET_INC}/
#
echo "\tset config script executable\n"
chmod +x ${UPD_TARGET_CONFIG}/${UPD_B2_GCC_CONFIG_SCRIPT}
echo "Done :\n"
echo "----------------------\n"
echo "\tfiles backups : .old"
