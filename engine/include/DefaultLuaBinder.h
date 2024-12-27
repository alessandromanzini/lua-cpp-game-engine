#pragma once

#include <sol/sol.hpp>

using COLORRGB = DataTypes::COLORRGB;
using VECTOR = DataTypes::VECTOR;
using SPRITEINFO = DataTypes::SPRITEINFO;
using SPRITE = DataTypes::SPRITE;

class DefaultLuaBinder
{
public:
	// Overload function operator
	void operator()( sol::state& luaState ) const
	{
		BindEngineCore( luaState );
		BindEnumerators( luaState );
		BindCallers( luaState );
		BindResourceTypes( luaState );
		BindDataTypes( luaState );
	}

private:
	void BindEngineCore( sol::state& luaState ) const
	{
		luaState.new_usertype<GameEngine>( "GameEngine",
										   "set_title", &GameEngine::SetTitle,
										   "set_window_position", &GameEngine::SetWindowPosition,
										   "set_key_list", &GameEngine::SetKeyList,
										   "set_frame_rate", &GameEngine::SetFrameRate,
										   "set_width", &GameEngine::SetWidth,
										   "set_height", &GameEngine::SetHeight,
										   "go_fullscreen", &GameEngine::GoFullscreen,
										   "go_windowed_mode", &GameEngine::GoWindowedMode,
										   "show_mouse_pointer", &GameEngine::ShowMousePointer,
										   "quit", &GameEngine::Quit,
										   "is_fullscreen", &GameEngine::IsFullscreen,
										   "is_key_down", &GameEngine::IsKeyDown,
										   "message_box", &GameEngine::MessageBoxCSTR,
										   "message_continue", &GameEngine::MessageContinue,
										   "set_color", sol::resolve<void( COLORRGB )>( &GameEngine::SetColor ),
										   "set_font", &GameEngine::SetFont,
										   "fill_window_rect", sol::resolve<bool( COLORRGB ) const>( &GameEngine::FillWindowRect ),
										   "draw_line", &GameEngine::DrawLine,
										   "draw_rect", sol::overload( sol::resolve<bool( int, int, int, int ) const>( &GameEngine::DrawRect ),
										   sol::resolve<bool( const RECT& ) const>( &GameEngine::DrawRect ) ),
										   "fill_rect", sol::overload( sol::resolve<bool( int, int, int, int ) const>( &GameEngine::FillRect ),
										   sol::resolve<bool( int, int, int, int, int ) const>( &GameEngine::FillRect ),
										   sol::resolve<bool( const RECT& ) const>( &GameEngine::FillRect ) ),
										   "draw_round_rect", sol::overload( sol::resolve<bool( const RECT&, int ) const>( &GameEngine::DrawRoundRect ),
										   sol::resolve<bool( int, int, int, int, int ) const>( &GameEngine::DrawRoundRect ) ),
										   "fill_round_rect", sol::overload( sol::resolve<bool( const RECT&, int ) const>( &GameEngine::FillRoundRect ),
										   sol::resolve<bool( int, int, int, int, int ) const>( &GameEngine::FillRoundRect ) ),
										   "draw_oval", &GameEngine::DrawOval,
										   "fill_oval", sol::overload( sol::resolve<bool( int, int, int, int ) const>( &GameEngine::FillOval ),
										   sol::resolve<bool( int, int, int, int, int ) const>( &GameEngine::FillOval ) ),
										   "draw_arc", &GameEngine::DrawArc,
										   "fill_arc", &GameEngine::FillArc,
										   "draw_string", sol::overload( sol::resolve<int( const tstring&, int, int ) const>( &GameEngine::DrawString ),
										   sol::resolve<int( const tstring&, int, int, int, int ) const>( &GameEngine::DrawString ) ),
										   "draw_bitmap", sol::overload( sol::resolve<bool( const Bitmap*, int, int ) const>( &GameEngine::DrawBitmap ),
										   sol::resolve<bool( const Bitmap*, int, int, RECT ) const>( &GameEngine::DrawBitmap ) ),
										   "draw_polygon", sol::overload( sol::resolve<bool( const POINT*, int ) const>( &GameEngine::DrawPolygon ),
										   sol::resolve<bool( const POINT*, int, bool ) const>( &GameEngine::DrawPolygon ) ),
										   "fill_polygon", sol::overload( sol::resolve<bool( const POINT*, int ) const>( &GameEngine::FillPolygon ),
										   sol::resolve<bool( const POINT*, int, bool ) const>( &GameEngine::FillPolygon ) ),
										   "get_draw_color", &GameEngine::GetDrawColor,
										   "repaint", &GameEngine::Repaint,
										   "get_title", &GameEngine::GetTitle,
										   "get_width", &GameEngine::GetWidth,
										   "get_height", &GameEngine::GetHeight,
										   "get_frame_rate", &GameEngine::GetFrameRate,
										   "get_frame_delay", &GameEngine::GetFrameDelay,
										   "get_window_position", &GameEngine::GetWindowPosition );
	};

