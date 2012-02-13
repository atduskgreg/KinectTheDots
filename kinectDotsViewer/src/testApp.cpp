#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
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
    
    canvasScale = 8;
    
    canvas.allocate(ofGetWidth() * canvasScale, ofGetHeight() * canvasScale);
 
}

//--------------------------------------------------------------
void testApp::update(){


}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    canvas.begin();
    ofPushMatrix();
    ofClear(255,0);

    ofScale(canvasScale, canvasScale);
    ofSetColor(0);
    for(int i = 0; i < lines.size(); i++){
        if(showLines){
          lines.at(i).draw();
        }
        vector<ofPoint> points = lines.at(i).getVertices();
        if(showAllPoints){  
            for(int i = 0; i < points.size(); i++){
                ofPoint p = points.at(i);
                ofCircle(p.x, p.y, 3);
                if(showNums){
                    ofDrawBitmapString(ofToString(i), p);
                } 
            }
        } else {
            ofCircle(nextPoint.x, nextPoint.y, 3);
        }
    }
    
    ofSetColor(255,0,0);
    ofCircle(currentPoint.x, currentPoint.y, 2);
    ofPopMatrix();
    canvas.end();
    
    if(lines.size() > 0){

        ofTranslate(-1 * (currentPoint.x * canvasScale) + ofGetWidth()/2, -1 * (currentPoint.y * canvasScale) + ofGetHeight()/2);
        ofSetColor(255);
        canvas.draw(0,0);
    }
    
}

ofPoint testApp::getNextPoint(){
    if(nextLineNum >= lines.size()){
        nextLineNum = 0;
    }
    
    cout << "line: " << nextLineNum <<  "/" << lines.size() -1 << " point: " << nextPointNum << "/" << lines.at(nextLineNum).getVertices().size() -1 << endl;
    
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
    
    cout << "line: " << currentLineNum <<  "/" << lines.size() -1 << " point: " << currentPointNum << "/" << lines.at(currentLineNum).getVertices().size() -1 << endl;
    
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
        }
        
        
        lines.push_back(line);
        
        xml.popTag();
    }
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
        currentPoint = getCurrentPoint();
        nextPoint = getNextPoint();
    }
    
    if(key == '='){
        canvasScale += 1;
        cout << canvasScale << endl;
    }
    
    if(key == '-'){
        canvasScale -= 1;
        cout << canvasScale << endl;
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