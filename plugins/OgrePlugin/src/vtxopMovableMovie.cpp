/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/
#include "vtxopMovableMovie.h"
#include "vtxopShape.h"

#include "vtxInstance.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		MovableMovie::MovableMovie(const std::string& name, vtx::File* file, MovieFactory* creator) 
			: vtx::Movie(name, file, creator)
		{
			mAAB.setInfinite();
		}
		//-----------------------------------------------------------------------
		MovableMovie::~MovableMovie()
		{

		}
		//-----------------------------------------------------------------------
		vtx::Instance* MovableMovie::getInstance(const std::string& id)
		{
			vtx::Instance* instance = vtx::Movie::getInstance(id);

			if(instance->getType() == "Shape")
			{
				ShapeList::iterator it = mShapes.find((OgreShape*)instance);

				if(it == mShapes.end())
				{
					mShapes.insert(ShapeList::value_type((OgreShape*)instance, 0));
				}
			}

			return instance;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::releaseInstance(vtx::Instance* instance)
		{
			if(instance->getType() == "Shape")
			{
				ShapeList::iterator it = mShapes.find((OgreShape*)instance);

				if(it != mShapes.end())
				{
					mShapes.erase(it);
				}
			}

			vtx::Movie::releaseInstance(instance);
		}
		//-----------------------------------------------------------------------
		const Ogre::String& MovableMovie::getMovableType(void) const
		{
			static Ogre::String temp = "myType";
			return temp;
		}
		//-----------------------------------------------------------------------
		const Ogre::AxisAlignedBox& MovableMovie::getBoundingBox(void) const
		{
			return mAAB;
		}
		//-----------------------------------------------------------------------
		Ogre::Real MovableMovie::getBoundingRadius(void) const
		{
			return 1.0f;
		}
		//-----------------------------------------------------------------------
		void MovableMovie::_updateRenderQueue(Ogre::RenderQueue* queue)
		{
			ShapeList::iterator it = mShapes.begin();

			for( ; it != mShapes.end(); ++it)
			{
				Ogre::Renderable* rend = dynamic_cast<Ogre::Renderable*>(it->first);
				queue->addRenderable(rend);
			}
		}
		//-----------------------------------------------------------------------
		void MovableMovie::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
		{

		}
		//-----------------------------------------------------------------------
	}
}
