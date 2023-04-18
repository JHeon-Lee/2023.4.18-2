#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <Windows.h>
#include <conio.h> // 콘솔창 키입력을 위한 라이브러리
#include <time.h>

#define BG_GRAY		BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE
#define FG_GRAY		FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_WHITE		BG_GRAY|BACKGROUND_INTENSITY
#define FG_WHITE		FG_GRAY|FOREGROUND_INTENSITY
#define BG_BLACK		0
#define FG_BLACK		0
#define BG_DYELLOW	BACKGROUND_RED  |BACKGROUND_GREEN
#define BG_DPINK		BACKGROUND_RED  |BACKGROUND_BLUE
#define BG_DGREEN	BACKGROUND_GREEN|BACKGROUND_BLUE
#define FG_DYELLOW	FOREGROUND_RED  |FOREGROUND_GREEN
#define FG_DPINK		FOREGROUND_RED  |FOREGROUND_BLUE
#define FG_DGREEN	FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_YELLOW	BG_DYELLOW	|BACKGROUND_INTENSITY
#define BG_PINK		BG_DPINK	|BACKGROUND_INTENSITY
#define BG_LDGREEN	BG_DGREEN	|BACKGROUND_INTENSITY
#define FG_YELLOW	FG_DYELLOW	|FOREGROUND_INTENSITY
#define FG_PINK		FG_DPINK	|FOREGROUND_INTENSITY
#define FG_LDGREEN	FG_DGREEN	|FOREGROUND_INTENSITY
#define BG_RED		BACKGROUND_RED   
#define BG_GREEN		BACKGROUND_GREEN 
#define BG_BLUE		BACKGROUND_BLUE  
#define BG_LRED		BG_RED   |BACKGROUND_INTENSITY
#define BG_LGREEN	BG_GREEN |BACKGROUND_INTENSITY
#define BG_LBLUE		BG_BLUE  |BACKGROUND_INTENSITY
#define FG_RED		FOREGROUND_RED	 
#define FG_GREEN		FOREGROUND_GREEN 
#define FG_BLUE		FOREGROUND_BLUE  
#define FG_LRED		FG_RED	 |FOREGROUND_INTENSITY
#define FG_LGREEN	FG_GREEN |FOREGROUND_INTENSITY
#define FG_LBLUE		FG_BLUE  |FOREGROUND_INTENSITY
#define BG_INTENSITY	BACKGROUND_INTENSITY
#define FG_INTENSITY	FOREGROUND_INTENSITY

using namespace std;