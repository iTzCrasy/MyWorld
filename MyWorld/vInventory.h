#pragma once
class vInventory
{
public:
	DWORD		GetAtItemId(DWORD dwItem);
	bool		IsEquip( DWORD dwObjId );
	vItemElem*	GetAtId( DWORD dwId );

	GET_ACCESSOR( DWORD,		Max,		0x10	);
	GET_ACCESSOR( vItemElem*,	IndexNum,	0x8		);
	GET_ACCESSOR( vItemElem*,	pItem,		0x4		);
};

