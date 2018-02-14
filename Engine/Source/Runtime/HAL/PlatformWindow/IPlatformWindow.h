//IPlatformWindow.h
//Created 11/08/18
//Created By Daniel Bowler
//
//Interface class that all OS windows will inherit from

#pragma once

#include <Core/CoreInclude.h>

class IPlatformWindow
{
public:
	virtual ~IPlatformWindow() = 0 {};

	virtual void UpdateWindowWidth(unsigned w) = 0;
	virtual void UpdateWindowHeight(unsigned h) = 0;

	virtual unsigned GetWindowWidth() = 0;
	virtual unsigned GetWindowHeight() = 0;
};