#pragma once

#include <Windows.h>
#include <cstdint>

class Bitmap;

namespace DataTypes
{
	struct COLORRGB
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;

		COLORRGB( uint8_t r, uint8_t g, uint8_t b );

		COLORRGB( COLORREF color );

		operator COLORREF( ) const;
	};

	struct VECTOR
	{
		VECTOR( ) = default;
		VECTOR( float x, float y );
		explicit VECTOR( const POINT& point );
		explicit VECTOR( const POINT& from, const POINT& to );

		float x;
		float y;

		float Magnitude( ) const;
		float SqrMagnitude( ) const;

		float Normalize( );
		VECTOR Normalized( ) const;

		void Round( );

		static float Dot( const VECTOR& v0, const VECTOR& v1 );
		static VECTOR Cross( const VECTOR& v0, const VECTOR& v1 );

		POINT ToPOINT( ) const;

		VECTOR operator+( const VECTOR& rhs ) const;
		VECTOR operator-( const VECTOR& rhs ) const;
		VECTOR operator*( float scalar ) const;
		VECTOR operator/( float scalar ) const;

		VECTOR operator-( ) const;

		VECTOR& operator+=( const VECTOR& rhs );
		VECTOR& operator-=( const VECTOR& rhs );
		VECTOR& operator*=( float scalar );

		bool operator==( const VECTOR& rhs ) const;
		bool operator!=( const VECTOR& rhs ) const;

		float operator|( const VECTOR& rhs ) const;
		VECTOR operator&( const VECTOR& rhs ) const;
	};

	POINT operator+( const POINT& lhs, const VECTOR& rhs );
	POINT operator-( const POINT& lhs, const VECTOR& rhs );

	struct SPRITEINFO
	{
		const Bitmap* pBitmap;
		int rows;
		int cols;
		int delay;
	};

	class SPRITE
	{
	public:
		explicit SPRITE( const Bitmap* pBitmap, int rows, int cols, int delay );
		explicit SPRITE( const SPRITEINFO& info );

		bool Paint( const POINT& position ) const;
		bool Paint( int x, int y ) const;
		void Tick( );

		int GetFrame( ) const
		{
			return m_CurrentFrame;
		}

	private:
		const Bitmap* const m_pBitmap;

		const int m_Rows;
		const int m_Cols;
		const int m_FrameWidth;
		const int m_FrameHeight;

		const int m_Delay;

		int m_CurrentFrame;
		int m_ElapsedTick;

	};
}
