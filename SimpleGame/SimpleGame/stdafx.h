#pragma once
#pragma comment(lib , "winmm.lib")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include <Windows.h>
#include <vector>
#include <ctime>

#include <mmsystem.h>
#include <algorithm>

#define OBJECT_BUILDING		0
#define OBJECT_CHARACTER		1
#define OBJECT_BULLET		2
#define OBJECT_ARROW		3

#define TEAM_1		0
#define TEAM_2		1
#define TEAM_NEUTRAL		2

#define UPDATE_RETURN_DELETE	1
#define UPDATE_RETURN_CREATE_BULLET	2
#define UPDATE_RETURN_CREATE_ARROW	3

#define WINCX	500
#define WINCY	800
using namespace std;
