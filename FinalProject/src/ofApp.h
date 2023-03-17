#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
    
        float r = 80.0f;
    
        //Define an array of floating point numbers called KeyFP which contains 8 elements. Each element represents a keyframe point that is used to switch between states in the animation.
        float KeyFP[8] = { r/5, 30, 42, 58, 90, 106, 134, 164};
    
        //music playing
        float t = 0;
        static constexpr size_t bandsToGet = 512; // Obtain 512 bands, i.e. bans maximum
        std::array<float, bandsToGet> fft{ {0} }; //fft stores sound buffer.
        ofSoundPlayer myMusic;

        ofMesh mesh, draw_mesh, line_mesh;
    
        float len2;
        vector<glm::vec2> base_location_list;
        vector<ofColor> color_list;
        vector<vector<glm::vec2>> log_list;

    

};
