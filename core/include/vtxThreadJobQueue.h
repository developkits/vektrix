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

#ifndef __vtxThreadJobQueue_H__
#define __vtxThreadJobQueue_H__

#include "vtxPrerequisites.h"
#include "vtxInterLockedType.h"
#include "vtxSemaphore.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A class for queuing and processing thread jobs */
	class vtxExport ThreadJobQueue
	{
	public:
		typedef std::deque<ThreadJob*> JobQueue;
		typedef std::vector<VTX_THREAD_TYPE*> ThreadPool;

		ThreadJobQueue();
		virtual ~ThreadJobQueue();

		/** Set the number of threads that will be used to process the ThreadJob queue */
		void setNumberOfThreads(const uint& num_threads);

		/** Add the given job to the job queue */
		void queueJob(ThreadJob* job);

	protected:
		InterLockedType<bool> mRunning;
		VTX_MUTEX(mMutex);
		Semaphore mSemaphore;
		JobQueue mQueue;
		ThreadPool mThreadPool;

		/** The method that will be called by the processing threads */
		void threadFunc();
		/** Join and destroy all active threads */
		void destroyThreads();
	};
	//-----------------------------------------------------------------------
}

#endif
