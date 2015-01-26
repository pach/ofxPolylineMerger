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
    nbPoints = 200;
}

void ofxPolylineMerger::update() {
    
}

void ofxPolylineMerger::draw() {
    poly1.draw();
    poly2.draw();
    polyOut.draw();
}

void ofxPolylineMerger::setNbPoints(int nbP){
    nbPoints = nbP;
}

void ofxPolylineMerger::setPoly1(ofPolyline &p1){
    if (&p1!=NULL && p1.size()>0) {
        poly1 = p1.getResampledByCount(nbPoints);
        while (poly1.size()<nbPoints) {
            poly1.addVertex(poly1[poly1.size()-1]);
        }
    }else{
        poly1.addVertex(ofVec2f(0.5, 0.5));
    }
//    cout<<"setting poly 1 of size "<<p1.size()<<endl;
}

void ofxPolylineMerger::setPoly2(ofPolyline &p2){
    if (&p2!=NULL && p2.size()>0) {
        poly2 = p2.getResampledByCount(nbPoints);
        while (poly2.size()<nbPoints) {
            poly2.addVertex(poly2[poly2.size()-1]);
        }
    }else{
        poly2.addVertex(ofVec2f(0.5, 0.5));
    }
//    cout<<"setting poly 2 of size "<<p2.size()<<endl;
}

void ofxPolylineMerger::mergePolyline(float interpolationCoeff){
    polyOut.clear();
    
    ofPoint ptOut;
    
//    cout<<"start lerp ";
    for (int i=0; i<nbPoints; i++) {
        ptOut.x = ofLerp(poly1[i].x, poly2[i].x, interpolationCoeff);
        ptOut.y = ofLerp(poly1[i].y, poly2[i].y, interpolationCoeff);
        
        polyOut.addVertex(ptOut);
//        cout<<" -- in1 "<<poly1[i]<<" . in2 "<<poly2[i]<<" . out "<<ptOut<<endl;
    }
//    cout<<endl;
    
//    cout<<"merging poly p1 "<<poly1.size()<<" and p2 "<<poly2.size()<<" to make "<<polyOut.size()<<" at coeff "<<interpolationCoeff<<endl;
    
//    polyOut.simplify();

}

void ofxPolylineMerger::mergePolyline(ofPolyline &p1, ofPolyline &p2, float interpolationCoeff){
    
    setPoly1(p1);
    setPoly2(p2);
    
    mergePolyline(interpolationCoeff);
}