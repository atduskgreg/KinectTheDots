#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    totalPointsHit = 0;
    totalPointCount = 0;
    
    loadData();
    showNums = true;
    showAllPoints = true;
    showLines = true;
    
    currentPointNum = 0;
    currentLineNum = 0;
    
    nextPointNum = 1;
    nextLineNum = 0;
    

    
    currentPoint =   getCurrentPoint();
    nextPoint = getNextPoint();
    
    canvasScale = 3 ;
    
    canvas.allocate(ofGetWidth(), ofGetHeight());
    drawingCanvas.allocate(ofGetWidth(), ofGetHeight());

    
    drawing.push_back(ofPolyline());
    
}

//--------------------------------------------------------------
void testApp::update(){

}

void testApp::transformView(){
    ofPoint viewTarget = getViewTarget();
    
    ofTranslate(-1 * (tween.update() * tween.getTarget(2)) + ofGetWidth()/2, -1 * (tween.getTarget(1) * tween.getTarget(2)) + ofGetHeight()/2);
    ofScale(tween.getTarget(2), tween.getTarget(2));

}

float testApp::currentScale(){
    float d = ofDist(currentPoint.x, currentPoint.y, nextPoint.x, nextPoint.y);
    float m = ofMap(d, 6, 38, 65, 5 ,true);
    
    return m;
}

void testApp::animateView(){
    totalPointsHit++;
    unsigned duration= 1000;
    unsigned delay = 0;
    ofPoint nextViewTarget = getViewTarget();
    tween.setParameters(easingcubic,ofxTween::easeInOut,previousViewTarget.x,nextViewTarget.x,duration,delay); // viewTarget.x
    tween.addValue(previousViewTarget.y, nextViewTarget.y); // viewTarget.y
    tween.addValue(prevCanvasScale, currentScale()); // canvasScale
    tween.start();
}



//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    
    canvas.begin();
    ofClear(255,0);
    transformView();
    
    ofSetColor(0);
    for(int i = 0; i < lines.size(); i++){
        if(showLines){
          lines.at(i).draw();
        }
        vector<ofPoint> points = lines.at(i).getVertices();
        if(showAllPoints){  
            for(int i = 0; i < points.size(); i++){
                ofPoint p = points.at(i);
                ofCircle(p.x, p.y, 1);
                if(showNums){
                    ofDrawBitmapString(ofToString(i), p);
                } 
            }
        } else {
            ofCircle(nextPoint.x, nextPoint.y, 1);
        }
    }
    
    ofPushStyle();
    ofSetColor(255,0,0);
    ofCircle(currentPoint.x, currentPoint.y, 1);
    ofPopStyle();

    
    canvas.end();
    
    drawingCanvas.begin();
    
    transformView();
    
    ofClear(255,0);
    ofSetColor(0, 0, 255);
    ofSetLineWidth(2);

    for(int i = 0; i < drawing.size(); i++){

        drawing.at(i).draw();

    }

    drawingCanvas.end();
    
    if(lines.size() > 0){

        ofSetColor(255,255,255,255);

        ofEnableAlphaBlending();

        canvas.draw(0,0);
        drawingCanvas.draw(0,0);
        
        ofSetColor(0, 0, 0);
        stringstream output;
        output << totalPointsHit << "/" << totalPointCount;
        ofDrawBitmapString(output.str(), ofPoint(10,20));
    }
    
    
}

ofPoint testApp::getViewTarget(){
    
    ofPoint result;
    
    result.x = (currentPoint.x + nextPoint.x)/2;
    result.y = (currentPoint.y + nextPoint.y)/2;
    
    return result;
}

ofPoint testApp::getNextPoint(){
    if(nextLineNum >= lines.size()){
        nextLineNum = 0;
    }
    
    ofPolyline line = lines.at(nextLineNum);
    ofPoint result = line[nextPointNum];
    
    nextPointNum++;
    
    if(nextPointNum >= lines.at(nextLineNum).getVertices().size()){
        nextPointNum = 0;
        nextLineNum++;
        
    }
    
    return result;

}

ofPoint testApp::getCurrentPoint(){
    if(currentLineNum >= lines.size()){
        currentLineNum = 0;
    }
    
    ofPolyline line = lines.at(currentLineNum);
    ofPoint result = line[currentPointNum];
    
    currentPointNum++;
    
    if(currentPointNum >= lines.at(currentLineNum).getVertices().size()){
        currentPointNum = 0;
        currentLineNum++;

    }
    
    return result;
}

void testApp::loadData(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select a file");    
    
    ofxXmlSettings xml;
    xml.loadFile(result.filePath);
    
    xml.pushTag("Lines");
    
    int numLines = xml.getNumTags("Line");
    for(int i = 0; i < numLines; i++){
        xml.pushTag("Line", i);
        
        ofPolyline line;
        
        int numPoints = xml.getNumTags("Point");
        for(int j = 0; j < numPoints; j++){        
            line.addVertex(ofPoint(xml.getAttribute("Point", "x", 0, j), xml.getAttribute("Point", "y", 0, j)));
            totalPointCount++;
            cout << totalPointCount << endl;
        }
        
        
        lines.push_back(line);
        
        xml.popTag();
    }
}

ofPoint testApp::convertToDrawingPoint(ofPoint p){
    ofPoint result = ofPoint(p.x, p.y);
    
    result.x = (p.x + getViewTarget().x * currentScale() - ofGetWidth()/2) / currentScale();
    result.y = (p.y + getViewTarget().y * currentScale() - ofGetHeight()/2) / currentScale();
    
    return result;
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'n'){
        showNums = !showNums;
    }
    
    if(key == 'l'){
        showLines = !showLines;
    }
    
    if(key == ' '){
        prevCanvasScale = currentScale();
        previousViewTarget = getViewTarget(); // store it before it changes for tweening
        
        currentPoint = getCurrentPoint();
        nextPoint = getNextPoint();
        animateView();
    }
    
    if(key == '='){
        canvasScale += 1;
       // cout << canvasScale << endl;
    }
    
    if(key == '-'){
        canvasScale -= 1;
       // cout << canvasScale << endl;
    }
    
    if(key == 'p'){
        showAllPoints = !showAllPoints;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){  
    if(!tween.isRunning()){

        ofPoint pointInDrawingSpace = convertToDrawingPoint(ofPoint(x,y));
        
        cout << "dist: " << ofDist(pointInDrawingSpace.x, pointInDrawingSpace.y, nextPoint.x, nextPoint.y) << endl;
        
        if(ofDist(pointInDrawingSpace.x, pointInDrawingSpace.y, nextPoint.x, nextPoint.y) <= 0.5 ){
            keyPressed(' ');
        } else {
                                                            
            drawing.at(0).addVertex(pointInDrawingSpace);
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}