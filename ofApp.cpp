#include "ofApp.h"

//--------------------------------------------------------------
Walker::Walker(glm::vec2 location) {

	this->location = location;
	this->direction = glm::normalize(glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1))) * 3;

	this->rotate_location = glm::vec2();
	this->rotate_radius = 0;
	this->rotate_deg = 0;
}

//--------------------------------------------------------------
void Walker::update() {

	if (this->location.x > -230 && this->location.x < 230 && this->location.y > -230 && this->location.y < 230) {

		if (this->log.size() > 0 && ofRandom(1000) < 5) {

			auto prev_location = this->log.back();
			auto rad = std::atan2(this->location.y - prev_location.y, this->location.x - prev_location.x);
			this->rotate_radius = 40;

			if (ofRandom(100) < 50) {

				this->rotate_location = this->location + glm::vec2(this->rotate_radius * cos(rad + PI * 0.5), this->rotate_radius * sin(rad + PI * 0.5));
				this->rotate_deg = 270;
			}
			else {

				this->rotate_location = this->location + glm::vec2(this->rotate_radius * cos(rad - PI * 0.5), this->rotate_radius * sin(rad - PI * 0.5));
				this->rotate_deg = 90;
			}
		}
	}

	if (this->rotate_radius < 10) {

		this->location += this->direction;

		if (this->location.x < -300 || this->location.x > 300) {

			this->direction *= -1;
			this->location += this->direction;
		}

		if (this->location.y < -300 || this->location.y > 300) {

			this->direction *= -1;
			this->location += this->direction;
		}
	}
	else {

		this->location = this->rotate_location + glm::vec2(this->rotate_radius * cos(this->rotate_deg * DEG_TO_RAD), this->rotate_radius * sin(this->rotate_deg * DEG_TO_RAD));
		this->rotate_deg += 15;
		this->rotate_radius = this->rotate_radius <= 0 ? 0 : this->rotate_radius - 0.5;

		this->direction = glm::normalize(this->location - this->log.back()) * 3;

		if (ofRandom(100) < 1) {

			this->rotate_radius = 0;
		}
	}

	this->log.push_back(this->location);

	while (this->log.size() > 35){
		
		this->log.erase(this->log.begin());
	}
}

//--------------------------------------------------------------
void Walker::draw() {

	
	for (int i = 0; i < this->log.size() - 1; i++) {

		ofSetColor(ofColor(ofMap(i, 0, this->log.size(), 239, 39)));
		ofDrawLine(this->log[i], this->log[i + 1]);
	}

	ofFill();
	ofDrawCircle(this->log.back(), 4);
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);

	for (int i = 0; i < 55; i++) {

		this->walker_list.push_back(Walker(glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300))));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& walker : this->walker_list) {

		walker.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (auto& walker : this->walker_list) {

		walker.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}