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

#define INITGUID
#define DIRECTINPUT_VERSION 0x0800
// DirectX includes
#include <d3d11.h>
#include <dinput.h>
#include <d3dCompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")

#include <DirectXMath.h>
using namespace DirectX;
#include <DirectXColors.h>
using namespace DirectX::Colors;

void com_safe_release(IUnknown* x);
#include "ComSmartPointer.h"

#define SAFE_RELEASE( x ) {if(x){(x)->Release();(x)=NULL;}}
#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}



// Define the number of threads to use for 
#define NUM_THREADS 4

#define PI 3.14159265f