/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#pragma once

#include "vtxPrerequesites.h"
#include "vtxInstancePool.h"
#include "vtxTimeline.h"
#include "vtxVector2.h"

namespace vtx
{
	class vtxExport Movie/* : public InstancePool*/
	{
	public:
		friend class MovieFactory;
		friend class Root;

		virtual ~Movie();

		typedef std::map<uint, MovableObject*> CanvasLayers;

		const String& getName();
		File* getFile();

		void addTime(float delta_time);

		void setMouseAbs(uint x, uint y);
		void setMouseRel(float x, float y);

		// timeline functions
		void play();
		void stop();
		bool goto_frame(uint frame);
		bool goto_time(float time);

		virtual Instance* getInstance(const String& id);
		virtual void releaseInstance(Instance* instance);

		bool setObjectToLayer(uint layer, MovableObject* object);
		MovableObject* getObjectFromLayer(uint layer);
		bool removeObjectFromLayer(uint layer);
		void clearLayers();

	protected:
		Movie(const String& name, File* file, MovieFactory* creator);

		String mName;
		File* mFile;
		MovieFactory* mCreator;
		RenderStrategy* mDataPool;
		Timeline mTimeline;
		CanvasLayers mLayers;
		Vector2 mMousePosition;

		//void _initialize(File* file);
		void _initialize(RenderStrategy* dataPool);
		void _setCreator(MovieFactory* factory);
	};
}