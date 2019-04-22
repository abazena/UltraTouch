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

CGPIOPin DecoderMasterEnable (15 , GPIOModeOutput);
CGPIOPin OutputMasterEnable (11 , GPIOModeOutput);
CGPIOPin DecoderEnableOne (2 , GPIOModeOutput);
CGPIOPin DecoderEnableTwo (17 , GPIOModeOutput);
CGPIOPin DecoderPins[] =
						{
							CGPIOPin (3 , GPIOModeOutput),
							CGPIOPin (4 , GPIOModeOutput),
							CGPIOPin (14 , GPIOModeOutput)
						};
CGPIOPin OutputPins[] =
						{
							CGPIOPin (18 , GPIOModeOutput),
							CGPIOPin (27 , GPIOModeOutput),
							CGPIOPin (22 , GPIOModeOutput),
							CGPIOPin (23 , GPIOModeOutput),
							CGPIOPin (24 , GPIOModeOutput),
							CGPIOPin (10 , GPIOModeOutput),
							CGPIOPin (9 , GPIOModeOutput),
							CGPIOPin (15 , GPIOModeOutput)
						};

CKernel::CKernel (void)
{
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	DecoderEnableOne.Write(0);
	DecoderEnableTwo.Write(0);
	return TRUE;
}
int UpdateOutput(int output[8])
{
	for (int i = 0; i++; i<8)
	{
		OutputPins[i].Write(output[i]);
  }
	return 0;
}
int UpdatePulse(unsigned output)
{
	if(output == 1)
	{
		DecoderPins[0].Write(0);
		DecoderPins[1].Write(0);
		DecoderPins[2].Write(0);
		DecoderMasterEnable.Write(1);

	}
	else if(output == 2)
	{
		DecoderPins[0].Write(1);
		DecoderPins[1].Write(0);
		DecoderPins[2].Write(0);
		DecoderMasterEnable.Write(1);
	}
	else
	{
		DecoderPins[0].Write(0);
		DecoderPins[1].Write(1);
		DecoderPins[2].Write(0);
		DecoderMasterEnable.Write(1);
	}
	return 0;
}

TShutdownMode CKernel::Run (void)
{
	//CGPIOPin AudioLeft (GPIOPinAudioLeft, GPIOModeOutput);
	//CGPIOPin AudioRight (GPIOPinAudioRight, GPIOModeOutput);
	//CGPIOPin GPIOOne (GPIOPinOne , GPIOModeOutput);
	// flash the Act LED 10 times and click on audio (3.5mm headphone jack)
	for (unsigned i = 1; i <= 1000; i++)
	{
		m_ActLED.On();
		int output[] = {0,0,0,0,0,0,0,0};
		UpdateOutput(output);
		UpdatePulse(1);
		m_ActLED.Off();
		CTimer::SimpleMsDelay(200);

		//GPIOOne.Write(1);
		//m_ActLED.On ();
		//CTimer::SimpleMsDelay (5000);
		//GPIOOne.Write(0);
		//m_ActLED.Off ();
		//AudioLeft.Invert ();
		//AudioRight.Invert ();
		//CTimer::SimpleMsDelay (5000);
	}

	return ShutdownReboot;
}
