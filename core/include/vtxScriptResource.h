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

#ifndef __vtxScriptResource_H__
#define __vtxScriptResource_H__

#include "vtxPrerequisites.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A Resource which contains binary or textual script data which can be executed at runtime */
	class vtxExport ScriptResource : public Resource
	{
	public:
		ScriptResource(const String& script_type);
		ScriptResource(const String& name, const String& script_type);
		virtual ~ScriptResource();

		/** @copybrief Resource::getType */
		const String& getType() const;

		const String& getScriptType() const;

	protected:
		String mScriptType;
	};
	//-----------------------------------------------------------------------
}

#endif
