/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "vtxSemaphore.h"
#include "vtxLogManager.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	Semaphore::Semaphore(const uint& initial_count)
	{
		VTX_LOCK_MUTEX(mMutex);
		mCount = initial_count;
	}
	//-----------------------------------------------------------------------
	Semaphore::~Semaphore()
	{

	}
	//-----------------------------------------------------------------------
	void Semaphore::release(const uint& count)
	{
		VTX_LOCK_MUTEX_NAMED(mMutex, lock);

		for(uint i=0; i<count; ++i)
		{
			++mCount;
			VTX_THREAD_NOTIFY_ONE(mSynchronizer);
		}
	}
	//-----------------------------------------------------------------------
	void Semaphore::acquire(const uint& count)
	{
		VTX_LOCK_MUTEX_NAMED(mMutex, lock);

		for(uint i=0; i<count; ++i)
		{
			if(mCount == 0)
			{
				VTX_THREAD_WAIT(mSynchronizer, mMutex, lock);
			}
			--mCount;
		}
	}
	//-----------------------------------------------------------------------
}
