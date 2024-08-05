#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetLineWidth(2);

	vector<glm::vec2> vertices_1;
	vector<glm::vec2> vertices_2;

	auto noise_seed = ofRandom(1000);
	for (int deg = 0; deg < 360; deg += 60) {

		auto noise_deg = ofMap(ofNoise(noise_seed, ofGetFrameNum() * 0.01), 0, 1, -360, 360);

		auto location_1 = glm::vec2(300 * cos(deg * DEG_TO_RAD), 300 * sin(deg * DEG_TO_RAD));
		auto location_2 = glm::vec2(200 * cos((deg + noise_deg) * DEG_TO_RAD), 200 * sin((deg + noise_deg) * DEG_TO_RAD));

		this->draw_arrow(location_1, location_2, 30, ofColor(39));

		vertices_1.push_back(location_1);
		vertices_2.push_back(location_2);
	}

	ofNoFill();
	ofSetLineWidth(0.5);
	ofSetColor(139);

	ofBeginShape();
	ofVertices(vertices_1);
	ofEndShape(true);

	ofBeginShape();
	ofVertices(vertices_2);
	ofEndShape(true);

	/*
	int start = 75;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto translate_location = target - glm::vec2(size * cos(angle), size * sin(angle));
	auto distance = glm::distance(translate_location, location);

	ofPushMatrix();
	ofTranslate(translate_location);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);

	ofEndShape();

	ofPopMatrix();

	ofDrawCircle(location, 5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}