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

#include "vtxd3d9Texture.h"

#include "vtxRect.h"

namespace vtx
{
	namespace d3d9
	{
		//-----------------------------------------------------------------------
		D3D9Texture::D3D9Texture(uint size) 
			: Texture(size)
		{
			// create updatable D3D9 texture here
		}
		//-----------------------------------------------------------------------
		D3D9Texture::~D3D9Texture()
		{
			// free texture here
		}
		//-----------------------------------------------------------------------
		void D3D9Texture::paintPixelsToRect(const vtx::Rect& coordinates, unsigned char* pixelData)
		{
			// blit the specified pixel rect to the texture
		}
		//-----------------------------------------------------------------------
	}
}
