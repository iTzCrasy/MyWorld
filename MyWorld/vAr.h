#pragma once

#include "stdafx.h"
#include <D3DX9Math.h>

#define	vAr_SAFE_READ( type, value )	\
	if( m_lpBufCur + sizeof(type) <= m_lpBufMax )	\
	{	value	= *(type*)m_lpBufCur;	m_lpBufCur += sizeof(type);	}	\
	else	\
	{	value	= (type)0;	m_lpBufCur	= m_lpBufMax;	}	\
	return *this

class vAr
{
	enum	{ store = 0, load = 1 };
	enum	{ nGrowSize = 16384 };

public:
	vAr(u_int nBufSize = nGrowSize)
	{
		m_nMode			= store;
		m_lpBufStart	= new byte[ nBufSize ];
		m_nBufSize		= nBufSize;

		m_lpBufMax	= m_lpBufStart + m_nBufSize;
		m_lpBufCur	= m_lpBufStart;
	}

	vAr(void *lpBuf, u_int nBufSize = 0)
	{
		m_nMode			= load;
		m_lpBufStart	= (byte*)lpBuf;
		m_nBufSize		= nBufSize;

		m_lpBufMax	= m_lpBufStart + m_nBufSize;
		m_lpBufCur	= m_lpBufStart;
	}

	~vAr()
	{
		if( IsStoring() )
			delete [] m_lpBufStart;
	}

	void Read( void* lpBuf, u_int nSize )
	{
		if( nSize == 0 )
			return;

		if( m_lpBufCur + nSize <= m_lpBufMax )
		{
			memcpy( lpBuf, m_lpBufCur, nSize );
			m_lpBufCur	+= nSize;
		}
		else
		{
			memset( lpBuf, 0, nSize );
			m_lpBufCur	= m_lpBufMax;
		}
	}

	void Write( void* lpBuf, size_t nSize )
	{
		if( nSize == 0 || nSize > INT_MAX )
			return;

		CheckBuf( nSize );

		memcpy( m_lpBufCur, lpBuf, nSize );
		m_lpBufCur	+= nSize;
	}

	inline void WriteString( char* lpsz )
	{
		static Address addr = 0x006F1490;

		__asm
		{
			push	lpsz;
			mov		ecx, this;
			call	addr;
		}
	}

	char* ReadString( char* lpsz )
	{
		int nLen;
		*this >> nLen;
		Read( lpsz, nLen );
		lpsz[nLen] = '\0';
		return lpsz;
	}

	char* ReadString( char* lpsz, int nBufSize )
	{
		int nLen;
		*this >> nLen;

		int nReadable	= nBufSize - 1;
		if( nLen > nReadable || nLen < 0 )
		{
			lpsz[0] = '\0';
			m_lpBufCur	= m_lpBufMax;
			return lpsz;
		}
		else
		{
			Read( lpsz, sizeof(char) * nLen );
			lpsz[nLen] = '\0';
			return lpsz;
		}
	}


	void CheckBuf( u_int nSize )
	{
		if( m_lpBufCur + nSize > m_lpBufMax )
		{
			u_int uOffset		= m_lpBufCur - m_lpBufStart;
			u_int nExtension	= m_nBufSize * 2;


			byte* lpBuf	= new byte[ m_nBufSize + nExtension ];
			memcpy( lpBuf, m_lpBufStart, m_nBufSize );
			delete m_lpBufStart;

			m_lpBufStart	= lpBuf;

			m_nBufSize	+= nExtension;
			m_lpBufCur	= m_lpBufStart + uOffset;
			m_lpBufMax	= m_lpBufStart + m_nBufSize;
		}
	}


	void DumpPacket()
	{
		printf("\n");
		for( int i = 0; i < GetLen(); i++)
			printf( "%x ", m_lpBufStart[i]);
	}

public:
	inline int 		GetLen()						{		return  m_lpBufCur - m_lpBufStart;													}
	inline byte*	GetBuffer( int* pnBufSize )		{		*pnBufSize	= m_lpBufCur - m_lpBufStart; 	return m_lpBufStart;					}
	inline u_long	GetOffset( void )				{		assert( IsStoring() );						return( m_lpBufCur - m_lpBufStart );	}


