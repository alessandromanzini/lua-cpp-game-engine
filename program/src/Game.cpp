//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"
#include "DataTypes.h"

#include "LuaLoader.h"

#include <functional>

//-----------------------------------------------------------------
// Game Member Functions																				
//-----------------------------------------------------------------

Game::Game( ) noexcept
{
	// nothing to create
}

Game::~Game( ) noexcept
{
	// nothing to destroy
}

void Game::Initialize( const wchar_t* scriptPath )
{
	// Code that needs to execute (once) at the start of the game, before the game window is created
	AbstractGame::Initialize( scriptPath );

	// Load lua state in the handler
	LuaLoader loader( scriptPath );
	// If loading the script fails, quit the application.
	if ( !loader.LoadScript( m_LuaHandler ) )
	{
		GAME_ENGINE->MessageBox( _T( "Error!\n\nFailed to load script.\n\nApplication is now closing..." ) );
		GAME_ENGINE->Quit( );
	}
	else
	{
		// Binding singleton GAME_ENGINE instance
		m_LuaHandler["GAME_ENGINE"] = GAME_ENGINE;

		// Hooks to callers binding functions
		m_LuaHandler.SetFunction( "bind_to_game", &Game::BindToCaller, this );
		m_LuaHandler.SetFunction( "unbind_from_game", &Game::UnbindFromCaller, this );

		m_LuaHandler.SetFunction( "log", &Game::Log, this );

		// Initialize the game
		m_LuaHandler.SafeInvoke( "on_initialize" );
	}

	// Set the keys that the game needs to listen to
	/*tstringstream buffer;
	buffer << _T("KLMO");
	buffer << (char) VK_LEFT;
	buffer << (char) VK_RIGHT;
	GAME_ENGINE->SetKeyList(buffer.str());*/
}

void Game::Start( )
{
	// Insert code that needs to execute (once) at the start of the game, after the game window is created
	m_LuaHandler.SafeInvoke( "on_start" );
}

void Game::End( )
{
	// Insert code that needs to execute when the game ends
	m_LuaHandler.SafeInvoke( "on_end" );
}

void Game::Paint( RECT rect ) const
{
	// Insert paint code
	m_LuaHandler.SafeInvoke( "on_paint" );

	if ( m_IsLogging )
	{
		GAME_ENGINE->SetColor( RGB( 255, 255, 255 ) );
		GAME_ENGINE->DrawString( m_LogMessage.c_str( ), 10, 10 );
	}
}

void Game::Tick( )
{
	// Insert non-paint code that needs to execute each tick
	m_LuaHandler.SafeInvoke( "on_tick" );
}

void Game::MouseButtonAction( bool isLeft, bool isDown, int x, int y, WPARAM wParam )
{
	// Insert code for a mouse button action
	m_LuaHandler.SafeInvoke( "on_mouse_button_action", isLeft, isDown, x, y, wParam );
}

void Game::MouseWheelAction( int x, int y, int distance, WPARAM wParam )
{
	// Insert code for a mouse wheel action
	m_LuaHandler.SafeInvoke( "on_mouse_wheel_action", x, y, distance, wParam );
}

void Game::MouseMove( int x, int y, WPARAM wParam )
{
	// Insert code that needs to execute when the mouse pointer moves across the game window
	m_LuaHandler.SafeInvoke( "on_mouse_move", x, y, wParam );
}

void Game::CheckKeyboard( )
{
	// Here you can check if a key is pressed down
	// Is executed once per frame 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void Game::KeyPressed( TCHAR key )
{
	// Insert code that needs to execute when a key is pressed
	// The function is executed when the key is *released*
	// You need to specify the list of keys with the SetKeyList() function
	m_LuaHandler.SafeInvoke( "on_key_pressed", key );

}

void Game::BindToCaller( Caller* callerPtr )
{
	callerPtr->AddActionListener( this );
}

void Game::UnbindFromCaller( Caller* callerPtr )
{
	callerPtr->RemoveActionListener( this );
}

void Game::CallAction( Caller* callerPtr )
{
	// Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
	m_LuaHandler.SafeInvoke( "on_call_action", callerPtr );
}

void Game::Log( tstring&& message )
{
	m_IsLogging = true;
	m_LogMessage = std::move( message );
}
