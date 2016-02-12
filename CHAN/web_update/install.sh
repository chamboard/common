#!/bin/sh
#
# install script for chantilly libraries
# v1.01, dev
# SUDO exec needed
#
UPD_WEB=http://chantilly.sideme-electronique.com/download/bin/
UPD_BP_HEADER=CHANTILLY_BP.h
UPD_BP_LIB=libchantilly_bp.a
UPD_BP_SHARED=libchantilly_bp.so
UPD_BP_GCC_CONFIG_SCRIPT=chantilly
#
UPD_TARGET_LIB=/usr/local/lib
UPD_TARGET_INC=/usr/local/include
UPD_TARGET_CONFIG=/usr/local/bin
#
echo "Checking for updates :\n"
echo "----------------------\n"
echo "(A)\tHeader file(s) :"
wget "${UPD_WEB}${UPD_BP_HEADER}"
echo "(B)\tStatic library (.a) :"
wget "${UPD_WEB}${UPD_BP_LIB}"
echo "(B)\tShared library (.so) :"
wget "${UPD_WEB}${UPD_BP_SHARED}"
echo "(C)\tGCC configuration script :"
wget "${UPD_WEB}${UPD_BP_GCC_CONFIG_SCRIPT}"
#
# checks files 
#
header=0
static_lib=0
config_script=0
if [ -f "${UPD_BP_HEADER}" ];then	echo "\t${UPD_BP_HEADER}:OK";else echo "${UPD_BP_HEADER} **ERROR**";fi
if [ -f "${UPD_BP_LIB}" ];then	echo "\t${UPD_BP_LIB}:OK";else echo "${UPD_BP_LIB} **ERROR**";fi
if [ -f "${UPD_BP_SHARED}" ];then	echo "\t${UPD_BP_SHARED}:OK";else echo "${UPD_BP_SHARED} **ERROR**";fi
if [ -f "${UPD_BP_GCC_CONFIG_SCRIPT}" ];then	echo "\t${UPD_BP_GCC_CONFIG_SCRIPT}:OK";else echo "${UPD_BP_GCC_CONFIG_SCRIPT} **ERROR**";fi
#
# rename target's files .old
#
cp ${UPD_TARGET_CONFIG}/${UPD_BP_GCC_CONFIG_SCRIPT} ${UPD_TARGET_CONFIG}/${UPD_BP_GCC_CONFIG_SCRIPT}.old
cp ${UPD_TARGET_LIB}/${UPD_BP_LIB} ${UPD_TARGET_LIB}/${UPD_BP_LIB}.old
cp ${UPD_TARGET_LIB}/${UPD_BP_SHARED} ${UPD_TARGET_LIB}/${UPD_BP_SHARED}.old
cp ${UPD_TARGET_INC}/${UPD_BP_HEADER} ${UPD_TARGET_INC}/${UPD_BP_HEADER}.old
#
# copy new files
#
mv ${UPD_BP_GCC_CONFIG_SCRIPT} ${UPD_TARGET_CONFIG}/
mv ${UPD_BP_LIB} ${UPD_TARGET_LIB}/
mv ${UPD_BP_SHARED} ${UPD_TARGET_LIB}/
mv ${UPD_BP_HEADER} ${UPD_TARGET_INC}/
#
echo "\tset config script executable\n"
chmod +x ${UPD_TARGET_CONFIG}/${UPD_BP_GCC_CONFIG_SCRIPT}
echo "Done :\n"
echo "----------------------\n"
echo "\tfiles backups : .old"
