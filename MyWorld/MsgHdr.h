#pragma once
#include "stdafx.h"

#define SNAPSHOTTYPE_TEXT 2162865
#define PACKET_SNAPSHOP 0x21000B6;




const byte COMMONPLACE_ACTION	= 0x00;
const byte COMMONPLACE_ALPHA	= 0x01;
const byte COMMONPLACE_QUAKE	= 0x02;
const byte CT_WANTED_REQ_LIST   = 0x00;		// Core->Trans ����Ʈ ��û 
const byte CT_WANTED_SET		= 0x01;		// Core->Trans ����� ���� 
const byte ADD_PLAYER_ENEMY		= 0x00;		// �÷��̾� �� �߰� 
const byte DEL_PLAYER_ENEMY		= 0x01;		// �÷��̾� �� ���� 
const byte GC_WINGUILD			= 0x00;		// �̱� ��� ����
const byte GC_IN_WINDOW			= 0x01;		// ���� ��û â ���
const byte GC_IN_APP			= 0x02;		// ���� ��û
const byte GC_IN_COMPLETE		= 0x03;		// ������ ��û �Ϸ�
const byte GC_REQUEST_STATUS	= 0x04;		// ���� ��û ��Ȳ
const byte GC_SELECTPLAYER		= 0x05;		// ������ ���� ĳ���� â ���
const byte GC_SELECTWARPOS		= 0x06;		// ������ġ ������ ���
const byte GC_BESTPLAYER		= 0x07;		// BEST Player ����
const byte GC_ISREQUEST			= 0x08;		// ��û������?
const byte GC_USERSTATE			= 0x10;		// ��������
const byte GC_WARPLAYERLIST		= 0x11;		// �������� ����
const byte GC_GUILDSTATUS		= 0x20;		// �ڽ��� ��� ��Ȳ
const byte GC_GUILDPRECEDENCE	= 0x21;		// ��� ����
const byte GC_PLAYERPRECEDENCE	= 0x22;		// ���� ����
const byte GC_GCSTATE			= 0x30;		// ���� ��Ȳ	
const byte GC_NEXTTIMESTATE		= 0x31;		// ������ ���� �ð��� ���� �Ѱ��ֱ�
const byte GC_ENTERTIME			= 0x32;		// ������ ���� �ִ� �ð�
const byte GC_DIAGMESSAGE		= 0x33;		// ���̾� �α� �޼���
const byte GC_TELE				= 0x34;		// �ڷ���Ʈ
const byte GC_LOG				= 0x35;		// ���� �α�( ������ ������ ������~ )
const byte GC_LOG_REALTIME		= 0x36;		// ���� �α�( �ǽð����� ä��â�� ������~ )
const byte GC_GETPENYAGUILD		= 0x40;		// ��� ��û�ݾ� �� ����
const byte GC_GETPENYAPLAYER	= 0x41;		// ����Ʈ �÷��̾� ����
const byte GC_PLAYERPOINT		= 0x42;		// ������ �÷��̾� ����Ʈ
const byte SOMMON_FRIEND			= 0x00;		// ģ�� ��ȯ
const byte SOMMON_FRIEND_CONFIRM	= 0x01;		// ģ�� ��ȯ Ȯ��
const byte SOMMON_PARTY_CONFIRM		= 0x10;		// ��Ƽ ��ȯ
const byte LOG_SKILLPOINT_GET_QUEST	= 0x00;		// ��ų����Ʈ ��� - ����Ʈ
const byte LOG_SKILLPOINT_GET_HUNT	= 0x01;		// ��ų����Ʈ ��� - ����
const byte LOG_SKILLPOINT_USE		= 0x10;		// ��ų����Ʈ ���� - ��ų������
const byte PK_PINK					= 0x00;		// ��ũ���� ����
const byte PK_PROPENSITY			= 0x01;		// ī������ ����
const byte PK_PKVALUE				= 0x02;		// ī����ġ ����
const byte ANGEL_INFO				= 0x01;		// ���� ���� �ֱ�(����ġ, ����)
const byte TEXT_GENERAL				= 0x01;		// OnText
const byte TEXT_DIAG				= 0x02;		// OnDiagText
const byte MINIGAME_KAWIBAWIBO_RESUTLT		= 0x01;		// ���������� �����
const byte MINIGAME_REASSEMBLE_RESULT		= 0x02;		// ���� ���
const byte MINIGAME_REASSEMBLE_OPENWND		= 0x03;		// ����â ���� ī������� ������ �������...
const byte MINIGAME_ALPHABET_OPENWND		= 0x04;		// ���ĺ� â ���� ���� ���ڿ� ��ġ
const byte MINIGAME_ALPHABET_RESULT			= 0x05;		// ���ĺ� ���߱� ���
const byte MINIGAME_FIVESYSTEM_OPENWND		= 0x06;		// ���� â ���� �ּ�, �ִ�, ���
const byte MINIGAME_FIVESYSTEM_RESULT		= 0x07;		// ���� ���
const byte ULTIMATE_MAKEITEM				= 0x01;		// ������ ����Į�� ����
const byte ULTIMATE_TRANSWEAPON				= 0x02;		// ���� ��ȯ(�Ϲ�->����ũ, ����ũ->���͸�)
const byte ULTIMATE_MAKEGEM					= 0x03;		// ���� ����(������ �ɰ���)
const byte ULTIMATE_SETGEM					= 0x04;		// ���� �ռ�
const byte ULTIMATE_REMOVEGEM				= 0x05;		// ���� ����
const byte ULTIMATE_ENCHANTWEAPON			= 0x06;		// ���͸� ���� ����
const byte EXCHANGE_RESULT					= 0x01;		// ��ȯ ��ũ��Ʈ ���
const byte LEGENDSKILL_RESULT					= 0x01;		// legend ��ų ���
const byte GI_LOG_VIEW_ITEM_ADD					= 0x01;		// ���â�� �������߰� �α�
const byte GI_LOG_VIEW_ITEM_REMOVE					= 0x02;		// ���â�� ���������� �α�
const byte GI_LOG_VIEW_MONEY_ADD					= 0x03;		// ���â�� ���߰� �α�
const byte GI_LOG_VIEW_MONEY_REMOVE					= 0x04;		// ���â�� ���߰� �α�
const byte SECRETROOM_GUILDLIST		= 0x01;
const byte SECRETROOM_KILLCOUNT		= 0x02;
const byte SECRETROOM_WARSTATE		= 0x03;