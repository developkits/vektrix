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

#ifndef __vtxHtmlParser_H__
#define __vtxHtmlParser_H__

#include "vtxPrerequisites.h"
#include "vtxXmlParser.h"

namespace vtx
{
	//-----------------------------------------------------------------------
	/** A XML-based HTML parser */
	class vtxExport HtmlParser : public XmlParser
	{
	public:
		HtmlParser();
		virtual ~HtmlParser();

		/** Parse the given HTML input String */
		bool parse(const String& input);

		/** Get the root node of the parsed HTML DOM tree */
		HtmlElement* getRoot() const;

		/** Get a unformatted text representation of the HTML text */
		const String& getPlainText() const;

	protected:
		typedef std::stack<HtmlElement*> ElementStack;

		bool mPrevElementWasText;
		String mConcatenatedText;

		HtmlElement* mRoot;
		String mPlainText;
		ElementStack mElementStack;

		void startElement(String name, StringMap atts);
		void endElement(String name);
		void elementData(String text);

		void font(StringMap& atts);
		void image(StringMap& atts);
		void paragraph(StringMap& atts);
		void linebreak();
	};
	//-----------------------------------------------------------------------
}

#endif
