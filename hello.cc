#include <napi.h>
#include "CMakeProject1.h"
#include "mylib2.h"
#include <opencv2/opencv.hpp>
static Napi::String Method(const Napi::CallbackInfo& info) {
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
  cv::Mat m;
  std::cout << "mylib2:" << mylib2() << std::endl;
  return Napi::String::New(env, helloWorld);
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(hello, Init)
