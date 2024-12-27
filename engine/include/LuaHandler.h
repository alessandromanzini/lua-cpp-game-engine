#pragma once

#include <sol/sol.hpp>

class LuaHandler
{
public:
	LuaHandler( ) = default;
	explicit LuaHandler( sol::state&& luaState )
		: m_State{ std::move( luaState ) }
	{
	}

	// Passthorugh function to access lua variables
	auto operator[]( const char* key )
	{
		return m_State[key];
	}

	void SetHandle( sol::state&& state )
	{
		m_State = std::move( state );
	}

	// Passthrough function to set a function in the lua state
	template <typename ...args_t>
	void SetFunction( std::string&& functionName, args_t&&... args )
	{
		m_State.set_function( std::move( functionName ), args... );
	}

	template <typename return_t = void, typename... args_t>
	return_t SafeInvoke( const std::string& functionName, args_t&&... args ) const
	{
		auto func = m_State[functionName];
		sol::protected_function_result func_return;

		// Call the function with the given arguments, if any
		if constexpr ( sizeof...( args_t ) == 0 )
		{
			func_return = func( );
		}
		else
		{
			func_return = func( std::forward<args_t>( args )... );
		}

		// If the function call failed, throw an exception
		if ( !func_return.valid( ) )
		{
			const sol::error err = func_return;
			LuaExceptionHandler( m_State.lua_state( ), err, err.what( ) );
			//throw err;
		}

		// If the function has a return value, return it
		if constexpr ( !std::is_void_v<return_t> )
		{
			return func_return.get<return_t>( );
		}
	}

	static int LuaExceptionHandler( lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description )
	{
		std::stringstream errorStream{};

		// L is the lua state, which you can wrap in a state_view if necessary
		// maybe_exception will contain exception, if it exists
		// description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
		errorStream << "Exception occured!\n";
		if ( maybe_exception )
		{
			errorStream << "\n[ FROM THE EXCEPTION ]:\n\n";
			errorStream << ( *maybe_exception ).what( ) << std::endl;
		}
		else
		{
			errorStream << "\n[ FROM THE DESCRIPTION PARAMETER ]:\n\n";
			errorStream.write( description.data( ), static_cast<std::streamsize>( description.size( ) ) );
			errorStream << std::endl;
		}

		std::string error{ errorStream.str( ) };
		GAME_ENGINE->MessageBox( tstring( error.begin( ), error.end( ) ) );

		// you must push 1 element onto the stack to be
		// transported through as the error object in Lua
		// note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
		// so we push a single string (in our case, the description of the error)
		return sol::stack::push( L, description );
	}

private:
	sol::state m_State;

};
