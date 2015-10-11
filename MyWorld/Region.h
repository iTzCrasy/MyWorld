#pragma once
#include "stdafx.h"


#define	MAX_REGIONELEM	256
class vRegionElemArray
{

	DWORD		m_cbRegionElem;
	REGIONELEM	m_aRegionElem[MAX_REGIONELEM];
public:
	vRegionElemArray()		
	{	
		m_cbRegionElem	= 0;	
	}


	inline DWORD GetSize( void )	{ return m_cbRegionElem;	}

	inline void AddTail( const LPREGIONELEM lpRegionElem )
	{
		assert( m_cbRegionElem < MAX_REGIONELEM );
		memcpy( &m_aRegionElem[m_cbRegionElem++], lpRegionElem, sizeof(REGIONELEM) );
	}

	inline LPREGIONELEM GetAt( int nIndex )
	{
		assert( nIndex >= 0 && nIndex < MAX_REGIONELEM );
		return &m_aRegionElem[nIndex];
	}
};