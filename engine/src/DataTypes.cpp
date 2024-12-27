#include "DataTypes.h"

#include <cmath>
#include <limits>

#include "GameEngine.h"

using namespace DataTypes;

#pragma region COLORRGB
COLORRGB::COLORRGB( uint8_t r, uint8_t g, uint8_t b )
	: r( r ), g( g ), b( b )
{
}

COLORRGB::COLORRGB( COLORREF color )
	: r( GetRValue( color ) ), g( GetGValue( color ) ), b( GetBValue( color ) )
{
}

COLORRGB::operator COLORREF( ) const
{
	return RGB( r, g, b );
}
#pragma endregion

#pragma region VECTOR
VECTOR::VECTOR( float x, float y )
	: x( x ), y( y )
{

}

VECTOR::VECTOR( const POINT& point )
	: x( static_cast<float>( point.x ) ), y( static_cast<float>( point.y ) )
{
}

VECTOR::VECTOR( const POINT& from, const POINT& to ) 
	: x( static_cast<float>( to.x - from.x ) ), y( static_cast<float>( to.y - from.y ) )
{
}

float VECTOR::Magnitude( ) const
{
	return sqrt( x * x + y * y );
}

float VECTOR::SqrMagnitude( ) const
{
	return x * x + y * y;
}

float VECTOR::Normalize( )
{
	float magnitude = Magnitude( );
	if ( magnitude > 0 )
	{
		x /= magnitude;
		y /= magnitude;
	}
	return magnitude;
}

VECTOR VECTOR::Normalized( ) const
{
	VECTOR result{ *this };
	result.Normalize( );
	return result;
}

void VECTOR::Round( )
{
	x = std::round( x );
	y = std::round( y );
}

float VECTOR::Dot( const VECTOR& v0, const VECTOR& v1 )
{
	return v0.x * v1.x + v0.y * v1.y;
}

VECTOR VECTOR::Cross( const VECTOR& v0, const VECTOR& v1 )
{
	return { v0.x * v1.y - v0.y * v1.x, v0.y * v1.x - v0.x * v1.y };
}

POINT VECTOR::ToPOINT( ) const
{
	return { static_cast<LONG>( x ), static_cast<LONG>( y ) };
}

VECTOR VECTOR::operator+( const VECTOR& rhs ) const
{
	return { x + rhs.x, y + rhs.y };
}

VECTOR VECTOR::operator-( const VECTOR& rhs ) const
{
	return { x - rhs.x, y - rhs.y };
}

VECTOR VECTOR::operator*( float scalar ) const
{
	return { x * scalar, y * scalar };
}

VECTOR VECTOR::operator/( float scalar ) const
{
	return { x / scalar, y / scalar };
}

VECTOR VECTOR::operator-( ) const
{
	return { -x, -y };
}

VECTOR& VECTOR::operator+=( const VECTOR& rhs )
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

VECTOR& VECTOR::operator-=( const VECTOR& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

VECTOR& VECTOR::operator*=( float scalar )
{
	x *= scalar;
	y *= scalar;
	return *this;
}

bool VECTOR::operator==( const VECTOR& rhs ) const
{
	constexpr float epsilon = std::numeric_limits<float>::epsilon( );
	return std::abs(x - rhs.x) < epsilon
		&& std::abs(y - rhs.y) < epsilon;
}

bool VECTOR::operator!=( const VECTOR& rhs ) const
{
	return !( *this == rhs );
}

float VECTOR::operator|( const VECTOR& rhs ) const
{
	return Dot( *this, rhs );
}

VECTOR VECTOR::operator&( const VECTOR& rhs ) const
{
	return Cross( *this, rhs );
}

POINT DataTypes::operator+( const POINT& lhs, const VECTOR& rhs )
{
	return { static_cast<LONG>( lhs.x + rhs.x ), static_cast<LONG>( lhs.x + rhs.y ) };
}

POINT DataTypes::operator-( const POINT& lhs, const VECTOR& rhs )
{
	return { static_cast<LONG>( lhs.x - rhs.x ), static_cast<LONG>( lhs.y - rhs.y ) };
}
#pragma endregion

#pragma region SPRITE
SPRITE::SPRITE( const Bitmap* pBitmap, int rows, int cols, int delay )
	: m_pBitmap( pBitmap ), m_Rows( rows ), m_Cols( cols ), m_Delay( delay )
	, m_FrameWidth( pBitmap->GetWidth( ) / cols )
	, m_FrameHeight( pBitmap->GetHeight( ) / rows )
	, m_CurrentFrame( 0 ), m_ElapsedTick( 0 )
{
}

SPRITE::SPRITE( const SPRITEINFO& info )
	: SPRITE( info.pBitmap, info.rows, info.cols, info.delay )
{
}

bool SPRITE::Paint( const POINT& position ) const
{
	if ( m_pBitmap == nullptr )
	{
		return false;
	}

	const int row = m_CurrentFrame / m_Cols;
	const int col = m_CurrentFrame % m_Cols;

	RECT sourceRect{ col * m_FrameWidth, row * m_FrameHeight, ( col + 1 ) * m_FrameWidth, ( row + 1 ) * m_FrameHeight };
	return GAME_ENGINE->DrawBitmap( m_pBitmap, position.x, position.y, sourceRect );
}

bool SPRITE::Paint( int x, int y ) const
{
	return Paint( { x, y } );
}

void SPRITE::Tick( )
{
	++m_ElapsedTick;
	if ( m_ElapsedTick >= m_Delay )
	{
		m_ElapsedTick -= m_Delay;
		m_CurrentFrame = ( m_CurrentFrame + 1 ) % ( m_Rows * m_Cols );
	}
}

#pragma endregion
