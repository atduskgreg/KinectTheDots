#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    loadNewImage();
    showImage =  true;
    showNums = true;
    penDown = true;
    
    lines.push_back(ofPolyline());
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    if(showImage){
        sourceImage.draw(0,0);
    }

    for(int i = 0; i < lines.size(); i++){
        lines.at(i).draw();
    }
    
    if(showNums){
        for(int i = 0; i < lines.size(); i++){
            vector<ofPoint> points = lines.at(i).getVertices();
            
            for(int i = 0; i < points.size(); i++){
                ofDrawBitmapString(ofToString(i), points.at(i));
            }
        }
    }
}

void testApp::saveData(){
    TiXmlElement* msg;
    
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );
    
    TiXmlElement * root = new TiXmlElement( "Lines" );  
	doc.LinkEndChild( root );  
    
    msg = new TiXmlElement( "Image" );  
    root->LinkEndChild( msg ); 
    
    msg->SetAttribute("filename", currentFilename);
    
    for(int i = 0; i < lines.size(); i++){
       
        TiXmlElement * line = new TiXmlElement( "Line" );  
        root->LinkEndChild( line );  
        
        vector<ofPoint> points = lines.at(i).getVertices();
        for(int j = 0; j < points.size(); j++){
            msg = new TiXmlElement( "Point" );  
            line->LinkEndChild( msg ); 
            
            msg->SetAttribute("x", points.at(j).x);
            msg->SetAttribute("y", points.at(j).y);
        }
	}
        
    stringstream filename;
    filename << currentFilename << ".xml";
    
    cout << "saving: " << ofToDataPath(filename.str()) << endl;
	doc.SaveFile( ofToDataPath(filename.str())  );

}

void testApp::loadNewImage(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an image");
    currentFilename = result.filePath;
    sourceImage.loadImage(currentFilename);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'h'){
        showImage = !showImage;
    }
    
    if(key == 'n'){
        showNums = !showNums;
    }
    
    if(key == ' '){
        if(!penDown){
            lines.push_back(ofPolyline());
        }
        
        penDown = !penDown;
    }
    
    if(key == 's'){
        saveData();
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
    if(penDown){
        lines.back().addVertex(ofPoint(x,y));
    }
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