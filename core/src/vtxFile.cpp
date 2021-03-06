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

#include "vtxFile.h"

#include "vtxAtlasPacker.h"
#include "vtxEventListener.h"
#include "vtxFileEvent.h"
#include "vtxFileManager.h"
#include "vtxFileStream.h"
#include "vtxFontManager.h"
#include "vtxFontResource.h"
#include "vtxImageResource.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxMovieClipResource.h"
#include "vtxResource.h"
#include "vtxShapeResource.h"
#include "vtxSubshapeResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	File::File(const String& filename) 
		: mFilename(filename), 
		mLoadingState(FLS_LOADING), 
		mScriptEngineFactory(""), 
		mMainMovieClip(NULL), 
		mMainResource(NULL)
	{
		ShapeResource* black_box = new ShapeResource("BlackBox");

		MaterialResource* material = new MaterialResource("BlackBox_Material", MaterialResource::MT_COLOR);
		material->setColor(Color(0.0f, 0.0f, 0.0f, 0.5f));

		const float dimensions = 1.0f;

		BoundingBox box(Vector2::ZERO, Vector2(dimensions, dimensions));
		black_box->setBoundingBox(box);

		SubshapeResource* subshape = new SubshapeResource();
		subshape->setMaterial(material);

		black_box->_injectScale(Vector2(32, 32));

		// counter-clockwise default rect

		// TOP-LEFT
		subshape->addShapeElement(
			ShapeElement(ShapeElement::SID_MOVE_TO, 0.0f, 0.0f));

		// BOTTOM-LEFT
		subshape->addShapeElement(
			ShapeElement(ShapeElement::SID_LINE_TO, 0.0f, dimensions));

		// BOTTOM-RIGHT
		subshape->addShapeElement(
			ShapeElement(ShapeElement::SID_LINE_TO, dimensions, dimensions));

		// TOP-RIGHT
		subshape->addShapeElement(
			ShapeElement(ShapeElement::SID_LINE_TO, dimensions, 0.0f));

		// TOP-LEFT
		subshape->addShapeElement(
			ShapeElement(ShapeElement::SID_LINE_TO, 0.0f, 0.0f));

		black_box->addSubshapeResource(subshape);

		// add resources
		addResource(material);
		addResource(black_box);
	}
	//-----------------------------------------------------------------------
	File::~File()
	{
		// destroy internal resources
		ResourceMap::iterator it = mResources.begin();
		ResourceMap::iterator end = mResources.end();
		while(it != end)
		{
			if(it->second != mMainMovieClip)
				delete it->second;

			++it;
		}

		delete mMainMovieClip;
	}
	//-----------------------------------------------------------------------
	const String& File::getFilename() const
	{
		return mFilename;
	}
	//-----------------------------------------------------------------------
	void File::setHeader(const FileHeader& header)
	{
		mHeader = header;
	}
	//-----------------------------------------------------------------------
	const File::FileHeader& File::getHeader()
	{
		return mHeader;
	}
	//-----------------------------------------------------------------------
	void File::setScriptEngine(const String& scriptEngineFactory)
	{
		mScriptEngineFactory = scriptEngineFactory;
	}
	//-----------------------------------------------------------------------
	const String& File::getScriptEngine()
	{
		return mScriptEngineFactory;
	}
	//-----------------------------------------------------------------------
	void File::setMainMovieClip(MovieClipResource* movieclip)
	{
		mMainMovieClip = movieclip;
	}
	//-----------------------------------------------------------------------
	MovieClipResource* File::getMainMovieClip()
	{
		return mMainMovieClip;
	}
	//-----------------------------------------------------------------------
	void File::addResource(Resource* res)
	{
		ResourceMap::iterator it = mResources.find(res->getID());

		if(it != mResources.end())
		{
			VTX_EXCEPT("\"%s\": Tried to add Resource with id \"%s\" twice!", 
				mFilename.c_str(), res->getID().c_str());
			return;
		}

		res->_setFile(this);

		mResources[res->getID()] = res;
		mResourcesByType[res->getType()].push_back(res);

		if(res->getType() == "Font")
		{
			FontResource* font = static_cast<FontResource*>(res);
			mFonts[font->getName()] = font;
		}

		FileEvent evt(FileEvent::RESOURCE_ADDED, res);

		for_each(it, ListenerMap, mListeners)
			it->second->eventFired(evt);

#ifdef _DEBUG
		//VTX_LOG("\"%s\": Added resource with id \"%s\" of type \"%s\"", 
		//	mFilename.c_str(), 
		//	res->getID().c_str(), res->getType().c_str());
#endif
	}
	//-----------------------------------------------------------------------
	Resource* File::getResource(const String& id, const String& requested_type)
	{
		ResourceMap::iterator it = mResources.find(id);

		if(it != mResources.end())
		{
			if(requested_type.length())
			{
				if(it->second->getType() == requested_type)
					return it->second;
			}
			else
				return it->second;
		}

		if(requested_type == "Font")
			return FontManager::getSingletonPtr()->getFont(id);

		return NULL;
	}
	//-----------------------------------------------------------------------
	const ResourceList& File::getResourcesByType(const String& type) const
	{
		ResourceTypeMap::const_iterator it = mResourcesByType.find(type);
		if(it != mResourcesByType.end())
		{
			return it->second;
		}

		static ResourceList empty;
		return empty;
	}
	//-----------------------------------------------------------------------
	const ResourceMap& File::getResources() const
	{
		return mResources;
	}
	//-----------------------------------------------------------------------
	FontResource* File::getFontByName(const String& font_name)
	{
		FontMap::iterator it = mFonts.find(font_name);

		if(it != mFonts.end() && it->second->getGlyphList().size())
			return it->second;

		return FontManager::getSingletonPtr()->getFont(font_name);
	}
	//-----------------------------------------------------------------------
	bool File::addListener(EventListener* listener)
	{
		ListenerMap::iterator it = mListeners.find(listener);
		if(it == mListeners.end())
		{
			mListeners.insert(std::make_pair(listener, listener));
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool File::removeListener(EventListener* listener)
	{
		ListenerMap::iterator it = mListeners.find(listener);
		if(it != mListeners.end())
		{
			mListeners.erase(it);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void File::_loadingCompleted()
	{
		FileEvent evt(FileEvent::LOADING_COMPLETED, this);

		for_each(it, ListenerMap, mListeners)
			it->second->eventFired(evt);
	}
	//-----------------------------------------------------------------------
	void File::_loadingFailed()
	{
		FileEvent evt(FileEvent::LOADING_FAILED, this);

		for_each(it, ListenerMap, mListeners)
			it->second->eventFired(evt);
	}
	//-----------------------------------------------------------------------
}
