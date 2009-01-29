// Copyright (C) 2003-2009 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef __AOSOUNDSTREAM_H__
#define __AOSOUNDSTREAM_H__

#include "SoundStream.h"

#if defined(HAVE_AO) && HAVE_AO
#include <ao/ao.h>
#endif

#include "Thread.h"


class AOSound : public SoundStream
{

#if defined(HAVE_AO) && HAVE_AO
    
    Common::Thread *thread;

    Common::CriticalSection *soundCriticalSection;
    
    Common::Event *soundSyncEvent;
    
    int buf_size;
    
    ao_device *device;
    ao_sample_format format;
    int default_driver;
    
    short realtimeBuffer[1024 * 1024];

public:
    AOSound(int _sampleRate, StreamCallback _callback) :
	SoundStream(_sampleRate, _callback) {}
    
    virtual ~AOSound() {}
    
    virtual bool Start();
    
    virtual void SoundLoop();
    
    virtual void Stop();
    
    static  bool isValid() {
        return true;
    }
    
    virtual bool usesMixer() { 
	return true; 
    }
    
    virtual void Update();

    virtual int GetSampleRate() {
        return sampleRate;
    }
    

#else

public:
    AOSound(int _sampleRate, StreamCallback _callback) :
	SoundStream(_sampleRate, _callback) {}

#endif
    
};

#endif //__AOSOUNDSTREAM_H__
