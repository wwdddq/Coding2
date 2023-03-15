#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //myClock.setTempo(200);
    //myClock.setTicksPerBeat(2);
    
    
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    /////////////// waveform
    ofTranslate(0, ofGetHeight()/2);
    ofSetColor(255, 255, 255);
    ofBackground(0, 0, 0); // Set the background colour
    ofFill();
    ofEnableAntiAliasing(); // Enable anti-aliasing
    ofSetLineWidth(2); // Set the line width to 2 pixels


    ofDrawLine(0, 0, 1, waveform[1] * ofGetHeight()/2.); //first line
    for(int i = 1; i < (ofGetWidth() - 1); ++i) {
        ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        
        //myClock.ticker();
        
        //if (myClock.tick) {
            
        //    myFreq+=30;
            
        //}
        
        //output[i * outChannels] = myOsc1.sinewave(3 + (myOsc2.sinewave(90)*50)) * myOsc3.sinewave(5 + (myOsc4.sinewave(60)*0.5));
        
        // The above is the first week's work in mimic. I wanted to make my sound vibrato and periodic, so I added a new sine wave oscillator, myOsc5, setting its frequency modFreq to a lower value and its amplitude modDepth to a higher value, producing a waveform that can be used as a modulation signal. I multiplied its output value by modDepth and added it to the frequency of the original high-frequency oscillator to achieve the effect of dither and periodic variation.
        
        float modFreq = 0.2; // Frequency of low frequency oscillators
        float modDepth = 5.0; // Amplitude of frequency modulation
        float mod = myOsc5.sinewave(modFreq) * modDepth;

        
        output[i * outChannels] = myOsc1.sinewave(myFreq + mod) * myOsc3.sinewave(5 + (myOsc4.sinewave(60)*0.5));
        
        output[i * outChannels + 1] = output[i * outChannels];
        
        //Hold the values so the draw method can draw them
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
