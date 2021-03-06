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

#include "vtxInstancePool.h"
#include "vtxInstance.h"

#include "vtxLogManager.h"
#include "vtxResource.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	InstancePool::InstancePool()
	{

	}
	//-----------------------------------------------------------------------
	InstancePool::~InstancePool()
	{
		uint numDeletes = 0;

		PoolMap::iterator it = mPoolMap.begin();
		PoolMap::iterator end = mPoolMap.end();
		while(it != end)
		{
			Pool* pool = it->second;
			VTX_LOG("Destroying %d instance(s) with type %s from instance pool", pool->size(), it->first.c_str());

			while(pool->size())
			{
				Instance* inst = pool->top();
				Resource* res = inst->getResource();
				if(inst->getName().length())
				{
					VTX_LOG("Destroyed instance with name %s", inst->getName().c_str());
				}
				if(res)
				{
					VTX_LOG("Destroyed instance with assigned resource type: %s, id: %s", 
						res->getType().c_str(), 
						res->getID().c_str());
				}
				delete inst;
				pool->pop();
				++numDeletes;
			}

			delete pool;
			++it;
		}

		VTX_LOG("InstancePool: destroyed %d instance%s", numDeletes, (numDeletes==1)?"":"s");
	}
	//-----------------------------------------------------------------------
	void InstancePool::push(Instance* inst)
	{
		_getPool(inst->getType(), true)->push(inst);
	}
	//-----------------------------------------------------------------------
	Instance* InstancePool::pop(const String& type)
	{
		Pool* pool = _getPool(type);

		if(pool && pool->size())
		{
			Instance* inst = pool->top();
			pool->pop();
			return inst;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	InstancePool::Pool* InstancePool::_getPool(const String& type, const bool& auto_create)
	{
		Pool* pool = NULL;

		PoolMap::iterator it = mPoolMap.find(type);
		if(it != mPoolMap.end())
		{
			pool = it->second;
		}
		else if(auto_create)
		{
			pool = new Pool;
			mPoolMap.insert(std::make_pair(type, pool));
		}

		return pool;
	}
	//-----------------------------------------------------------------------
}
