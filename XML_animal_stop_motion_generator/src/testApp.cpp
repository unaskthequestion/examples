#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofSetLogLevel(OF_LOG_NOTICE);

	threshold		 = 30;
	bLearnBakground = true;

	bTakeB2DShot = false;
	bCaptured = false;
	bPlay = false;
	bMovie = false;
	bDrawLines = false;

	vw = 640;
	vh = 480;
	vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(vw, vh);

	movie.loadMovie("elephant.gif");
	movPos.x=10;
	movPos.y=250;

	color.allocate(vw, vh, OF_IMAGE_COLOR);
	bgImgColor.allocate(vw, vh, OF_IMAGE_COLOR);

	// nobody dragged
	whoisdragged=-1;

	images.setup(vw, vh);
	// max num blobs
	images.setMaxBlobs(10);
	images.setThreshold(threshold);
 
}

//--------------------------------------------------------------
void testApp::update(){
	bool bNewFrame = false;
	vidGrabber.grabFrame();
    bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame) {
        color.setFromPixels(vidGrabber.getPixels(), vw,vh, OF_IMAGE_COLOR);

		if (bLearnBakground == true) {
			bgImgColor = color;
			bLearnBakground = false;
		}


		if(bDrawLines)
			blobInspector.capture(&color,&bgImgColor);

        // Captura de l' objecte 2D
        if(bTakeB2DShot && !bCaptured)
		{
			bCaptured = true;
			bTakeB2DShot = false;
			
			images.capture(&color,&bgImgColor);
			images.OrderSkins();
			for(int i=0; i < images.skins.size(); i++)
			{
				pieceInfo piece;

				piece.pos = images.skins[i].posSkin;
				piece.ang = 0.0;
				// add piece position to frame
				frame.push_back(piece);

				bDraggable.push_back(true);
			}
		}
	}

	if(bCaptured)
	{
		for (int i = 0; i < images.getNumberSkins(); i++)
		{
			images.setPosition(i, frame[i].pos);
			images.setRotation(i, frame[i].ang);
		}
	}

	if(bPlay)
	{
		updateFrame(XML.getNextFrame());

		if (XML.getCurrentFrame()==XML.getNumFrames()-1)
			bPlay=false;

	}



}

