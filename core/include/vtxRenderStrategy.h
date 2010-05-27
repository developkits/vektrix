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

#ifndef __vtxRenderStrategy_H__
#define __vtxRenderStrategy_H__

#include "vtxPrerequesites.h"

namespace vtx
{
	/** Defines a strategy for rendering Movie instances and their related objects (@see Instance) */
	class vtxExport RenderStrategy
	{
	public:
		RenderStrategy(MovieFactory* factory, File* file);
		virtual ~RenderStrategy();

		/** Hand back an Instance which is no longer being used */
		virtual void storeInstance(Instance* inst) = 0;
		/** Request an Instance with a given ID for use in a certain Movie */
		virtual Instance* shareInstance(const String& id, Movie* movie) = 0;

		virtual Instance* shareInstanceByType(const String& type, Movie* movie) = 0;

	protected:
		File* mFile;
		MovieFactory* mFactory;
	};
}

#endif
