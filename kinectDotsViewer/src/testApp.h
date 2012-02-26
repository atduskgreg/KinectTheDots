#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTween.h"
#include "ofxOpenNI.h"
#include "inkParticleSystem.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void loadData();
    ofPoint getNextPoint();
    ofPoint getCurrentPoint();
    void animateView();
    void transformView();
    ofPoint getViewTarget();
    
    void drawDots();
    void drawDrawing();
    
    void fullReveal();
    
    float currentScale();
    
    string finalTime;
    bool timeStopped;
    
    string currentHint;
    
    bool victory;
    
    bool useKinect;
    
    bool skipToNextLine;
    
    int currentXml;
    
    int prevLineNum;
    
    bool pointBaseNeedsRefresh;
    ofPoint pointBase;
    
    ofDirectory xmlDir;

    float canvasWidth;
    
    int currentDrawingSegment;
    
    ofPoint previousViewTarget;
    
    int totalPointCount;
    int totalPointsHit;
    
    ofxOpenNIContext	recordContext, playContext;
	ofxImageGenerator	recordImage, playImage;
    
    ofxDepthGenerator	recordDepth, playDepth;
	ofxHandGenerator	recordHandTracker, playHandTracker;
	ofxUserGenerator	recordUser, playUser;
    
    //  ofxHandGenerator handTracker;
    // ofxOpenNIContext	kinect;
    //ofxDepthGenerator depthGenerator;
    //  ofxUserGenerator	user;
    
    
    ofxTween tween;
    ofxEasingCubic easingcubic;
    
    ofImage currentDrawingImage;
    
    ofImage handWarning;
    
    ofImage ink;
    
    ofPoint convertToDrawingPoint(ofPoint p);
    
    vector<ofPolyline> lines;
    
    vector<ofPolyline> drawing;
    
    inkParticleSystem particleSystem;

    
    bool promptForHand;
    bool prevPromptForHand;
    
    bool showNums;
    bool showLines;
    bool showAllPoints;
    bool showDebug;
    
    int canvasScale, prevCanvasScale;
    
    ofFbo canvas, drawingCanvas, preview, noise;
    
    ofShader shader;
    
    ofPoint currentPoint;
    ofPoint nextPoint;
    
    int currentPointNum;
    int currentLineNum;
    
    int nextPointNum;
    int nextLineNum;
    
    
};
