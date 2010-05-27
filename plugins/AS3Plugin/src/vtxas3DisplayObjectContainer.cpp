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

#include "flash_package.h"

#include "vtxDisplayObjectContainer.h"

namespace vtx
{
	namespace as3
	{
		//-----------------------------------------------------------------------
		DisplayObjectContainerClass::DisplayObjectContainerClass(avmplus::VTable* cvtable) 
			: ClassClosure(cvtable)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DisplayObjectContainerClass));
			createVanillaPrototype();
		}
		//-----------------------------------------------------------------------
		avmplus::ScriptObject* DisplayObjectContainerClass::createInstance(avmplus::VTable* ivtable, avmplus::ScriptObject* prototype)
		{
			return new (core()->GetGC(), ivtable->getExtraSize()) DisplayObjectContainer(ivtable, prototype);
		}
		//-----------------------------------------------------------------------
		DisplayObjectContainer::DisplayObjectContainer(avmplus::VTable* vtable, avmplus::ScriptObject* prototype) 
			: InteractiveObject(vtable, prototype), 
			mDisplayObjectContainer(NULL)
		{

		}
		//-----------------------------------------------------------------------
		DisplayObjectContainer::~DisplayObjectContainer()
		{

		}
		//-----------------------------------------------------------------------
		DisplayObject* DisplayObjectContainer::addChild(DisplayObject* child)
		{
			if(mDisplayObjectContainer)
			{
				vtx::Instance* inst = child->getNativeObject();
				vtx::DisplayObject* native_child = dynamic_cast<vtx::DisplayObject*>(inst);
				if(native_child)
				{
					mDisplayObjectContainer->addChild(native_child);
					return child;
				}
			}
			return NULL;
		}
		//-----------------------------------------------------------------------
		void DisplayObjectContainer::_setNativeObject(Instance* inst)
		{
			InteractiveObject::_setNativeObject(inst);
			mDisplayObjectContainer = dynamic_cast<vtx::DisplayObjectContainer*>(inst);
		}
		//-----------------------------------------------------------------------
	}
}
