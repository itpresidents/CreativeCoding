#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Pbo.h"

#include "cinder/Capture.h"
#include "cinder/Surface.h"

#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const int NUM_BUFFERS = 2;
static const int IMAGE_WIDTH = 640;
static const int IMAGE_HEIGHT = 480;
static const int IMAGE_CHANNELS = 3; // set to 3 to experiment with no alpha channel

enum class SortType {
	SLOW,
	FAST,
	PBO,
};

class PixelSortingApp : public AppNative {
  public:
	void setup() override;
	void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
	
	void slowSort( const Surface8u &sortableSurface );
	void fastSort( const Surface8u &sortableSurface );
	void pboSort( const Surface8u &sortableSurface );
	void sortWholeImage( const Surface8u &sortableSurface );
	
	CaptureRef			mCapture;
	gl::TextureRef		mTexture;
	std::list<Color8u>	mSortablePixels;
	std::array<Color8u, IMAGE_WIDTH*IMAGE_HEIGHT> mPixels;
	
	gl::TextureRef		mTexs[NUM_BUFFERS];
	gl::PboRef			mPbos[NUM_BUFFERS];
	uint32_t			mCurrentTex, mCurrentPbo;
	
	SortType			mSortType;
};

bool comparator ( const Color8u &first, const Color8u &second )
{
	return first.r < second.r;
}

void PixelSortingApp::setup()
{
	std::array<Color8u, IMAGE_WIDTH> mTest;
	for( auto & pixel : mTest ) {
		pixel = Color8u(rand() % 255, rand() % 255, rand() % 255);
	}
	std::sort( mTest.begin(), mTest.end(), ::comparator );
	
	try {
		mCapture = Capture::create(IMAGE_WIDTH,IMAGE_HEIGHT );
		auto devices = Capture::getDevices();
		mCapture->start();
	}
	catch( ci::Exception &exc ) {
		console() << "Failed to initialize capture, what: " << exc.what() << std::endl;
	}
	mSortablePixels.resize(640);
	mSortType = SortType::FAST;
	
	for( int b = 0; b < NUM_BUFFERS; ++b )
		mTexs[b] = gl::Texture::create( IMAGE_WIDTH, IMAGE_HEIGHT, gl::Texture::Format().internalFormat( (IMAGE_CHANNELS==4)?GL_RGBA:GL_RGB ) );
	mCurrentTex = 0;
	
	for( int b = 0; b < NUM_BUFFERS; ++b )
		mPbos[b] = gl::Pbo::create( GL_PIXEL_UNPACK_BUFFER, IMAGE_WIDTH * IMAGE_HEIGHT * IMAGE_CHANNELS, nullptr, GL_STREAM_DRAW );
	mCurrentPbo = 0;
	
}

void PixelSortingApp::keyDown( cinder::app::KeyEvent event )
{
	if( event.getChar() == 'f' )
		mSortType = SortType::FAST;
	else if( event.getChar() == 's' )
		mSortType = SortType::SLOW;
	else if( event.getChar() == 'p' )
		mSortType = SortType::PBO;
	else if( event.getChar() == ' ' )
		( mCapture && mCapture->isCapturing() ) ? mCapture->stop() : mCapture->start();
}

void PixelSortingApp::slowSort( const Surface8u &sortableSurface )
{
	auto iter = sortableSurface.getIter();
	int y = 0;
	while ( iter.line() ) {
		
		auto sortPixelIt = mSortablePixels.begin();
		while ( iter.pixel() ) {
			sortPixelIt->r = iter.r();
			sortPixelIt->g = iter.g();
			sortPixelIt->b = iter.b();
			++sortPixelIt;
		}
		auto iterator = mPixels.begin()+(y * sortableSurface.getWidth() );
		mSortablePixels.sort( ::comparator );
		std::move( mSortablePixels.begin(), mSortablePixels.end(), iterator );
		y++;
	}
	
	mTexture = gl::Texture::create( &mPixels.data()->r,
								   GL_RGB,
								  IMAGE_WIDTH,
								  IMAGE_HEIGHT,
								   gl::Texture2d::Format().loadTopDown() );
}

