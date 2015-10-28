// pxCore CopyRight 2007-2015 John Robinson
// pxText2.h

#ifndef PX_TEXT2_H
#define PX_TEXT2_H

// TODO it would be nice to push this back into implemention
#include <ft2build.h>
#include FT_FREETYPE_H

#include "rtString.h"
#include "rtRefT.h"
#include "pxScene2d.h"
#include "pxText.h"


/*#### truncation - one of the following values
* NONE - no trunctaction
* TRUNCATE - text is truncated at the bottom of the text object.  The last word may be partially truncated. 
* TRUNCATE_AT_WORD_BOUNDARY - text is truncated at the bottom of the text object.  Truncation occurs at the word boundary.
* ELLIPSES - text is truncated at the bottom of the text object with ellipses applied.  The last word may be broken off by the ellipses.
* ELLIPSES_AT_WORD_BOUNDARY - text is truncated at the bottom of the text object with ellipses applied to the last possible full word.
###### Note: When truncation is applied at the word boundary, in a situation where the last line of text to be rendered contains a
*/
enum PX_TRUNCATION {
	NONE, 
	TRUNCATE,
	TRUNCATE_AT_WORD
};
enum PX_VERTICAL_ALIGN {
	V_TOP, 
	V_CENTER,
	V_BOTTOM
};
enum PX_HORIZONTAL_ALIGN {
	H_LEFT, 
	H_CENTER,
	H_RIGHT
};
#define ELLIPSIS_STR "\u2026"
#define ELLIPSIS_LEN (sizeof(ELLIPSIS_STR)-1)	
static const char isnew_line_chars[] = "\n\v\f\r";
static const char word_boundary_chars[] = " \t/:&,;.";
static const char space_chars[] = " \t";

/**********************************************************************
 * 
 * pxTextMetrics
 * 
 **********************************************************************/
class pxTextMetrics: public pxObject {

public:
	pxTextMetrics(pxScene2d* s): pxObject(s), mRefCount(0) {  }
	virtual ~pxTextMetrics() {}

	virtual unsigned long AddRef() 
	{
		return rtAtomicInc(&mRefCount);
	}

	virtual unsigned long Release() 
	{
		long l = rtAtomicDec(&mRefCount);
		if (l == 0) delete this;
			return l;
	}
	rtDeclareObject(pxTextMetrics, pxObject);
	rtReadOnlyProperty(height, height, float); 
	rtReadOnlyProperty(ascent, ascent, float);
	rtReadOnlyProperty(descent, descent, float);
  rtReadOnlyProperty(naturalLeading, naturalLeading, float);
  rtReadOnlyProperty(baseline, baseline, float);
 
