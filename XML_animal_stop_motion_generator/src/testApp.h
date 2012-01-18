#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "wuSkinManager.h"
#include "wuXMLvectorManager.h"
#include "wuBlobInspector.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void touch(int _x, int _y);
		void updateFrame(vector<pieceInfo> * _newframe);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	// OpenCV
	int						vw, vh;
    int		threshold;
	bool	bLearnBakground;
	bool	bTakeB2DShot, bCaptured, bPlay;

	// CV images
    ofVideoGrabber			vidGrabber;

	ofImage			color;
	ofImage			bgImgColor;

	wuXMLvectorManager XML;
	vector<pieceInfo> frame;
	vector <bool> bDraggable;

	wuSkinManager images;
	wuBlobInspector blobInspector;

	int whoisdragged, offX, offY, lastX, lastY;

	// QT movie
	ofVideoPlayer 		movie;
	bool bMovie, bDrawLines;
	ofPoint movPos;
};

#endif
