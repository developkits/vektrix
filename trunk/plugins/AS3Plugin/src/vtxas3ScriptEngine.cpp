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

#include "vtxas3ScriptEngine.h"

#include "vtxButton.h"
#include "vtxEditText.h"
#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMovie.h"
#include "vtxMovieClip.h"
#include "vtxResource.h"
#include "vtxScriptObject.h"
#include "vtxStringHelper.h"
#include "vtxSymbolClassResource.h"

#include "cspNativePackage.h"
#include "cspSystem.h"
#include "cspVmCore.h"

#include "flash_package.h"

namespace vtx { namespace as3 {
	//-----------------------------------------------------------------------
	AS3ScriptEngine::AS3ScriptEngine(Movie* parent) 
		: ScriptEngine(parent), 
		mVmCore(NULL), 
		mRootObject(NULL)
	{
		CSP_CREATE_VMCORE(mVmCore);
		mVmCore->setUserData(mParent);

		mVmCore->addListener(this);

		NativePackage(mVmCore, caspin_base);
		NativePackage(mVmCore, flash);

		mVmCore->initializePackages();
	}
	//-----------------------------------------------------------------------
	AS3ScriptEngine::~AS3ScriptEngine()
	{
		CSP_DESTROY_VMCORE(mVmCore);
	}
	//-----------------------------------------------------------------------
	bool AS3ScriptEngine::executeCode(const char* code, const uint& len)
	{
		return mVmCore->executeByteCode(code, len);
	}
	//-----------------------------------------------------------------------
	ScriptObject* AS3ScriptEngine::getRootScriptObject()
	{
		if(!mRootObject)
		{
			const String& root_class = mParent->getFile()->getHeader().script_root_class;
			if(root_class.length())
			{
				StringList vec = StringHelper::splitString(root_class, '.');

				if(vec.size() > 1)
				{
					// ActionScript 3 class declaration -> [package.ClassName]
					mRootObject = static_cast<as3::MovieClip*>(mVmCore->createObject(vec.at(1), vec.at(0)));
				}
				else
				{
					mRootObject = static_cast<as3::MovieClip*>(mVmCore->createObject(vec.at(0)));
				}
			}
		}

		return mRootObject;
	}
	//-----------------------------------------------------------------------
	ScriptObject* AS3ScriptEngine::createScriptObject(Resource* res)
	{
		MMGC_GCENTER(mVmCore->GetGC());

		SymbolClassResource* symb_res = 
			static_cast<SymbolClassResource*>(mParent->getFile()->getResource("__SymbolClassResource__"));

		if(symb_res)
		{
			if(symb_res->hasSymbol(res->getID()))
			{
				const StringPair class_def = symb_res->getSymbol(res->getID());
				return (ScriptObject*)mVmCore->createObject(class_def.second, class_def.first);
			}
		}

		if(res->getType() == vtx::MovieClip::TYPE)
		{
			return static_cast<MovieClip*>(mVmCore->createObject("MovieClip", "flash.display"));
		}
		else if(res->getType() == vtx::EditText::TYPE)
		{
			return static_cast<TextField*>(mVmCore->createObject("TextField", "flash.text"));
		}
		else if(res->getType() == vtx::Button::TYPE)
		{
			return static_cast<SimpleButton*>(mVmCore->createObject("SimpleButton", "flash.display"));
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void AS3ScriptEngine::destroyScriptObject(ScriptObject* script_object)
	{

	}
	//-----------------------------------------------------------------------
	void AS3ScriptEngine::output(const String& message)
	{
		VTX_LOG("ActionScript3: '%s'", message.c_str());
	}
	//-----------------------------------------------------------------------
}}