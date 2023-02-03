//file for testing aruco marker detection. 
//need to print aruco marker
#include <opencv2/opencv.hpp>   
#include <opencv2/aruco.hpp>
using namespace cv2;
int main ()
{
  Mat markerImage;
  aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
  //                         dictionary, code, size in pixels, image, border thickness. 
  aruco::generateImageMarker(dictionary, 23, 400, markerImage, 1);
  imwrite("marker.png", markerImage);
}
