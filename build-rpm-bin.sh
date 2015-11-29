#!/bin/sh

mkdir -p /var/tmp/freelife/usr/bin
cp Release/freelife  /var/tmp/freelife/usr/bin
strip /var/tmp/freelife/usr/bin/freelife
sudo touch /usr/src/redhat/RPMS/i386/freelife-0-2.i386.rpm
sudo chmod a+rw /usr/src/redhat/RPMS/i386/freelife-0-2.i386.rpm

rpmbuild -bb freelife.spec
