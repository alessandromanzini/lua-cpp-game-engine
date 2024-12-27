//-----------------------------------------------------------------
// Game Engine WinMain Function
// C++ Source - GameWinMain.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameWinMain.h"
#include "GameEngine.h"

#include "Game.h"	

#include <shellapi.h>

constexpr const wchar_t* DEFAULT_SCRIPT_PATH{ L"example.lua" };

//-----------------------------------------------------------------
// Create GAME_ENGINE global (singleton) object and pointer
//-----------------------------------------------------------------
GameEngine myGameEngine;
GameEngine* GAME_ENGINE{ &myGameEngine };

//-----------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------
int APIENTRY wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
    // Combine program name and lpCmdLine into full command line
    LPWSTR cmdLine = GetCommandLineW( );

    // Parse the command-line string into arguments
    int argc;
    LPWSTR* argv = CommandLineToArgvW( cmdLine, &argc );
    if ( argv == NULL )
    {
		std::cerr << "Failed to parse command line." << std::endl;
        return 1;
    }

	// Create the game instance
	GAME_ENGINE->SetGame( new Game( ) );

	// Set the script path
    const wchar_t* scriptPath{ DEFAULT_SCRIPT_PATH };
	if ( argc > 1 )
	{
		scriptPath = argv[1];
	}

    // Run the game loop
    auto runRes = GAME_ENGINE->Run( hInstance, nCmdShow, scriptPath );

    // Free memory allocated by CommandLineToArgvW
    LocalFree( argv );
	
    return runRes;
}

