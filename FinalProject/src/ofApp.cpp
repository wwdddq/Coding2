#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(1); // Set automatic full screen
    ofBackground(0, 0, 0); // Set the background colour
    
    myMusic.load("Energetic-dreamy-electronic-music.mp3"); // Loading music
    myMusic.setVolume(0.7f); // Setting the volume
    myMusic.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    //Get a sample of the audio spectrum
    t += 0.06;
    float* buf = ofSoundGetSpectrum(bandsToGet); //Capture the audio spectrum and put it into the buf array
    
    // Each band is traversed using a for loop and its value is multiplied by 0.8 for smoothing. Then, if the current band value fft[i] is smaller than the obtained band value buf[i], it is updated to buf[i]. In this way, we can continuously update the audio spectrum and store the maximum frequency amplitude value in the fft array each time.
    for (int i = 0; i < bandsToGet; i++) {
        fft[i] *= 0.8f;
        if (fft[i] < buf[i]) fft[i] = buf[i];
    }
    
    // Check if music is playing
    if (!myMusic.isPlaying()) {
        // Close the app when the music is over
        ofExit();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Audio spectrum bar
    float width = (float)(5*128) / bandsToGet;
    for (int i = 0; i < bandsToGet; i++) {
        ofDrawRectangle(50 + i * width, ofGetHeight() - 5, width+10, -(fft[i] * 350));
    }
    
    //Gradient transition colour settings
    int time = ofGetSystemTimeMillis() / 10;
    float w = time / 500.0;
    float colorValue = ofMap(sin(w), -1, 1, 0, 255);
    ofColor color = ofColor::fromHsb(colorValue, 255, 255);
    ofSetColor(color);

    // Switching animation states according to keyframe points
    if (t < KeyFP[0]) {
        // Status1
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2 + fft[0] / 1000, ofGetHeight()/2 + fft[4] * 1000); // Move the animation centre point in the middle of the screen and move it with the fft array
        ofRotateDeg(45); //Set the rotation angle
        
        // draw status1
        for(int i=0; i <400; i+=25){
            //ofDrawCone(i, 0, 0, 20, 10);
            ofRotateDeg(time % 360);
            ofDrawBox(i, i, i, 10, 10, 10);
            ofDrawCircle(i, i, i/4);
            
        }
        ofPopMatrix();
        
    }
    
        // If the current time t is before the 1st keyframe KeyFP[2], the following block of code is executed to switch to state 2
    else if(t < KeyFP[2])
    {
        // Status2
        ofSetFrameRate(60); // Set the frame rate
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2 + fft[0] / 1000, ofGetHeight()/2 + fft[4] * 1000);
     
        int radius = 350 + fft[0]*2000; // Calculate the radius of the circle so that it varies with the audio.
        int deg_span = 10 + fft[8]*500; // Calculate the angle of division of the circle so that it also varies with the audio.
     
        int target_deg = ofGetFrameNum() % 360; // The target angle is calculated and updated every frame.
        
        // Use the loop to draw each line segment of the circle.
        for (int deg = 0; deg < 360; deg += deg_span) {
     
            auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);  // Calculates the position of the current point.
            auto target_location = glm::vec3(radius * cos(target_deg * DEG_TO_RAD), radius * sin(target_deg * DEG_TO_RAD), 0); // Calculate the position of the target point.
            auto distance = glm::distance(location, target_location); // Calculate the distance between the current point and the target point.
            
            ofSetLineWidth(3); // Set line thickness
            
            //Calculate the length of the line segment. If the distance between the current point and the target point is less than 60, the length of the line segment varies according to the distance, otherwise the length is fixed at fft[4]*300 + 80.
            int len = fft[4]*300 + 150;
            if (distance < 60) {
                
                len = ofMap(distance, 0, 60, 60, 20);
            }
     
            // Calculate the position of the start and end points of a line segment.
            auto location_1 = glm::vec3((radius + len * 2) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD), 0);
            auto location_2 = glm::vec3((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD), 0);
     
            ofDrawLine(location_1, location_2); //Draw the line between location_1 and location_2
            ofDrawSphere(location_1, 8); //Draws a small sphere location_1 with a radius of 2.
            ofDrawSphere(location_2, 5); // Draws a small sphere location_2 with a radius of 2.
     
            ofDrawSphere(target_location, 20); // Draws a larger sphere with a target_location radius of 8.
        }
     
        ofPopMatrix();
    }
    
    else if(t < KeyFP[3])
    {
        //Status3 - Zach Lieberman‘s sine wave with FFT
        ofNoFill();
        ofSetCircleResolution(1000);
        ofSetDepthTest(true);

        float time2 = ofGetElapsedTimef(); // Create a variable called time to get the elapsed time from the system. Use the time as an incremental counter
        for (int x = 1; x < 20; x ++){
            for (int i=0; i < 500; i+=9){
                //                ofSetColor(127 + 127 * sin(i * 0.01 + time + x) +  + fft[8] * 1000, 127 + 127 *sin(i * 0.011 +time) +  + fft[4] * 500, 127 + 127 * sin(i * 0.012 +time) +  + fft[12] * 2000);
                
                ofDrawCircle(105 * x + 100 * sin(i * 20 +time2 + x) + fft[4] * 1000, 100 + i + fft[8] * 500, 40 * sin(i * 20 +time2 +x) * 2 + fft[0] * 1000);
                
                //绘制粒子周围的光晕效果
                //ofSetColor(0, 0, 0, 20 + fft[8] * 50); // 将fft的值映射到透明度上
                //ofDrawCircle(50 * x + 100 * sin(i * 0.01 +time + x), 50 + i, 40 * sin(i * 0.05 +time +x) * 2); // 绘制光晕
            }
        }
     }
        
     else if (t < KeyFP[4])
     {
         //Status4
         ofSetFrameRate(30);
         
         ofPushMatrix();
         ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
         
         //Large circle
         ofSeedRandom(39); //Set random seeds
         for(int i = 0; i < 200; i++) {
             auto deg = ofRandom(360); // Generate a random number between 0 and 360 degrees.
             
             auto radius = int(ofRandom(720) + ofGetFrameNum() * ofRandom(5, 10)) % 500 + fft[0] * 1000; //Generates a random radius that varies with time and FFT. The %500 limits the radius to the window.
             
             //auto radius = int(ofRandom(720) + fft[3] * 100 * ofRandom(5, 10)) % 720;
             auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD)+ fft[8] * 500, radius * sin(deg * DEG_TO_RAD)+ fft[10] * 500); // Calculate the position of the circle from the radius and angle.
             auto size = ofRandom(fft[4] * 1000, 60);
             size += 4; // Set the size of the circle and add 4 pixels.
             ofDrawCircle(location, size);
         }
         
         //Small circle
         ofSeedRandom(39);
         for (int i = 0; i < 200; i++) {
      
             auto deg = ofRandom(360);
             auto radius = int(ofRandom(720) + fft[3] * 100 * ofRandom(5, 10)) % 500;
             auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
             auto size = ofRandom(fft[4] * 1000, 30);
             ofDrawCircle(location, size);
         }
         ofPopMatrix();
         
    }
    
     else if(t < KeyFP[5])
     {
         //Status5
         auto ico_sphere = ofIcoSpherePrimitive(300, 4); // Create a 4 level Icosphere with a radius of 300
         
         this->mesh = ico_sphere.getMesh(); // Get Icosphere's Mesh
         
         // Assign the mesh to this->draw_mesh and this->line_mesh respectively
         this->draw_mesh = this->mesh;
         this->line_mesh = this->mesh;
         
         // Loop through each vertex
         for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {
             // Get the coordinates of the current vertex
             glm::vec3 vertex = this->draw_mesh.getVertex(i);
             
             // Calculate the noise value
             auto noise_value = ofNoise(glm::vec4(vertex * 0.005, ofGetFrameNum() * 0.0005 * fft[10] * 1000));
             
             if (noise_value > 0.46 && noise_value < 0.5) {
                 vertex = glm::normalize(vertex) * ofMap(noise_value, 0.46, 0.5, 300, 350) * fft[4] * 1000;
             }
             
             else if (noise_value > 0.5 && noise_value < 0.54) {
                 vertex = glm::normalize(vertex) * ofMap(noise_value, 0.5, 0.54, 350, 300) * fft[8] * 1000;
             }
             
             // Set the vertex coordinates
             this->draw_mesh.setVertex(i, vertex);
             this->line_mesh.setVertex(i, vertex);
             
             // Add black to the vertices
             this->draw_mesh.addColor(ofColor(0));
         }
         

         ofPushMatrix();
         ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
         
         // Rotate around the X axis
         ofRotateX(ofGetFrameNum() * 0.37);
      
         // Drawing Mesh and Wireframe
         this->draw_mesh.draw();
         this->line_mesh.drawWireframe();
      
         ofPopMatrix();


      }
    
 /*
  This code implements the effect of scene six. First the length of the line is set to 500 and a list of colours is defined. Then a set of base coordinates is generated based on the length and these coordinates are stored in a vector. Next, lines of the corresponding colour are generated according to the position of the coordinates and the colours of these lines are also stored in a vector. A grid is then generated from the list of base coordinates and colours and set to OF_PRIMITIVE_LINE_STRIP mode.

  Next the coordinate record list log_list is cleared and each base coordinate is stored in log_list. The offset of each base coordinate is then calculated using the Perlin Noise algorithm and the new coordinate after the offset is added to the coordinate record list log corresponding to that base coordinate. If the new coordinate is out of the line's length range, the calculation of the offset for that base coordinate is stopped and the calculation of the offset for the next base coordinate is started. Finally, all the lines are drawn to the screen according to the coordinate log list.

  It is worth noting that the spectrum array fft is used here, where fft[2] represents the volume of the low frequency tones and fft[5] the volume of the high frequency tones. These spectral values are used to calculate the offset of the lines.

  Unfortunately, the code does not run very smoothly and I suspect that this may be due to colour resets or the use of too much repetitive code. But I don't have the ability to optimise it anymore, and I feel like my whole code is a mess.
  */
         
         else if (t < KeyFP[6])
         {
             // Status6

             ofNoFill();

             this->len2 = 500;
             ofColor color;

             int numVertices = 0;
             for (int y = -this->len2; y <= this->len2; y += 20) {
                 this->base_location_list.push_back(glm::vec2(this->len2, y));
                 color.setHsb(ofMap(y, -this->len2, this->len2, 0, 255), 255, 255);
                 this->color_list.push_back(color);

                 this->base_location_list.push_back(glm::vec2(-this->len2, y));
                 color.setHsb(ofMap(y, -this->len2, this->len2, 255, 0), 255, 255);
                 this->color_list.push_back(color);

                 this->base_location_list.push_back(glm::vec2(y, this->len2));
                 color.setHsb(ofMap(y, -this->len2, this->len2, 0, 255), 255, 255);
                 this->color_list.push_back(color);

                 this->base_location_list.push_back(glm::vec2(y, -this->len2));
                 color.setHsb(ofMap(y, -this->len2, this->len2, 255, 0), 255, 255);
                 this->color_list.push_back(color);

                 numVertices += 4;
             }

             this->mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
             this->mesh.getVertices().resize(numVertices);

             this->log_list.clear();
             for (int i = 0; i < this->base_location_list.size(); i++) {
                 vector<glm::vec2> log;
                 log.push_back(this->base_location_list[i]);
                 this->log_list.push_back(log);
             }

             int step = 1;
             for (int i = 0; i < this->log_list.size(); i++) {
                 int k = 0;
                 while (true) {
                     auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.0015, ofGetFrameNum() * 0.004 + k * 0.001)), 0, 1, -720, 720);
                     auto next = this->log_list[i].back() + glm::vec2(fft[2] * 500 * cos(deg * DEG_TO_RAD), fft[5] * 1000 * sin(deg * DEG_TO_RAD));

                     if (abs(next.x) < this->len2 && abs(next.y) < this->len2) {
                         this->log_list[i].push_back(next);
                     }
                     else {
                         break;
                     }
                     k++;
                 }
             }

             ofPushMatrix();
             ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

             for (int i = 0; i < this->log_list.size(); i++) {
                 ofBeginShape();
                 ofVertices(this->log_list[i]);
                 ofEndShape();
             }
             ofPopMatrix();
             
         }
    

         
    
        ofDrawBitmapString("Audio visualisation with a multitude of expressions", 30, 30, 10);
    
}

//--------------------------------------------------------------
void ofApp::exit(){

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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
