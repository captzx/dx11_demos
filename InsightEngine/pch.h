#pragma once

#ifndef STRICT
#define STRICT
#endif

// Standard C++ Library includes
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <exception>

// Standard C Library includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>

// DirectX includes
#include <d3d11_1.h>
#include <d3dCompiler.h>


#include <DirectXMath.h>
using namespace DirectX;
#include <DirectXColors.h>
using namespace DirectX::Colors;

#define SAFE_RELEASE( x ) {if(x){(x)->Release();(x)=NULL;}}
#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}

// Define the number of threads to use for 
#define NUM_THREADS 4

#define PI 3.14159265f


#include <glog/logging.h>
using namespace google;