void PixelSortingApp::fastSort( const Surface8u &sortableSurface )
{
	auto surfaceData = (Color8u*)sortableSurface.getData();
	
	for( int y = 0; y <IMAGE_HEIGHT; y++ ) {
		auto rowOffset = y *IMAGE_WIDTH;
		std::copy( surfaceData, surfaceData +IMAGE_WIDTH, mSortablePixels.begin() );
		mSortablePixels.sort( ::comparator );
		auto iterator = mPixels.begin() + rowOffset;
		std::move( mSortablePixels.begin(), mSortablePixels.end(), iterator );
		surfaceData = surfaceData +IMAGE_WIDTH;
	}
	
	mTexture = gl::Texture::create( &mPixels.data()->r,
								   GL_RGB,
								  IMAGE_WIDTH,
								  IMAGE_HEIGHT,
								   gl::Texture2d::Format().loadTopDown() );
}

void PixelSortingApp::pboSort( const Surface8u &sortableSurface )
{
	gl::ScopedBuffer bscp( mPbos[mCurrentPbo] );
	
	auto surfaceData = (Color8u*)sortableSurface.getData();
	// why does this slow things down on the Mac?
	//	mPbos[mCurrentPbo]->bufferData( mPbos[mCurrentPbo]->getSize(), nullptr, GL_STREAM_DRAW );
	void *pboData = mPbos[mCurrentPbo]->map( GL_WRITE_ONLY );
	for( int y = 0; y <IMAGE_HEIGHT; y++ ) {
		auto rowOffset = y *IMAGE_WIDTH;
		std::copy( surfaceData, surfaceData +IMAGE_WIDTH, mSortablePixels.begin() );
		mSortablePixels.sort( ::comparator );
		std::array<Color8u,IMAGE_WIDTH> mMoveableRow;
		std::move( mSortablePixels.begin(), mSortablePixels.end(), mMoveableRow.begin() );
		memcpy( (Color8u*)pboData + rowOffset, mMoveableRow.data(),IMAGE_WIDTH * sizeof(Color8u) );
		surfaceData = surfaceData +IMAGE_WIDTH;
	}
	mPbos[mCurrentPbo]->unmap();
	
	mTexs[mCurrentTex]->update( mPbos[mCurrentPbo], GL_RGB, GL_UNSIGNED_BYTE );
	
	mCurrentPbo = ( mCurrentPbo + 1 ) % NUM_BUFFERS;
	
	mCurrentTex = ( mCurrentTex + 1 ) % NUM_BUFFERS;
	
	mTexture = mTexs[mCurrentTex];
}

void PixelSortingApp::sortWholeImage( const Surface8u &sortableSurface )
{
	std::list<Color8u> sortableImage(IMAGE_WIDTH*IMAGE_HEIGHT);
	auto surfaceData = (Color8u*) sortableSurface.getData();
	std::copy( surfaceData, surfaceData + IMAGE_WIDTH * IMAGE_HEIGHT, sortableImage.begin() );
	sortableImage.sort( ::comparator );
	std::move( sortableImage.begin(), sortableImage.end(), mPixels.begin() );
	
	mTexture = gl::Texture::create( &mPixels.data()->r,
								   GL_RGB,
								   IMAGE_WIDTH,
								   IMAGE_HEIGHT,
								   gl::Texture2d::Format().loadTopDown() );
}

void PixelSortingApp::update()
{
	if( mCapture && mCapture->checkNewFrame() ) {
		
		switch ( mSortType ) {
			case SortType::SLOW: {
				Timer time;
				time.start();
				slowSort( mCapture->getSurface() );
				time.stop();
				cout << "slowSort: " << time.getSeconds() << endl;
			}
			break;
			case SortType::FAST: {
				Timer time;
				time.start();
				fastSort( mCapture->getSurface() );
				time.stop();
				cout << "fastSort: " << time.getSeconds() << endl;
			}
			break;
			case SortType::PBO: {
				Timer time;
				time.start();
				pboSort( mCapture->getSurface() );
				time.stop();
				cout << "pboSort: " << time.getSeconds() << endl;
			}
			break;
			default:
				cout << "No Sort Chosen" << endl;
			break;
		}
	}
	
	getWindow()->setTitle(to_string(getAverageFps()));
}

void PixelSortingApp::draw()
{
	gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
	gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
	
	if( mTexture ) {
		gl::pushModelMatrix();
		gl::draw( mTexture );
		gl::popModelMatrix();
	}

}

CINDER_APP_NATIVE( PixelSortingApp, RendererGl )
