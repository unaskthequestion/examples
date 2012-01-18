#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofSetLogLevel(OF_LOG_NOTICE);

	vw = 640;
	vh = 480;
	kinSkel.setup();

	color.allocate(vw,vh);
 
}

//--------------------------------------------------------------
void testApp::update(){
	kinSkel.update();

	skel = kinSkel.getSkeleton();

	color.setFromPixels( kinSkel.getPixelsImage(), vw, vh);

	if(countdown > 0)
		countdown--;
	else
		bRecord = true;

	if(bRecord)
	{
			pieceInfo piece;
			piece.ang = 0.0;

			frame.clear();

			piece.pos = skel.head;
			frame.push_back(piece);
			piece.pos = skel.neck;
			frame.push_back(piece);
			piece.pos = skel.Lshoulder;
			frame.push_back(piece);
			piece.pos = skel.Rshoulder;
			frame.push_back(piece);
			piece.pos = skel.Lelbow;
			frame.push_back(piece);
			piece.pos = skel.Relbow;
			frame.push_back(piece);
			piece.pos = skel.Lhand;
			frame.push_back(piece);
			piece.pos = skel.Rhand;
			frame.push_back(piece);
			piece.pos = skel.torso;
			frame.push_back(piece);
			piece.pos = skel.Lhip;
			frame.push_back(piece);
			piece.pos = skel.Rhip;
			frame.push_back(piece);
			piece.pos = skel.Lknee;
			frame.push_back(piece);
			piece.pos = skel.Rknee;
			frame.push_back(piece);
			piece.pos = skel.Lfoot;
			frame.push_back(piece);
			piece.pos = skel.Rfoot;
			frame.push_back(piece);

			XML.addFrame(&frame);
	}


}

//--------------------------------------------------------------
void testApp::draw(){
		ofSetColor(255,255,255);

		if(skel.bDetected)
			color.draw(0,0);

	ofSetColor(255, 255, 0);
	string info = "COUNTDOWN: "+ofToString(countdown);
	ofDrawBitmapString(info, 30, 20);

	info = "r: clear & record";
	ofDrawBitmapString(info, 30, 40);

	info = "'number': saves as 'number'.xml";
	ofDrawBitmapString(info, 30, 60);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	switch (key){
		case '1':
			XML.saveXML("1.xml");
			break;
		case '2':
			XML.saveXML("2.xml");
			break;
		case '3':
			XML.saveXML("3.xml");
			break;
		case '4':
			XML.saveXML("4.xml");
			break;
		case '5':
			XML.saveXML("5.xml");
			break;
		case '6':
			XML.saveXML("6.xml");
			break;
		case '7':
			XML.saveXML("7.xml");
			break;
		case '8':
			XML.saveXML("8.xml");
			break;
		case '9':
			XML.saveXML("9.xml");
			break;
		case '0':
			XML.saveXML("0.xml");
			break;
		case 'r':
			countdown = 200;
			XML.clear();
			break;
		case 's':
			bRecord = false;
			break;

	}

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

