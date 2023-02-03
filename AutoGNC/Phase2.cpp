//code should hopefully show both colored and depth camera footage through the use of imshow

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include <iostream>

using namespace cv;

int main(int argc, char * argv[]) try
  {
   
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Create a Pipeline - this serves as a top-level API for streaming and processing frames
    rs2::pipeline p;

    // Configure and start the pipeline
    p.start();

    const auto window_name = "Display Image";
    namedWindow(window_name, WINDOW_AUTOSIZE);

    secondWindow('Second Display', WINDOW_AUTOSIZE);

    while (waitKey(1))
      {
        // Block program until frames arrive
	rs2::frameset data = p.wait_for_frames();

        // Try to get a frame of a depth image and color image
	rs2::frame color = data.get_color_frame(); 
	rs2::frame depth = data.get_depth_frame().apply_filter(color_map);


	//what is the difference between this and the commented version of getting w and h
	const int w = depth.as<rs2::video_frame>().get_width();
        const int h = depth.as<rs2::video_frame>().get_height();
        // Get the depth frame's dimensions
	//        auto width = depth.get_width();
        //        auto height = depth.get_height();
	
	//instead of render we need to make them into mat and use image show to pull the images with cv
        Mat image(Size(w, h), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
	Mat image2(Size(w,h), CV_8UC3, (void*)color.get_data(), Mat::Auto_STEP);

        imshow(window_name, image);
	imshow('Second Display',image2);
	//depth_image.render(depth, { 0, 0, app.width() / 2, app.height() });
	//color_image.render(color, { app.width() / 2, 0, app.width() / 2, app.height() });

        // Query the distance from the camera to the object in the center of the image
        float dist_to_center = depth.get_distance(width / 2, height / 2);
	


        // Print the distance
	std::cout << "The camera is facing an object " << dist_to_center << " meters away \r";
      }

    return EXIT_SUCCESS;
  }
 catch (const rs2::error & e)
   {
     std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
     return EXIT_FAILURE;
   }
 catch (const std::exception& e)
   {
     std::cerr << e.what() << std::endl;
     return EXIT_FAILURE;
   }
