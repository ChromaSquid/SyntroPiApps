# SyntroPiApps

SyntroApps contains all the SyntroNet Raspberry Pi apps in one repo.

Check out www.richards-tech.com for more details.

### Dependencies

1. Qt4 or Qt5 development libraries and headers (Qt5 recommended if possible)
2. SyntroCore libraries and headers 
3. gstreamer sdk installed in standard location for GS apps


### Fetch and Build

If SyntroCore has not been installed yet:

	mkdir ~/SyntroNet
	cd ~/SyntroNet
	git clone git://github.com/richards-tech/SyntroCore.git
	cd SyntroCore
	qmake
	make
	sudo make install

To compile the GS apps, install the gstreamer sdk at the standard location. See http://docs.gstreamer.com/display/GstSDK/Installing+the+SDK for Windows and Mac. For Ubuntu,

	sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libgstreamer-plugins-bad0.10-dev	

	
Then:

	cd ~/SyntroNet
	git clone git://github.com/richards-tech/SyntroApps.git
	git clone git://github.com/richards-tech/SyntroPiApps.git
	cd SyntroPiApps
	qmake SyntroPiApps.pro
	make
	sudo make install

To make the GS apps:

	qmake SyntroPiAppsGS.pro
	make
	sudo make install


Alternatively, each app can be individually compiled (better on lower power processors such as ARMs). For example, to compile SyntroPiCam:

	cd ~/SyntroNet/SyntroPiApps/SyntroPiCam
	qmake
	make
	sudo make install



