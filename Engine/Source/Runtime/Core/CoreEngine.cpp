#include "CoreEngine.h"

#include "Platform/Application/Win32Application.h"
#include "Core/AppDelegate/IAppDelegate.h"

FCoreEngine::FCoreEngine()
	: CachedAppDelegate(nullptr)
	, MainLoopTimer()
	, bShouldShutdownNextTick(false)
{}

FCoreEngine::~FCoreEngine()
{}

FCoreEngine* FCoreEngine::GetInstance()
{
	static FCoreEngine Instance;
	return &Instance;
}

int32 FCoreEngine::RunEngine(const FEngineStartupParams& EngineStartupParams)
{
	assert(EngineStartupParams.AppDelegate != nullptr);
	CachedAppDelegate = EngineStartupParams.AppDelegate;
	
	//Engine init
	InitEngine(EngineStartupParams);
	CachedAppDelegate->OnPostEngineInit();

	//Game loop
	int32 ReturnValue = EnterMainGameLoop();

	//Engine shutdown
	CachedAppDelegate->OnPreEngineShutdown();
	ShutdownEngine();

	return ReturnValue;
}

void FCoreEngine::InitEngine(const FEngineStartupParams& EngineStartupParams)
{
	//Init platform
	HINSTANCE HInstance = *((HINSTANCE*)EngineStartupParams.AppHandle);
	uint32 WindowWidth = EngineStartupParams.DefaultWindowWidth;
	uint32 WindowHeight = EngineStartupParams.DefaultWindowHeight;
	LPCWSTR MainWindowTitle = *((LPCWSTR*)EngineStartupParams.DefaultMainWindowTitle);

	FWin32Application* Application = FWin32Application::GetInstance();
	Application->InitApplication(HInstance, WindowWidth, WindowHeight, MainWindowTitle);

	//Init graphics

	//TODO: Init thread system, etc
}

void FCoreEngine::ShutdownEngine()
{
	//Shutdown engine

	//Shutdown application
	FWin32Application* Application = FWin32Application::GetInstance();
	Application->ShutdownApplication();
}

void FCoreEngine::ShutdownNextTick()
{
	bShouldShutdownNextTick = true;
}

int32 FCoreEngine::EnterMainGameLoop()
{
	static int32 ReturnVal = 0;

	FWin32Application* Application = FWin32Application::GetInstance();
	assert(Application);

	MainLoopTimer.Reset();
	MainLoopTimer.Start();

	//Temp: First frame of the game loop, wait a bit and tick so
	//first frame delta is something useful.
	Sleep(16);
	MainLoopTimer.Tick();

	while (bShouldShutdownNextTick == false)
	{
		float Dt = MainLoopTimer.DeltaTime();

		Application->TickApplication(Dt);

		//Temp: Allow exit by pressing escape embedded deep in the game loop. 
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			ShutdownNextTick();
		}

		MainLoopTimer.Tick();
	}

	return ReturnVal;
}