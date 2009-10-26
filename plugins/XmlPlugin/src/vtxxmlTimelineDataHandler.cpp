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
#include "vtxxmlTimelineDataHandler.h"

#include "vtxCreateObjectEvent.h"
#include "vtxMoveObjectEvent.h"
#include "vtxRemoveObjectEvent.h"
#include "vtxFile.h"
#include "vtxKeyframe.h"
#include "vtxLogManager.h"
#include "vtxMatrix.h"
#include "vtxStringHelper.h"

namespace vtx
{
	namespace xml
	{
		//-----------------------------------------------------------------------
		void TimelineDataHandler::handle(const std::string& key, StringMap& atts, void* userdata)
		{
			mCurrentFile = static_cast<File*>(userdata);
			mAttributes = &atts;

			if(key == "vectrix|timeline|")
				mTimeline.clear();

			else if(key == "vectrix|timeline|keyframe|")
				handleKeyframe();

			else if(key == "vectrix|timeline|keyframe|event|")
				handleEvent();
		}
		//-----------------------------------------------------------------------
		void TimelineDataHandler::end(const std::string& key)
		{
			if(key == "vectrix|timeline|")
				mCurrentFile->setTimeline(mTimeline);

			else if(key == "vectrix|timeline|keyframe|")
				mTimeline.addKeyframe((Keyframe*)mContainer);
		}
		//-----------------------------------------------------------------------
		void TimelineDataHandler::handleKeyframe()
		{
			//mContainer->clear();
			mContainer = new Keyframe;

			size_t index = StringHelper::toUint((*mAttributes)["index"]);

			if(!index)
			{
				VTX_EXCEPT("\"%s\":Missing parameter \"index\" was not set!", mCurrentFile->getFilename().c_str());
			}

			static_cast<Keyframe*>(mContainer)->setIndex(index);
		}
		//-----------------------------------------------------------------------
		//void TimelineDataHandler::handleEvent()
		//{
		//	std::string type = (*mAttributes)["type"];

		//	if(!type.length())
		//	{
		//		VTX_EXCEPT("\"%s\": Missing parameter \"type\" in <event .../>!", mCurrentFile->getFilename().c_str());
		//	}

		//	if(type == "create")
		//	{
		//		std::string id = (*mAttributes)["id"];
		//		size_t layer = StringHelper::toUint((*mAttributes)["layer"]);
		//		Matrix matrix = StringHelper::toMatrix((*mAttributes)["matrix"]);
		//		CXForm cxform = StringHelper::toCXForm((*mAttributes)["cxform"]);

		//		mContainer->addEvent(new CreateObjectEvent(id, layer, matrix, cxform));
		//	}
		//	else if(type == "move")
		//	{
		//		size_t layer = StringHelper::toUint((*mAttributes)["layer"]);
		//		Matrix matrix = StringHelper::toMatrix((*mAttributes)["matrix"]);
		//		CXForm cxform = StringHelper::toCXForm((*mAttributes)["cxform"]);

		//		mContainer->addEvent(new MoveObjectEvent(layer, matrix, cxform));
		//	}
		//	else if(type == "remove")
		//	{
		//		size_t layer = StringHelper::toUint((*mAttributes)["layer"]);

		//		mContainer->addEvent(new RemoveObjectEvent(layer));
		//	}
		//}
		//-----------------------------------------------------------------------
	}
}
