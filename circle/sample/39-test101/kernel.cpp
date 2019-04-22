//
// kernel.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2016  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"
#include <circle/gpiopin.h>
#include <circle/timer.h>
#define GPIOPinOne 19

CGPIOPin MasterEnable (15 , GPIOModeOutput);
CGPIOPin EnableOne (2 , GPIOModeOutput);
CGPIOPin EnableTwo (17 , GPIOModeOutput);
CGPIOPin InputOne (3 , GPIOModeOutput);
CGPIOPin InputTwo (4 , GPIOModeOutput);
CGPIOPin InputThree (14 , GPIOModeOutput);

CKernel::CKernel (void)
{
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	return TRUE;
}
int UpdatePulse(int output)
{
	if(output == 1)
	{
		MasterEnable.Write(1);
		EnableOne.Write(0);
		EnableTwo.Write(0);
		InputOne.Write(0);
		InputTwo.Write(0);
		InputThree.Write(0);
	}
	else if(output == 2)
	{
		MasterEnable.Write(1);
		EnableOne.Write(0);
		EnableTwo.Write(0);
		InputOne.Write(1);
		InputTwo.Write(0);
		InputThree.Write(0);
	}
	else
	{
		MasterEnable.Write(1);
		EnableOne.Write(0);
		EnableTwo.Write(0);
		InputOne.Write(0);
		InputTwo.Write(1);
		InputThree.Write(0);
	}
	return 0;
}

TShutdownMode CKernel::Run (void)
{
	CGPIOPin AudioLeft (GPIOPinAudioLeft, GPIOModeOutput);
	CGPIOPin AudioRight (GPIOPinAudioRight, GPIOModeOutput);
	CGPIOPin GPIOOne (GPIOPinOne , GPIOModeOutput);
	// flash the Act LED 10 times and click on audio (3.5mm headphone jack)
	for (unsigned i = 1; i <= 1000; i++)
	{
		UpdatePulse(1);
		GPIOOne.Write(1);
		m_ActLED.On ();
		CTimer::SimpleMsDelay (5000);
		GPIOOne.Write(0);
		m_ActLED.Off ();
		AudioLeft.Invert ();
		AudioRight.Invert ();
		CTimer::SimpleMsDelay (5000);
	}

	return ShutdownReboot;
}
