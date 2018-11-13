#include "RotatingCubeApp.h"
#include <glog/logging.h>

using namespace insight;
using namespace google;

RotatingCubeApp _RotatingCubeInstance;
RotatingCubeApp::RotatingCubeApp() {
	LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
	LOG(WARNING) << "warning test";  //输出一个Warning日志
	LOG(ERROR) << "error test";  //输出一个Error日志
}

bool RotatingCubeApp::ConfigureEngineComponent() {

}

void RotatingCubeApp::ShutdownEngineComponent() {

}

void RotatingCubeApp::Initialize() {

}

void RotatingCubeApp::Update() {

}

void RotatingCubeApp::Shutdown() {

}