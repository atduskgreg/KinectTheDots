#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    loadData();
    showNums = true;
    showLines = true;
}

//--------------------------------------------------------------
void testApp::update(){


}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    for(int i = 0; i < lines.size(); i++){
        if(showLines){
            lines.at(i).draw();
        }
      vector<ofPoint> points = lines.at(i).getVertices();
        
      for(int i = 0; i < points.size(); i++){
          ofPoint p = points.at(i);
          ofCircle(p.x, p.y, 3);
          if(showNums){
            ofDrawBitmapString(ofToString(i), p);
          } 
      }
    }
    
            
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
    
    cout << "numLines: " << lines.size() << endl;

    
  //  if (!pElem) return false;
    
    //hRoot = TiXmlHandle(pElem);
    
    //const char *attribval = hRoot.FirstChild("card").ToElement()->Attribute("card");
    //pElem = hDoc.FirstChild("EGCs").Child("card", 1).ToElement();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'n'){
        showNums = !showNums;
    }
    
    if(key == 'l'){
        showLines = !showLines;
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