	inline bool vAr::IsLoading()			{	return m_nMode == 0;				}
	inline bool vAr::IsStoring()			{	return m_nMode != 0;				}

	inline vAr& operator<<(int i)			{	return operator<<((long)i);			}
	inline vAr& operator<<(unsigned u)		{ 	return operator<<((long)u); 		}
	inline vAr& operator<<(short w)			{ 	return operator<<((WORD)w);			}
	inline vAr& operator<<(char ch)			{	return operator<<((byte)ch);		}

	inline vAr& operator>>(int& i)			{	return operator>>((long&)i);		}
	inline vAr& operator>>(unsigned& u)		{ 	return operator>>((long&)u);		}
	inline vAr& operator>>(short& w)		{	return operator>>((WORD&)w);		}
	inline vAr& operator>>(char& ch)		{	return operator>>((byte&)ch);		}

	inline vAr& operator>>(byte& by)		{	vAr_SAFE_READ( byte, by );			}
	inline vAr& operator>>(WORD& w)			{	vAr_SAFE_READ( WORD, w );			}
	inline vAr& operator>>(DWORD& dw)		{	vAr_SAFE_READ( DWORD, dw );			}
	inline vAr& operator>>(float& f)		{	vAr_SAFE_READ( float, f );			}
	inline vAr& operator>>(double& d)		{	vAr_SAFE_READ( double, d );			}
	inline vAr& operator>>(long& l)			{	vAr_SAFE_READ( long, l );			}

	inline vAr& operator<<(D3DXVECTOR3 v)	{	Write(	&v,		sizeof(D3DXVECTOR3) );		return *this;	}
	inline vAr& operator>>(D3DXVECTOR3& v)	{	Read(	&v,		sizeof(D3DXVECTOR3) );		return *this;	}
	inline vAr& operator<<(__int64 i)		{	Write(	&i,		sizeof(__int64)		);		return *this;	}
	inline vAr& operator>>(__int64& i)		{	Read(	&i,		sizeof(__int64)		);		return *this;	}
	inline vAr& operator<<(RECT rect)		{	Write(	&rect,	sizeof(RECT)		);		return *this;	}
	inline vAr& operator>>(RECT & rect)		{	Read(	&rect,	sizeof(RECT)		);		return *this;	}

	inline vAr& operator<<(byte by)			{	CheckBuf( sizeof(byte)		);		*(byte*)m_lpBufCur		= by;				m_lpBufCur += sizeof(byte);		return *this;	}
	inline vAr& operator<<(WORD w)			{	CheckBuf( sizeof(WORD)		);		*(WORD*)m_lpBufCur		= w; 				m_lpBufCur += sizeof(WORD);		return *this;	}
	inline vAr& operator<<(long l)			{	CheckBuf( sizeof(long)		);		*(long*)m_lpBufCur		= l; 				m_lpBufCur += sizeof(long); 	return *this;	}
	inline vAr& operator<<(DWORD dw)		{  	CheckBuf( sizeof(DWORD)		);		*(DWORD*)m_lpBufCur		= dw;				m_lpBufCur += sizeof(DWORD);	return *this;	}
	inline vAr& operator<<(float f)			{	CheckBuf( sizeof(float)		);		*(float*)m_lpBufCur		= *(float*)&f;		m_lpBufCur += sizeof(float);	return *this;	}
	inline vAr& operator<<(double d)		{	CheckBuf( sizeof(double)	);		*(double*)m_lpBufCur	= *(double*)&d;		m_lpBufCur += sizeof(double);	return *this; 	}

private:

	BOOL	m_nMode;
	u_int	m_nBufSize;
	byte*	m_lpBufCur;
	byte*	m_lpBufMax;
	byte*	m_lpBufStart;
};
