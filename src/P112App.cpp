#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P112App : public AppNative {
  public:
	void prepareSettings(Settings *settings);
	void setup();
	void mouseDown(MouseEvent event);
	void mouseMove(MouseEvent event);
    void keyDown(KeyEvent event);
	void update();
	void draw();
    
    Vec2i mMouseLoc;
    int segmentCount;
};

void P112App::prepareSettings( Settings *settings ){
	settings->setWindowSize(800, 800);
	settings->setFrameRate(10.0f);
    
    segmentCount = 10;
    mMouseLoc = Vec2i(800, 800);
}

void P112App::setup()
{
}

void P112App::mouseMove(MouseEvent event) {
    mMouseLoc = event.getPos();
}

void P112App::keyDown( KeyEvent event ) {
    switch (event.getChar()) {
        case '1':
            segmentCount = 360;
            break;
        case '2':
            segmentCount = 45;
            break;
        case '3':
            segmentCount = 24;
            break;
        case '4':
            segmentCount = 12;
            break;
        case '5':
            segmentCount = 6;
            break;
    }
}

void P112App::mouseDown( MouseEvent event )
{
}

void P112App::update()
{
}

void P112App::draw()
{
	// clear out the window with black
	gl::clear(Color(1.0f, 1.0f, 1.0f));
    
    int width = getWindowWidth();
    int height = getWindowHeight();
    
    float radius = 360.0f;
    float angleStep = 360.0f/segmentCount;
    
    float color_s = float(mMouseLoc.x)/width;
    float color_v = float(mMouseLoc.y)/height;
    
    Vec2f c = Vec2f(width/2, height/2);
    Vec2f v2 = Vec2f(width/2 + radius, height/2);
    
    for (float angle = 0; angle <= 360; angle += angleStep) {
        float vx = width/2 + cosf(ci::toRadians(angle))*radius;
        float vy = height/2 + sinf(ci::toRadians(angle))*radius;
        
        Vec2f v3(vx, vy);
        
        gl::color(Color(CM_HSV, angle/360, color_s, color_v));
        gl::drawSolidTriangle(c, v2, v3);
        
        v2 = v3;
    }
    
    //console() << mMouseLoc.x << std::endl;
}

CINDER_APP_NATIVE( P112App, RendererGl )
