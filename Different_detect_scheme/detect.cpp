#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define CPU_ONLY = 1
#include "caffe/caffe.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
int face_input;
/**
 * @function main
 */
int main( int argc, const char** argv )
{

  //cout << "There will be a log.txt recording the records" << endl;
     
  ofstream log;
  log.open("log.txt", ios_base::app); 
  
  CvCapture* capture;

  Mat frame;

  //-- 1. Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  //-- 2. Read the video stream
  //capture = cvCaptureFromCAM( -1 );

  capture = cvCreateCameraCapture(-1);
  
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,400);
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,400); 

  
  
  
  if( capture )
  {
    while( true )
    {
      //frame = cvQueryFrame( capture );
      
      frame = cvQueryFrame( capture );

      //-- 3. Apply the classifier to the frame
      if( !frame.empty() )
       { detectAndDisplay( frame ); }
      else
       { printf(" --(!) No captured frame -- Break!"); break; }

      int c = waitKey(10);
      if( (char)c == 'c' ) { break; }
      if( face_input == 1 ) { break; }
    }
  }
  else{
    printf(" --(!) No Webcam!");
  }
  
   log.close(); 
   

   return 0;
}



























/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;
   Mat frame_gray;

   cvtColor( frame, frame_gray, CV_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );
   //-- Detect faces
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size( 250,250) );
   //Size means the resolutions of detect window.
   //In this case, the size of detect window is 10x10. The faces which are smaller than 10x10 will be ignored.
   
   int *x ;
   int *y ;
   int *w ;
   int *h ;
   
   x = new int;
   y = new int; 
   w = new int;  
   h = new int;
   
   if (faces.size() <= 1){
      for( unsigned int i = 0; i < faces.size(); i++ ){
         *x = faces[i].x;
         *y = faces[i].y;
         *w = faces[i].width;
         *h = faces[i].height;
         
         cout << "HI" << *x << endl;
                  cout << "HI" << *y << endl;
                           cout << "HI" << *w << endl;
                                    cout << "HI" << *h << endl;
         
         
         Mat croppped_face1 = frame(Rect(*x,*y,*w,*h));
         Mat croppped_face2 = frame(Rect(*x+20,*y+50,200,200));
      
            
         //Crop the face and save it.
         ostringstream *name1 = new ostringstream;
         ostringstream *name2 = new ostringstream;
         *name1 << "Current/" << "Cropped_face_" << i << ".jpg";      
         *name2 << "Current/" << "Cropped_face_" << i+1 << ".jpg";  
         imwrite( name1->str(), croppped_face1 );  
         
         resize(croppped_face2,croppped_face2,Size(250,250));
         
         imwrite( name2->str(), croppped_face2 );  
         delete name1;
         delete name2;
      
         //Draw the rectangle on the original image.
         rectangle( frame, Point (*x,*y), Point (*x+*w,*y+*h), Scalar(255,0,0),2,8,0);

      };
   };
    
   delete x; 
   delete y; 
   delete w; 
   delete h; 
   
   //rectangle( frame, Point (160,120), Point (160+250,120+250), Scalar(255,0,0),2,8,0);
   
   //-- Show what you got
   
   imshow( window_name, frame );
   
   imwrite( "result.jpg", frame );
   
   if (faces.size() == 1){
      face_input = 1;
   }else{
      face_input = 0;
   }
   
}