//--------------------------------------------------------------
void testApp::draw(){
		ofSetColor(255,255,255);
		ofPoint pos;
		float ang;

		if(bMovie)
			movie.draw(movPos.x, movPos.y);

		if(!bCaptured)
		{
		    ofPushMatrix();
				ofEnableAlphaBlending();
				ofSetColor(255, 255, 255, 180);
				color.draw(0,0);
				ofDisableAlphaBlending();
			ofPopMatrix();
			blobInspector.draw(bDrawLines);
		}

		// draw skins
		images.draw();

		for (int i = 0; i < images.getNumberSkins(); i++)
		{
			ang = frame[i].ang;
			pos = frame[i].pos;

			ofPushMatrix();
				ofEnableAlphaBlending();
				ofNoFill();
				ofSetColor(255, 255, 255,60);
				ofCircle(pos.x,pos.y,3);
				string info = ofToString(i);
				ofSetColor(255, 0, 0,255);
				ofDrawBitmapString(info, pos.x-5, pos.y-5);
				ofDisableAlphaBlending();
			ofPopMatrix();
		}

		for(int i=frame.size()-1; i > -1; i--)
		{
			int gruix;
			if (images.skins[i].getWidth()> images.skins[i].getHeight())
				gruix = images.skins[i].getWidth();
			else
				gruix = images.skins[i].getHeight();

		    ofPushMatrix();
				ofEnableAlphaBlending();
				ofNoFill();
				if(bDraggable[i])
					ofSetColor(255, 255, 255,40);
				else
					ofSetColor(255, 255, 255,40);

				ofRect(frame[i].pos.x-gruix/2, frame[i].pos.y-gruix/2, gruix, gruix);
				ofDisableAlphaBlending();
			ofPopMatrix();
		}

		ofSetColor(255, 255, 0);
		string info = "frame: "+ofToString(XML.getCurrentFrame()+1)+"/"+ofToString(XML.getNumFrames());
		ofDrawBitmapString(info, 20, 20);

		ofSetColor(255, 0, 0);
		info = "pieces: "+ofToString((int)images.skins.size());
		ofDrawBitmapString(info, 20, 40);

		ofSetColor(255, 255, 0);
		info = "threshold: "+ofToString(threshold);
		ofDrawBitmapString(info, 400, 20);

		info = "a: add frame";
		ofDrawBitmapString(info, 690, 20);
		info = "d: delete frame ??";
		ofDrawBitmapString(info, 690, 40);
		info = "s: save movie";
		ofDrawBitmapString(info, 690, 60);
		info = "l: load movie";
		ofDrawBitmapString(info, 690, 80);
		info = "p: play movie";
		ofDrawBitmapString(info, 690, 100);
		info = "m: show bg movie";
		ofDrawBitmapString(info, 690, 120);
		info = "v: show blobInspector";
		ofDrawBitmapString(info, 690, 140);
		info = "e: set piece editable/draggable ??";
		ofDrawBitmapString(info, 690, 160);
		info = "UP,DOWN: change threshold";
		ofDrawBitmapString(info, 690, 180);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '1':
               bTakeB2DShot = true;
			break;
		case 'a':
			XML.addFrame(&frame);
			break;
		case 'e':
			touch(mouseX,mouseY);
			bDraggable[whoisdragged] = !bDraggable[whoisdragged];
			break;
		case 'd':
//			XML.deleteFrame(currentFrame);
//			if (i < bDraggable.size())
		break;
		case 's':
			XML.saveXML("filmOUT.xml");
			break;
		case 'l':
			XML.loadXML("filmIN.xml");
			break;
		case 'p':
			bPlay=true;
			XML.goto0();
			break;
		case 'm':
			bMovie=!bMovie;
			break;
		case '.':
			bMovie=!bMovie;
	        movie.previousFrame();
			break;
		case '-':
			bMovie=!bMovie;
	        movie.nextFrame();
			break;
		case 'v':
			bDrawLines=!bDrawLines;
			break;

	}
		// gray threshold
	if(key == OF_KEY_UP) {
		threshold ++;
		if(threshold > 255) threshold = 255;
		images.setThreshold(threshold);
	}
	if(key == OF_KEY_DOWN) {
		threshold --;
		if(threshold < 0) threshold = 0;
		images.setThreshold(threshold);
	}

	if(key == OF_KEY_LEFT) {
		updateFrame(XML.getPrevFrame());
	}
	if(key == OF_KEY_RIGHT) {
		updateFrame(XML.getNextFrame());
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

	if(whoisdragged>-1)
	{
		if(whoisdragged == 99)
		{
			movPos.x = x -offX;
			movPos.y = y -offY;
		}
		else
		{
			if (button==2) {
				if(x > frame[whoisdragged].pos.x)
					frame[whoisdragged].ang = frame[whoisdragged].ang + 0.007*(y-lastY);
				else
					frame[whoisdragged].ang = frame[whoisdragged].ang - 0.007*(y-lastY);
			}else
			{
				frame[whoisdragged].pos.x = x -offX;
				frame[whoisdragged].pos.y = y -offY;
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	touch(x,y);
	lastY = y;
//	cout << " " << whoisdragged;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
// returns piece number
void testApp::touch(int x, int y){
	whoisdragged = -1;

	// pilla el movie
	bool xcond = ( x > movPos.x && x <  movPos.x + movie.getWidth() ); 
	bool ycond = ( y > movPos.y && y <  movPos.y + movie.getHeight() ); 

	whoisdragged = 99;
	offX = x - movPos.x;
	offY = y - movPos.y;

	for(int i=frame.size()-1; i > -1; i--)
	{
		int gruix;
		if (images.skins[i].getWidth()> images.skins[i].getHeight())
			gruix = images.skins[i].getWidth();
		else
			gruix = images.skins[i].getHeight();

		bool xcond = ( x > (frame[i].pos.x - gruix/2) && x <  (frame[i].pos.x + gruix/2) ); 
		bool ycond = ( y > (frame[i].pos.y - gruix/2) && y <  (frame[i].pos.y + gruix/2) ); 

		if(xcond && ycond && bDraggable[i])
		{
			whoisdragged = i;
			offX = x - frame[i].pos.x;
			offY = y - frame[i].pos.y;
		}
	}


}

void testApp::updateFrame(vector<pieceInfo> * _newframe)
{
		frame.clear();

		for(int i=0; i < images.skins.size(); i++)
		{
			pieceInfo piece;

			piece.pos = (*_newframe)[i].pos;
			piece.ang = (*_newframe)[i].ang;
			// add piece position to frame
			frame.push_back(piece);
		}
}

