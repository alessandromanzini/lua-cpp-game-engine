#pragma once

#include "DefaultLuaBinder.h"
#include "LuaHandler.h"

// Class that loads a Lua script and binds it to a Lua state.
// The binder_t template parameter is a functor that binds methods, defaulted to the basic engine bindings.
class LuaLoader
{
public:
	#pragma warning( push )
	#pragma warning( disable : 4244 ) // conversion from 'const wchar_t' to 'char', possible loss of data
	LuaLoader( const std::wstring& scriptPath )
		: m_ScriptPath( scriptPath.begin( ), scriptPath.end( ) )
	{
	}
	#pragma warning( pop )

	template <typename binder_t = DefaultLuaBinder>
	bool LoadScript( sol::state& luaState ) const
	{
		// Grant access to base libraries
		luaState.open_libraries( sol::lib::base, sol::lib::math, sol::lib::package, sol::lib::debug, sol::lib::table, sol::lib::string, sol::lib::io );
		luaState.set_exception_handler( &LuaHandler::LuaExceptionHandler );

		// Load and execute the ext. Lua Script
		try
		{
			const auto scriptResult = luaState.safe_script_file( m_ScriptPath );
			if ( !scriptResult.valid( ) )
			{
				const sol::error err = scriptResult;
				throw err;
			}
		}
		catch ( const sol::error& err )
		{
			// if loading fails run handler and return false
			LuaHandler::LuaExceptionHandler( luaState.lua_state( ), err, err.what( ) );
			return false;
		}

		binder_t{}.operator()( luaState );
		return true;
	}

	template <typename binder_t = DefaultLuaBinder>
	bool LoadScript( LuaHandler& handler ) const
	{
		sol::state state{};

		bool result{ LoadScript<binder_t>( state ) };

		if ( result )
		{
			handler.SetHandle( std::move( state ) );
			return true;
		}
		return false;
	}

private:
	const std::string m_ScriptPath;

};
