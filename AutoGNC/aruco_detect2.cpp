#include <opencv2/aruco.hpp>
#include <iostream>


using namespace cv
using namespace std
int main (){
  Mat img;
  Ptr<aruco::Dictionary> dict = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
  namedWindow("Out",0);
  VideoCapture cap(-1);

  while (1){

      cap >> img;
      vector<vector<Point2f>> corners;
      vector<int> ids;
      aruco::detectMarkers(img,dict, corners, ids);//need to print coners so I know exactly what it is.
      //if(ids.size()>0){
      //aruco::drawDetectedMarkeres(img,corners,ids);
      //}

      //need to mess with points and use their coordinates to tell the lidar what pixels depth we want. Eventually we can perhaps add optical flow to calculate aruco markers velocity in 3 dimensions. 
      if (corners.size()>0){
	for(int i =0; i<(int)corners.size();i++){
	  int x = corners[i][0].x+corners[i][2].x;
	  int y = corners[i][0].y+corners[i][2].y;
	  putText(image,"id=" + to_string()(ids[i]),Point(x/2,y/2),1,1,Scalar(0,255,255));
	}
      }
      aruco::drawMarker(dict, 23, 200,1);
      imshow("Out", img);
      waitKey(1);
    }
}

