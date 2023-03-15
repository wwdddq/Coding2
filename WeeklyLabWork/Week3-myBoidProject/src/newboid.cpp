
//  newboid.cpp
//  Biscuits!

#include "newboid.hpp"

// constructor for the newboid class
newboid::newboid()
{
    // Set the weights for separation, cohesion and alignment
    separationWeight = 3.0f;
    cohesionWeight = 0.7f;
    alignmentWeight = 1.2f;
    
    // Set the threshold for separation and the neighbourhood size
    separationThreshold = 12;
    neighbourhoodSize = 20;
    
    //Set the initial position of the boid to a random point in the upper left part of the screen
    position = ofVec3f(ofRandom(0, 150), ofRandom(150, 0));
    // Set the initial velocity of the boid to a random vector
    velocity = ofVec3f(ofRandom(-50, 2), ofRandom(-2, 50));
}

// method to draw the boid
void newboid::draw(){
    // Render the boid to the screen
    
    // Set the color of the boid
    ofSetColor(235, 198, 124);
    // Draw a circle to represent the boid with the position as the center and a radius of 100
    ofCircle(position.x, position.y, 100);
    //ofDrawLine(10,10,100,100);
}