	float height()             const { rtValue value;if (getCloneProperty("height", value) == RT_OK){ return value.toFloat();} return mHeight; }
	rtError height(float& v)   const { rtValue value;if (getCloneProperty("height", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mHeight; return RT_OK;   }
	rtError setHeight(float v)       {  setCloneProperty("height",v); /*mHeight = v;*/ return RT_OK;   }

	float ascent()             const { rtValue value;if (getCloneProperty("ascent", value) == RT_OK){ return value.toFloat();} return mAscent; }
	rtError ascent(float& v)   const { rtValue value;if (getCloneProperty("ascent", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mAscent; return RT_OK;   }
	rtError setAscent(float v)       { setCloneProperty("ascent",v); /*mAscent = v;*/ return RT_OK;   }

	float descent()             const { rtValue value;if (getCloneProperty("descent", value) == RT_OK){ return value.toFloat();} return mDescent; }
	rtError descent(float& v)   const { rtValue value;if (getCloneProperty("descent", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mDescent; return RT_OK;   }
	rtError setDescent(float v)       { setCloneProperty("descent",v); /*mDescent = v;*/ return RT_OK;   }
 
 	float naturalLeading()             const { rtValue value;if (getCloneProperty("naturalLeading", value) == RT_OK){ return value.toFloat();} return mNaturalLeading; }
	rtError naturalLeading(float& v)   const { rtValue value;if (getCloneProperty("naturalLeading", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mNaturalLeading; return RT_OK;   }
	rtError setNaturalLeading(float v)       { setCloneProperty("naturalLeading",v); /*mNaturalLeading = v;*/ return RT_OK;   }
  
 	float baseline()             const { rtValue value;if (getCloneProperty("baseline", value) == RT_OK){ return value.toFloat();} return mBaseline; }
	rtError baseline(float& v)   const { rtValue value;if (getCloneProperty("baseline", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mBaseline; return RT_OK;   }
	rtError setBaseline(float v)       { setCloneProperty("baseline",v); /*mBaseline = v;*/ return RT_OK;   }

  virtual void commitClone();
   
  private:
    rtAtomic mRefCount;	
   	float mHeight;
    float mAscent;
    float mDescent;
    float mNaturalLeading;
    float mBaseline;
};

/**********************************************************************
 * 
 * pxCharPosition
 * 
 **********************************************************************/
class pxCharPosition: public pxObject {

public:
	pxCharPosition(pxScene2d* s): pxObject(s), mRefCount(0) {  }
	virtual ~pxCharPosition() {}

	virtual unsigned long AddRef() 
	{
		return rtAtomicInc(&mRefCount);
	}

	virtual unsigned long Release() 
	{
		long l = rtAtomicDec(&mRefCount);
		if (l == 0) delete this;
			return l;
	}
  
	rtDeclareObject(pxCharPosition, pxObject);
	rtReadOnlyProperty(x, x, float);
  rtReadOnlyProperty(y, y, float);

	float x()             const { rtValue value;if (getCloneProperty("x", value) == RT_OK){ return value.toFloat();}  return mX; }
	rtError x(float& v)   const { rtValue value;if (getCloneProperty("x", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mX; return RT_OK;   }
	rtError setX(float v)       { setCloneProperty("x",v); /*mX = v;*/ return RT_OK;   }

	float y()             const { rtValue value;if (getCloneProperty("y", value) == RT_OK){ return value.toFloat();} return mY; }
	rtError y(float& v)   const { rtValue value;if (getCloneProperty("y", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mY; return RT_OK;   }
	rtError setY(float v)       { setCloneProperty("y",v); /*mY = v;*/ return RT_OK;   }

  void clear() {
    mX = 0;
    mY = 0;
  }

  virtual void commitClone();
      
  private:
    rtAtomic mRefCount;	
    float mX;
    float mY;
    
};

/**********************************************************************
 * 
 * pxTextBounds
 * 
 **********************************************************************/
class pxTextBounds: public pxObject {

public:
	pxTextBounds(pxScene2d* s): pxObject(s), mRefCount(0) { clear(); }
	virtual ~pxTextBounds() {}

	virtual unsigned long AddRef() 
	{
		return rtAtomicInc(&mRefCount);
	}

	virtual unsigned long Release() 
	{
		long l = rtAtomicDec(&mRefCount);
		if (l == 0) delete this;
			return l;
	}
  
	rtDeclareObject(pxTextBounds, pxObject);
	rtReadOnlyProperty(x1, x1, float);
  rtReadOnlyProperty(y1, y1, float);
  rtReadOnlyProperty(x2, x2, float);
  rtReadOnlyProperty(y2, y2, float);

	float x1()             const { rtValue value;if (getCloneProperty("x1", value) == RT_OK){ return value.toFloat();} return mX1; }
	rtError x1(float& v)   const { rtValue value;if (getCloneProperty("x1", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mX1; return RT_OK;   }
	rtError setX1(float v)       { setCloneProperty("x1",v); mX1 = v; return RT_OK;   }

	float y1()             const { rtValue value;if (getCloneProperty("y1", value) == RT_OK){ return value.toFloat();} return mY1; }
	rtError y1(float& v)   const { rtValue value;if (getCloneProperty("y1", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mY1; return RT_OK;   }
	rtError setY1(float v)       { setCloneProperty("y1",v); mY1 = v; return RT_OK;   }

	float x2()             const { rtValue value;if (getCloneProperty("x2", value) == RT_OK){ return value.toFloat();} return mX2; }
	rtError x2(float& v)   const { rtValue value;if (getCloneProperty("x2", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mX2; return RT_OK;   }
	rtError setX2(float v)       { setCloneProperty("x2",v); mX2 = v; return RT_OK;   }

	float y2()             const { rtValue value;if (getCloneProperty("y2", value) == RT_OK){ return value.toFloat();} return mY2; }
	rtError y2(float& v)   const { rtValue value;if (getCloneProperty("y2", value) == RT_OK){ v = value.toFloat(); return RT_OK;} v = mY2; return RT_OK;   }
	rtError setY2(float v)       { setCloneProperty("y2",v); mY2 = v; return RT_OK;   }
      
  void clear() {
    mX1 = 0;
    mY1 = 0;
    mX2 = 0;
    mY2 = 0;
  }

  virtual void commitClone();

  private:
    rtAtomic mRefCount;	
    float mX1;
    float mY1;
    float mX2;
    float mY2;  
    
};
/**********************************************************************
 * 
 * pxTextMeasurements
 * 
 **********************************************************************/
class pxTextMeasurements: public pxObject {

public:
	pxTextMeasurements(pxScene2d* s): pxObject(s), mRefCount(0) { 
    mBounds = new pxTextBounds(s);
    mFirstChar = new pxCharPosition(s);
    mLastChar = new pxCharPosition(s);
  }
	virtual ~pxTextMeasurements() {}

	virtual unsigned long AddRef() 
	{
		return rtAtomicInc(&mRefCount);
	}

	virtual unsigned long Release() 
	{
		long l = rtAtomicDec(&mRefCount);
		if (l == 0) delete this;
			return l;
	}
	rtDeclareObject(pxTextMeasurements, pxObject);
  rtReadOnlyProperty(bounds, bounds, rtObjectRef);
  rtReadOnlyProperty(firstChar, firstChar, rtObjectRef);
  rtReadOnlyProperty(lastChar, lastChar, rtObjectRef);

  /*TODO: do these need to be updated for clone support*/
  
  rtError bounds(rtObjectRef& v) const
  {
    v = mBounds;
    return RT_OK;
  }
  rtError firstChar(rtObjectRef& v) const
  {
    v = mFirstChar;
    return RT_OK;
  }
  rtError lastChar(rtObjectRef& v) const
  {
    v = mLastChar;
    return RT_OK;
  }

  rtRefT<pxTextBounds> getBounds()      { return mBounds;}
  rtRefT<pxCharPosition> getFirstChar() { return mFirstChar; }
  rtRefT<pxCharPosition> getLastChar()  { return mLastChar; }
  
  void clear() {
    mBounds->clear();
    mFirstChar->clear();
    mLastChar->clear();
  }
      
  private:
    rtAtomic mRefCount;	
    
    rtRefT<pxTextBounds> mBounds;
    rtRefT<pxCharPosition> mFirstChar;
    rtRefT<pxCharPosition> mLastChar;
    
};

/**********************************************************************
 * 
 * pxTex2
 * 
 **********************************************************************/
class pxText2: public pxText {
public:
  rtDeclareObject(pxText2, pxText);

  pxText2(pxScene2d* s);
  ~pxText2();
  
  rtProperty(wordWrap, wordWrap, setWordWrap, bool);
  rtProperty(ellipsis, ellipsis, setEllipsis, bool);
  rtProperty(xStartPos, xStartPos, setXStartPos, float); 
  rtProperty(xStopPos, xStopPos, setXStopPos, float);
  rtProperty(truncation, truncation, setTruncation, uint32_t);
  rtProperty(verticalAlign, verticalAlign, setVerticalAlign, uint32_t);
  rtProperty(horizontalAlign, horizontalAlign, setHorizontalAlign, uint32_t);
  rtProperty(leading, leading, setLeading, float); 	
  
  bool wordWrap()            const {rtValue value;if (getCloneProperty("wordWrap", value) == RT_OK){ return value.toBool();} return mWordWrap;}
  rtError wordWrap(bool& v)  const {rtValue value;if (getCloneProperty("wordWrap", value) == RT_OK){v = value.toBool();return RT_OK;} v = mWordWrap; return RT_OK;  }
  rtError setWordWrap(bool v) { setCloneProperty("wordWrap",v); /*mWordWrap = v;*/ return RT_OK; }
  
  bool ellipsis()            const {rtValue value;if (getCloneProperty("ellipsis", value) == RT_OK){ return value.toBool();} return mEllipsis;}
  rtError ellipsis(bool& v)  const {rtValue value;if (getCloneProperty("ellipsis", value) == RT_OK){v = value.toBool();return RT_OK;} v = mEllipsis; return RT_OK;  }
  rtError setEllipsis(bool v) { setCloneProperty("ellipsis",v); /*mEllipsis = v;*/ return RT_OK; }
  
  float xStartPos()             const { rtValue value;if (getCloneProperty("xStartPos", value) == RT_OK){ return value.toFloat();}return mXStartPos; }
  rtError xStartPos(float& v)   const { rtValue value;if (getCloneProperty("xStartPos", value) == RT_OK){v = value.toFloat();return RT_OK;}v = mXStartPos; return RT_OK;   }
  rtError setXStartPos(float v) { setCloneProperty("xStartPos",v); /*mXStartPos = v;*/ return RT_OK; }
  
  float xStopPos()             const { rtValue value;if (getCloneProperty("xStopPos", value) == RT_OK){ return value.toFloat();}return mXStopPos; }
  rtError xStopPos(float& v)   const {rtValue value;if (getCloneProperty("xStopPos", value) == RT_OK){v = value.toFloat();return RT_OK;} v = mXStopPos; return RT_OK;   }
  rtError setXStopPos(float v) { setCloneProperty("xStopPos",v); /*mXStopPos = v;*/ return RT_OK; }
    
  uint32_t truncation()             const { rtValue value;if (getCloneProperty("truncation", value) == RT_OK){ return value.toInt32();}return mTruncation; }
  rtError truncation(uint32_t& v)   const {rtValue value;if (getCloneProperty("truncation", value) == RT_OK){v = value.toInt32();return RT_OK;} v = mTruncation; return RT_OK;   }
  rtError setTruncation(uint32_t v)       { setCloneProperty("truncation",v); /*mTruncation = v;*/ return RT_OK;   }

  uint8_t verticalAlign()             const { rtValue value;if (getCloneProperty("verticalAlign", value) == RT_OK){ return value.toInt8();}return mVerticalAlign; }
  rtError verticalAlign(uint32_t& v)   const {rtValue value;if (getCloneProperty("verticalAlign", value) == RT_OK){v = value.toInt8();return RT_OK;} v = mVerticalAlign; return RT_OK;   }
  rtError setVerticalAlign(uint32_t v)       { setCloneProperty("verticalAlign",v); /*mVerticalAlign = v;*/ return RT_OK;   }
  
  uint8_t horizontalAlign()             const { rtValue value;if (getCloneProperty("horizontalAlign", value) == RT_OK){ return value.toInt8();}return mHorizontalAlign; }
  rtError horizontalAlign(uint32_t& v)   const {rtValue value;if (getCloneProperty("horizontalAlign", value) == RT_OK){v = value.toInt8();return RT_OK;} v = mHorizontalAlign; return RT_OK;   }
  rtError setHorizontalAlign(uint32_t v)       { setCloneProperty("horizontalAlign",v); /*mHorizontalAlign = v; */ return RT_OK;   }
  
  float leading()             const { rtValue value;if (getCloneProperty("leading", value) == RT_OK){ return value.toFloat();}return mLeading; }
  rtError leading(float& v)   const {rtValue value;if (getCloneProperty("leading", value) == RT_OK){v = value.toFloat();return RT_OK;} v = mLeading; return RT_OK;   }
  rtError setLeading(float v)       { setCloneProperty("leading",v); /*mLeading = v;*/ return RT_OK;   }
  
  virtual rtError setText(const char* s); 
  virtual rtError setPixelSize(uint32_t v);
  virtual rtError setFaceURL(const char* s);
  virtual rtError setW(float v)       { return pxObject::setW(v);   }
  virtual rtError setH(float v)       { return pxObject::setH(v);   }  
  virtual rtError setClip(bool v) {  setCloneProperty("clip",v); /*mClip = v;*/ return RT_OK; }
  void renderText(uint8_t render);
  virtual void fontLoaded();
  void determineMeasurementBounds();
  virtual void draw();
  virtual void onInit();
  virtual void update(double t);
  virtual void commitClone();
  rtError setCloneProperty(rtString propertyName, rtValue value);
 
  rtMethodNoArgAndReturn("getFontMetrics", getFontMetrics, rtObjectRef);
  rtError getFontMetrics(rtObjectRef& o);
  rtMethodNoArgAndReturn("measureText", measureText, rtObjectRef);
  rtError measureText(rtObjectRef& o); 

  virtual rtError Set(const char* name, const rtValue* value)
  {
	  //printf("pxText2 Set for %s\n", name );

    mDirty = mDirty || (!strcmp(name,"wordWrap") ||
              !strcmp(name,"ellipsis") ||
              !strcmp(name,"xStartPos") ||
              !strcmp(name,"xStopPos") ||
              !strcmp(name,"truncation") ||
              !strcmp(name,"verticalAlign")||
              !strcmp(name,"horizontalAlign") ||
              !strcmp(name,"leading"));

    rtError e = pxText::Set(name, value);

    return e;
  }


 protected:
 
	uint32_t mTruncation;  
	float mXStartPos;
	float mXStopPos;
	uint32_t mVerticalAlign;
	uint32_t mHorizontalAlign;
	float mLeading;
	bool mWordWrap;
	bool mEllipsis;
  
  bool mInitialized;
  bool mNeedsRecalc;
  
  rtRefT<pxTextMeasurements> measurements;
  uint32_t lineNumber;
  uint32_t lastLineNumber;
  float noClipX, noClipY, noClipW, noClipH;
//  float startX;
  float startY;
//  bool clippedLastLine;
  
  void setNeedsRecalc(bool recalc);
  virtual float getFBOWidth();
  virtual float getFBOHeight(); 
  bool isNewline( char ch );
  bool isWordBoundary( char ch );
  bool isSpaceChar( char ch );  
  
  void renderTextRowWithTruncation(rtString & accString, float lineWidth, float tempX, float tempY, float sx, float sy, uint32_t pixelSize, float* color, uint8_t render);
  void renderTextNoWordWrap(float sx, float sy, float tempX, uint8_t render);
  void renderTextWithWordWrap(const char *text, float sx, float sy, float tempX, uint32_t pixelSize, float* color, uint8_t render);
  void measureTextWithWrapOrNewLine(const char *text, float sx, float sy, float tempX, float &tempY, uint32_t size, float* color, uint8_t render);
  void renderOneLine(const char * tempStr, float tempX, float tempY, float sx, float sy,  uint32_t size, float* color, float lineWidth, uint8_t render );
  
  void recalc();
  void clearMeasurements();
  void setMeasurementBoundsY(bool start, float yVal);
  void setMeasurementBoundsX(bool start, float xVal);  
  void setMeasurementBounds(bool start, float xVal, float yVal);
  void setMeasurementBounds(float xPos, float width, float yPos, float height);
  void setLineMeasurements(bool firstLine, float xPos, float y);
};

#endif
