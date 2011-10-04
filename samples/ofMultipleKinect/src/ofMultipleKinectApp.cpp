#include "ofMultipleKinectApp.h"


using namespace _2Real;

ofMultipleKinectApp::~ofMultipleKinectApp()
{
	m_2RealKinect->shutdown();
}

//--------------------------------------------------------------
void ofMultipleKinectApp::setup(){

	ofSetWindowTitle("CADET| http://www.cadet.at | MultipleKinectSample");	

	m_iKinectWidth = 640;
	m_iKinectHeight = 480;
	m_iScreenWidth = 1024;
	m_iScreenHeight = 768;
	m_bIsMirroring = true;	// generators are mirrored by default

	try
	{	
		m_2RealKinect = _2RealKinect::getInstance();
		std::cout << "_2RealKinectWrapper Version: " << m_2RealKinect->getVersion() << std::endl;
		bool bResult = m_2RealKinect->start( COLORIMAGE | USERIMAGE | DEPTHIMAGE );
		if( bResult )
			std::cout << "\n\n_2Real started successfully!...";
		m_iNumberOfDevices = m_2RealKinect->getNumberOfDevices();
		resizeImages();
	}
	catch ( std::exception& e )
	{
		std::cout << "\n\n_2Real: Exception occurred when trying to start:\n" << e.what() << std::endl;
		m_2RealKinect->shutdown();
		int pause = 0;
		std::cin >> pause;
	}
}

//--------------------------------------------------------------
void ofMultipleKinectApp::update(){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::draw(){
	try
	{
		ofClear( 1.0f, 1.0f, 1.0f, 1.0f);		
		drawKinectImages();				//oututs all connected kinect devices generators (depth, rgb, user imgage, skeletons)			
	}
	catch( std::exception& e )
	{
		std::cout << "\nException in draw: " << e.what() << std::endl;
	}
}

void ofMultipleKinectApp::drawKinectImages()
{
	for( int i = 0; i < m_iNumberOfDevices; ++i)
	{
		//rgb image
		uint8_t* imgRef = (uint8_t*)m_2RealKinect->getImageData( i, COLORIMAGE );
		int numberChannels = m_2RealKinect->getBytesPerPixel( COLORIMAGE );
		int m_iKinectWidth = m_2RealKinect->getImageWidth( i, COLORIMAGE );		
		int m_iKinectHeight = m_2RealKinect->getImageHeight( i, COLORIMAGE );
		ofImage colorImage;
		colorImage.setFromPixels(imgRef, m_iKinectWidth, m_iKinectHeight, OF_IMAGE_COLOR, true);
		colorImage.draw(i * m_ImageSize.x, 0, m_ImageSize.x*(i+1) , m_ImageSize.y);

		//depth image
		numberChannels = m_2RealKinect->getBytesPerPixel( DEPTHIMAGE );
		m_iKinectWidth = m_2RealKinect->getImageWidth( i, DEPTHIMAGE );		
		m_iKinectHeight = m_2RealKinect->getImageHeight( i, DEPTHIMAGE );
		ofImage depthImage;
		depthImage.setFromPixels(m_2RealKinect->getImageData( i, DEPTHIMAGE), m_iKinectWidth, m_iKinectHeight, OF_IMAGE_GRAYSCALE, true);
		depthImage.draw(i * m_ImageSize.x, m_ImageSize.y, m_ImageSize.x*(i+1), m_ImageSize.y);

		//user image
#ifdef	TARGET_MSKINECTSDK
		if( i == 0 )						
#endif
		{
			m_iKinectWidth = m_2RealKinect->getImageWidth( i, USERIMAGE_COLORED );		
			m_iKinectHeight = m_2RealKinect->getImageHeight( i, USERIMAGE_COLORED );
			uint8_t* imgRef = (uint8_t*)m_2RealKinect->getImageData( i, USERIMAGE_COLORED, false, 0 );
			ofImage colorImage;
			colorImage.setFromPixels(imgRef, m_iKinectWidth, m_iKinectHeight, OF_IMAGE_COLOR, true);
			colorImage.draw(i * m_ImageSize.x,  m_ImageSize.y*2, m_ImageSize.x*(i+1) , m_ImageSize.y);
						
		}

		m_iKinectWidth = m_2RealKinect->getImageWidth( i, COLORIMAGE );		
		m_iKinectHeight = m_2RealKinect->getImageHeight( i, COLORIMAGE );
		//skeleton		
		//drawSkeletons(i, ofRect( i * m_ImageSize.x, m_ImageSize.y *3 , m_ImageSize.x, m_ImageSize.y);

		//drawing debug strings for devices
	}
}

void ofMultipleKinectApp::resizeImages()
{
	//calculate imagesize
	int iImageHeight = (int)(m_iScreenHeight / 4.0);		// divide window height according to the number of generator outputs (rgb, depth, user, skeleton)
	int iImageWidth = (int)(iImageHeight * 4.0 / 3.0);		// keep images aspect ratio 4:3
	if(iImageWidth * m_iNumberOfDevices > m_iScreenWidth)	// aspect ratio 	
	{
		iImageWidth = m_iScreenWidth / m_iNumberOfDevices;
		iImageHeight = iImageWidth * 3 / 4;
	}
	//size of plane to draw textures on
	m_ImageSize = ofPoint( iImageWidth, iImageHeight );
}

void ofMultipleKinectApp::mirrorImages()
{
	m_bIsMirroring = !m_bIsMirroring;	// toggleMirroring
	for( int i = 0; i < m_iNumberOfDevices; ++i)
	{
		m_2RealKinect->setMirrored( i, COLORIMAGE, m_bIsMirroring );
		m_2RealKinect->setMirrored( i, DEPTHIMAGE, m_bIsMirroring );
		m_2RealKinect->setMirrored( i, USERIMAGE, m_bIsMirroring );		// OpenNI has no capability yet to mirror the user image
	}
}

//--------------------------------------------------------------
void ofMultipleKinectApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::windowResized(int w, int h){
	m_iScreenWidth = ofGetWindowWidth();
	m_iScreenHeight = ofGetWindowHeight();
	resizeImages();
}

//--------------------------------------------------------------
void ofMultipleKinectApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofMultipleKinectApp::dragEvent(ofDragInfo dragInfo){ 

}