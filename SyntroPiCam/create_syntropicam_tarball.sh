#!/bin/bash

if [ -f Makefile ]; then
        make clean
fi

rm -f *.bz2 *.log* *.ini
rm -f Makefile* *.so*
rm -rf release debug Output GeneratedFiles

tar -cjf SyntroPiCam.tar.bz2  --exclude='.git' *


echo "Created: SyntroPiCam.tar.bz2"
echo -n "Size: "
ls -l SyntroPiCam.tar.bz2 | awk '{ print $5 }'

echo -n "md5sum: "
md5sum SyntroPiCam.tar.bz2 | awk '{ print $1 }'

echo -n "sha256sum: "
sha256sum SyntroPiCam.tar.bz2 | awk '{ print $1 }'

