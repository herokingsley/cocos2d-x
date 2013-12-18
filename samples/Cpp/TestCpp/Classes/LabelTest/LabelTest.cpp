    #include "LabelTest.h"
#include "../testResource.h"

enum {
    kTagTileMap = 1,
    kTagSpriteManager = 1,
    kTagAnimation1 = 1,
    kTagBitmapAtlas1 = 1,
    kTagBitmapAtlas2 = 2,
    kTagBitmapAtlas3 = 3,
};

enum {
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

//------------------------------------------------------------------
//
// AtlasDemo
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

Layer* nextAtlasAction();
Layer* backAtlasAction();
Layer* restartAtlasAction();

static int sceneIdx = -1; 

static std::function<Layer*()> createFunctions[] =
{
    CL(LabelAtlasTest),
    CL(LabelAtlasColorTest),
    CL(Atlas3),
    CL(Atlas4),
    CL(Atlas5),
    CL(Atlas6),
    CL(AtlasBitmapColor),
    CL(AtlasFastBitmap),
    CL(BitmapFontMultiLine),
    CL(LabelsEmpty),
    CL(LabelBMFontHD),
    CL(LabelAtlasHD),
    CL(LabelGlyphDesigner),
    CL(LabelTTFTest),
    CL(LabelTTFMultiline),
    CL(LabelTTFChinese),
    CL(LabelBMFontChinese),
    CL(BitmapFontMultiLineAlignment),
    CL(LabelTTFA8Test),
    CL(BMFontOneAtlas),
    CL(BMFontUnicode),
    CL(BMFontInit),
    CL(TTFFontInit),
    CL(Issue1343),
    CL(LabelTTFAlignment),
    CL(LabelBMFontBounds),
    CL(TTFFontShadowAndStroke),
    // should be moved to another test
    CL(Atlas1),
    CL(LabelBMFontCrashTest),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextAtlasAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backAtlasAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartAtlasAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
} 


AtlasDemo::AtlasDemo(void)
{
}

AtlasDemo::~AtlasDemo(void)
{
}

std::string AtlasDemo::title()
{
    return "No title";
}

std::string AtlasDemo::subtitle()
{
    return "";
}

void AtlasDemo::onEnter()
{
    BaseTest::onEnter();
}

void AtlasDemo::restartCallback(Object* sender)
{
    auto s = new AtlasTestScene();
    s->addChild(restartAtlasAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemo::nextCallback(Object* sender)
{
    auto s = new AtlasTestScene();
    s->addChild( nextAtlasAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void AtlasDemo::backCallback(Object* sender)
{
    auto s = new AtlasTestScene();
    s->addChild( backAtlasAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
Atlas1::Atlas1()
{
    _textureAtlas = TextureAtlas::create(s_AtlasTest, 3); _textureAtlas->retain();
    
    auto s = Director::getInstance()->getWinSize();

    //
    // Notice: u,v tex coordinates are inverted
    //
    V3F_C4B_T2F_Quad quads[] = 
    {
        {
            {Vertex3F(0,0,0),Color4B(0,0,255,255),Tex2F(0.0f,1.0f),},                // bottom left
            {Vertex3F(s.width,0,0),Color4B(0,0,255,0),Tex2F(1.0f,1.0f),},            // bottom right
            {Vertex3F(0,s.height,0),Color4B(0,0,255,0),Tex2F(0.0f,0.0f),},            // top left
            {Vertex3F(s.width,s.height,0),Color4B(0,0,255,255),Tex2F(1.0f,0.0f),},    // top right
        },        
        {
            {Vertex3F(40,40,0),Color4B(255,255,255,255),Tex2F(0.0f,0.2f),},            // bottom left
            {Vertex3F(120,80,0),Color4B(255,0,0,255),Tex2F(0.5f,0.2f),},            // bottom right
            {Vertex3F(40,160,0),Color4B(255,255,255,255),Tex2F(0.0f,0.0f),},        // top left
            {Vertex3F(160,160,0),Color4B(0,255,0,255),Tex2F(0.5f,0.0f),},            // top right
        },

        {
            {Vertex3F(s.width/2,40,0),Color4B(255,0,0,255),Tex2F(0.0f,1.0f),},        // bottom left
            {Vertex3F(s.width,40,0),Color4B(0,255,0,255),Tex2F(1.0f,1.0f),},        // bottom right
            {Vertex3F(s.width/2-50,200,0),Color4B(0,0,255,255),Tex2F(0.0f,0.0f),},        // top left
            {Vertex3F(s.width,100,0),Color4B(255,255,0,255),Tex2F(1.0f,0.0f),},        // top right
        },
        
    };
    
    
    for( int i=0;i<3;i++) 
    {
        _textureAtlas->updateQuad(&quads[i], i);
    }
}

Atlas1::~Atlas1()
{
    _textureAtlas->release();
}

void Atlas1::draw()
{
    // GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
    // GL_TEXTURE_2D

    _textureAtlas->drawQuads();

//    [textureAtlas drawNumberOfQuads:3];
    
}

std::string Atlas1::title()
{
    return "CCTextureAtlas";
}

std::string Atlas1::subtitle()
{
    return "Manual creation of TextureAtlas";
}

//------------------------------------------------------------------
//
// LabelAtlasTest
//
//------------------------------------------------------------------

LabelAtlasTest::LabelAtlasTest()
{
    _time = 0;

    auto label1 = LabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Point(10,100) );
    label1->setOpacity( 200 );

    auto label2 = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Point(10,200) );
    label2->setOpacity( 32 );

    schedule(schedule_selector(LabelAtlasTest::step)); 
    
}

void LabelAtlasTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //string.format("%2.2f Test", _time);

    auto label1 = (LabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (LabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    //string.format("%d", (int)_time);
    label2->setString(string);
}

std::string LabelAtlasTest::title()
{
    return "LabelAtlas";
}

std::string LabelAtlasTest::subtitle()
{
    return "Updating label should be fast";
}

//------------------------------------------------------------------
//
// LabelAtlasColorTest
//
//------------------------------------------------------------------
LabelAtlasColorTest::LabelAtlasColorTest()
{
    auto label1 = LabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( Point(10,100) );
    label1->setOpacity( 200 );
    
    auto label2 = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( Point(10,200) );
    label2->setColor( Color3B::RED );

    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto cb = CallFunc::create(CC_CALLBACK_0(LabelAtlasColorTest::actionFinishCallback, this));
    auto seq = Sequence::create(fade, fade_in, cb, NULL);
    auto repeat = RepeatForever::create( seq );
    label2->runAction( repeat );    

    _time = 0;
    
    schedule( schedule_selector(LabelAtlasColorTest::step) ); //:@selector(step:)];
}

void LabelAtlasColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelAtlasColorTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //std::string string = std::string::createWithFormat("%2.2f Test", _time);
    auto label1 = (LabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);
    
    auto label2 = (LabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString( string );    
}

std::string LabelAtlasColorTest::title()
{
    return "CCLabelAtlas";
}

std::string LabelAtlasColorTest::subtitle()
{
    return "Opacity + Color should work at the same time";
}


//------------------------------------------------------------------
//
// LabelTTFAlignment
//
//------------------------------------------------------------------
LabelTTFAlignment::LabelTTFAlignment()
{
    auto s = Director::getInstance()->getWinSize();

    auto ttf0 = LabelTTF::create("Alignment 0\nnew line", "Helvetica", 12,
                                          Size(256, 32), TextHAlignment::LEFT);
    
    ttf0->setPosition(Point(s.width/2,(s.height/6)*2));
    ttf0->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf0);
    
    auto ttf1 = LabelTTF::create("Alignment 1\nnew line", "Helvetica", 12,
                                      Size(245, 32), TextHAlignment::CENTER);
    ttf1->setPosition(Point(s.width/2,(s.height/6)*3));
    ttf1->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf1);

    auto ttf2 = LabelTTF::create("Alignment 2\nnew line", "Helvetica", 12,
                                          Size(245, 32), TextHAlignment::RIGHT);
    ttf2->setPosition(Point(s.width/2,(s.height/6)*4));
    ttf2->setAnchorPoint(Point(0.5f,0.5f));
    this->addChild(ttf2);
}

std::string LabelTTFAlignment::title()
{
    return "CCLabelTTF alignment";
}

std::string LabelTTFAlignment::subtitle()
{
    return "Tests alignment values";
}
//------------------------------------------------------------------
//
// Atlas3
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas3::Atlas3()
{
    _time = 0;

    auto col = LayerColor::create( Color4B(128,128,128,255) );
    addChild(col, -10);
    
    auto label1 = LabelBMFont::create("Test",  "fonts/bitmapFontTest2.fnt");
    
    // testing anchors
    label1->setAnchorPoint( Point(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto seq = Sequence::create(fade, fade_in, NULL);
    auto repeat = RepeatForever::create(seq);
    label1->runAction(repeat);
    

    // VERY IMPORTANT
    // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
    // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
    // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
    auto label2 = LabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label2->setAnchorPoint( Point(0.5f, 0.5f) );
    label2->setColor( Color3B::RED );
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->runAction( repeat->clone() );
    
    auto label3 = LabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label3->setAnchorPoint( Point(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
       
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );

    schedule( schedule_selector(Atlas3::step) );//:@selector(step:)];
}

void Atlas3::step(float dt)
{
    _time += dt;
    //std::string string;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    //string.format("%2.2f Test j", _time);
    
    auto label1 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    auto label2 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    auto label3 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);
}

std::string Atlas3::title()
{
    return "CCLabelBMFont";
}

std::string Atlas3::subtitle()
{
    return "Testing alignment. Testing opacity + tint";
}

//------------------------------------------------------------------
//
// Atlas4
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas4::Atlas4()
{
    _time = 0;

    // Upper Label
    auto label = LabelBMFont::create("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    
    
    auto BChar = (Sprite*) label->getChildByTag(0);
    auto FChar = (Sprite*) label->getChildByTag(7);
    auto AChar = (Sprite*) label->getChildByTag(12);
    
    
    auto rotate = RotateBy::create(2, 360);
    auto rot_4ever = RepeatForever::create(rotate);
    
    auto scale = ScaleBy::create(2, 1.5f);
    auto scale_back = scale->reverse();
    auto scale_seq = Sequence::create(scale, scale_back,NULL);
    auto scale_4ever = RepeatForever::create(scale_seq);
    
    auto jump = JumpBy::create(0.5f, Point::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    
    auto fade_out = FadeOut::create(1);
    auto fade_in = FadeIn::create(1);
    auto seq = Sequence::create(fade_out, fade_in, NULL);
    auto fade_4ever = RepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    auto label2 = LabelBMFont::create("00.0", "fonts/bitmapFontTest.fnt");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( Point(s.width/2.0f, 80) );
    
    auto lastChar = (Sprite*) label2->getChildByTag(3);
    lastChar->runAction( rot_4ever->clone() );
    
    schedule( schedule_selector(Atlas4::step), 0.1f);
}

void Atlas4::draw()
{
    auto s = Director::getInstance()->getWinSize();
    DrawPrimitives::drawLine( Point(0, s.height/2), Point(s.width, s.height/2) );
    DrawPrimitives::drawLine( Point(s.width/2, 0), Point(s.width/2, s.height) );
}

void Atlas4::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
//     std::string string;
//     string.format("%04.1f", _time);
    
    auto label1 = (LabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string Atlas4::title()
{
    return "CCLabelBMFont";
}

std::string Atlas4::subtitle()
{
    return "Using fonts as Sprite objects. Some characters should rotate.";
}

//------------------------------------------------------------------
//
// Atlas5
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas5::Atlas5()
{
    auto label = LabelBMFont::create("abcdefg", "fonts/bitmapFontTest4.fnt");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
}

std::string Atlas5::title()
{
    return "CCLabelBMFont";
}

std::string Atlas5::subtitle()
{
    return "Testing padding";
}
//------------------------------------------------------------------
//
// Atlas6
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas6::Atlas6()
{
    auto s = Director::getInstance()->getWinSize();

    LabelBMFont* label = NULL;
    label = LabelBMFont::create("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2+50) );
    label->setAnchorPoint( Point(0.5f, 0.5f) ) ;
    
    label = LabelBMFont::create("fafefifofu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );

    label = LabelBMFont::create("aeiou", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/2-50) );
    label->setAnchorPoint( Point(0.5f, 0.5f) ); 
}

std::string Atlas6::title()
{
    return "CCLabelBMFont";
}

std::string Atlas6::subtitle()
{
    return "Rendering should be OK. Testing offset";
}

//------------------------------------------------------------------
//
// AtlasBitmapColor
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
AtlasBitmapColor::AtlasBitmapColor()
{
    auto s = Director::getInstance()->getWinSize();
    
    LabelBMFont* label = NULL;
    label = LabelBMFont::create("Blue", "fonts/bitmapFontTest5.fnt");
    label->setColor( Color3B::BLUE );
    addChild(label);
    label->setPosition( Point(s.width/2, s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );

    label = LabelBMFont::create("Red", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    label->setColor( Color3B::RED );

    label = LabelBMFont::create("G", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( Point(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( Point(0.5f, 0.5f) );
    label->setColor( Color3B::GREEN );
    label->setString("Green");
}

std::string AtlasBitmapColor::title()
{
    return "CCLabelBMFont";
}

std::string AtlasBitmapColor::subtitle()
{
    return "Testing color";
}

//------------------------------------------------------------------
//
// AtlasFastBitmap
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

AtlasFastBitmap::AtlasFastBitmap()
{
        // Upper Label
        for( int i=0 ; i < 100;i ++ ) 
        {
            char str[6] = {0};
            sprintf(str, "-%d-", i);
            auto label = LabelBMFont::create(str, "fonts/bitmapFontTest.fnt");
            addChild(label);
            
            auto s = Director::getInstance()->getWinSize();

            auto p = Point( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
            label->setPosition( p );
            label->setAnchorPoint(Point(0.5f, 0.5f));
        }
}

std::string AtlasFastBitmap::title()
{
    return "CCLabelBMFont";
}

std::string AtlasFastBitmap::subtitle()
{
    return "Creating several LabelBMFont with the same .fnt file should be fast";
}

//------------------------------------------------------------------
//
// BitmapFontMultiLine
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
BitmapFontMultiLine::BitmapFontMultiLine()
{
    Size s;

    // Left
    auto label1 = LabelBMFont::create(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(Point(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    auto label2 = LabelBMFont::create("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(Point(0.5f, 0.5f));
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    auto label3 = LabelBMFont::create("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(Point(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string BitmapFontMultiLine::title()
{
    return "CCLabelBMFont";
}

std::string BitmapFontMultiLine::subtitle()
{
    return "Multiline + anchor point";
}

//------------------------------------------------------------------
//
// LabelsEmpty
//
//------------------------------------------------------------------
LabelsEmpty::LabelsEmpty()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelBMFont::create("", "fonts/bitmapFontTest3.fnt");
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Point(s.width/2, s.height-100));

    // LabelTTF
    auto label2 = LabelTTF::create("", "Arial", 24);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Point(s.width/2, s.height/2));

    // LabelAtlas
    auto label3 = LabelAtlas::create("", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(Point(s.width/2, 0+100));

    schedule(schedule_selector(LabelsEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelsEmpty::updateStrings(float dt)
{
    auto label1 = static_cast<LabelBMFont*>( getChildByTag(kTagBitmapAtlas1) );
    auto label2 = static_cast<LabelTTF*>( getChildByTag(kTagBitmapAtlas2) );
    auto label3 = static_cast<LabelAtlas*>( getChildByTag(kTagBitmapAtlas3) );

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
        label3->setString("hi");

        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
        label3->setString("");

        setEmpty = false;
    }
}

std::string LabelsEmpty::title()
{
    return "Testing empty labels";
}

std::string LabelsEmpty::subtitle()
{
    return "3 empty labels: LabelAtlas, LabelTTF and LabelBMFont";
}

//------------------------------------------------------------------
//
// LabelBMFontHD
//
//------------------------------------------------------------------
LabelBMFontHD::LabelBMFontHD()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelBMFont::create("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelBMFontHD::title()
{
    return "Testing Retina Display BMFont";
}

std::string LabelBMFontHD::subtitle()
{
    return "loading arista16 or arista16-hd";
}

//------------------------------------------------------------------
//
// LabelAtlasHD
//
//------------------------------------------------------------------
LabelAtlasHD::LabelAtlasHD()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = LabelAtlas::create("TESTING RETINA DISPLAY", "fonts/larabie-16.plist");
    label1->setAnchorPoint(Point(0.5f, 0.5f));

    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelAtlasHD::title()
{
    return "LabelAtlas with Retina Display";
}

std::string LabelAtlasHD::subtitle()
{
    return "loading larabie-16 / larabie-16-hd";
}

//------------------------------------------------------------------
//
// LabelGlyphDesigner
//
//------------------------------------------------------------------
LabelGlyphDesigner::LabelGlyphDesigner()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);

    // LabelBMFont
    auto label1 = LabelBMFont::create("Testing Glyph Designer", "fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelGlyphDesigner::title()
{
    return "Testing Glyph Designer";
}

std::string LabelGlyphDesigner::subtitle()
{
    return "You should see a font with shawdows and outline";
}

void AtlasTestScene::runThisTest()
{
    sceneIdx = -1;
    auto layer = nextAtlasAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------
LabelTTFTest::LabelTTFTest()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    auto colorLayer = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(Point(0,0));
    colorLayer->setPosition(Point((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

    this->addChild(colorLayer);

    MenuItemFont::setFontSize(30);
    auto menu = Menu::create(
		MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFTest::setAlignmentLeft, this)),
		MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFTest::setAlignmentCenter, this)),
		MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFTest::setAlignmentRight, this)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(50, s.height / 2 - 20));
    this->addChild(menu);

    menu = Menu::create(
		MenuItemFont::create("Top", CC_CALLBACK_1(LabelTTFTest::setAlignmentTop, this)),
		MenuItemFont::create("Middle", CC_CALLBACK_1(LabelTTFTest::setAlignmentMiddle, this)),
		MenuItemFont::create("Bottom", CC_CALLBACK_1(LabelTTFTest::setAlignmentBottom, this)),
		NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Point(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    _plabel = NULL;
    _horizAlign = TextHAlignment::LEFT;
    _vertAlign = TextVAlignment::TOP;

    this->updateAlignment();
}

LabelTTFTest::~LabelTTFTest()
{
    CC_SAFE_RELEASE(_plabel);
}

void  LabelTTFTest::updateAlignment()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    if (_plabel)
    {
        _plabel->removeFromParentAndCleanup(true);
    }

    CC_SAFE_RELEASE(_plabel);

    _plabel = LabelTTF::create(this->getCurrentAlignment(), "Marker Felt", 32,
                                  blockSize, _horizAlign, _vertAlign);
    _plabel->retain();

    _plabel->setAnchorPoint(Point(0,0));
    _plabel->setPosition(Point((s.width - blockSize.width) / 2, (s.height - blockSize.height)/2 ));

    this->addChild(_plabel);
}

void LabelTTFTest::setAlignmentLeft(Object* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentCenter(Object* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentRight(Object* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentTop(Object* sender)
{
    _vertAlign = TextVAlignment::TOP;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentMiddle(Object* sender)
{
    _vertAlign = TextVAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentBottom(Object* sender)
{
    _vertAlign = TextVAlignment::BOTTOM;
    this->updateAlignment();
}

const char* LabelTTFTest::getCurrentAlignment()
{
    const char* vertical = NULL;
    const char* horizontal = NULL;
    switch (_vertAlign) {
        case TextVAlignment::TOP:
            vertical = "Top";
            break;
        case TextVAlignment::CENTER:
            vertical = "Middle";
            break;
        case TextVAlignment::BOTTOM:
            vertical = "Bottom";
            break;
    }
    switch (_horizAlign) {
        case TextHAlignment::LEFT:
            horizontal = "Left";
            break;
        case TextHAlignment::CENTER:
            horizontal = "Center";
            break;
        case TextHAlignment::RIGHT:
            horizontal = "Right";
            break;
    }

    return String::createWithFormat("Alignment %s %s", vertical, horizontal)->getCString();
}

std::string LabelTTFTest::title()
{
    return "Testing LabelTTF";
}

std::string LabelTTFTest::subtitle()
{
    return "Select the buttons on the sides to change alignment";
}

LabelTTFMultiline::LabelTTFMultiline()
{
    auto s = Director::getInstance()->getWinSize();

    auto center = LabelTTF::create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
                                            "Paint Boy",
                                            32,
                                            Size(s.width/2,200),
                                            TextHAlignment::CENTER,
                                            TextVAlignment::TOP);

    center->setPosition(Point(s.width / 2, 150));

    addChild(center);
}

std::string LabelTTFMultiline::title()
{
    return "Testing LabelTTF Word Wrap";
}

std::string LabelTTFMultiline::subtitle()
{
    return "Word wrap using LabelTTF and a custom TTF font";
}

LabelTTFChinese::LabelTTFChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("中国", "Marker Felt", 30);
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelTTFChinese::title()
{
    return "Testing LabelTTF with Chinese character";
}

LabelBMFontChinese::LabelBMFontChinese()
{
    auto size = Director::getInstance()->getWinSize();
    auto label = LabelBMFont::create("中国", "fonts/bitmapFontChinese.fnt");
    label->setPosition(Point(size.width / 2, size.height /2));
    this->addChild(label);
}

std::string LabelBMFontChinese::title()
{
    return "Testing LabelBMFont with Chinese character";
}

/// BitmapFontMultiLineAlignment

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding = 50;
static float menuItemPaddingCenter = 50;
BitmapFontMultiLineAlignment::BitmapFontMultiLineAlignment()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BitmapFontMultiLineAlignment::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // ask director the the window size
    auto size = Director::getInstance()->getWinSize();

    // create and initialize a Label
    this->_labelShouldRetain = LabelBMFont::create(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, TextHAlignment::CENTER);
    this->_labelShouldRetain->retain();

    this->_arrowsBarShouldRetain = Sprite::create("Images/arrowsBar.png");
    this->_arrowsBarShouldRetain->retain();
    this->_arrowsShouldRetain = Sprite::create("Images/arrows.png");
    this->_arrowsShouldRetain->retain();

    MenuItemFont::setFontSize(20);
    auto longSentences = MenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto lineBreaks = MenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto mixed = MenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    auto stringMenu = Menu::create(longSentences, lineBreaks, mixed, NULL);
    stringMenu->alignItemsVertically();

    longSentences->setColor(Color3B::RED);
    _lastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    MenuItemFont::setFontSize(30);

    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto center = MenuItemFont::create("Center", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    auto alignmentMenu = Menu::create(left, center, right, NULL);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(Color3B::RED);
    _lastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->_labelShouldRetain->setPosition(Point(size.width/2, size.height/2));

    this->_arrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->_arrowsBarShouldRetain->setScaleX(arrowsWidth / this->_arrowsBarShouldRetain->getContentSize().width);
    this->_arrowsBarShouldRetain->setPosition(Point(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_labelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(Point(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(Point(size.width/2, menuItemPaddingCenter+15));

    this->addChild(this->_labelShouldRetain);
    this->addChild(this->_arrowsBarShouldRetain);
    this->addChild(this->_arrowsShouldRetain);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);
}

BitmapFontMultiLineAlignment::~BitmapFontMultiLineAlignment()
{
    this->_labelShouldRetain->release();
    this->_arrowsBarShouldRetain->release();
    this->_arrowsShouldRetain->release();
}

std::string BitmapFontMultiLineAlignment::title()
{
    return "";
}

std::string BitmapFontMultiLineAlignment::subtitle()
{
    return "";
}

void BitmapFontMultiLineAlignment::stringChanged(cocos2d::Object *sender)
{
    auto item = (MenuItemFont*)sender;
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        this->_labelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        this->_labelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        this->_labelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::alignmentChanged(cocos2d::Object *sender)
{
    auto item = static_cast<MenuItemFont*>(sender);
    item->setColor(Color3B::RED);
    this->_lastAlignmentItem->setColor(Color3B::WHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::LEFT);
        break;
    case CenterAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::CENTER);
        break;
    case RightAlign:
        this->_labelShouldRetain->setAlignment(TextHAlignment::RIGHT);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches[0];
    auto location = touch->getLocationInView();

    if (this->_arrowsShouldRetain->getBoundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBarShouldRetain->setVisible(true);
    }
}

void BitmapFontMultiLineAlignment::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBarShouldRetain->setVisible(false);
}

void BitmapFontMultiLineAlignment::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (! _drag)
    {
        return;
    }

    auto touch = touches[0];
    auto location = touch->getLocationInView();

    auto winSize = Director::getInstance()->getWinSize();

    this->_arrowsShouldRetain->setPosition(Point(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->_arrowsShouldRetain->getPosition().x - this->_labelShouldRetain->getPosition().x) * 2;

    this->_labelShouldRetain->setWidth(labelWidth);
}

void BitmapFontMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrowsShouldRetain->setPosition(Point(this->_labelShouldRetain->getPosition().x + this->_labelShouldRetain->getContentSize().width/2,
        this->_labelShouldRetain->getPosition().y));
}

/// LabelTTFA8Test
LabelTTFA8Test::LabelTTFA8Test()
{
    auto s = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128, 128, 128, 255));
    addChild(layer, -10);

    // LabelBMFont
    auto label1 = LabelTTF::create("Testing A8 Format", "Marker Felt", 48);
    addChild(label1);
    label1->setColor(Color3B::RED);
    label1->setPosition(Point(s.width/2, s.height/2));

    auto fadeOut = FadeOut::create(2);
    auto fadeIn = FadeIn::create(2);
    auto seq = Sequence::create(fadeOut, fadeIn, NULL);
    auto forever = RepeatForever::create(seq);
    label1->runAction(forever);
}

std::string LabelTTFA8Test::title()
{
    return "Testing A8 Format";
}

std::string LabelTTFA8Test::subtitle()
{
    return "RED label, fading In and Out in the center of the screen";
}

/// BMFontOneAtlas
BMFontOneAtlas::BMFontOneAtlas()
{
    auto s = Director::getInstance()->getWinSize();

    auto label1 = LabelBMFont::create("This is Helvetica", "fonts/helvetica-32.fnt", kLabelAutomaticWidth, TextHAlignment::LEFT, Point::ZERO);
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/3*2));

    auto label2 = LabelBMFont::create("And this is Geneva", "fonts/geneva-32.fnt", kLabelAutomaticWidth, TextHAlignment::LEFT, Point(0, 128));
    addChild(label2);
    label2->setPosition(Point(s.width/2, s.height/3*1));
}

std::string BMFontOneAtlas::title()
{
    return "CCLabelBMFont with one texture";
}

std::string BMFontOneAtlas::subtitle()
{
    return "Using 2 .fnt definitions that share the same texture atlas.";
}

/// BMFontUnicode
BMFontUnicode::BMFontUnicode()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/strings.xml");
    std::string chinese  = strings["chinese1"].asString();
    std::string russian  = strings["russian"].asString();
    std::string spanish  = strings["spanish"].asString();
    std::string japanese = strings["japanese"].asString();

    auto s = Director::getInstance()->getWinSize();

    auto label1 = LabelBMFont::create(spanish, "fonts/arial-unicode-26.fnt", 200, TextHAlignment::LEFT);
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/5*4));

    auto label2 = LabelBMFont::create(chinese, "fonts/arial-unicode-26.fnt");
    addChild(label2);
    label2->setPosition(Point(s.width/2, s.height/5*3));

    auto label3 = LabelBMFont::create(russian, "fonts/arial-26-en-ru.fnt");
    addChild(label3);
    label3->setPosition(Point(s.width/2, s.height/5*2));

    auto label4 = LabelBMFont::create(japanese, "fonts/arial-unicode-26.fnt");
    addChild(label4);
    label4->setPosition(Point(s.width/2, s.height/5*1));
}

std::string BMFontUnicode::title()
{
    return "CCLabelBMFont with Unicode support";
}

std::string BMFontUnicode::subtitle()
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

// BMFontInit

BMFontInit::BMFontInit()
{
    auto s = Director::getInstance()->getWinSize();

    auto bmFont = LabelBMFont::create();

    bmFont->setFntFile("fonts/helvetica-32.fnt");
    bmFont->setString("It is working!");
    this->addChild(bmFont);
    bmFont->setPosition(Point(s.width/2,s.height/4*2));
}

std::string BMFontInit::title()
{
    return "LabelBMFont create()";
}

std::string BMFontInit::subtitle()
{
    return "Testing LabelBMFont::create() wihtout params";
}

// TTFFontInit

TTFFontInit::TTFFontInit()
{
    auto s = Director::getInstance()->getWinSize();

    auto font = LabelTTF::create();

    font->setFontName("Marker Felt");
    font->setFontSize(48);
    font->setString("It is working!");
    this->addChild(font);
    font->setPosition(Point(s.width/2,s.height/4*2));
}

std::string TTFFontInit::title()
{
    return "LabelTTF create()";
}

std::string TTFFontInit::subtitle()
{
    return "Testing LabelTTF::create() wihtout params";
}

TTFFontShadowAndStroke::TTFFontShadowAndStroke()
{
    auto layer = LayerColor::create(Color4B(0,190,0,255));
    addChild(layer, -10);
    
    auto s = Director::getInstance()->getWinSize();
    
    Color3B tintColorRed(  255, 0, 0   );
    Color3B tintColorYellow( 255, 255, 0 );
    Color3B tintColorBlue( 0, 0, 255   );
    Color3B strokeColor( 0, 10, 255  );
    Color3B strokeShadowColor( 255, 0, 0   );
    
    Size shadowOffset(12.0, 12.0);
    
    FontDefinition shadowTextDef;
    shadowTextDef._fontSize = 20;
    shadowTextDef._fontName = std::string("Marker Felt");
    
    shadowTextDef._shadow._shadowEnabled = true;
    shadowTextDef._shadow._shadowOffset  = shadowOffset;
    shadowTextDef._shadow._shadowOpacity = 1.0;
    shadowTextDef._shadow._shadowBlur    = 1.0;
    shadowTextDef._fontFillColor   = tintColorRed;
    
    // shadow only label
    auto fontShadow = LabelTTF::createWithFontDefinition("Shadow Only Red Text", shadowTextDef);
    
    // add label to the scene
    this->addChild(fontShadow);
    fontShadow->setPosition(Point(s.width/2,s.height/4*2.5));
    

    // create the stroke only label
    FontDefinition strokeTextDef;
    strokeTextDef._fontSize = 20;
    strokeTextDef._fontName = std::string("Marker Felt");
    
    strokeTextDef._stroke._strokeEnabled = true;
    strokeTextDef._stroke._strokeColor   = strokeColor;
    strokeTextDef._stroke._strokeSize    = 1.5;
    
    strokeTextDef._fontFillColor   = tintColorYellow;
    
    // stroke only label
    auto fontStroke = LabelTTF::createWithFontDefinition("Stroke Only Yellow Text", strokeTextDef);
    
    // add label to the scene
    this->addChild(fontStroke);
    fontStroke->setPosition(Point(s.width/2,s.height/4*1.8));
    
    
    
    // create the label stroke and shadow
    FontDefinition strokeShaodwTextDef;
    strokeShaodwTextDef._fontSize = 20;
    strokeShaodwTextDef._fontName = std::string("Marker Felt");
    
    strokeShaodwTextDef._stroke._strokeEnabled = true;
    strokeShaodwTextDef._stroke._strokeColor   = strokeShadowColor;
    strokeShaodwTextDef._stroke._strokeSize    = 1.5;
    
    strokeShaodwTextDef._shadow._shadowEnabled = true;
    strokeShaodwTextDef._shadow._shadowOffset  = shadowOffset;
    strokeShaodwTextDef._shadow._shadowOpacity = 1.0;
    strokeShaodwTextDef._shadow._shadowBlur    = 1.0;
    
    
    strokeShaodwTextDef._fontFillColor   = tintColorBlue;
    
    // shadow + stroke label
    auto fontStrokeAndShadow = LabelTTF::createWithFontDefinition("Stroke & Shadow Blue Text", strokeShaodwTextDef);
    
    // add label to the scene
    this->addChild(fontStrokeAndShadow);
    fontStrokeAndShadow->setPosition(Point(s.width/2,s.height/4*1.1));
}

std::string TTFFontShadowAndStroke::title()
{
    return "CCLabelTTF  shadows + stroke";
}

std::string TTFFontShadowAndStroke::subtitle()
{
    return "Test for support of TTF label with stroke and shadow";
}


// Issue1343

Issue1343::Issue1343()
{
    auto s = Director::getInstance()->getWinSize();

    auto bmFont = LabelBMFont::create();

    bmFont->setFntFile("fonts/font-issue1343.fnt");
    bmFont->setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'");

    this->addChild(bmFont);

    bmFont->setScale(0.3f);
    bmFont->setPosition(Point(s.width/2,s.height/4*2));
}

std::string Issue1343::title()
{
    return "Issue 1343";
}

std::string Issue1343::subtitle()
{
    return "You should see: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'";
}

LabelBMFontBounds::LabelBMFontBounds()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);
    
    // LabelBMFont
    label1 = LabelBMFont::create("Testing Glyph Designer", "fonts/boundsTestFont.fnt");
    
    addChild(label1);
    label1->setPosition(Point(s.width/2, s.height/2));
}

std::string LabelBMFontBounds::title()
{
    return "Testing LabelBMFont Bounds";
}

std::string LabelBMFontBounds::subtitle()
{
    return "You should see string enclosed by a box";
}

void LabelBMFontBounds::draw()
{
    auto labelSize = label1->getContentSize();
    auto origin = Director::getInstance()->getWinSize();
    
    origin.width = origin.width / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Point vertices[4]=
    {
        Point(origin.width, origin.height),
        Point(labelSize.width + origin.width, origin.height),
        Point(labelSize.width + origin.width, labelSize.height + origin.height),
        Point(origin.width, labelSize.height + origin.height)
    };
    DrawPrimitives::drawPoly(vertices, 4, true);
}

// LabelBMFontCrashTest
void LabelBMFontCrashTest::onEnter()
{
    AtlasDemo::onEnter();
    
    auto winSize = Director::getInstance()->getWinSize();
    //Create a label and add it
    auto label1 = new LabelBMFont();
    label1->initWithString("test", "fonts/bitmapFontTest2.fnt");
    this->addChild(label1);
    // Visit will call draw where the function "ccGLBindVAO(m_uVAOname);" will be invoked.
    label1->visit();
    
    // Remove this label
    label1->removeFromParentAndCleanup(true);
    label1->release();
    
    // Create a new label and add it (then crashes)
    auto label2 = LabelBMFont::create("test 2", "fonts/bitmapFontTest.fnt");
    label2->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(label2);
}

std::string LabelBMFontCrashTest::title()
{
    return "LabelBMFont Crash Test";
}

std::string LabelBMFontCrashTest::subtitle()
{
    return "Should not crash.";
}