	void BindEnumerators( sol::state& luaState ) const
	{
		luaState.new_enum( "CALLER_TYPE",
						   "text_box", Caller::Type::TextBox,
						   "button", Caller::Type::Button,
						   "timer", Caller::Type::Timer,
						   "audio", Caller::Type::Audio,
						   "video", Caller::Type::Video );

		luaState.new_enum( "SHAPE",
						   "ellipse", HitRegion::Shape::Ellipse,
						   "rectangle", HitRegion::Shape::Rectangle );
	}

	void BindCallers( sol::state& luaState ) const
	{
		luaState.new_usertype<Caller>( "Caller",
									   "get_type", &Caller::GetType );

		luaState.new_usertype<Button>( "Button",
									   sol::constructors<Button( const tstring& ), Button( )>( ),
									   "set_bounds", &Button::SetBounds,
									   "set_text", &Button::SetText,
									   "set_font", sol::resolve<void( Font* )>( &Button::SetFont ),
									   "set_enabled", &Button::SetEnabled,
									   "show", &Button::Show,
									   "hide", &Button::Hide,
									   "get_bounds", &Button::GetBounds,
									   "get_text", &Button::GetText,
									   sol::base_classes, sol::bases<Caller>( ) );

		luaState.new_usertype<TextBox>( "TextBox",
										sol::constructors<TextBox( const tstring& ), TextBox( )>( ),
										"set_bounds", &TextBox::SetBounds,
										"set_text", &TextBox::SetText,
										"set_font", &TextBox::SetFont,
										"set_backcolor", sol::resolve<void( COLORRGB ) >( &TextBox::SetBackcolor ),
										"set_forecolor", sol::resolve<void( COLORRGB )>( &TextBox::SetForecolor ),
										"set_enabled", &TextBox::SetEnabled,
										"show", &TextBox::Show,
										"hide", &TextBox::Hide,
										"get_bounds", &TextBox::GetBounds,
										"get_text", &TextBox::GetText,
										sol::base_classes, sol::bases<Caller>( ) );

		luaState.new_usertype<Audio>( "Audio",
									  sol::constructors<Audio( const tstring& )>( ),
									  "tick", &Audio::Tick,
									  "play", sol::overload( &Audio::Play, &Audio::PlayFromTo ),
									  "pause", &Audio::Pause,
									  "stop", &Audio::Stop,
									  "set_volume", &Audio::SetVolume,
									  "set_repeat", &Audio::SetRepeat,
									  "get_name", &Audio::GetName,
									  "get_alias", &Audio::GetAlias,
									  "get_duration", &Audio::GetDuration,
									  "is_playing", &Audio::IsPlaying,
									  "is_paused", &Audio::IsPaused,
									  "get_repeat", &Audio::GetRepeat,
									  "exists", &Audio::Exists,
									  "get_volume", &Audio::GetVolume,
									  "get_type", &Audio::GetType,
									  sol::base_classes, sol::bases<Caller>( ) );
	}

	void BindResourceTypes( sol::state& luaState ) const
	{
		luaState.new_usertype<Bitmap>( "Bitmap",
									   sol::constructors<Bitmap( const tstring&, bool )>( ),
									   "set_transparency_color", sol::resolve<void( COLORRGB )>( &Bitmap::SetTransparencyColor ),
									   "get_width", &Bitmap::GetWidth,
									   "get_height", &Bitmap::GetHeight,
									   "get_transparency_color", &Bitmap::GetTransparencyColorStruct,
									   "get_opacity", &Bitmap::GetOpacity,
									   "has_alpha_channel", &Bitmap::HasAlphaChannel,
									   "save_to_file", &Bitmap::SaveToFile );

		luaState.new_usertype<Font>( "Font",
									 sol::constructors<Font( const tstring&, bool, bool, bool, int )>( ) );
	}

