//-----------------------------------------------------------------
// Main Game  File
// C++ Header - Game.h - version v8_01			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"
#include "AbstractGame.h"
#include "GameEngine.h"

#include "LuaHandler.h"

//-----------------------------------------------------------------
// Game Class																
//-----------------------------------------------------------------
class Game : public AbstractGame, public Callable
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	Game( ) noexcept;

	virtual ~Game( ) noexcept override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	Game( const Game& other ) = delete;
	Game( Game&& other ) noexcept = delete;
	Game& operator=( const Game& other ) = delete;
	Game& operator=( Game&& other ) noexcept = delete;

	//---------------------------
	// General Member Functions
	//---------------------------
	void Initialize( const wchar_t* scriptPath ) override;
	void Start( )															override;
	void End( )															override;
	void Paint( RECT rect )	const											override;
	void Tick( )															override;
	void MouseButtonAction( bool isLeft, bool isDown, int x, int y, WPARAM wParam )		override;
	void MouseWheelAction( int x, int y, int distance, WPARAM wParam )					override;
	void MouseMove( int x, int y, WPARAM wParam )								override;
	void CheckKeyboard( )															override;
	void KeyPressed( TCHAR key )													override;

	void BindToCaller( Caller* callerPtr );
	void UnbindFromCaller( Caller* callerPtr );
	void CallAction( Caller* callerPtr )											override;

	void Log( tstring&& message );

private:
	// -------------------------
	// Datamembers
	// -------------------------
	LuaHandler m_LuaHandler{};

	bool m_IsLogging{ false };
	tstring m_LogMessage{};

};
