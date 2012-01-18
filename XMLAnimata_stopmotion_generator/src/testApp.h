#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "wuSkin.h"
#include "wuXMLvectorManager.h"
#include "wuKinectSkel.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	// OpenCV
	int						vw, vh;
	bool	bRecord;

	ofxCvColorImage			color;

	wuXMLvectorManager XML;
	vector<pieceInfo> frame;

	wuKinectSkel kinSkel;
	Skeleton skel;
	int countdown;
};

#endif