	void BindDataTypes( sol::state& luaState ) const
	{
		luaState.new_usertype<COLORRGB>( "RGB",
										 sol::constructors<COLORRGB( uint8_t, uint8_t, uint8_t )>( ),
										 "r", &COLORRGB::r,
										 "g", &COLORRGB::g,
										 "b", &COLORRGB::b );

		luaState.new_usertype<POINT>( "Point",
									  sol::constructors<POINT(), POINT( int, int )>( ),
									  "x", &POINT::x,
									  "y", &POINT::y );

		luaState.new_usertype<VECTOR>( "float2",
									   sol::constructors<VECTOR(), VECTOR( float, float ), VECTOR( const POINT& ), VECTOR( const POINT&, const POINT& )>( ),
									   "x", &VECTOR::x,
									   "y", &VECTOR::y,
									   "magnitude", &VECTOR::Magnitude,
									   "sqr_magnitude", &VECTOR::SqrMagnitude,
									   "normalize", &VECTOR::Normalize,
									   "normalized", &VECTOR::Normalized,
									   "round", &VECTOR::Round,
									   "dot", &VECTOR::Dot,
									   "cross", &VECTOR::Cross,
									   "to_point", &VECTOR::ToPOINT,
									   "__add", sol::overload( sol::resolve<VECTOR( const VECTOR& ) const>( &VECTOR::operator+ ),
									   sol::resolve<POINT( const POINT&, const VECTOR& )>( &DataTypes::operator+ ) ),
									   "__sub", sol::overload( sol::resolve<VECTOR( const VECTOR& ) const>( &VECTOR::operator- ),
									   sol::resolve<POINT( const POINT&, const VECTOR& )>( &DataTypes::operator- ) ),
									   "__mul", &VECTOR::operator*,
									   "__div", &VECTOR::operator/,
									   "__unm", sol::resolve<VECTOR( ) const>( &VECTOR::operator- ),
									   "__eq", &VECTOR::operator==,
									   "__bor", &VECTOR::operator|,
									   "__band", &VECTOR::operator& );

		luaState.new_usertype<RECT>( "Rect",
									 sol::constructors<RECT( int, int, int, int )>( ),
									 "left", &RECT::left,
									 "top", &RECT::top,
									 "right", &RECT::right,
									 "bottom", &RECT::bottom );

		luaState.new_usertype<HitRegion>( "HitRegion",
										  sol::constructors<HitRegion( HitRegion::Shape, int, int, int, int ), HitRegion( const POINT*, int ), HitRegion( const Bitmap* )>( ),
										  "move", &HitRegion::Move,
										  "hit_test", sol::overload( sol::resolve<bool( int, int ) const>( &HitRegion::HitTest ),
										  sol::resolve<bool( const HitRegion* ) const>( &HitRegion::HitTest ) ),
										  "collision_test", &HitRegion::CollisionTest,
										  "get_bounds", &HitRegion::GetBounds,
										  "exists", &HitRegion::Exists );

		luaState.new_usertype<SPRITEINFO>( "SpriteInfo",
										   sol::constructors<SPRITEINFO( const Bitmap*, int, int, int )>( ),
										   "bitmap", &SPRITEINFO::pBitmap,
										   "rows", &SPRITEINFO::rows,
										   "cols", &SPRITEINFO::cols,
										   "delay", &SPRITEINFO::delay );

		luaState.new_usertype<SPRITE>( "Sprite",
									   sol::constructors<SPRITE( const Bitmap*, int, int, int ), SPRITE( const SPRITEINFO& )>( ),
									   "paint", sol::overload( sol::resolve<bool( const POINT& ) const>( &SPRITE::Paint ),
									   sol::resolve<bool(int, int) const>( &SPRITE::Paint )),
									   "tick", &SPRITE::Tick,
									   "get_frame", &SPRITE::GetFrame );
	}

};
