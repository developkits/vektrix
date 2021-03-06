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

#ifndef __vtxswfParserTypes_H__
#define __vtxswfParserTypes_H__

#include "vtxswf.h"

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	// unsigned types
	typedef unsigned char	UI8;
	typedef unsigned short	UI16;
	typedef unsigned int	UI32;
	typedef unsigned		UBits;

	// signed types
	typedef signed short	SI16;
	typedef signed			SBits;
	//-----------------------------------------------------------------------
	class TagNames
	{
	public:
		static const char* getTagName(const uint& tag_type);

	protected:
		static const char* mNames[];
	};
	//-----------------------------------------------------------------------
	enum TagTypes
	{
		TT_End = 0, 
		TT_ShowFrame = 1, 
		TT_DefineShape = 2, 
		TT_PlaceObject = 4, 
		TT_DefineBits = 6, 
		TT_DefineButton = 7, 
		TT_JPEGTables = 8, 
		TT_SetBackgroundColor = 9, 
		TT_DefineFont = 10, 
		TT_DefineText = 11, 
		TT_DefineBitsLossless = 20, 
		TT_DefineBitsJPEG2 = 21, 
		TT_DefineShape2 = 22, 
		TT_PlaceObject2 = 26, 
		TT_RemoveObject2 = 28, 
		TT_DefineShape3 = 32, 
		TT_DefineText2 = 33, 
		TT_DefineButton2 = 34, 
		TT_DefineBitsJPEG3 = 35, 
		TT_DefineBitsLossless2 = 36, 
		TT_DefineEditText = 37, 
		TT_DefineSprite = 39, 
		TT_FrameLabel = 43, 
		TT_FileAttributes = 69, 
		TT_DefineFont3 = 75, 
		TT_SymbolClass = 76, 
		TT_MetaData = 77, 
		TT_DefineScalingGrid = 78, 
		TT_DoABC = 82, 
		TT_DefineShape4 = 83, 
		TT_DefineSceneAndFrameLabelData = 86, 
		TT_DefineBitsJPEG4 = 90
	};
	//-----------------------------------------------------------------------
	enum BitmapFormat
	{
		BF_8BIT_COLOR_MAPPED = 3, 
		BF_15BIT_RGB = 4, 
		BF_24BIT_RGB = 5, 
		BF_32BIT_ARGB = 5
	};
	//-----------------------------------------------------------------------
	enum LanguageCode
	{
		LC_Latin = 1, 
		LC_Japanese = 2, 
		LC_Korean = 3, 
		LC_Simplified_Chinese = 4, 
		LC_Traditional_Chinese = 5
	};
	//-----------------------------------------------------------------------
	enum ShapeElementType
	{
		SET_MOVE = 0, 
		SET_LINE, 
		SET_BEZIER
	};
	//-----------------------------------------------------------------------
	enum FillStyleType
	{
		FST_Solid = 0, 
		FST_LinearGradient = 16, 
		FST_RadialGradient = 18, 
		FST_FocalRadialGradient = 19, 
		FST_RepeatingBitmap = 64, 
		FST_ClippedBitmap = 65, 
		FST_NonSmoothedRepeatingBitmap = 66, 
		FST_NonSmoothedClippedBitmap = 67
	};
	//-----------------------------------------------------------------------
	enum FontFlag
	{
		FF_HasLayout	= 128, 
		FF_ShiftJIS		= 64, 
		FF_SmallText	= 32, 
		FF_ANSI			= 16, 
		FF_WideOffsets	= 8, 
		FF_WideCodes	= 4, 
		FF_Italic		= 2, 
		FF_Bold			= 1
	};
	//-----------------------------------------------------------------------
	enum PlaceObjectFlag
	{
		POF_HasClipActions		= 128, 
		POF_HasClipDepth		= 64, 
		POF_HasName				= 32, 
		POF_HasRatio			= 16, 
		POF_HasColorTransform	= 8, 
		POF_HasMatrix			= 4, 
		POF_HasCharacter		= 2, 
		POF_Move				= 1
	};
	//-----------------------------------------------------------------------
	enum EditTextFlag
	{
		ETF_HasText			= 128,
		ETF_WordWrap		= 64, 
		ETF_Multiline		= 32, 
		ETF_Password		= 16, 
		ETF_ReadOnly		= 8, 
		ETF_HasTextColor	= 4, 
		ETF_HasMaxLength	= 2, 
		ETF_HasFont			= 1, 
		ETF_HasFontClass	= 128 << 8, 
		ETF_AutoSize		= 64 << 8, 
		ETF_HasLayout		= 32 << 8, 
		ETF_NoSelect		= 16 << 8, 
		ETF_Border			= 8 << 8, 
		ETF_WasStatic		= 4 << 8, 
		ETF_HTML			= 2 << 8, 
		ETF_UseOutlines		= 1 << 8
	};
	//-----------------------------------------------------------------------
	// MATH
	//-----------------------------------------------------------------------
	class RECT
	{
	public:
		SBits xmin, ymin, xmax, ymax;

		RECT() 
			: xmin(0), 
			xmax(0), 
			ymin(0), 
			ymax(0){}
	};
	//-----------------------------------------------------------------------
	class MATRIX
	{
	public:
		SBits sx, cx, tx, 
			cy, sy, ty;

		MATRIX() 
			: sx(65536), cx(0), tx(0), 
			cy(0), sy(65536), ty(0){}
	};
	//-----------------------------------------------------------------------
	class CXFORM
	{
	public:
		SBits add_red, add_green, add_blue, add_alpha, 
			mul_red, mul_green, mul_blue, mul_alpha;

		CXFORM() 
			: add_red(255), add_green(255), add_blue(255), add_alpha(255), 
			mul_red(255), mul_green(255), mul_blue(255), mul_alpha(255){}
	};
	//-----------------------------------------------------------------------
	// COLORS
	//-----------------------------------------------------------------------
	class RGB
	{
	public:
		UI8 red, green, blue;

		RGB() 
			: red(255), 
			green(255), 
			blue(255) {}
	};
	//-----------------------------------------------------------------------
	class RGBA
	{
	public:
		UI8 red, green, blue, alpha;

		RGBA() 
			: red(255), 
			green(255), 
			blue(255), 
			alpha(255) {}
	};
	//-----------------------------------------------------------------------
	class ARGB
	{
	public:
		UI8 alpha, red, green, blue;

		ARGB() 
			: alpha(255), 
			red(255), 
			green(255), 
			blue(255) {}
	};
	//-----------------------------------------------------------------------
	// FONT TYPES
	//-----------------------------------------------------------------------
	class KERNINGRECORD
	{
	public:
		UI16 left_char_code;
		UI16 right_char_code;
		SI16 adjustment;
	};
	//-----------------------------------------------------------------------
	class TEXTRECORD
	{
	public:
		UI16 font_id;
		RGBA color;
		SI16 x, y;
		UI16 size;
	};
	typedef std::vector<TEXTRECORD> TextRecordList;
	//-----------------------------------------------------------------------
	class GLYPHENTRY
	{
	public:
		UBits index;
		SBits x_advance;
	};
	typedef std::vector<GLYPHENTRY> GlyphEntryList;
	//-----------------------------------------------------------------------
	// SHAPE TYPES
	//-----------------------------------------------------------------------
	class FILLSTYLE
	{
	public:
		typedef std::map<UI8, RGBA> GradientMap;

		FillStyleType type;
		RGBA color;
		GradientMap gradient;
		MATRIX matrix;
		UI16 bitmapId;
	};
	typedef std::vector<FILLSTYLE> FillstyleList;
	typedef std::map<uint, FILLSTYLE> FillstyleMap;
	//-----------------------------------------------------------------------
	class LINESTYLE
	{
	public:
		RGBA color;
		UI16 width;
	};
	typedef std::vector<LINESTYLE> LinestyleList;
	typedef std::map<uint, LINESTYLE> LinestyleMap;
	//-----------------------------------------------------------------------
	class SHAPEELEMENT
	{
	public:
		int i;
		SBits x, y, cx, cy;
		int fill0, fill1, line;
		ShapeElementType type;

		SHAPEELEMENT() 
			: x(0), y(0), 
			cx(0), cy(0), 
			type(SET_MOVE){}
	};
	typedef std::vector<SHAPEELEMENT> ShapeElementList;
	//-----------------------------------------------------------------------
	class SHAPE
	{
	public:
		FillstyleList fillstyles;
		LinestyleList linestyles;
		ShapeElementList elements;

		void clear()
		{
			elements.clear();
			fillstyles.clear();
			linestyles.clear();
		}
	};
	//-----------------------------------------------------------------------
}}

#endif
