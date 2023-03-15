#include "testApp.h"

testApp::~testApp()
{
	for (int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
}

//--------------------------------------------------------------
void testApp::setup(){
	
	
	int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();
    // ofBackground(0,50,50); change it to draw
	
	// set up the cookies!
	for (int i = 0; i < 50; i++)
    {
        boids.push_back(new newboid());
        boids.push_back(new Boid());
    }

}


//--------------------------------------------------------------
void testApp::update(){
	
    ofVec3f min(0, 0);
	ofVec3f max(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->update(boids, min, max);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //ofColor colorOne(25, 25, 112);
    //ofColor colorTwo(135, 206, 235);

    //ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
    // Sets the background to a linear gradient
    
    ofColor colorOne(135, 206, 235);
    ofColor colorTwo(25, 25, 112);

    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
    // Sets the background to a circular gradient

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->draw();
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
 
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
