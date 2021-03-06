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

#ifndef __vtxDisplayObjectContainer_H__
#define __vtxDisplayObjectContainer_H__

#include "vtxPrerequisites.h"
#include "vtxInteractiveObject.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** Base class for everything visual that can itself contain other visual objects */
	class vtxExport DisplayObjectContainer : public InteractiveObject
	{
	public:
		typedef std::map<uint, DisplayObject*> LayerMap;
		typedef std::map<String, DisplayObject*> NameMap;

		DisplayObjectContainer(const bool& auto_update_bbs = true);
		virtual ~DisplayObjectContainer();

		virtual bool isDisplayObjectContainer() const;

		/** Add a child object at the topmost available layer */
		void addChild(DisplayObject* object);

		/** Add a child object at the given layer */
		bool addChildAt(DisplayObject* object, uint layer);

		/** Get the child object located at the given layer */
		DisplayObject* getChildAt(uint layer);

		DisplayObject* getChildByIndex(const uint& index);

		DisplayObject* getChildByName(const String& name);

		/** Remove a child object from the given layer */
		DisplayObject* removeChildAt(uint layer);

		uint numChildren() const;

		/** Remove all objects from all layers */
		void clearLayers();

		const LayerMap& getLayers() const;

		/** Implementation of DisplayObject::isPointInside */
		bool isPointInside(const Vector2& coord);

		virtual void processEvents();

		/** @copybrief DisplayObject::_update */
		virtual void updateGraphics(const float& delta_time = 0.0f);

		// inherited from EventListener
		virtual void eventFired(const Event& evt);

	protected:
		bool mChildListChanged;
		bool mAutoUpdateBBs;
		bool mNeedBoundingBoxUpdate;
		LayerMap mLayers;
		NameMap mNameMap;
	};
	//-----------------------------------------------------------------------
}

#endif
