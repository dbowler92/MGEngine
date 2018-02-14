//CoreMacros.h
//Created 27/01/18
//Created By Daniel Bowler
//
//Global macros

#pragma once

//Global macros
//
//Converts from mebibyte to bytes
#define MEB_TO_BYTES(meb) meb * (1024 * 1024)

//For debug builds, output extra info every time we dynamically allocate memory
#ifdef CONFIGURATION_DEBUG
//#define MGE_NEW new (_NORMAL_BLOCK,__FILE__, __LINE__)
#define MGE_NEW new
#else
#define MGE_NEW new
#endif

//TODO? Delete...
#ifdef CONFIGURATION_DEBUG
#define MGE_DELETE delete
#else
#define MGE_DELETE delete
#endif

#ifdef CONFIGURATION_DEBUG
#define MGE_DELETE_ARRAY delete[]
#else
#define MGE_DELETE_ARRAY delete[]
#endif

//Macro to disable/hide copy constructor and assignment operator
#define HIDE_COPY_ASSIGNMENT(c) private: c(const c &other) {}; c& operator = (const c &other) {};

//Hides constructor + destructor
#define HIDE_CONSTRUCTOR(c) private: c() {};
#define HIDE_CONSTRUCTOR_DESTRUCTOR(c) private: c() {}; ~c() {};

//Macro to disable constructor, destructor, assignment operator && destructor (statics classes)
#define MAKE_STATICS_CLASS_ONLY(c) private: c(); ~c(); c(const c &other); c& operator = (const c &other);

//Macro which simplifies the process of generating a platform agnostic class. Eg: FApplication from FWin32Application
#define GENERATE_PLATFORM_AGNOSTIC_CLASS(c, p) class c : public p	{	public:	c() {};	~c() {}; };																						 
#define GENERATE_PLATFORM_AGNOSTIC_CLASS_WITH_VIRTUAL_DTOR(c, p) class c : public p	{ public: c() {}; virtual ~c() {}; };