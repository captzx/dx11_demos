#include "RotatingCubeApp.h"
#include <glog/logging.h>

using namespace insight;
using namespace google;

RotatingCubeApp _RotatingCubeInstance;
RotatingCubeApp::RotatingCubeApp() {
	LOG(INFO) << "info test" << "hello log!";  //���һ��Info��־
	LOG(WARNING) << "warning test";  //���һ��Warning��־
	LOG(ERROR) << "error test";  //���һ��Error��־
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