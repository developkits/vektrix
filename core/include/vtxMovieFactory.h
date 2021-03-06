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

#ifndef __vtxMovieFactory_H__
#define __vtxMovieFactory_H__

#include "vtxPrerequisites.h"
#include "vtxFactory.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** The Factory that is used for creating Movie objects */
	class vtxExport MovieFactory : public Factory<Movie, String>
	{
	public:
		friend class Movie;
		friend class Root;

		typedef std::map<String, InstanceFactory*> FactoryMap;

		MovieFactory();
		virtual ~MovieFactory();

		/** Get the TextureFactory that is used for creating Texture instances */
		TextureFactory* getTextureFactory();

		/** Get the InstanceFactory for the given Instance type */
		InstanceFactory* getFactory(const String& type);

	protected:
		// map of the used factories <InstanceType, FactoryPtr>
		FactoryMap mFactories;

		// factories
		TextureFactory* mTextureFactory;

		/** Abstract method for creating a MovieDebugger for the given Movie */
		virtual MovieDebugger* _newDebugger(Movie* movie) = 0;

		/** Initialize this Factory */
		void _initialize();
	};
	//-----------------------------------------------------------------------
}

#endif
