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

#include "vtxLogManager.h"
#include "vtxOpSysHelper.h"
#include "vtxStringHelper.h"

#if VTX_OS == VTX_WIN32
#	include "windows.h"
#endif

namespace vtx
{
	//-----------------------------------------------------------------------
	template<> LogManager* Singleton<LogManager>::sInstance = 0;
	//-----------------------------------------------------------------------
	LogManager::LogManager() 
		: mCout(false), 
		mFilename("NULL"), 
		mLineNr(0)
	{
		mLogFile.open("vektrix.log");
	}
	//-----------------------------------------------------------------------
	LogManager::~LogManager()
	{
		mLogFile.flush();
		mLogFile.close();
	}
	//-----------------------------------------------------------------------
	void LogManager::logToCout(bool log_to_cout)
	{
		mCout = log_to_cout;
	}
	//-----------------------------------------------------------------------
	void LogManager::exception(const char* format, ...)
	{
		VTX_LOCK_MUTEX(mLogMutex);

		VTX_DEBUG_ASSERT(mLogFile.is_open(), "Log file is in closed state!");

		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		String temp = "EXCEPTION: " + String(mMessageBuffer) + 
			"\n(occured in '" + mFilename + " at line " + StringHelper::toString(mLineNr) + "')";

		mLogFile << temp << std::endl;

		if(mCout)
		{
			std::cout << "<VTX> " << temp << std::endl;
		}

#if VTX_OS == VTX_WIN32
		MessageBox(NULL, temp.c_str(), "vektrix exception", MB_OK | MB_ICONERROR);
#endif
		VTX_DEBUG_FAIL("Exception Assert");
	}
	//-----------------------------------------------------------------------
	void LogManager::warning(const char* format, ...)
	{
		VTX_LOCK_MUTEX(mLogMutex);

		VTX_DEBUG_ASSERT(mLogFile.is_open(), "Log file is in closed state!");

		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		mLogFile << "Warning: " << mMessageBuffer << std::endl;

		if(mCout)
		{
			std::cout << "<VTX> Warning: " << mMessageBuffer << "    (" << mFilename << ")" << std::endl;
		}
	}
	//-----------------------------------------------------------------------
	void LogManager::log(const char* format, ...)
	{
		VTX_LOCK_MUTEX(mLogMutex);

		VTX_DEBUG_ASSERT(mLogFile.is_open(), "Log file is in closed state!");

		va_list argptr;
		va_start(argptr, format);
		vsprintf(mMessageBuffer, format, argptr);
		va_end(argptr);

		if(mCout)
		{
			std::cout << "<VTX> " << mMessageBuffer << std::endl;
		}

		mLogFile << "[" << OpSysHelper::getSystemTime() << "]" << mMessageBuffer << std::endl;
	}
	//-----------------------------------------------------------------------
	void LogManager::file(const String& source)
	{
		VTX_LOCK_MUTEX(mLogMutex);

		uint pos = (uint)source.find_last_of('\\')+1;
		mFilename = source.substr(pos, source.length()-pos);
	}
	//-----------------------------------------------------------------------
	void LogManager::line(const uint& line)
	{
		VTX_LOCK_MUTEX(mLogMutex);

		mLineNr = line;
	}
	//-----------------------------------------------------------------------
}
