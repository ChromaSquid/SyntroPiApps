#
#  Copyright (c) 2014 Scott Ellis and Richard Barnett.
#
#  This file is part of SyntroNet
#
#  SyntroNet is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  SyntroNet is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with SyntroNet.  If not, see <http://www.gnu.org/licenses/>.
#

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += SyntroPiCam.h \
        SyntroPiCamConsole.h \
	VideoDriver.h \
	CamClient.h \	
	AudioDriver.h \	
        RaspiCamControl.h \
        RaspiPreview.h \
    	RaspiDriver.h \
	AVMuxEncodeGS.h

SOURCES += main.cpp \
        SyntroPiCam.cpp \
        SyntroPiCamConsole.cpp \
	VideoDriver.cpp \
	CamClient.cpp \
  	AudioDriver.cpp \
    	RaspiCamControl.c \
    	RaspiPreview.c \
    	RaspiDriver.c \
	AVMuxEncodeGS.cpp

FORMS +=

