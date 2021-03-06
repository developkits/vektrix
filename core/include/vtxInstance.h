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

#ifndef __vtxInstance_H__
#define __vtxInstance_H__

#include "vtxPrerequisites.h"
#include "vtxEventDispatcher.h"
#include "vtxEventListener.h"
#include "vtxFactory.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Base class for everything visual, audible, etc that can be created by a Movie instance */
	class vtxExport Instance : public EventListener, public EventDispatcher
	{
	public:
		Instance();
		virtual ~Instance();

		// TODO: temporary hacks ??
		virtual bool isDisplayObject() const;
		virtual bool isDisplayObjectContainer() const;

		/** Initialize this Instance with the given Resource */
		virtual void initFromResource(Resource* resource) { mResource = resource; }

		/** Get the unique type of this instance */
		virtual const String& getType() const = 0;

		/** Notify this instance about its parent Movie */
		virtual void _setParent(Movie* parent);

		/** Get the current parent Movie of this instance */
		Movie* getParent() const;

		Resource* getResource() const;

		void setName(const String& name);
		const String& getName() const;

		virtual void processEvents();

		/** Set the ScriptObject that is associated with this instance */
		virtual void setScriptObject(ScriptObject* obj);

		/** Get the ScriptObject that is associated with this instance */
		virtual ScriptObject* getScriptObject() const;

		virtual void initScriptObject();

	protected:
		String mName;
		Movie* mParentMovie;
		Resource* mResource;
		ScriptObject* mScriptObject;
	};
	//-----------------------------------------------------------------------
	/** The Factory for creating Instance objects */
	class InstanceFactory : public Factory<Instance> {};
	//-----------------------------------------------------------------------
}

#endif
