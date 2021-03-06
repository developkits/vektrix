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

#include "vtxopMovableShape.h"
#include "vtxopMovableMovie.h"
#include "vtxogreShapeAtlasElement.h"
#include "vtxopTexture.h"

#include "vtxAtlasNode.h"
#include "vtxLogManager.h"
#include "vtxResource.h"
#include "vtxShapeResource.h"

#include "OgrePass.h"
#include "OgreTechnique.h"

namespace vtx
{
	namespace ogre
	{
		//-----------------------------------------------------------------------
		OgreMovableShape::OgreMovableShape() 
			: MovableInstanceBase(this), 
			mLayer(0.0f)
		{
			_createBuffers();
			_resizeBuffers(1);
		}
		//-----------------------------------------------------------------------
		OgreMovableShape::~OgreMovableShape()
		{

		}
		//-----------------------------------------------------------------------
		void OgreMovableShape::_setParent(Movie* parent)
		{
			Shape::_setParent(parent);
			mParentMovable = static_cast<MovableMovie*>(parent);

			if(mParentMovable)
			{
				mPacker = mParentMovable->getPacker();

				if(mPacker)
				{
					mPacker->addListener(this);
				}
			}
			else
			{
				if(mPacker)
				{
					mPacker->removeListener(this);
				}
			}
		}
		//-----------------------------------------------------------------------
		void OgreMovableShape::initFromResource(Resource* resource)
		{
			Shape::initFromResource(resource);

			if(mPacker)
			{
				//if(!mPacker->containsElement((uint)resource))
				//{
				//	ShapeResource* shape = static_cast<ShapeResource*>(resource);
				//	mPacker->addElement(new ShapeAtlasElement(shape));
				//	mPacker->packAtlas();
				//	mPacker->renderAtlas();
				//}

				AtlasPacker::PackResultList list = mPacker->getResultList();
				AtlasPacker::PackResultList::iterator it = list.find((uint)resource);
				if(it != list.end())
				{
					setAtlasQuad(it->second);
				}
				else
				{
					VTX_EXCEPT("blah");
				}
			}
		}
		//-----------------------------------------------------------------------
		void OgreMovableShape::updateGraphics(const float& delta_time)
		{
			Shape::updateGraphics(delta_time);

			const Matrix& mat = getWorldMatrix();

			mWorldMatrix = Ogre::Matrix4(
				mat.m[0][0], -mat.m[0][1], 0,  mat.m[0][2], 
				-mat.m[1][0], mat.m[1][1], 0, -mat.m[1][2], 
				0,		  0,		   1,				0,
				0,		  0,		   0,				1);

			mMULcolor = mTransform.getColor().mul;
			mADDcolor = mTransform.getColor().add;
		}
		//-----------------------------------------------------------------------
		void OgreMovableShape::setAtlasQuad(const AtlasPacker::PackResult& quad)
		{
			mMaterial = static_cast<OgreTexture*>(quad.texture)->getMaterial();
			RectF tex_coords = quad.node->getRect().contractedCopy(1).relativeTo(
				quad.texture->getWidth(), quad.texture->getHeight());

			const BoundingBox& bb = getBoundingBox();

			_lock();

			// TOP-LEFT
			_addVertex(
				Vector2(bb.getMinX(), -bb.getMinY()), 
				Vector2(tex_coords.left, tex_coords.top), 
				mMULcolor, mADDcolor);

			// BOTTOM-LEFT
			_addVertex(
				Vector2(bb.getMinX(), -bb.getMaxY()), 
				Vector2(tex_coords.left, tex_coords.bottom), 
				mMULcolor, mADDcolor);

			// BOTTOM-RIGHT
			_addVertex(
				Vector2(bb.getMaxX(), -bb.getMaxY()), 
				Vector2(tex_coords.right, tex_coords.bottom), 
				mMULcolor, mADDcolor);

			// TOP-RIGHT
			_addVertex(
				Vector2(bb.getMaxX(), -bb.getMinY()), 
				Vector2(tex_coords.right, tex_coords.top), 
				mMULcolor, mADDcolor);

			_unlock();
		}
		//-----------------------------------------------------------------------
		void OgreMovableShape::packed(const AtlasPacker::PackResultList& pack_result)
		{
			AtlasPacker::PackResultList::const_iterator it = pack_result.find((uint)mShapeResource);
			if(it != pack_result.end())
			{
				setAtlasQuad(it->second);
			}
		}
		//-----------------------------------------------------------------------
	}
}
