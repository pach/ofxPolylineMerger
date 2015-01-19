#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    interpolateCoeff = 0;
    lastTime = 0;
    interpolateTime = 2.5;
    
    generatePolyline();
    
    pMerge.setup();
}

void ofApp::generatePolyline(){
    p1.clear();
    p2.clear();
    
    ofPoint p;
    int nbPoints = (int)ofRandom(100)+2;
    float noiseSeed= ofGetElapsedTimef();
    
    for (int i=0; i<nbPoints; i++) {
        p = ofPoint(ofNoise(i*0.05+noiseSeed, 0)*ofGetWidth(), ofNoise(i*0.05+noiseSeed, 1)*ofGetHeight());
        p1.addVertex(p);
    }
    
    nbPoints = (int)ofRandom(100)+2;
    noiseSeed= ofGetElapsedTimeMillis();
    
    for (int i=0; i<nbPoints; i++) {
        p = ofPoint(ofNoise(i*0.05+noiseSeed, 0)*ofGetWidth(), ofNoise(i*0.05+noiseSeed, 1)*ofGetHeight());
        p2.addVertex(p);
    }
    
    p1 = p1.getSmoothed(7.);
    p2 = p2.getSmoothed(7.);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    time = ofGetElapsedTimef()-lastTime;
    if (time>interpolateTime*2.) {
        lastTime = ofGetElapsedTimef();
    }
    
    interpolateCoeff = time/interpolateTime;
    if(interpolateCoeff>1.){
        interpolateCoeff = 2.-interpolateCoeff;
    }
    
    pMerge.mergePolyline(p1, p2, interpolateCoeff);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    
    ofSetColor(255, 0, 0);
    p1.draw();
    
    ofSetColor(0, 255, 0);
    p2.draw();
    
    ofSetColor(0, 0, 255);
    pMerge.draw();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("fps : "+ofToString(ofGetFrameRate()), 20, ofGetHeight()-60);
    ofDrawBitmapString("hit g to regenerate lines", 20, ofGetHeight()-40);
    ofDrawBitmapString("hit f / d to change numbers of points in merge polyline. actual number : "+ofToString(pMerge.getNbPoints()), 20, ofGetHeight()-20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        generatePolyline();
    }
    if(key == 'f'){
        pMerge.setNbPoints(pMerge.getNbPoints()+1);
    }
    else if (key == 'd'){
        if(pMerge.getNbPoints()>3){
            pMerge.setNbPoints(pMerge.getNbPoints()-1);
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
