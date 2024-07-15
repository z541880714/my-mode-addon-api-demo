#include <napi.h>
#include "CMakeProject1.h"
#include "mylib2.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

static void drawText(Mat &image)
{
  putText(image, "Hello OpenCV",
          Point(20, 50),
          FONT_HERSHEY_COMPLEX, 1, // font face and scale
          Scalar(255, 255, 255),   // white
          1, LINE_AA);             // line thickness and type
}

static int _test()
{
  cout << "Built with OpenCV " << CV_VERSION << endl;
  Mat image;
  VideoCapture capture;
  capture.open(0);
  if (capture.isOpened())
  {
    cout << "Capture is opened" << endl;
    for (;;)
    {
      capture >> image;
      if (image.empty())
        break;
      drawText(image);
      imshow("Sample", image);
      if (waitKey(10) >= 0)
        break;
    }
  }
  else
  {
    cout << "No capture" << endl;
    image = Mat::zeros(480, 640, CV_8UC1);
    drawText(image);
    imshow("Sample", image);
    waitKey(0);
  }
  return 0;
}

static Napi::String Method(const Napi::CallbackInfo &info)
{
  // Napi::Env is the opaque data structure containing the environment in which
  // the request is being run. We will need this env when we want to create any
  // new objects inside of the node.js environment
  Napi::Env env = info.Env();

  // Create a C++ level variable
  std::string helloWorld = "Hello, world!";

  // Return a new javascript string that we copy-construct inside of the node.js
  // environment
  my_test();
  std::cout << "my lib ret:" << my_test() << std::endl;
  my_test_2();
  _test();
  std::cout << "mylib2:" << mylib2() << std::endl;
  return Napi::String::New(env, helloWorld);
}

static Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(hello, Init)
