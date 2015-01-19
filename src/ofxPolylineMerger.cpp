//
//  ofxPolylineMerger.cpp
//  ofxPolylineMerger
//
//  Created by pach on 19/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "ofxPolylineMerger.h"

ofxPolylineMerger::ofxPolylineMerger(){
    
}

ofxPolylineMerger::~ofxPolylineMerger(){
    
}


void ofxPolylineMerger::setup() {
    nbPoints = 100;
}

void ofxPolylineMerger::update() {
    
}

void ofxPolylineMerger::draw() {
    polyOut.draw();
}

void ofxPolylineMerger::setNbPoints(int nbP){
    nbPoints = nbP;
}

void ofxPolylineMerger::setPoly1(ofPolyline &p1){
    poly1 = p1.getResampledByCount(nbPoints);
    while (poly1.size()<nbPoints) {
        poly1.addVertex(poly1[poly1.size()-1]);
    }
}

void ofxPolylineMerger::setPoly2(ofPolyline &p2){
    poly2 = p2.getResampledByCount(nbPoints);
    while (poly2.size()<nbPoints) {
        poly2.addVertex(poly2[poly2.size()-1]);
    }
}

void ofxPolylineMerger::mergePolyline(float interpolationCoeff){
    polyOut.clear();
    
    ofPoint pt1;
    ofPoint pt2;
    ofPoint ptOut;
    
    for (int i=0; i<nbPoints; i++) {
        pt1 = poly1[i];
        pt2 = poly2[i];
        
        ptOut.x = ofLerp(pt1.x, pt2.x, interpolationCoeff);
        ptOut.y = ofLerp(pt1.y, pt2.y, interpolationCoeff);
        
        polyOut.addVertex(ptOut);
    }
    
    polyOut.simplify();

}

void ofxPolylineMerger::mergePolyline(ofPolyline &p1, ofPolyline &p2, float interpolationCoeff){
    
    setPoly1(p1);
    setPoly2(p2);
    
    mergePolyline(interpolationCoeff);
}